#include "rfm22driver.h"
#include "rfm22ports.h"
#include "rfm22bands.h"
#include "rfm22_registers.h"
#include "rfm22callbacks.h"
#include "rfm22frame.h"
//#include "actuator.h"

#define RFM22DRIVER_RSSI_THRESHOLD                               65

//KOMUNIKACJA PRZEZ SPI
#define RFM22_WRITE_FLAG                     0x80U
#define RFM22_READ_FLAG                      0x00U


//funkcje prywatne
void rfm22driver_module_setup();
uint8_t rfm22driver_crc_ibutton_update(uint8_t crc, uint8_t byte);
void rfm22driver_reset_on();
void rfm22driver_reset_off();
void rfm22driver_tune_mode();

//do drivera wtp3
void rfm22driver_clear_fifo();

uint8_t rfm22driver_trans_read(uint8_t address)
{
    return rfm22ports_trans(RFM22_READ_FLAG | address, 0);
}

void rfm22driver_trans_write(uint8_t address, uint8_t value)
{
    rfm22ports_trans(RFM22_WRITE_FLAG | (address), value);
}

void rfm22driver_burst_read(uint8_t address, uint8_t length, uint8_t *values)
{
    rfm22ports_burst(RFM22_READ_FLAG | (address), length, values);
}

void rfm22driver_burst_write(uint8_t address, uint8_t length, uint8_t *values)
{
    rfm22ports_burst(RFM22_WRITE_FLAG | (address), length, values);
}

//setup spi i modulu rfm22
void rfm22driver_init(uint8_t long_delay)
{
    //uC setup
    rfm22ports_initVccPort();
    rfm22ports_initSDNPort();
    rfm22ports_initIntPort();
    //rfm22ports_activateInt();

    //rfm22 reset
    rfm22driver_reset_on();
    rfm22callbacks_delay_ms(32);

    //uC setup
    rfm22ports_initSPI();
    rfm22ports_activateInt();

    //rfm22 init
    //POR 16ms
    rfm22driver_reset_off();
    rfm22callbacks_delay_ms(32);
    rfm22driver_module_setup();

    //frequency & channel init
    rfm22bands_init();
}

void rfm22driver_reset_on()
{
    switch(rfm22ports_getResetMethod())
    {
        case RFM22PORTS_RESET_VCC:
            rfm22ports_setSDN(0);
            rfm22ports_deinitSPI();
            rfm22ports_setVcc(1);
            break;
        case RFM22PORTS_RESET_SDN:
            rfm22ports_setVcc(0);
            rfm22ports_setSDN(1);
            break;
        case RFM22PORTS_RESET_SOFT:
            rfm22ports_setVcc(0);
            rfm22ports_setSDN(0);
            break;
    }
}

void rfm22driver_reset_off()
{
    switch(rfm22ports_getResetMethod())
    {
        case RFM22PORTS_RESET_VCC:
            rfm22ports_setVcc(0);
            break;
        case RFM22PORTS_RESET_SDN:
            rfm22ports_setSDN(0);
            break;
        case RFM22PORTS_RESET_SOFT:
            break;
    }
}

