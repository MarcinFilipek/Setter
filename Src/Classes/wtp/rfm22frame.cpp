#include "rfm22frame.h"
#include "prot3buff.h"
#include "rfm22driver.h"
#include "rfm22_registers.h"
#include "wtp3drivercalls.h"


//activateInt i deactivateInt?

#define dim(x) (sizeof(x)/sizeof((x)[0]))
#define BLOW_OUT_TIMEOUT     100

#define BUFF_LEN                   170
#define PREAMBLE_LEN_DEFAULT       5
#define FIFO_TX_MAX_LOAD           62
#define TX_SCRAMBLER_START_INDEX   1        //first data byte (index 0) not scrambled

static prot3buff_t rfm22frame_tx_buff;
static uint8_t     rfm22frame_tx_buff_array[BUFF_LEN];

static prot3buff_t rfm22frame_rx_buff;
static uint8_t     rfm22frame_rx_buff_array[BUFF_LEN];

static uint16_t     rfm22frame_preamble_len;

static rfm22frame_state_t rfm22frame_state;

//tx state flags
static uint8_t rfm22frame_tx_last_interrupt;

//tx error flags
static uint8_t rfm22frame_tx_err_underflow;
static uint8_t rfm22frame_tx_err_no_almost_empty;
static uint8_t rfm22frame_tx_err_channel_occupied;

//rx config data
static uint16_t (*rfm22frame_rx_package_size_getter)();
static uint16_t rfm22frame_rx_package_size_threshold;

//rx state data
static uint16_t rfm22frame_rx_package_size;

//rx error flags
static uint8_t rfm22frame_rx_err_no_sync;
static uint8_t rfm22frame_rx_err_overflow;
static uint8_t rfm22frame_rx_err_no_almost_full;

//rx callback error flag
static uint8_t rfm22frame_rx_callback_err_size;

//general error flag
static uint8_t rfm22frame_general_err_blowout;

//signal strength
/*static*/ uint8_t rfm22frame_signal_strength;

//private functions
void rfm22frame_put_starting_bytes(uint8_t preamble_len);
void rfm22frame_put_tx_bytes(uint8_t bytes_in_fifo);
void rfm22frame_get_rx_bytes(uint8_t bytes_in_fifo);

void rfm22frame_isr_tx();
void rfm22frame_isr_rx();

void rfm22frame_init(uint8_t long_delay, uint16_t (*package_size_getter)(), uint16_t package_size_threshold)
{
    rfm22frame_state = FRS_IDLE;

    rfm22driver_init(long_delay);    //uC interrupt activated in rfm22driver_init()?

    prot3buff_init(&rfm22frame_tx_buff, rfm22frame_tx_buff_array, dim(rfm22frame_tx_buff_array));
    prot3buff_init(&rfm22frame_rx_buff, rfm22frame_rx_buff_array, dim(rfm22frame_rx_buff_array));
    rfm22frame_preamble_len = PREAMBLE_LEN_DEFAULT;
    //error flags to be cleared?

    rfm22frame_rx_package_size_getter = package_size_getter;
    rfm22frame_rx_package_size_threshold = package_size_threshold;

    rfm22frame_clear_error_flags();
    rfm22frame_signal_strength = 0;
}

prot3buff_t *rfm22frame_get_tx_buff()
{
    return &rfm22frame_tx_buff;
}

prot3buff_t *rfm22frame_get_rx_buff()
{
    return &rfm22frame_rx_buff;
}

rfm22frame_state_t rfm22frame_get_state()
{
    return rfm22frame_state;
}

uint8_t rfm22frame_is_tx_error()
{
    return rfm22frame_tx_err_channel_occupied || rfm22frame_tx_err_no_almost_empty || rfm22frame_tx_err_underflow;
}

uint8_t rfm22frame_is_rx_error()
{
    return rfm22frame_rx_err_no_almost_full || rfm22frame_rx_err_no_sync || rfm22frame_rx_err_overflow;
}

uint8_t rfm22frame_is_rx_callback_error()
{
    return rfm22frame_rx_callback_err_size;
}

uint8_t rfm22frame_is_general_error()
{
    return rfm22frame_general_err_blowout;
}

