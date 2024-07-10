#ifndef TTFY_BUFFER_H
#define TTFY_BUFFER_H

#include "TTFY_DATA_TYPES.h"
#include "TTFY_DEFINE.h"

typedef struct TTFY_Buffer TTFY_Buffer;

TTFY_API TTFY_Buffer *TTFY_BufferCreate(const char *file);
TTFY_API void TTFY_BufferDestroy(TTFY_Buffer **buffer);

// ----------------------- TTFY_Buffer FUNCTIONS ------------------------------
TTFY_API uint8 TTFY_BufferGetU8(TTFY_Buffer *buffer);
TTFY_API int8 TTFY_BufferGetI8(TTFY_Buffer *buffer);
TTFY_API uint16 TTFY_BufferGetU16(TTFY_Buffer *buffer);
TTFY_API int16 TTFY_BufferGetI16(TTFY_Buffer *buffer);
TTFY_API uint24 TTFY_BufferGetU24(TTFY_Buffer *buffer);
TTFY_API int24 TTFY_BufferGetI24(TTFY_Buffer *buffer);
TTFY_API uint32 TTFY_BufferGetU32(TTFY_Buffer *buffer);
TTFY_API int32 TTFY_BufferGetI32(TTFY_Buffer *buffer);
TTFY_API Fixed TTFY_BufferGetFixed(TTFY_Buffer *buffer);
TTFY_API FWord TTFY_BufferGetFWord(TTFY_Buffer *buffer);
TTFY_API UFWord TTFY_BufferGetUFWord(TTFY_Buffer *buffer);
TTFY_API F2DOT14 TTFY_BufferGetF2DOT14(TTFY_Buffer *buffer);
TTFY_API LONGDATETIME TTFY_BufferGetLONGDATETIME(TTFY_Buffer *buffer);
TTFY_API Offset8 TTFY_BufferGetOffset8(TTFY_Buffer *buffer);
TTFY_API Offset16 TTFY_BufferGetOffset16(TTFY_Buffer *buffer);
TTFY_API Offset24 TTFY_BufferGetOffset24(TTFY_Buffer *buffer);
TTFY_API Offset32 TTFY_BufferGetOffset32(TTFY_Buffer *buffer);
TTFY_API Version16Dot16 TTFY_BufferGetVersion16Dot16(TTFY_Buffer *buffer);
TTFY_API uint64_t TTFY_BufferGetPosition(TTFY_Buffer *buffer);
TTFY_API void TTFY_BufferSetPosition(TTFY_Buffer *buffer, uint64_t position);
TTFY_API void *TTFY_BufferGetAddressUnderPos(TTFY_Buffer *buffer);

#endif