void rfm22driver_module_setup()
{
    rfm22driver_trans_write(RFM22_ADDR_OPERATING_1, 0b10000000);
    rfm22callbacks_delay_ms(3);

    //standby
    rfm22driver_trans_write(RFM22_ADDR_OPERATING_1, 0x00);

    rfm22driver_trans_read(RFM22_ADDR_INTERRUPT_STATUS_1);
    rfm22driver_trans_read(RFM22_ADDR_INTERRUPT_STATUS_2);

    //interrupt enable
    rfm22driver_trans_write(RFM22_ADDR_INTERRUPT_ENABLE_1, 0);
    rfm22driver_trans_write(RFM22_ADDR_INTERRUPT_ENABLE_2, 0);

    //gpio
    rfm22driver_trans_write(RFM22_ADDR_GPIO_0_CONFIG, 0b11110010);
    rfm22driver_trans_write(RFM22_ADDR_GPIO_1_CONFIG, 0b11110101);
    rfm22driver_trans_write(RFM22_ADDR_GPIO_2_CONFIG, 0b00100011);

    //frequency
    //rfm22driver_trans_write(RFM22_ADDR_FREQUENCY_BAND_SELECT, 0b01010011);  /*5 bit - High Band Select*/
    /*19776 = 0x4D40*/
    //rfm22driver_trans_write(RFM22_ADDR_NOMINAL_CARRIER_FREQ_1, 0x4D);
    //rfm22driver_trans_write(RFM22_ADDR_NOMINAL_CARRIER_FREQ_0, 0x40);
    //rfm22driver_trans_write(RFM22_ADDR_FREQ_HOPPING_CH_SELECT, 0x00);
    //rfm22driver_trans_write(RFM22_ADDR_FREQ_HOPPING_STEP_SIZE, 8);

    //rfm22driver_trans_write(RFM22_ADDR_FREQUENCY_BAND_SELECT, 0x73);  /*5 bit - High Band Select*/
    //rfm22driver_trans_write(RFM22_ADDR_NOMINAL_CARRIER_FREQ_1, 0x70);
    //rfm22driver_trans_write(RFM22_ADDR_NOMINAL_CARRIER_FREQ_0, 0x80);
    //0x7573,
    //0x7670,
    //0x7780,

    //data rate - 2.4kbps
    //rfm22driver_trans_write(RFM22_ADDR_TX_DATARATE1, 0x13);
    //rfm22driver_trans_write(RFM22_ADDR_TX_DATARATE0, 0xA9);

    //rx data rate - 2.4kbps
    //rfm22driver_trans_write(RFM22_ADDR_IF_FILTER_BANDWIDTH, 0x1D);
    //rfm22driver_trans_write(RFM22_ADDR_AFC_LOOP_GEARSHIFT_OVERR, 0x40);
    //rfm22driver_trans_write(RFM22_ADDR_CLOCK_RECOV_OVERSAM_RATIO, 0x41);
    //rfm22driver_trans_write(RFM22_ADDR_CLOCK_RECOV_OFFSET_2, 0x60);
    //rfm22driver_trans_write(RFM22_ADDR_CLOCK_RECOV_OFFSET_1, 0x27);
    //rfm22driver_trans_write(RFM22_ADDR_CLOCK_RECOV_OFFSET_0, 0x52);
    //rfm22driver_trans_write(RFM22_ADDR_CLOCK_RECOV_TIMING_LOOP_1, 0x00);
    //rfm22driver_trans_write(RFM22_ADDR_CLOCK_RECOV_TIMING_LOOP_0, 0x06);
    //rfm22driver_trans_write(RFM22_ADDR_AFC_LIMITER, 0x1E);

    //packet format
    //rfm22driver_trans_write(RFM22_ADDR_MODULATION_MODE_CONTROL_1, 0x20);
    rfm22driver_trans_write(RFM22_ADDR_DATA_ACCESS_CONTROL, 0x00);
    rfm22driver_trans_write(RFM22_ADDR_HEADER_CONTROL_1, 0x00);
    rfm22driver_trans_write(RFM22_ADDR_HEADER_CONTROL_2, 0x02);
    rfm22driver_trans_write(RFM22_ADDR_PREAMBLE_LENGTH, 0x0A);
    rfm22driver_trans_write(RFM22_ADDR_SYNC_WORD_3, 0x89);
    rfm22driver_trans_write(RFM22_ADDR_SYNC_WORD_2, 0x6B);
    rfm22driver_trans_write(RFM22_ADDR_TRANSMIT_PACKET_LENGTH, 0xFF);

    //tx settings
    //rfm22driver_trans_write(RFM22_ADDR_TX_POWER, (RFM22_TX_POWER_LNA_SW | RFM22_TX_POWER_14_DBM));
    //rfm22driver_trans_write(RFM22_ADDR_FREQUENCY_DEVIATION, 0x38);
    //rfm22driver_trans_write(RFM22_ADDR_MODULATION_MODE_CONTROL_2, 0x23);

    //rssi
    rfm22driver_trans_write(RFM22_ADDR_RSSI_THRESHOLD, RFM22DRIVER_RSSI_THRESHOLD);

    //almost-empty, almost-full thresholds
    rfm22driver_trans_write(RFM22_ADDR_TX_FIFO_CONTROL_2, RFM22FRAME_TX_ALMOST_EMPTY_THRESHOLD);
    rfm22driver_trans_write(RFM22_ADDR_RX_FIFO_CONTROL, RFM22FRAME_RX_ALMOST_FULL_THRESHOLD);

    //standby
    //rfm22driver_trans_write(RFM22_ADDR_OPERATING_1, 0x00);
}

