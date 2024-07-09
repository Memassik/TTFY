#ifndef TTFY_HEAD_TABLE_H
#define TTFY_HEAD_TABLE_H

#include "TTFY_buffer.h"
#include "TTFY_TableDirectory.h"

typedef struct TTFY_HEAD TTFY_HEAD;

TTFY_API TTFY_HEAD *TTFY_HEADCreate(TTFY_Buffer *buffer, TTFY_TableDirectory *directory);
TTFY_API void TTFY_HEADDestroy(TTFY_HEAD **head);

TTFY_API uint16 TTFY_HEADGetMajorVersion(TTFY_HEAD *head);
TTFY_API uint16 TTFY_HEADGetMinorVersion(TTFY_HEAD *head);
TTFY_API Fixed TTFY_HEADGetFontRevision(TTFY_HEAD *head);
TTFY_API uint32 TTFY_HEADGetChecksumAdjustment(TTFY_HEAD *head);
TTFY_API uint32 TTFY_HEADGetMagicNumber(TTFY_HEAD *head);
TTFY_API uint16 TTFY_HEADGetFlags(TTFY_HEAD *head);
TTFY_API uint16 TTFY_HEADGetUnitsPerEm(TTFY_HEAD *head);
TTFY_API LONGDATETIME TTFY_HEADGetCreated(TTFY_HEAD *head);
TTFY_API LONGDATETIME TTFY_HEADGetModified(TTFY_HEAD *head);
TTFY_API int16 TTFY_HEADGetXMin(TTFY_HEAD *head);
TTFY_API int16 TTFY_HEADGetYMin(TTFY_HEAD *head);
TTFY_API int16 TTFY_HEADGetXMax(TTFY_HEAD *head);
TTFY_API int16 TTFY_HEADGetYMax(TTFY_HEAD *head);
TTFY_API uint16 TTFY_HEADGetMacStyle(TTFY_HEAD *head);
TTFY_API uint16 TTFY_HEADGetLowestRecPPEM(TTFY_HEAD *head);
TTFY_API int16 TTFY_HEADGetFontDirectoryHint(TTFY_HEAD *head);
TTFY_API int16 TTFY_HEADGetIndexToLocFormat(TTFY_HEAD *head);
TTFY_API int16 TTFY_HEADGetGlyphDataFormat(TTFY_HEAD *head);

#endif