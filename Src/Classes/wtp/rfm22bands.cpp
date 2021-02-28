/*
 * rfm22bands.cpp
 *
 *  Created on: 31 paź 2013
 *      Author: Maciek
 */

/*
 *   absolute channel numbering
 *   ch. spacing, center freq. and freq. deviation in kHz
 *
 *   -----------------------------------------------------------------------------------------------------------------------------
 *   no           max.power  ch. spacing       1st ch. center freq.   last ch. center freq.   9600bps Fd     2400bps Fd    band
 *   -----------------------------------------------------------------------------------------------------------------------------
 *    0-63         25mW         100             ch. 0 - 863 050.0      ch.63 - 869 350.0        32.5           32.5        BAND1
 *   64-66         as above     as above        ch.64 - 869 750.0      ch.66 - 869 950.0        as above       as above    BAND2
 *   67-78         100mW        25              ch.67 - 869 412.5      ch.78 - 869 687.5         4.375          7.5        BAND3
 *   -----------------------------------------------------------------------------------------------------------------------------
 *
 *   channels 77-78 are not ETSI-compliant.
 */

/*
 *   absolute channel numbering <--> developer & user numbering
 *
 *   -----------------------------------------------------------------------------------------------
 *   abs. ch.    user ch.  user->abs.    dev. ch.  dev.->abs.  remarks
 *                           offset                 offset
 *   -----------------------------------------------------------------------------------------------
 *    0- 9         -          -            0- 9       0
 *   10-47         0-37       10          -           -
 *   48            -          -           -           -        for 'choose channel' command at 25mW & 100kHz
 *   49-66         38-55      11          -           -
 *   67            -          -           -           -        for 'choose channel' command at 100mW & 25kHz
 *   68-76         56-64      12          -           -
 *   77-78         -          -           10-11       67
 *   -----------------------------------------------------------------------------------------------
 *
 *        total user channels: 65 (0-64)
 *   total developer channels: 12 (0-11)
 *     total special channels: 2 (48 and 67)
 *             total channels: 79 (0-78)
 */

#include "rfm22bands.h"
#include "rfm22callbacks.h"
#include "rfm22profiles.h"
#include "rfm22ports.h"
#include "rfm22_registers.h"


#define RFM22BANDS_FIRST_DEVELOPER_CHANNEL          0U
#define RFM22BANDS_LAST_DEVELOPER_CHANNEL           9U
#define RFM22BANDS_FIRST_ABSOLUTE_CHANNEL           0U
#define RFM22BANDS_LAST_ABSOLUTE_CHANNEL            66U

#define RFM22BANDS_CHOOSE_CHANNEL_25mW              48U
#define RFM22BANDS_CHOOSE_CHANNEL_100mW             67U

#define RFM22BANDS_LAST_ABSOLUTE_25mW_CHANNEL       66U

//frequency part exceeding 860MHz is only given (in Hz)
#define RFM22BANDS_25mW_BAND1_FIRST_CHANNEL         0U
#define RFM22BANDS_25mW_BAND1_LAST_CHANNEL          63U
#define RFM22BANDS_25mW_BAND1_FIRST_CHANNEL_FREQ    3050000UL

#define RFM22BANDS_25mW_BAND2_FIRST_CHANNEL         64U
#define RFM22BANDS_25mW_BAND2_LAST_CHANNEL          66U
#define RFM22BANDS_25mW_BAND2_FIRST_CHANNEL_FREQ    9750000UL

//channel spacing (in Hz)
#define RFM22BANDS_25mW_BANDS_1_2_CH_SPACING        100000UL


/**private functions**/

//main profile updaterers
void rfm22bands_update_profile(uint8_t force_full_loading);
void rfm22bands_update_profile_for_channel(uint8_t force_full_loading, int16_t channel);

//helpers for rfm22bands_update_profile()
void rfm22bands_fill_profile_regs(rfm22profiles_regs_t *regs);
void rfm22bands_send_profile_regs_spi(const rfm22profiles_regs_t *regs);

//profiles-dependant functions

//non profiles-dependant functions
uint8_t rfm22bands_validate_abs_channel(uint8_t channel);
uint8_t rfm22bands_validate_user_channel(uint8_t channel);
uint8_t rfm22bands_validate_dev_channel(uint8_t channel);
uint8_t rfm22bands_validate_power(uint8_t power);

//main channel carrier frequency setter
void rfm22bands_set_abs_channel_carrier_frequency(uint8_t channel);

//center frequency selection
uint16_t rfm22bands_freq2regs(uint32_t freq);                                   //center freq. (increment over 860MHz only) in Hz
void     rfm22bands_send_freq_spi(uint16_t fc_regs);

//channel->frequency conversion
uint32_t rfm22bands_frequency_of_abs_channel(uint8_t abs_channel);