void rfm22driver_tune_mode()
{
    rfm22driver_trans_write(RFM22_ADDR_OPERATING_1, 0b00000011);
}

#if 0
void rfm22driver_update()
{
    uint8_t pakiet[5];
    uint8_t correctPacket;
    //uint8_t signalDetected;
    uint8_t rxAnswer, rxTimeout;

    if (rfm22driver_init_needed)
    {
        rfm22driver_init();
    }

    switch(rfm22driver_stan)
    {
        case RFM22DRIVER_IDLE:
            if (rfm22driver_pending_send_channel)
            {
                rfm22bands_set_user_channel(rfm22driver_pending_channel);
                rfm22driver_pending_send_channel = 0;
            }
            else if (rfm22ports_isIdleTimerZero())
            {
                rfm22driver_sending_needed = 1;
            }
            if (rfm22driver_sending_needed && !actuator.isCalibration())
            {
                if (rfm22driver_pending_send_channel)
                {
                	rfm22bands_set_choose_channel();
                    //zrobic przygotowanie wyslania numeru kanalu
                    //rfm22driver_prepare_packet(&pakiet[0], 8, rfm22driver_eep_channel);
                    rfm22driver_prepare_packet(&pakiet[0], (0b001001 << 8) | rfm22driver_pending_channel);
                }
                else
                {
                    //zrobic przygotowanie wyslania stanu dogrzania
                    //rfm22driver_prepare_packet(&pakiet[0], 4, menu_get_dane_pokojowki()->dogrzane != 0);
                    rfm22driver_prepare_packet(&pakiet[0], (0b001010 << 8) | (uint8_t)(actuator.getPercentPos()));
                }
                rfm22driver_clear_fifo();
                rfm22driver_burst_write(RFM22_ADDR_FIFO_ACCESS, 5, &pakiet[0]);
                rfm22driver_trans_write(RFM22_ADDR_INTERRUPT_ENABLE_1, 0x04);                           /* ustawia enpksent */
                rfm22driver_trans_write(RFM22_ADDR_OPERATING_1, 0x08);                                  //ustawia txon
                rfm22driver_stan = RFM22DRIVER_TRANSMITER;
                //rfm22driver_poprzedni_wyslany_stan - trzeba ustawic przy przygotowaniu pakietu
                rfm22ports_activateInt();
            }
            break;

        case RFM22DRIVER_TRANSMITER:                                                                  /* obsluga tego przypadku do przerwania*/
            break;

        case RFM22DRIVER_RECEIVER:
            //if (!(rfm22driver_trans_read(RFM22_ADDR_OPERATING_1) & (1 << 2)))                        /*odbior pakietu zakonczony*/
            rxAnswer = rfm22ports_isINTActive();
            rxTimeout = rfm22ports_isTimeoutTimerZero();

            //wylaczenie przerwania i odbiornika
            if (rxAnswer || rxTimeout)
            {
                rfm22driver_trans_write(RFM22_ADDR_INTERRUPT_ENABLE_1, 0);
                rfm22driver_trans_write(RFM22_ADDR_OPERATING_1, 0);
            }

            if (rxAnswer)
            {
                rfm22driver_burst_read(RFM22_ADDR_FIFO_ACCESS, 5, &pakiet[0]);
                correctPacket = rfm22driver_checkPakiet(&pakiet[0]);
                if (!correctPacket)
                {
                    if (rfm22driver_debug_2 % 10 == 9)
                    {
                        rfm22driver_debug_2 -= 9;
                    }
                    else
                    {
                        rfm22driver_debug_2++;
                    }
                    //menu_get_dane_pokojowki()->minute = (menu_get_dane_pokojowki()->minute / 10) + rfm22driver_get_losowy_czas();
                    if (rfm22driver_check_unwanted_reset())
                    {
                        //menu_get_dane_pokojowki()->minute = (menu_get_dane_pokojowki()->minute + 10) % 100;
                    }
                }
            }

            if (rxAnswer || rxTimeout)
            {
                if (rfm22driver_pending_send_channel)
                {
                    //kanal zmieniony przed przejsciem w rx
                    rfm22driver_pending_send_channel = 0;
                    //kontynuacja czasu w COUNTER_IDLE_RFM
                }
                else
                {
                    rfm22ports_setIdleTimer(RFM22DRIVER_IDLE_DURATION);
                }
                rfm22driver_sending_needed = 0;
                rfm22driver_stan = RFM22DRIVER_IDLE;
            }

            if (rxTimeout)
            {
                rfm22driver_debug_1 = (rfm22driver_debug_1 + 1) % 100;                                  /* timeout zamiast odpowiedzi od st268*/
                //menu_get_dane_pokojowki()->minute = (menu_get_dane_pokojowki()->minute / 10) + rfm22driver_get_losowy_czas();
                if (rfm22driver_check_unwanted_reset())
                {
                    //menu_get_dane_pokojowki()->minute = (menu_get_dane_pokojowki()->minute + 10) % 100;
                }
            }
            break;
    }
}
#endif

