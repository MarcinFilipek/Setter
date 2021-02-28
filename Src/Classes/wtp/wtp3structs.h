#ifndef WTP3STRUCTS_H_
#define WTP3STRUCTS_H_

#include <stdint.h>

#define  PACKED  __attribute__((packed))

typedef enum
{
    WTP3_BROADCAST = 0xFFFFFFFF,
} EWtp3Address;

typedef struct
{
    uint32_t dest;
    uint32_t sender;
    uint8_t answer;
    uint8_t signin;
    uint16_t device;
} SWtp3AddressHeader;

typedef enum
{
    REC_FRAME_NO_ANSWER = 0,
    REC_FRAME_ANSWER = 1,
    REC_FRAME_NO_ANSWER_STOP_RX = 2,
} ERecFrameResult;

typedef enum
{
    RECEIVE_MODE_OFF = 0,
    RECEIVE_MODE_AFTER_TX = 1,
    RECEIVE_MODE_CONTINUOUS = 2,
} EReceiveMode;

#endif /* WTP3STRUCTS_H_ */
