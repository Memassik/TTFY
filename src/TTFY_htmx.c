#include <TTFY_htmx.h>
#include <stdlib.h>
#include <stdio.h>

struct TTFY_LongHorMetric
{
    UFWord advanceWidth;
    FWord lsb;
};

struct TTFY_HTMX
{
    TTFY_LongHorMetric *hMetrics;
    FWord *leftSideBearings;
    uint16 numberOfHMetrics;
    uint16 numGlyps;
};

TTFY_HTMX *TTFY_HTMXCreate(TTFY_Buffer *buffer, TTFY_TableDirectory *directory, TTFY_HHEA *hhea, TTFY_MAXP *maxp)
{
    if (!buffer)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_Buffer has been passed");
        return NULL;
    }
    if (!directory)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_TableDirectory has been passed");
        return NULL;
    }
    if (!hhea)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_HHEA has been passed");
        return NULL;
    }
    if (!maxp)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_MAXP has been passed");
        return NULL;
    }

    TTFY_TableRecord *htmx_record = TTFY_TableDirectoryGetTableRecord(directory, TTFY_TABLE_NAME_HTMX);
    if (!htmx_record)
    {
        fprintf(stderr, "%s\n", "Failed To Locate HTMX Table");
        return NULL;
    }

    TTFY_HTMX *ret = malloc(sizeof(TTFY_HTMX));
    if (!ret)
    {
        fprintf(stderr, "%s\n", "Failed To Allocate Memory For TTFY_HTMX");
        return NULL;
    }

    ret->numberOfHMetrics = TTFY_HHEAGetNumberOfHMetrics(hhea);
    if (!ret->numberOfHMetrics)
    {
        fprintf(stderr, "%s\n", "Wrong Number Of hMetrics");
        free(ret);
        return NULL;
    }

    ret->hMetrics = malloc(sizeof(TTFY_LongHorMetric) * ret->numberOfHMetrics);
    if (!ret->hMetrics)
    {
        fprintf(stderr, "%s\n", "Failed To Allocate Memory For TTFY_HTMX hMetrics");
        free(ret);
        return NULL;
    }

    ret->numGlyps = TTFY_MAXPGetNumGlyphs(maxp);
    if (!(ret->numGlyps - ret->numberOfHMetrics))
    {
        fprintf(stderr, "%s\n", "Wrong Number Of LSBs");
        free(ret);
        return NULL;
    }

    ret->leftSideBearings = malloc(sizeof(FWord) * (ret->numGlyps - ret->numberOfHMetrics));
    if (!ret->leftSideBearings)
    {
        fprintf(stderr, "%s\n", "Failed To Allocate Memory For TTFY_HTMX LSB");
        free(ret);
        return NULL;
    }

    TTFY_BufferSetPosition(buffer, TTFY_TableRecordGetOffset(htmx_record));

    for (uint16 i = 0; i < ret->numberOfHMetrics; ++i)
    {
        TTFY_LongHorMetric *hMetric = &ret->hMetrics[i];
        hMetric->advanceWidth = TTFY_BufferGetUFWord(buffer);
        hMetric->lsb = TTFY_BufferGetFWord(buffer);
    }

    for (uint16 i = 0; i < ret->numGlyps - ret->numberOfHMetrics; ++i)
    {
        ret->leftSideBearings[i] = TTFY_BufferGetFWord(buffer);
    }
    return ret;
}

void TTFY_HTMXDestroy(TTFY_HTMX **htmx)
{
    if (!htmx)
    {
        fprintf(stderr, "%s\n", "Invalid Pointer to TTFY_HTMX has been passed");
        return;
    }
    if (!*htmx)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_HTMX has been passed");
        return;
    }
    if ((*htmx)->numberOfHMetrics)
    {
        free((*htmx)->hMetrics);
    }
    if ((*htmx)->numGlyps - (*htmx)->numberOfHMetrics)
    {
        free((*htmx)->leftSideBearings);
    }
    free(*htmx);
    *htmx = NULL;
}

TTFY_LongHorMetric *TTFY_HTMXGetLongHorMetric(TTFY_HTMX *htmx, uint16 ID)
{
    if (!htmx)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_HTMX has been passed");
        return NULL;
    }
    if (ID >= htmx->numberOfHMetrics)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_HTMX ID has been passed");
        return NULL;
    }
    return &htmx->hMetrics[ID];
}

FWord TTFY_HTMXGetLeftSideBearing(TTFY_HTMX *htmx, uint16 ID)
{
    if (!htmx)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_HTMX has been passed");
        return 0;
    }
    if (ID >= (htmx->numGlyps - htmx->numberOfHMetrics))
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_HTMX ID has been passed");
        return 0;
    }
    return htmx->leftSideBearings[ID];
}

UFWord TTFY_LongHorMetricGetAdwanceWidth(TTFY_LongHorMetric *longHorMetric)
{
    if (!longHorMetric)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_LongHorMetric has been passed");
        return 0;
    }
    return longHorMetric->advanceWidth;
}

FWord TTFY_LongHorMetricGetLsb(TTFY_LongHorMetric *longHorMetric)
{
    if (!longHorMetric)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_LongHorMetric has been passed");
        return 0;
    }
    return longHorMetric->lsb;
}