void rfm22driver_clear_fifo()
{
    rfm22driver_trans_write(RFM22_ADDR_OPERATING_2, RFM22DRIVER_OP2_RX_FIFO_CLEAR | RFM22DRIVER_OP2_TX_FIFO_CLEAR);
    rfm22driver_trans_write(RFM22_ADDR_OPERATING_2, 0x00);
}

void rfm22driver_interrupt_enable(uint8_t enable1, uint8_t enable2)
{
    rfm22driver_trans_write(RFM22_ADDR_INTERRUPT_ENABLE_1, enable1);
    rfm22driver_trans_write(RFM22_ADDR_INTERRUPT_ENABLE_2, enable2);
}

uint8_t rfm22driver_compute_package_crc(uint8_t package[], uint8_t length)
{
    const uint8_t IBUTTON_INITIAL_VAL = 0;
    uint8_t crc = IBUTTON_INITIAL_VAL;
    uint8_t i;

    for (i = 0; i < length; i++)
    {
        crc = rfm22driver_crc_ibutton_update(crc, package[i]);
    }

    return crc;
}

uint8_t rfm22driver_crc_ibutton_update(uint8_t crc, uint8_t byte)
{
    uint8_t i;

    crc = crc ^ byte;
    for (i = 0; i < 8; i++)
    {
        if (crc & 0x01)
            crc = (crc >> 1) ^ 0x8C;
        else
            crc >>= 1;
    }

    return crc;
}

#if 0
void rfm22driver_isr()
{
    if (rfm22driver_stan == RFM22DRIVER_TRANSMITER)
    {
        rfm22ports_deactivateInt();
        rfm22driver_trans_write(RFM22_ADDR_INTERRUPT_ENABLE_1, 0);
        rfm22driver_clear_fifo();                                                                  /* usuniecie ew. danych z nasluchu */
        if (rfm22driver_pending_send_channel)
        {
            rfm22bands_set_user_channel(rfm22driver_pending_channel);
        }
        rfm22driver_trans_write(RFM22_ADDR_INTERRUPT_ENABLE_1, 1 << 1);                             /* ustawia enpkvalid */
        rfm22driver_trans_write(RFM22_ADDR_OPERATING_1, 1 << 2);                                    //ustawia rxon
        rfm22ports_setTimeoutTimer(50);                                                            //ok. 50 ms
        rfm22driver_stan = RFM22DRIVER_RECEIVER;
    }
}
#endif

