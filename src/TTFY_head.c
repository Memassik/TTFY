#include <TTFY_head.h>
#include <stdio.h>
#include <stdlib.h>

struct TTFY_HEAD
{
    uint16 majorVersion;
    uint16 minorVersion;
    Fixed fontRevision;
    uint32 checksumAdj;
    uint32 magicNumber;
    uint16 flags;
    uint16 unitsPerEM;
    LONGDATETIME created;
    LONGDATETIME modified;
    int16 xMin;
    int16 yMin;
    int16 xMax;
    int16 yMax;
    uint16 macStyle;
    uint16 lowestRecPPEM;
    int16 fontDirectoryHint;
    int16 indexToLocFormat;
    int16 glyphDataFormat;
};

TTFY_HEAD *TTFY_HEADCreate(TTFY_Buffer *buffer, TTFY_TableDirectory *directory)
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
    TTFY_TableRecord *head_record = TTFY_TableDirectoryGetTableRecord(directory, TTFY_TABLE_NAME_HEAD);
    if (!head_record)
    {
        fprintf(stderr, "%s\n", "Failed To Locate Head Table");
        return NULL;
    }

    TTFY_HEAD *ret = malloc(sizeof(TTFY_HEAD));
    if (!ret)
    {
        fprintf(stderr, "%s\n", "Failed To Allocate Memory For TTFY_HEAD");
        return NULL;
    }

    TTFY_BufferSetPosition(buffer, TTFY_TableRecordGetOffset(head_record));
    ret->majorVersion = TTFY_BufferGetU16(buffer);
    ret->minorVersion = TTFY_BufferGetU16(buffer);
    ret->fontRevision = TTFY_BufferGetFixed(buffer);
    ret->checksumAdj = TTFY_BufferGetU32(buffer);
    ret->magicNumber = TTFY_BufferGetU32(buffer);
    ret->flags = TTFY_BufferGetU16(buffer);
    ret->unitsPerEM = TTFY_BufferGetU16(buffer);
    ret->created = TTFY_BufferGetLONGDATETIME(buffer);
    ret->modified = TTFY_BufferGetLONGDATETIME(buffer);
    ret->xMin = TTFY_BufferGetI16(buffer);
    ret->yMin = TTFY_BufferGetI16(buffer);
    ret->xMax = TTFY_BufferGetI16(buffer);
    ret->yMax = TTFY_BufferGetI16(buffer);
    ret->macStyle = TTFY_BufferGetU16(buffer);
    ret->lowestRecPPEM = TTFY_BufferGetU16(buffer);
    ret->fontDirectoryHint = TTFY_BufferGetI16(buffer);
    ret->indexToLocFormat = TTFY_BufferGetI16(buffer);
    ret->glyphDataFormat = TTFY_BufferGetI16(buffer);
    return ret;
}

void TTFY_HEADDestroy(TTFY_HEAD **head)
{
    if (!head)
    {
        fprintf(stderr, "%s\n", "Invalid Pointer to TTFY_HEAD has been passed");
        return;
    }
    if (!*head)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_HEAD has been passed");
        return;
    }
    free(*head);
    *head = NULL;
}

uint16 TTFY_HEADGetMajorVersion(TTFY_HEAD *head)
{
    if (!head)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_HEAD has been passed");
        return 0;
    }
    return head->majorVersion;
}

uint16 TTFY_HEADGetMinorVersion(TTFY_HEAD *head)
{
    if (!head)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_HEAD has been passed");
        return 0;
    }
    return head->minorVersion;
}

Fixed TTFY_HEADGetFontRevision(TTFY_HEAD *head)
{
    if (!head)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_HEAD has been passed");
        return 0;
    }
    return head->fontRevision;
}

uint32 TTFY_HEADGetChecksumAdjustment(TTFY_HEAD *head)
{
    if (!head)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_HEAD has been passed");
        return 0;
    }
    return head->checksumAdj;
}

uint32 TTFY_HEADGetMagicNumber(TTFY_HEAD *head)
{
    if (!head)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_HEAD has been passed");
        return 0;
    }

    return head->magicNumber;
}

uint16 TTFY_HEADGetFlags(TTFY_HEAD *head)
{
    if (!head)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_HEAD has been passed");
        return 0;
    }
    return head->flags;
}

uint16 TTFY_HEADGetUnitsPerEm(TTFY_HEAD *head)
{
    if (!head)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_HEAD has been passed");
        return 0;
    }
    return head->unitsPerEM;
}

LONGDATETIME TTFY_HEADGetCreated(TTFY_HEAD *head)
{
    if (!head)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_HEAD has been passed");
        return 0;
    }
    return head->created;
}

LONGDATETIME TTFY_HEADGetModified(TTFY_HEAD *head)
{
    if (!head)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_HEAD has been passed");
        return 0;
    }
    return head->modified;
}

int16 TTFY_HEADGetXMin(TTFY_HEAD *head)
{
    if (!head)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_HEAD has been passed");
        return 0;
    }
    return head->xMin;
}

int16 TTFY_HEADGetYMin(TTFY_HEAD *head)
{
    if (!head)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_HEAD has been passed");
        return 0;
    }
    return head->yMin;
}

int16 TTFY_HEADGetXMax(TTFY_HEAD *head)
{
    if (!head)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_HEAD has been passed");
        return 0;
    }
    return head->xMax;
}

int16 TTFY_HEADGetYMax(TTFY_HEAD *head)
{
    if (!head)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_HEAD has been passed");
        return 0;
    }
    return head->yMax;
}

uint16 TTFY_HEADGetMacStyle(TTFY_HEAD *head)
{
    if (!head)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_HEAD has been passed");
        return 0;
    }
    return head->macStyle;
}

uint16 TTFY_HEADGetLowestRecPPEM(TTFY_HEAD *head)
{
    if (!head)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_HEAD has been passed");
        return 0;
    }
    return head->lowestRecPPEM;
}

int16 TTFY_HEADGetFontDirectoryHint(TTFY_HEAD *head)
{
    if (!head)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_HEAD has been passed");
        return 0;
    }
    return head->fontDirectoryHint;
}

int16 TTFY_HEADGetIndexToLocFormat(TTFY_HEAD *head)
{
    if (!head)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_HEAD has been passed");
        return 0;
    }
    return head->indexToLocFormat;
}

int16 TTFY_HEADGetGlyphDataFormat(TTFY_HEAD *head)
{
    if (!head)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_HEAD has been passed");
        return 0;
    }
    return head->glyphDataFormat;
}