void rfm22frame_clear_error_flags()
{
    rfm22frame_clear_tx_error_flags();
    rfm22frame_clear_rx_error_flags();
    rfm22frame_clear_rx_callback_error_flags();
    rfm22frame_clear_general_error_flags();
}

void rfm22frame_clear_tx_error_flags()
{
    rfm22frame_tx_err_underflow = 0;
    rfm22frame_tx_err_no_almost_empty = 0;
    rfm22frame_tx_err_channel_occupied = 0;
}

void rfm22frame_clear_rx_error_flags()
{
    rfm22frame_rx_err_no_sync = 0;
    rfm22frame_rx_err_overflow = 0;
    rfm22frame_rx_err_no_almost_full = 0;
}

void rfm22frame_clear_rx_callback_error_flags()
{
    rfm22frame_rx_callback_err_size = 0;
}

void rfm22frame_clear_general_error_flags()
{
    rfm22frame_general_err_blowout = 0;
}

uint8_t rfm22frame_get_signal_strength()
{
    return rfm22frame_signal_strength;
}

void rfm22frame_start_tx()
{
    uint8_t put_bytes = 0;
    uint8_t en1;

    if((rfm22frame_state == FRS_IDLE) && (prot3buff_getReaderPos(&rfm22frame_tx_buff) == 0))
    {
        rfm22frame_clear_general_error_flags();
        rfm22frame_clear_tx_error_flags();
        //rfm22driver_clear_fifo();
        rfm22frame_put_starting_bytes(PREAMBLE_LEN_DEFAULT);
        put_bytes = PREAMBLE_LEN_DEFAULT + 2;
        rfm22frame_put_tx_bytes(put_bytes);
        if(prot3buff_getBytesAvail(&rfm22frame_tx_buff) > 0)
        {
            en1 = RFM22DRIVER_IN1_TX_FIFO_AL_EMPTY | RFM22DRIVER_IN1_PACKET_SENT;
            rfm22frame_tx_last_interrupt = 0;
        }
        else
        {
            en1 = RFM22DRIVER_IN1_PACKET_SENT;
            rfm22frame_tx_last_interrupt = 1;
        }
        rfm22driver_interrupt_enable(en1, 0);
        rfm22driver_trans_write(RFM22_ADDR_OPERATING_1, RFM22DRIVER_OP1_TX_ON);
        rfm22frame_state = FRS_TX;
        wtp3drivercalls_setTimer(1, BLOW_OUT_TIMEOUT);
        //uC interrupt already on?
    }
}

void rfm22frame_start_rx_waiting(uint8_t low_duty_cycle_mode)
{
    //low_duty_cycle_mode not configured yet

    uint8_t op1, op2;

    if((rfm22frame_state == FRS_IDLE) && (prot3buff_getWriterPos(&rfm22frame_rx_buff) == 0))
    {
        rfm22frame_clear_general_error_flags();
        rfm22frame_clear_rx_error_flags();
        rfm22frame_clear_rx_callback_error_flags();
        //rfm22driver_clear_fifo();
        rfm22frame_rx_package_size = 0;
        rfm22frame_signal_strength = 0;
        rfm22driver_interrupt_enable(RFM22DRIVER_IN1_FIFO_FLOW | RFM22DRIVER_IN1_RX_FIFO_AL_FULL, RFM22DRIVER_IN2_SYNC_WORD_DET);
        if(low_duty_cycle_mode)
        {
            op1 = 0;
            op2 = RFM22DRIVER_OP2_LOW_DUTY_MODE;
        }
        else
        {
            op1 = RFM22DRIVER_OP1_RX_ON;
            op2 = 0;
        }
        rfm22driver_trans_write(RFM22_ADDR_OPERATING_1, op1);
        rfm22driver_trans_write(RFM22_ADDR_OPERATING_2, op2);
        rfm22frame_state = FRS_RX_WAIT;
    }
}

