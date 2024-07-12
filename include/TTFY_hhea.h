#ifndef TTFY_HHEA_TABLE_H
#define TTFY_HHEA_TABLE_H

#include <TTFY_TableDirectory.h>

typedef struct TTFY_HHEA TTFY_HHEA;

TTFY_API TTFY_HHEA *TTFY_HHEACreate(TTFY_Buffer *buffer, TTFY_TableDirectory *directory);
TTFY_API void TTFY_HHEADestroy(TTFY_HHEA **hhea);

TTFY_API uint16 TTFY_HHEAGetMajorVersion(TTFY_HHEA *hhea);
TTFY_API uint16 TTFY_HHEAGetMinorVersion(TTFY_HHEA *hhea);
TTFY_API FWord TTFY_HHEAGetAscender(TTFY_HHEA *hhea);
TTFY_API FWord TTFY_HHEAGetDescender(TTFY_HHEA *hhea);
TTFY_API FWord TTFY_HHEAGetLineGap(TTFY_HHEA *hhea);
TTFY_API UFWord TTFY_HHEAGetAdvanceWidthMax(TTFY_HHEA *hhea);
TTFY_API FWord TTFY_HHEAGetMinLeftSideBearing(TTFY_HHEA *hhea);
TTFY_API FWord TTFY_HHEAGetMinRightSideBearing(TTFY_HHEA *hhea);
TTFY_API FWord TTFY_HHEAGetXMaxExtent(TTFY_HHEA *hhea);
TTFY_API int16 TTFY_HHEAGetCaretSlopeRise(TTFY_HHEA *hhea);
TTFY_API int16 TTFY_HHEAGetCaretSlopeRun(TTFY_HHEA *hhea);
TTFY_API int16 TTFY_HHEAGetCaretOffset(TTFY_HHEA *hhea);
TTFY_API int16 TTFY_HHEAGetMetricDataFormat(TTFY_HHEA *hhea);
TTFY_API uint16 TTFY_HHEAGetNumberOfHMetrics(TTFY_HHEA *hhea);

#endif