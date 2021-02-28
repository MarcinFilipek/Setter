#ifndef RFM22_REGISTERS_H_
#define RFM22_REGISTERS_H_


#define RFM22_WRITE_FLAG                                         0x80U
#define RFM22_READ_FLAG                                          0x00U


#define RFM22_ADDR_DEVICE_STATUS                                 0x02U
#define RFM22_ADDR_INTERRUPT_STATUS_1                            0x03U
#define RFM22_ADDR_INTERRUPT_STATUS_2                            0x04U
#define RFM22_ADDR_INTERRUPT_ENABLE_1                            0x05U
#define RFM22_ADDR_INTERRUPT_ENABLE_2                            0x06U
#define RFM22_ADDR_OPERATING_1                                   0x07U
#define RFM22_ADDR_OPERATING_2                                   0x08U

#define RFM22_ADDR_OUTPUT_CLOCK                                  0x0AU
#define RFM22_ADDR_GPIO_0_CONFIG                                 0x0BU
#define RFM22_ADDR_GPIO_1_CONFIG                                 0x0CU
#define RFM22_ADDR_GPIO_2_CONFIG                                 0x0DU
#define RFM22_ADDR_IO_PORT_CONFIG                                0x0EU

#define RFM22_ADDR_IF_FILTER_BANDWIDTH                           0x1CU
#define RFM22_ADDR_AFC_LOOP_GEARSHIFT_OVERR                      0x1DU
#define RFM22_ADDR_AFC_TIMING_CONTROL                            0x1EU
#define RFM22_ADDR_CLOCK_RECOV_GEARSHIFT_OVERR                   0x1FU
#define RFM22_ADDR_CLOCK_RECOV_OVERSAM_RATIO                     0x20U
#define RFM22_ADDR_CLOCK_RECOV_OFFSET_2                          0x21U
#define RFM22_ADDR_CLOCK_RECOV_OFFSET_1                          0x22U
#define RFM22_ADDR_CLOCK_RECOV_OFFSET_0                          0x23U
#define RFM22_ADDR_CLOCK_RECOV_TIMING_LOOP_1                     0x24U
#define RFM22_ADDR_CLOCK_RECOV_TIMING_LOOP_0                     0x25U
#define RFM22_ADDR_RSSI                                          0x26U
#define RFM22_ADDR_RSSI_THRESHOLD                                0x27U
#define RFM22_ADDR_AFC_LIMITER                                   0x2AU
#define RFM22_ADDR_OOK_COUNTER_VALUE_1                           0x2CU
#define RFM22_ADDR_OOK_COUNTER_VALUE_2                           0x2DU
#define RFM22_ADDR_SLICER_PEAK_HOLD                              0x2EU

#define RFM22_ADDR_DATA_ACCESS_CONTROL                           0x30U
#define RFM22_ADDR_EZMAC_STATUS                                  0x31U
#define RFM22_ADDR_HEADER_CONTROL_1                              0x32U
#define RFM22_ADDR_HEADER_CONTROL_2                              0x33U
#define RFM22_ADDR_PREAMBLE_LENGTH                               0x34U
#define RFM22_ADDR_SYNC_WORD_3                                   0x36U
#define RFM22_ADDR_SYNC_WORD_2                                   0x37U
#define RFM22_ADDR_TRANSMIT_PACKET_LENGTH                        0x3EU
#define RFM22_ADDR_RECEIVED_PACKET_LENGTH                        0x4BU

#define RFM22_ADDR_AGC_OVERRIDE_1                                0x69U
#define RFM22_ADDR_TX_POWER                                      0x6DU
#define RFM22_ADDR_TX_DATARATE1                                  0x6EU
#define RFM22_ADDR_TX_DATARATE0                                  0x6FU
#define RFM22_ADDR_MODULATION_MODE_CONTROL_1                     0x70U
#define RFM22_ADDR_MODULATION_MODE_CONTROL_2                     0x71U
#define RFM22_ADDR_FREQUENCY_DEVIATION                           0x72U
#define RFM22_ADDR_FREQUENCY_OFFSET_1                            0x73U
#define RFM22_ADDR_FREQUENCY_OFFSET_2                            0x74U
#define RFM22_ADDR_FREQUENCY_BAND_SELECT                         0x75U
#define RFM22_ADDR_NOMINAL_CARRIER_FREQ_1                        0x76U
#define RFM22_ADDR_NOMINAL_CARRIER_FREQ_0                        0x77U
#define RFM22_ADDR_FREQ_HOPPING_CH_SELECT                        0x79U
#define RFM22_ADDR_FREQ_HOPPING_STEP_SIZE                        0x7AU

#define RFM22_ADDR_TX_FIFO_CONTROL_1                             0x7CU
#define RFM22_ADDR_TX_FIFO_CONTROL_2                             0x7DU
#define RFM22_ADDR_RX_FIFO_CONTROL                               0x7EU
#define RFM22_ADDR_FIFO_ACCESS                                   0x7FU


//flagi do TX_POWER - 0x6DU
#define RFM22_TX_POWER_LNA_SW                     (1 << 3)
#define RFM22_TX_POWER_1_DBM                      0
#define RFM22_TX_POWER_2_DBM                      1
#define RFM22_TX_POWER_5_DBM                      2
#define RFM22_TX_POWER_8_DBM                      3
#define RFM22_TX_POWER_11_DBM                     4
#define RFM22_TX_POWER_14_DBM                     5
#define RFM22_TX_POWER_17_DBM                     6
#define RFM22_TX_POWER_20_DBM                     7


#endif /*RFM22_REGISTERS_H_*/