void rfm22frame_stop_rx_waiting()
{
    if(rfm22frame_state == FRS_RX_WAIT)
    {
        //hazardous switch to FRS_RX possible here
        rfm22frame_state = FRS_IDLE;
        //hazardous isr possible with FRS_IDLE state
        //low duty mode can trigger rx, its turned off first
        rfm22driver_trans_write(RFM22_ADDR_OPERATING_2, 0);
        rfm22driver_trans_write(RFM22_ADDR_OPERATING_1, 0);
        rfm22driver_interrupt_enable(0, 0);
        rfm22driver_clear_fifo();
    }
}

void rfm22frame_update()
{
    //blowout error detection
    switch(rfm22frame_state)
    {
        case FRS_IDLE:
        case FRS_RX_WAIT:
        {
        }
        break;

        case FRS_TX:
        {
            if(wtp3drivercalls_isTimerZero(1))
            {
                //hazardous switch to FRS_IDLE possible here
                rfm22frame_state = FRS_IDLE;
                //hazardous isr possible with FRS_IDLE state
                rfm22driver_trans_write(RFM22_ADDR_OPERATING_1, 0);
                rfm22driver_interrupt_enable(0, 0);
                rfm22driver_clear_fifo();
                rfm22frame_tx_last_interrupt = 0;
                rfm22frame_general_err_blowout = 1;
            }
        }
        break;

        case FRS_RX:
        {
            if(wtp3drivercalls_isTimerZero(1))
            {
                //hazardous switch to FRS_IDLE possible here
                rfm22frame_state = FRS_IDLE;
                //hazardous isr possible with FRS_IDLE state
                //low duty mode can trigger rx, its turned off first
                rfm22driver_trans_write(RFM22_ADDR_OPERATING_2, 0);
                rfm22driver_trans_write(RFM22_ADDR_OPERATING_1, 0);
                rfm22driver_interrupt_enable(0, 0);
                rfm22driver_clear_fifo();
                rfm22frame_general_err_blowout = 1;
            }
        }
        break;
    }
}

void rfm22frame_isr()
{
    switch(rfm22frame_state)
    {
        case FRS_IDLE:
        {

        }
        break;

        case FRS_TX:
        {
            rfm22frame_isr_tx();
        }
        break;

        case FRS_RX_WAIT:
        {
            rfm22frame_isr_rx();
        }
        break;

        case FRS_RX:
        {
            rfm22frame_isr_rx();
        }
        break;
    }
}

void rfm22frame_isr_tx()
{
    uint8_t put_bytes;
    uint8_t en1;
    uint8_t status1;

    if(rfm22frame_tx_last_interrupt)
    {
        rfm22driver_trans_write(RFM22_ADDR_OPERATING_1, 0);
        rfm22driver_interrupt_enable(0, 0);                           //clears int pin
        rfm22driver_clear_fifo();
        rfm22frame_tx_last_interrupt = 0;
        rfm22frame_state = FRS_IDLE;
    }
    else
    {
        put_bytes = RFM22FRAME_TX_ALMOST_EMPTY_THRESHOLD;
        rfm22frame_put_tx_bytes(put_bytes);

        //statuses of interrupts still is status1 register
        status1 = rfm22driver_trans_read(RFM22_ADDR_INTERRUPT_STATUS_1);
        if(status1 & RFM22DRIVER_IN1_PACKET_SENT)
        {
            rfm22frame_tx_err_underflow = 1;
        }
        else if(!(status1 & RFM22DRIVER_IN1_TX_FIFO_AL_EMPTY))
        {
            rfm22frame_tx_err_no_almost_empty = 1;
        }

        if(rfm22frame_tx_err_underflow || rfm22frame_tx_err_no_almost_empty)
        {
            rfm22driver_trans_write(RFM22_ADDR_OPERATING_1, 0);
            rfm22driver_interrupt_enable(0, 0);                           //clears int pin
            rfm22driver_clear_fifo();
            rfm22frame_tx_last_interrupt = 0;
            rfm22frame_state = FRS_IDLE;                                  //accidentally triggered interrupt allowed
        }
        else
        {
            if(prot3buff_getBytesAvail(&rfm22frame_tx_buff) > 0)
            {
                //still en1 is (RFM22DRIVER_IN1_TX_FIFO_AL_EMPTY | RFM22DRIVER_IN1_PACKET_SENT)
                //still rfm22frame_tx_last_interrupt is 0
            }
            else
            {
                rfm22frame_tx_last_interrupt = 1;
                en1 = RFM22DRIVER_IN1_PACKET_SENT;
                rfm22driver_interrupt_enable(en1, 0);
            }

            //still RFM22_ADDR_OPERATING_1 is RFM22DRIVER_OP1_TX_ON
            //still rfm22frame_state is FRS_TX
        }
    }
}

