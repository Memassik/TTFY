#include <TTFY_buffer.h>
#include <stdio.h>
#include <stdlib.h>

struct TTFY_Buffer
{
    const char *filepath;
    FILE *filePointer;
    char *buffer;
    uint64_t size;
    uint64_t position;
};

TTFY_Buffer *TTFY_BufferCreate(const char *file)
{
    if (!file)
    {
        fprintf(stderr, "%s\n", "No Filename has been passed");
        return NULL;
    }
    TTFY_Buffer *ret = malloc(sizeof(TTFY_Buffer));
    if (!ret)
    {
        fprintf(stderr, "%s\n", "Failed To Allocate Memory For TTFY_Buffer");
        return NULL;
    }
    ret->filepath = file;
    ret->filePointer = fopen(ret->filepath, "rb");
    if (!ret->filePointer)
    {
        fprintf(stderr, "%s\n", "Failed To Open File");
        free(ret);
        return NULL;
    }
    fseek(ret->filePointer, 0, SEEK_END);
    ret->size = ftell(ret->filePointer);
    if (!ret->size)
    {
        fprintf(stderr, "%s\n", "File is empty");
        free(ret);
        return NULL;
    }
    fseek(ret->filePointer, 0, SEEK_SET);
    ret->buffer = malloc(ret->size);
    if (!ret->buffer)
    {
        fprintf(stderr, "%s\n", "Failed To Allocate Memory For Buffer");
        free(ret);
        return NULL;
    }
    fread(ret->buffer, 1, ret->size, ret->filePointer);
    ret->position = 0;
    return ret;
}

void TTFY_BufferDestroy(TTFY_Buffer **buffer)
{
    if (!buffer || !*buffer)
    {
        fprintf(stderr, "%s\n", "Passed Non Valid TTFY_Buffer pointer");
        return;
    }
    if ((*buffer)->buffer)
        free((*buffer)->buffer);
    if (!(*buffer)->filePointer)
        fclose((*buffer)->filePointer);
    free(*buffer);
    *buffer = NULL;
}

// ----------------------- TTFY_Buffer FUNCTIONS ------------------------------
uint8 TTFY_BufferGetU8(TTFY_Buffer *buffer)
{
    if (!buffer)
    {
        fprintf(stderr, "%s\n", "Passed Non Valid TTFY_Buffer");
        return 0;
    }
    return buffer->buffer[buffer->position++];
}

int8 TTFY_BufferGetI8(TTFY_Buffer *buffer)
{
    return TTFY_BufferGetU8(buffer);
}

uint16 TTFY_BufferGetU16(TTFY_Buffer *buffer)
{
    return (uint16)(TTFY_BufferGetU8(buffer) << 8) | (TTFY_BufferGetU8(buffer));
}

int16 TTFY_BufferGetI16(TTFY_Buffer *buffer)
{
    uint16 number = TTFY_BufferGetU16(buffer);
    if (number & 0x8000)
        number -= 1 << 16;
    return number;
}

uint24 TTFY_BufferGetU24(TTFY_Buffer *buffer)
{
    return (uint24)(TTFY_BufferGetU8(buffer) << 16) | (TTFY_BufferGetU8(buffer) << 8) | (TTFY_BufferGetU8(buffer));
}

int24 TTFY_BufferGetI24(TTFY_Buffer *buffer)
{
    uint24 number = TTFY_BufferGetU24(buffer);
    if (number & (1 << 24))
        number -= 1 << 24;
    return number;
}

uint32 TTFY_BufferGetU32(TTFY_Buffer *buffer)
{
    return TTFY_BufferGetI32(buffer);
}

int32 TTFY_BufferGetI32(TTFY_Buffer *buffer)
{
    return (TTFY_BufferGetU8(buffer) << 24) | (TTFY_BufferGetU8(buffer) << 16) | (TTFY_BufferGetU8(buffer) << 8) | (TTFY_BufferGetU8(buffer));
}

Fixed TTFY_BufferGetFixed(TTFY_Buffer *buffer)
{
    return TTFY_BufferGetI32(buffer) / (1 << 16);
}

FWord TTFY_BufferGetFWord(TTFY_Buffer *buffer)
{
    return TTFY_BufferGetI16(buffer);
}

UFWord TTFY_BufferGetUFWord(TTFY_Buffer *buffer)
{
    return TTFY_BufferGetU16(buffer);
}

F2DOT14 TTFY_BufferGetF2DOT14(TTFY_Buffer *buffer)
{
    return TTFY_BufferGetI16(buffer) / (1 << 14);
}

LONGDATETIME TTFY_BufferGetLONGDATETIME(TTFY_Buffer *buffer)
{
    return TTFY_BufferGetU32(buffer) * 0x100000000 + TTFY_BufferGetU32(buffer);
}

Offset8 TTFY_BufferGetOffset8(TTFY_Buffer *buffer)
{
    return TTFY_BufferGetU8(buffer);
}

Offset16 TTFY_BufferGetOffset16(TTFY_Buffer *buffer)
{
    return TTFY_BufferGetU16(buffer);
}

Offset24 TTFY_BufferGetOffset24(TTFY_Buffer *buffer)
{
    return TTFY_BufferGetU24(buffer);
}

Offset32 TTFY_BufferGetOffset32(TTFY_Buffer *buffer)
{
    return TTFY_BufferGetU32(buffer);
}

Version16Dot16 TTFY_BufferGetVersion16Dot16(TTFY_Buffer *buffer)
{
    return TTFY_BufferGetFixed(buffer);
}

uint64_t TTFY_BufferGetPosition(TTFY_Buffer *buffer)
{
    if (!buffer)
    {
        fprintf(stderr, "%s\n", "Passed Non Valid TTFY_Buffer");
        return 0;
    }
    return buffer->position;
}

TTFY_API void TTFY_BufferSetPosition(TTFY_Buffer *buffer, uint64_t position)
{
    if (!buffer)
    {
        fprintf(stderr, "%s\n", "Passed Non Valid TTFY_Buffer");
        return;
    }
    buffer->position = position;
}