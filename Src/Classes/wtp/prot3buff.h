#ifndef prot3buff_H_
#define prot3buff_H_

#include <stdint.h>

typedef struct
{
    uint16_t capacity;
    uint8_t *buffer;
    uint16_t writer_pos;
    uint16_t reader_pos;
} prot3buff_t;

void     prot3buff_init(prot3buff_t *ob, uint8_t *buffer, uint16_t buffer_len);
uint16_t prot3buff_getWriterPos(prot3buff_t *ob);
uint16_t prot3buff_getReaderPos(prot3buff_t *ob);
void     prot3buff_setWriterToPos(prot3buff_t *ob, uint16_t pos);
void     prot3buff_setReaderToPos(prot3buff_t *ob, uint16_t pos);
void     prot3buff_clear(prot3buff_t *ob);

uint16_t  prot3buff_getCapacityAvail(prot3buff_t *ob);
uint16_t  prot3buff_putByte(prot3buff_t *ob, uint8_t byte);
uint16_t  prot3buff_putBytes(prot3buff_t *ob, uint8_t *array, uint16_t size);

uint16_t  prot3buff_getBytesAvail(prot3buff_t *ob);
uint16_t  prot3buff_isByteAvailable(prot3buff_t *ob);
int16_t   prot3buff_readByte(prot3buff_t *ob);
uint16_t  prot3buff_readBytes(prot3buff_t *ob, uint8_t *array, uint16_t size);

uint16_t  prot3buff_replaceLastReadByte(prot3buff_t *ob, uint8_t byte);
uint16_t  prot3buff_replaceLastNReadBytes(prot3buff_t *ob, uint8_t *array, uint16_t size);

int16_t  prot3buff_readByte_unchecked(prot3buff_t *ob);
uint16_t prot3buff_readBytes_unchecked(prot3buff_t *ob, uint8_t *array, uint16_t size);

#endif /* prot3buff_H_ */