void rfm22frame_isr_rx()
{
    uint8_t first_interrupt = (rfm22frame_state == FRS_RX_WAIT);
    uint8_t status1, status2;
    uint8_t avail_bytes;

    if(first_interrupt)
    {
        status2 = rfm22driver_trans_read(RFM22_ADDR_INTERRUPT_STATUS_2);
        if(!(status2 & RFM22DRIVER_IN2_SYNC_WORD_DET))
        {
            rfm22frame_rx_err_no_sync = 1;
        }
        else
        {
            status1 = rfm22driver_trans_read(RFM22_ADDR_INTERRUPT_STATUS_1);
            if((status1 & RFM22DRIVER_IN1_FIFO_FLOW) || (status1 & RFM22DRIVER_IN1_RX_FIFO_AL_FULL))
            {
                rfm22frame_rx_err_overflow = 1;
            }
        }

        if(rfm22frame_rx_err_no_sync || rfm22frame_rx_err_overflow)
        {
            //low duty mode can trigger rx, its turned off first
            rfm22driver_trans_write(RFM22_ADDR_OPERATING_2, 0);
            rfm22driver_trans_write(RFM22_ADDR_OPERATING_1, 0);
            rfm22driver_interrupt_enable(0, 0);                           //clears int pin
            rfm22driver_clear_fifo();
            rfm22frame_signal_strength = 0;
            rfm22frame_state = FRS_IDLE;                                  //accidentally triggered interrupt allowed
        }
        else
        {
            //overflow and rx_al_full interrupts
            rfm22frame_signal_strength = rfm22driver_trans_read(RFM22_ADDR_RSSI);
            rfm22driver_interrupt_enable(RFM22DRIVER_IN1_FIFO_FLOW | RFM22DRIVER_IN1_RX_FIFO_AL_FULL, 0);
            rfm22frame_state = FRS_RX;
            wtp3drivercalls_setTimer(1, BLOW_OUT_TIMEOUT);
        }
    }
    else
    {
        uint8_t rx_error;

        avail_bytes = RFM22FRAME_RX_ALMOST_FULL_THRESHOLD;
        rfm22frame_get_rx_bytes(avail_bytes);
        if(rfm22frame_rx_package_size == 0)
        {
            if(prot3buff_getWriterPos(&rfm22frame_rx_buff) >= rfm22frame_rx_package_size_threshold)
            {
                //0 -> not checked yet
                //0xFFFF -> incorrect data in the beginning of package
                rfm22frame_rx_package_size = rfm22frame_rx_package_size_getter();
                if(rfm22frame_rx_package_size != 0xFFFF)
                {
                    if(prot3buff_getWriterPos(&rfm22frame_rx_buff) > rfm22frame_rx_package_size)
                    {
                        prot3buff_setWriterToPos(&rfm22frame_rx_buff, rfm22frame_rx_package_size);
                    }
                }
            }
        }

        //statuses of interrupts still is status1 register
        status1 = rfm22driver_trans_read(RFM22_ADDR_INTERRUPT_STATUS_1);
        if(status1 & RFM22DRIVER_IN1_FIFO_FLOW)
        {
            rfm22frame_rx_err_overflow = 1;
        }
        else if(!(status1 & RFM22DRIVER_IN1_RX_FIFO_AL_FULL))
        {
            rfm22frame_rx_err_no_almost_full = 1;
        }
        else if(rfm22frame_rx_package_size == 0xFFFF)
        {
            rfm22frame_rx_callback_err_size = 1;
        }
        else if(rfm22frame_rx_package_size > BUFF_LEN)
        {
            rfm22frame_rx_callback_err_size = 1;
        }

        rx_error = (rfm22frame_rx_err_overflow || rfm22frame_rx_err_no_almost_full || rfm22frame_rx_callback_err_size);
        if(rx_error)
        {
            rfm22frame_signal_strength = 0;
        }
        if(rx_error || ((rfm22frame_rx_package_size > 0) && (prot3buff_getWriterPos(&rfm22frame_rx_buff) >= rfm22frame_rx_package_size))
                || (prot3buff_getCapacityAvail(&rfm22frame_rx_buff) == 0))
        {
            //low duty mode can trigger rx, its turned off first
            rfm22driver_trans_write(RFM22_ADDR_OPERATING_2, 0);
            rfm22driver_trans_write(RFM22_ADDR_OPERATING_1, 0);
            rfm22driver_interrupt_enable(0, 0);                           //clears int pin
            rfm22driver_clear_fifo();
            rfm22frame_state = FRS_IDLE;                                  //accidentally triggered interrupt allowed
        }
        else
        {
            //still en1 == (RFM22DRIVER_IN1_FIFO_FLOW | RFM22DRIVER_IN1_RX_FIFO_AL_FULL) and en2 == 0
            //still rfm22frame_state == FRS_RX
        }
    }

}

