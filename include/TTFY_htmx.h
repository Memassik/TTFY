#ifndef TTFY_HTMX_TABLE_H
#define TTFY_HTMX_TABLE_H
#include "TTFY_TableDirectory.h"
#include "TTFY_maxp.h"
#include "TTFY_hhea.h"

typedef struct TTFY_LongHorMetric TTFY_LongHorMetric;
typedef struct TTFY_HTMX TTFY_HTMX;

TTFY_API TTFY_HTMX *TTFY_HTMXCreate(TTFY_Buffer *buffer, TTFY_TableDirectory *directory, TTFY_HHEA *hhea, TTFY_MAXP *maxp);
TTFY_API void TTFY_HTMXDestroy(TTFY_HTMX **htmx);

TTFY_API TTFY_LongHorMetric *TTFY_HTMXGetLongHorMetric(TTFY_HTMX *htmx, uint16 ID);
TTFY_API FWord TTFY_HTMXGetLeftSideBearing(TTFY_HTMX *htmx, uint16 ID);

TTFY_API UFWord TTFY_LongHorMetricGetAdwanceWidth(TTFY_LongHorMetric *longHorMetric);
TTFY_API FWord TTFY_LongHorMetricGetLsb(TTFY_LongHorMetric *longHorMetric);

#endif