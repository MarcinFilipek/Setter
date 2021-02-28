#include "prot3buff.h"
#include <stdlib.h>

void prot3buff_init(prot3buff_t *ob, uint8_t *buffer, uint16_t buffer_len)
{
    ob->buffer = buffer;
    ob->capacity = buffer_len;
    ob->writer_pos = 0;
    ob->reader_pos = 0;
}

uint16_t prot3buff_getWriterPos(prot3buff_t *ob)
{
    return ob->writer_pos;
}

uint16_t prot3buff_getReaderPos(prot3buff_t *ob)
{
    return ob->reader_pos;
}

void prot3buff_setWriterToPos(prot3buff_t *ob, uint16_t pos)
{
    if(pos < ob->capacity)
    {
        ob->writer_pos = pos;
    }
}

void prot3buff_setReaderToPos(prot3buff_t *ob, uint16_t pos)
{
    if(pos < ob->capacity)
    {
        ob->reader_pos = pos;
    }
}

void prot3buff_clear(prot3buff_t *ob)
{
    prot3buff_setWriterToPos(ob, 0);
    prot3buff_setReaderToPos(ob, 0);
}

uint16_t prot3buff_getCapacityAvail(prot3buff_t *ob)
{
    return ob->capacity - ob->writer_pos;
}

uint16_t prot3buff_putByte(prot3buff_t *ob, uint8_t byte)
{
    if(ob->writer_pos < ob->capacity)
    {
        ob->buffer[ob->writer_pos] = byte;
        ob->writer_pos++;
        return 1;
    }
    return 0;
}

uint16_t prot3buff_putBytes(prot3buff_t *ob, uint8_t *array, uint16_t size)
{
    uint16_t put = 0;

    while((ob->writer_pos < ob->capacity) && (put < size))
    {
        ob->buffer[ob->writer_pos] = *array;
        ob->writer_pos++;
        array++;
        put++;
    }
    return put;
}

uint16_t prot3buff_getBytesAvail(prot3buff_t *ob)
{
    return ob->writer_pos - ob->reader_pos;
}

uint16_t prot3buff_isByteAvailable(prot3buff_t *ob)
{
    return ob->reader_pos < ob->writer_pos;
}

int16_t prot3buff_readByte(prot3buff_t *ob)
{
    if(ob->reader_pos < ob->writer_pos)
    {
        uint8_t byte = ob->buffer[ob->reader_pos];

        ob->reader_pos++;
        return byte;
    }
    return -1;
}

uint16_t prot3buff_readBytes(prot3buff_t *ob, uint8_t *array, uint16_t size)
{
    uint16_t read = 0;

    if(array != NULL)
    {
        while((ob->reader_pos < ob->writer_pos) && (read < size))
        {
            *array = ob->buffer[ob->reader_pos];
            ob->reader_pos++;
            array++;
            read++;
        }
    }
    else
    {
        uint16_t available = ob->writer_pos - ob->reader_pos;

        read = (available < size) ? available : size;
        ob->reader_pos += read;
    }
    return read;
}

uint16_t prot3buff_replaceLastReadByte(prot3buff_t *ob, uint8_t byte)
{
    if(ob->reader_pos >= 1)
    {
        ob->buffer[ob->reader_pos - 1] = byte;
        return 1;
    }
    return 0;
}

uint16_t prot3buff_replaceLastNReadBytes(prot3buff_t *ob, uint8_t *array, uint16_t size)
{
    uint16_t i;

    if(ob->reader_pos >= size)
    {
        for(i = ob->reader_pos - size; i < ob->reader_pos; i++)
        {
            ob->buffer[i] = *array;
            array++;
        }
        return 1;
    }
    return 0;
}

int16_t prot3buff_readByte_unchecked(prot3buff_t *ob)
{
    uint8_t byte = ob->buffer[ob->reader_pos];

    ob->reader_pos++;
    return byte;
}

uint16_t prot3buff_readBytes_unchecked(prot3buff_t *ob, uint8_t *array, uint16_t size)
{
    while(size > 0)
    {
        *array = ob->buffer[ob->reader_pos];
        ob->reader_pos++;
        array++;
        size--;
    }
    return 1;
}