//conversions of channel numbering
uint8_t rfm22bands_user_2_abs_channel(uint8_t user_channel);
int16_t rfm22bands_abs_2_user_channel(uint8_t abs_channel);
uint8_t rfm22bands_developer_2_abs_channel(uint8_t dev_channel);
int16_t rfm22bands_abs_2_developer_channel(uint8_t abs_channel);

//tx power setter
void rfm2bands_send_power_spi(uint8_t power);                                   //power is RFM22_TX_POWER_xx_DBM constant

/**PUBLIC FUNCTIONS**/
/*---------------------------------------------------------------------------*/
void rfm22bands_init()
{
    uint8_t abs_channel = rfm22callbacks_get_channel();
    uint8_t power = rfm22callbacks_get_power();

    //channel validation
    if(!rfm22bands_validate_abs_channel(abs_channel))
    {
        abs_channel = RFM22BANDS_DEFAULT_CHANNEL;
        rfm22callbacks_set_channel(abs_channel);
    }

    //power validation
    if(!rfm22bands_validate_power(power))
    {
        power = RFM22BANDS_DEFAULT_POWER;
        rfm22callbacks_set_power(power);
    }

    rfm22bands_update_profile(1);
    rfm2bands_send_power_spi(power);
    rfm22bands_set_abs_channel_carrier_frequency(abs_channel);
}

/*---------------------------------------------------------------------------*/
void rfm22bands_set_user_channel(uint8_t user_channel)
{
    uint8_t abs_channel;

    if (rfm22bands_validate_user_channel(user_channel))
    {
        abs_channel = rfm22bands_user_2_abs_channel(user_channel);
        rfm22callbacks_set_channel(abs_channel);
        rfm22bands_update_profile(0);
        rfm22bands_set_abs_channel_carrier_frequency(abs_channel);
    }
}

/*---------------------------------------------------------------------------*/
int16_t rfm22bands_get_user_channel()
{
    return rfm22bands_abs_2_user_channel(rfm22callbacks_get_channel());
}

/*---------------------------------------------------------------------------*/
int16_t rfm22bands_get_default_user_channel()
{
	return rfm22bands_abs_2_user_channel(RFM22BANDS_DEFAULT_CHANNEL);
}

/*---------------------------------------------------------------------------*/
void rfm22bands_set_developer_channel(uint8_t dev_channel)
{
    uint8_t abs_channel;

    if (rfm22bands_validate_dev_channel(dev_channel))
    {
        abs_channel = rfm22bands_developer_2_abs_channel(dev_channel);
        rfm22callbacks_set_channel(abs_channel);
        rfm22bands_update_profile(0);
        rfm22bands_set_abs_channel_carrier_frequency(abs_channel);
    }
}

/*---------------------------------------------------------------------------*/
int16_t rfm22bands_get_developer_channel()
{
    return rfm22bands_abs_2_developer_channel(rfm22callbacks_get_channel());
}

/*---------------------------------------------------------------------------*/
int16_t rfm22bands_get_default_developer_channel()
{
	return rfm22bands_abs_2_developer_channel(RFM22BANDS_DEFAULT_CHANNEL);
}

/*---------------------------------------------------------------------------*/
void rfm22bands_set_choose_channel()
{
    int16_t abs_channel = -1;

    abs_channel = RFM22BANDS_CHOOSE_CHANNEL_25mW;
    if (abs_channel >= 0)
    {
        rfm22bands_update_profile_for_channel(0, abs_channel);
        rfm22bands_set_abs_channel_carrier_frequency(abs_channel);
    }
}

/**PRIVATE FUNCTIONS**/

//main profile updaterers
/*---------------------------------------------------------------------------*/
void rfm22bands_update_profile_for_channel(uint8_t force_full_loading, int16_t channel)
{
    uint8_t load = force_full_loading;
    //channel == -1 means channel has been set in pernament memory and have to be read by callback
//    uint8_t new_channel = (channel == -1) ? rfm22callbacks_get_channel() : channel;
    rfm22profiles_regs_t regs;

    //when force_full_loading==0 profile is loaded only if necessary
    if(load)
    {
        rfm22bands_fill_profile_regs(&regs);
        rfm22bands_send_profile_regs_spi(&regs);
    }
}

/*---------------------------------------------------------------------------*/
void rfm22bands_update_profile(uint8_t force_full_loading)
{
    rfm22bands_update_profile_for_channel(force_full_loading, -1);
}

//helpers for rfm22bands_update_profile()
/*---------------------------------------------------------------------------*/
void rfm22bands_fill_profile_regs(rfm22profiles_regs_t *regs)
{
    rfm22profiles_fill_standard_profile(regs);
}

