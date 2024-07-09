#include <TTFY_hhea.h>
#include <stdio.h>
#include <stdlib.h>

struct TTFY_HHEA
{
    uint16 majorVersion;
    uint16 minorVersion;
    FWord ascender;
    FWord descender;
    FWord lineGap;
    UFWord advanceWidthMax;
    FWord minLeftSideBearing;
    FWord minRightSideBearing;
    FWord xMaxExtent;
    int16 caretSlopeRise;
    int16 caretSlopeRun;
    int16 caretOffset;
    int16 metricDataFormat;
    uint16 numberOfHMetrics;
};

TTFY_HHEA *TTFY_HHEACreate(TTFY_Buffer *buffer, TTFY_TableDirectory *directory)
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

    TTFY_TableRecord *hhea_record = TTFY_TableDirectoryGetTableRecord(directory, TTFY_TABLE_NAME_HHEA);
    if (!hhea_record)
    {
        fprintf(stderr, "%s\n", "Failed To Locate HHEA Table");
        return NULL;
    }

    TTFY_HHEA *ret = malloc(sizeof(TTFY_HHEA));
    if (!ret)
    {
        fprintf(stderr, "%s\n", "Failed To Allocate Memory For TTFY_HHEA");
        return NULL;
    }

    TTFY_BufferSetPosition(buffer, TTFY_TableRecordGetOffset(hhea_record));
    ret->majorVersion = TTFY_BufferGetU16(buffer);
    ret->minorVersion = TTFY_BufferGetU16(buffer);
    ret->ascender = TTFY_BufferGetFWord(buffer);
    ret->descender = TTFY_BufferGetFWord(buffer);
    ret->lineGap = TTFY_BufferGetFWord(buffer);
    ret->advanceWidthMax = TTFY_BufferGetUFWord(buffer);
    ret->minLeftSideBearing = TTFY_BufferGetFWord(buffer);
    ret->minRightSideBearing = TTFY_BufferGetFWord(buffer);
    ret->xMaxExtent = TTFY_BufferGetFWord(buffer);
    ret->caretSlopeRise = TTFY_BufferGetI16(buffer);
    ret->caretSlopeRun = TTFY_BufferGetI16(buffer);
    ret->caretOffset = TTFY_BufferGetI16(buffer);
    TTFY_BufferGetI16(buffer);
    TTFY_BufferGetI16(buffer);
    TTFY_BufferGetI16(buffer);
    TTFY_BufferGetI16(buffer);
    ret->metricDataFormat = TTFY_BufferGetI16(buffer);
    ret->numberOfHMetrics = TTFY_BufferGetU16(buffer);
}

void TTFY_HHEADestroy(TTFY_HHEA **hhea)
{
    if (!hhea)
    {
        fprintf(stderr, "%s\n", "Invalid Pointer to TTFY_HHEA has been passed");
        return;
    }
    if (!*hhea)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_HHEA has been passed");
        return;
    }
    free(*hhea);
    *hhea = NULL;
}

uint16 TTFY_HHEAGetMajorVersion(TTFY_HHEA *hhea)
{
    if (!hhea)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_hhea has been passed");
        return 0;
    }
    return hhea->majorVersion;
}

uint16 TTFY_HHEAGetMinorVersion(TTFY_HHEA *hhea)
{
    if (!hhea)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_hhea has been passed");
        return 0;
    }
    return hhea->minorVersion;
}

FWord TTFY_HHEAGetAscender(TTFY_HHEA *hhea)
{
    if (!hhea)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_hhea has been passed");
        return 0;
    }
    return hhea->ascender;
}

FWord TTFY_HHEAGetDescender(TTFY_HHEA *hhea)
{
    if (!hhea)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_hhea has been passed");
        return 0;
    }
    return hhea->descender;
}

FWord TTFY_HHEAGetLineGap(TTFY_HHEA *hhea)
{
    if (!hhea)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_hhea has been passed");
        return 0;
    }
    return hhea->lineGap;
}

UFWord TTFY_HHEAGetAdvanceWidthMax(TTFY_HHEA *hhea)
{
    if (!hhea)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_hhea has been passed");
        return 0;
    }
    return hhea->advanceWidthMax;
}

FWord TTFY_HHEAGetMinLeftSideBearing(TTFY_HHEA *hhea)
{
    if (!hhea)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_hhea has been passed");
        return 0;
    }
    return hhea->minLeftSideBearing;
}

FWord TTFY_HHEAGetMinRightSideBearing(TTFY_HHEA *hhea)
{
    if (!hhea)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_hhea has been passed");
        return 0;
    }
    return hhea->minRightSideBearing;
}

FWord TTFY_HHEAGetXMaxExtent(TTFY_HHEA *hhea)
{
    if (!hhea)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_hhea has been passed");
        return 0;
    }
    return hhea->xMaxExtent;
}

int16 TTFY_HHEAGetCaretSlopeRise(TTFY_HHEA *hhea)
{
    if (!hhea)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_hhea has been passed");
        return 0;
    }
    return hhea->caretSlopeRise;
}

int16 TTFY_HHEAGetCaretSlopeRun(TTFY_HHEA *hhea)
{
    if (!hhea)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_hhea has been passed");
        return 0;
    }
    return hhea->caretSlopeRun;
}

int16 TTFY_HHEAGetCaretOffset(TTFY_HHEA *hhea)
{
    if (!hhea)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_hhea has been passed");
        return 0;
    }
    return hhea->caretOffset;
}

int16 TTFY_HHEAGetMetricDataFormat(TTFY_HHEA *hhea)
{
    if (!hhea)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_hhea has been passed");
        return 0;
    }
    return hhea->metricDataFormat;
}

uint16 TTFY_HHEAGetNumberOfHMetrics(TTFY_HHEA *hhea)
{
    if (!hhea)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_hhea has been passed");
        return 0;
    }
    return hhea->numberOfHMetrics;
}
