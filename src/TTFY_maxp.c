#include <TTFY_maxp.h>
#include <stdio.h>
#include <stdlib.h>

struct TTFY_MAXP
{
    Version16Dot16 version;
    uint16 numGlyphs;
    uint16 maxPoints;
    uint16 maxContours;
    uint16 maxCompositePoints;
    uint16 maxCompositeContours;
    uint16 maxZones;
    uint16 maxTwilightPoints;
    uint16 maxStorage;
    uint16 maxFunctionDefs;
    uint16 maxInstructionsDefs;
    uint16 maxStackElements;
    uint16 maxSizeOfInstructions;
    uint16 maxComponentElements;
    uint16 maxComponentDepth;
};

TTFY_MAXP *TTFY_MAXPCreate(TTFY_Buffer *buffer, TTFY_TableDirectory *directory)
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

    TTFY_TableRecord *maxp_record = TTFY_TableDirectoryGetTableRecord(directory, TTFY_TABLE_NAME_MAXP);
    if (!maxp_record)
    {
        fprintf(stderr, "%s\n", "Failed To Locate MAXP Table");
        return NULL;
    }

    TTFY_MAXP *ret = malloc(sizeof(TTFY_MAXP));
    if (!ret)
    {
        fprintf(stderr, "%s\n", "Failed To Allocate Memory For TTFY_MAXP");
        return NULL;
    }

    TTFY_BufferSetPosition(buffer, TTFY_TableRecordGetOffset(maxp_record));
    ret->version = TTFY_BufferGetVersion16Dot16(buffer);
    ret->numGlyphs = TTFY_BufferGetU16(buffer);
    ret->maxPoints = TTFY_BufferGetU16(buffer);
    ret->maxContours = TTFY_BufferGetU16(buffer);
    ret->maxCompositePoints = TTFY_BufferGetU16(buffer);
    ret->maxCompositeContours = TTFY_BufferGetU16(buffer);
    ret->maxZones = TTFY_BufferGetU16(buffer);
    ret->maxTwilightPoints = TTFY_BufferGetU16(buffer);
    ret->maxStorage = TTFY_BufferGetU16(buffer);
    ret->maxFunctionDefs = TTFY_BufferGetU16(buffer);
    ret->maxInstructionsDefs = TTFY_BufferGetU16(buffer);
    ret->maxStackElements = TTFY_BufferGetU16(buffer);
    ret->maxSizeOfInstructions = TTFY_BufferGetU16(buffer);
    ret->maxComponentElements = TTFY_BufferGetU16(buffer);
    ret->maxComponentDepth = TTFY_BufferGetU16(buffer);
    return ret;
}

void TTFY_MAXPDestroy(TTFY_MAXP **maxp)
{
    if (!maxp)
    {
        fprintf(stderr, "%s\n", "Invalid Pointer to TTFY_MAXP has been passed");
        return;
    }
    if (!*maxp)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_MAXP has been passed");
        return;
    }
    free(*maxp);
    *maxp = NULL;
}

Version16Dot16 TTFY_MAXPGetVersion(TTFY_MAXP *maxp)
{
    if (!maxp)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_maxp has been passed");
        return 0;
    }
    return maxp->version;
}

uint16 TTFY_MAXPGetNumGlyphs(TTFY_MAXP *maxp)
{
    if (!maxp)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_maxp has been passed");
        return 0;
    }
    return maxp->numGlyphs;
}

uint16 TTFY_MAXPGetMaxPoints(TTFY_MAXP *maxp)
{
    if (!maxp)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_maxp has been passed");
        return 0;
    }
    return maxp->maxPoints;
}

uint16 TTFY_MAXPGetMaxContours(TTFY_MAXP *maxp)
{
    if (!maxp)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_maxp has been passed");
        return 0;
    }
    return maxp->maxContours;
}

uint16 TTFY_MAXPGetMaxCompositePoints(TTFY_MAXP *maxp)
{
    if (!maxp)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_maxp has been passed");
        return 0;
    }
    return maxp->maxCompositePoints;
}

uint16 TTFY_MAXPGetMaxCompositeContours(TTFY_MAXP *maxp)
{
    if (!maxp)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_maxp has been passed");
        return 0;
    }
    return maxp->maxCompositeContours;
}

uint16 TTFY_MAXPGetMaxZones(TTFY_MAXP *maxp)
{
    if (!maxp)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_maxp has been passed");
        return 0;
    }
    return maxp->maxZones;
}

uint16 TTFY_MAXPGetMaxTwilightPoints(TTFY_MAXP *maxp)
{
    if (!maxp)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_maxp has been passed");
        return 0;
    }
    return maxp->maxTwilightPoints;
}

uint16 TTFY_MAXPGetMaxStorage(TTFY_MAXP *maxp)
{
    if (!maxp)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_maxp has been passed");
        return 0;
    }
    return maxp->maxStorage;
}

uint16 TTFY_MAXPGetMaxFunctionDefs(TTFY_MAXP *maxp)
{
    if (!maxp)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_maxp has been passed");
        return 0;
    }
    return maxp->maxFunctionDefs;
}

uint16 TTFY_MAXPGetMaxInstructionsDefs(TTFY_MAXP *maxp)
{
    if (!maxp)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_maxp has been passed");
        return 0;
    }
    return maxp->maxInstructionsDefs;
}

uint16 TTFY_MAXPGetMaxStackElements(TTFY_MAXP *maxp)
{
    if (!maxp)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_maxp has been passed");
        return 0;
    }
    return maxp->maxStackElements;
}

uint16 TTFY_MAXPGetMaxSizeOfInstructions(TTFY_MAXP *maxp)
{
    if (!maxp)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_maxp has been passed");
        return 0;
    }
    return maxp->maxSizeOfInstructions;
}

uint16 TTFY_MAXPGetMaxComponentElements(TTFY_MAXP *maxp)
{
    if (!maxp)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_maxp has been passed");
        return 0;
    }
    return maxp->maxComponentElements;
}

uint16 TTFY_MAXPGetMaxComponentDepth(TTFY_MAXP *maxp)
{
    if (!maxp)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_maxp has been passed");
        return 0;
    }
    return maxp->maxComponentDepth;
}