/*---------------------------------------------------------------------------*/
void rfm22bands_send_profile_regs_spi(const rfm22profiles_regs_t *regs)
{
    //carrier freqency
    rfm22ports_trans_write(RFM22_ADDR_FREQUENCY_BAND_SELECT, regs->reg75);
    rfm22ports_trans_write(RFM22_ADDR_NOMINAL_CARRIER_FREQ_1, regs->reg76);
    rfm22ports_trans_write(RFM22_ADDR_NOMINAL_CARRIER_FREQ_0, regs->reg77);

    //tx data rate
    rfm22ports_trans_write(RFM22_ADDR_TX_DATARATE1, regs->reg6E);
    rfm22ports_trans_write(RFM22_ADDR_TX_DATARATE0, regs->reg6F);
    rfm22ports_trans_write(RFM22_ADDR_MODULATION_MODE_CONTROL_1, regs->reg70);

    //tx frequency deviation
    rfm22ports_trans_write(RFM22_ADDR_FREQUENCY_DEVIATION, regs->reg72);
    rfm22ports_trans_write(RFM22_ADDR_MODULATION_MODE_CONTROL_2, regs->reg71);

    //rx (G)FSK and OOK
    rfm22ports_trans_write(RFM22_ADDR_IF_FILTER_BANDWIDTH, regs->reg1C);
    rfm22ports_trans_write(RFM22_ADDR_CLOCK_RECOV_OVERSAM_RATIO, regs->reg20);
    rfm22ports_trans_write(RFM22_ADDR_CLOCK_RECOV_OFFSET_2, regs->reg21);
    rfm22ports_trans_write(RFM22_ADDR_CLOCK_RECOV_OFFSET_1, regs->reg22);
    rfm22ports_trans_write(RFM22_ADDR_CLOCK_RECOV_OFFSET_0, regs->reg23);
    rfm22ports_trans_write(RFM22_ADDR_CLOCK_RECOV_TIMING_LOOP_1, regs->reg24);
    rfm22ports_trans_write(RFM22_ADDR_CLOCK_RECOV_TIMING_LOOP_0, regs->reg25);
    rfm22ports_trans_write(RFM22_ADDR_CLOCK_RECOV_GEARSHIFT_OVERR, regs->reg1F);
    rfm22ports_trans_write(RFM22_ADDR_AGC_OVERRIDE_1, regs->reg69);

    //rx (G)FSK
    rfm22ports_trans_write(RFM22_ADDR_AFC_LOOP_GEARSHIFT_OVERR, regs->reg1D);
    rfm22ports_trans_write(RFM22_ADDR_AFC_TIMING_CONTROL, regs->reg1E);
    rfm22ports_trans_write(RFM22_ADDR_AFC_LIMITER, regs->reg2A);

    //rx OOK
    rfm22ports_trans_write(RFM22_ADDR_OOK_COUNTER_VALUE_1, regs->reg2C);
    rfm22ports_trans_write(RFM22_ADDR_OOK_COUNTER_VALUE_2, regs->reg2D);
    rfm22ports_trans_write(RFM22_ADDR_SLICER_PEAK_HOLD, regs->reg2E);
}

/*---------------------------------------------------------------------------*/
uint8_t rfm22bands_validate_abs_channel(uint8_t channel)
{
    return (RFM22BANDS_FIRST_ABSOLUTE_CHANNEL <= channel) && (channel <= RFM22BANDS_LAST_ABSOLUTE_CHANNEL);
}

/*---------------------------------------------------------------------------*/
uint8_t rfm22bands_validate_user_channel(uint8_t channel)
{
    return (RFM22BANDS_FIRST_USER_CHANNEL <= channel) && (channel <= RFM22BANDS_LAST_USER_CHANNEL);
}

/*---------------------------------------------------------------------------*/
uint8_t rfm22bands_validate_dev_channel(uint8_t channel)
{
    return (RFM22BANDS_FIRST_DEVELOPER_CHANNEL <= channel) && (channel <= RFM22BANDS_LAST_DEVELOPER_CHANNEL);
}

/*---------------------------------------------------------------------------*/
uint8_t rfm22bands_validate_power(uint8_t power)
{
    return (RFM22_TX_POWER_1_DBM <= power) && (power <= RFM22_TX_POWER_20_DBM);
}

//main channel carrier frequency setter
/*---------------------------------------------------------------------------*/
void rfm22bands_set_abs_channel_carrier_frequency(uint8_t abs_channel)
{
    uint32_t frequency;
    uint16_t regs;

    if (rfm22bands_validate_abs_channel(abs_channel))
    {
        frequency = rfm22bands_frequency_of_abs_channel(abs_channel);
        regs = rfm22bands_freq2regs(frequency);
        rfm22bands_send_freq_spi(regs);
    }
}