void rfm22frame_put_starting_bytes(uint8_t preamble_len)
{
    uint8_t arr[10];
    uint8_t portion;
    uint8_t i;

    while(preamble_len > 0)
    {
        for(i = 0; i < 10; i++)
        {
            arr[i] = 0xAA;
        }
        portion = (preamble_len >= 10) ? 10 : preamble_len;
        rfm22driver_burst_write(RFM22_ADDR_FIFO_ACCESS, portion, arr);
        preamble_len -= portion;
    }
    arr[0] = 0x89;
    arr[1] = 0x6B;    //prawidlowe
    //arr[1] = 0x6C;      //bledne
    rfm22driver_burst_write(RFM22_ADDR_FIFO_ACCESS, 2, arr);
}

void rfm22frame_put_tx_bytes(uint8_t bytes_in_fifo)
{
    uint8_t arr[10];
    uint8_t portion;
    uint8_t fifo_free_spots = (bytes_in_fifo < FIFO_TX_MAX_LOAD) ? (FIFO_TX_MAX_LOAD - bytes_in_fifo) : 0;
    uint8_t bytes_to_put = (fifo_free_spots < prot3buff_getBytesAvail(&rfm22frame_tx_buff)) ?
            fifo_free_spots : prot3buff_getBytesAvail(&rfm22frame_tx_buff);

    while(bytes_to_put > 0)
    {
        portion = (bytes_to_put > 10) ? 10 : bytes_to_put;
        prot3buff_readBytes(&rfm22frame_tx_buff, arr, portion);
        rfm22driver_burst_write(RFM22_ADDR_FIFO_ACCESS, portion, arr);
        bytes_to_put -= portion;
    }
}

void rfm22frame_get_rx_bytes(uint8_t bytes_in_fifo)
{
    uint8_t arr[10];
    uint8_t portion;
    uint16_t buffer_free_spots = prot3buff_getCapacityAvail(&rfm22frame_rx_buff);
    uint16_t remaining_package_bytes;
    uint8_t bytes_to_put;

    if(rfm22frame_rx_package_size > 0)
    {
        if(rfm22frame_rx_package_size >= prot3buff_getWriterPos(&rfm22frame_rx_buff))
        {
            remaining_package_bytes = rfm22frame_rx_package_size - prot3buff_getWriterPos(&rfm22frame_rx_buff);
        }
        else
        {
            remaining_package_bytes = 0;
        }
    }
    else
    {
        remaining_package_bytes = 0xFFFF;
    }

    //portion := temporary var for min(bytes_in_fifo, buffer_free_spots)
    portion = (bytes_in_fifo < buffer_free_spots) ? bytes_in_fifo : buffer_free_spots;
    bytes_to_put = (portion < remaining_package_bytes) ? portion : remaining_package_bytes;

    while(bytes_to_put > 0)
    {
        portion = (bytes_to_put > 10) ? 10 : bytes_to_put;
        rfm22driver_burst_read(RFM22_ADDR_FIFO_ACCESS, portion, arr);
        prot3buff_putBytes(&rfm22frame_rx_buff, arr, portion);
        bytes_to_put -= portion;
    }
}