//center frequency selection
/*---------------------------------------------------------------------------*/
uint16_t rfm22bands_freq2regs(uint32_t freq)
{
    //arg. "freq" - center freq. (increment over 860MHz only) in Hz
    //center frequency cannot exceed 870MHz. It means "freq" can't exceed 10 mln
    //freq should be multiplicity of 625Hz

    uint16_t fc = (uint16_t) (freq * 2UL / 625UL);           //division by 312,5Hz

    return fc;
}

/*---------------------------------------------------------------------------*/
void rfm22bands_send_freq_spi(uint16_t fc_regs)
{
    uint8_t frequencyMSB = (fc_regs >> 8);
    uint8_t frequencyLSB = (fc_regs & 0xFF);

    rfm22ports_trans_write(RFM22_ADDR_NOMINAL_CARRIER_FREQ_1, frequencyMSB);
    rfm22ports_trans_write(RFM22_ADDR_NOMINAL_CARRIER_FREQ_0, frequencyLSB);
}

//channel->frequency conversion
/*---------------------------------------------------------------------------*/
uint32_t rfm22bands_frequency_of_abs_channel(uint8_t abs_channel)
{
    uint32_t frequency = RFM22BANDS_25mW_BAND1_FIRST_CHANNEL_FREQ;

    if (rfm22bands_validate_abs_channel(abs_channel))
    {
        if ((RFM22BANDS_25mW_BAND1_FIRST_CHANNEL <= abs_channel) && (abs_channel <= RFM22BANDS_25mW_BAND1_LAST_CHANNEL))
        {
            frequency = RFM22BANDS_25mW_BAND1_FIRST_CHANNEL_FREQ;
            frequency += (abs_channel - RFM22BANDS_25mW_BAND1_FIRST_CHANNEL) * RFM22BANDS_25mW_BANDS_1_2_CH_SPACING;
        }
        else if ((RFM22BANDS_25mW_BAND2_FIRST_CHANNEL <= abs_channel) && (abs_channel <= RFM22BANDS_25mW_BAND2_LAST_CHANNEL))
        {
            frequency = RFM22BANDS_25mW_BAND2_FIRST_CHANNEL_FREQ;
            frequency += (abs_channel - RFM22BANDS_25mW_BAND2_FIRST_CHANNEL) * RFM22BANDS_25mW_BANDS_1_2_CH_SPACING;
        }
    }

    return frequency;
}

//conversions of channel numbering
/*---------------------------------------------------------------------------*/
uint8_t rfm22bands_user_2_abs_channel(uint8_t user_channel)
{
    uint8_t abs_channel = 10;

    if ((0 <= user_channel) && (user_channel <= 37))
    {
        abs_channel = user_channel + 10;
    }
    else if ((38 <= user_channel) && (user_channel <= 55))
    {
        abs_channel = user_channel + 11;
    }
    return abs_channel;
}

/*---------------------------------------------------------------------------*/
int16_t rfm22bands_abs_2_user_channel(uint8_t abs_channel)
{
    int16_t user_channel = -1;

    if ((10 <= abs_channel) && (abs_channel <= 47))
    {
        user_channel = abs_channel - 10;
    }
    else if ((49 <= abs_channel) && (abs_channel <= 66))
    {
        user_channel = abs_channel - 11;
    }
    return user_channel;
}

/*---------------------------------------------------------------------------*/
uint8_t rfm22bands_developer_2_abs_channel(uint8_t dev_channel)
{
    uint8_t abs_channel = 0;

    if ((0 <= dev_channel) && (dev_channel <= 9))
    {
        abs_channel = dev_channel;
    }
    return abs_channel;
}

/*---------------------------------------------------------------------------*/
int16_t rfm22bands_abs_2_developer_channel(uint8_t abs_channel)
{
    int16_t dev_channel = -1;

    if ((0 <= abs_channel) && (abs_channel <= 9))
    {
        dev_channel = abs_channel;
    }
    return dev_channel;
}

/*---------------------------------------------------------------------------*/
void rfm22bands_set_power(int16_t power)
{
    if(rfm22bands_validate_power(power))
    {
        rfm22callbacks_set_power(power);
        rfm2bands_send_power_spi(power);
    }

}

/*---------------------------------------------------------------------------*/
int16_t rfm22bands_get_power()
{
    int16_t power = -1;
    uint8_t callback_power = rfm22callbacks_get_power();

    if(rfm22bands_validate_power(callback_power))
    {
        power = callback_power;
    }
    return power;
}

/*---------------------------------------------------------------------------*/
void rfm2bands_send_power_spi(uint8_t power)
{
    if (rfm22bands_validate_power(power))
    {
        rfm22ports_trans_write(RFM22_ADDR_TX_POWER, RFM22_TX_POWER_LNA_SW | power);
    }
}





