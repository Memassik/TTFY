#include <TTFY_loca.h>
#include <stdio.h>
#include <stdlib.h>

struct TTFY_LOCA
{
    Offset32 *offsets;
    uint32 numGlyphs;
};

TTFY_LOCA *TTFY_LOCACreate(TTFY_Buffer *buffer, TTFY_TableDirectory *directory, TTFY_HEAD *head, TTFY_MAXP *maxp)
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
    if (!head)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_HEAD has been passed");
        return NULL;
    }
    if (!maxp)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_MAXP has been passed");
        return NULL;
    }

    TTFY_TableRecord *loca_record = TTFY_TableDirectoryGetTableRecord(directory, TTFY_TABLE_NAME_LOCA);
    if (!loca_record)
    {
        fprintf(stderr, "%s\n", "Failed To Locate TTFY_LOCA");
        return NULL;
    }

    TTFY_LOCA *ret = malloc(sizeof(TTFY_LOCA));
    if (!ret)
    {
        fprintf(stderr, "%s\n", "Failed To Allocate Memory for TTFY_LOCA");
        return NULL;
    }

    ret->numGlyphs = TTFY_MAXPGetNumGlyphs(maxp) + 1;
    ret->offsets = malloc(sizeof(Offset32) * ret->numGlyphs);
    if (!ret->offsets)
    {
        fprintf(stderr, "%s\n", "Failed To Allocate Memory for offsets TTFY_LOCA");
        free(ret);
        return NULL;
    }
    TTFY_BufferSetPosition(buffer, TTFY_TableRecordGetOffset(loca_record));
    int isLong = TTFY_HEADGetIndexToLocFormat(head);
    for (uint32 i = 0; i < ret->numGlyphs; ++i)
    {
        if (isLong)
            ret->offsets[i] = TTFY_BufferGetOffset32(buffer);
        else
            ret->offsets[i] = TTFY_BufferGetOffset16(buffer);
    }
    return ret;
}

void TTFY_LOCADestroy(TTFY_LOCA **loca)
{
    if (!loca)
    {
        fprintf(stderr, "%s\n", "Invalid Pointer to TTFY_LOCA has been passed");
        return;
    }
    if (!*loca)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_LOCA has been passed");
        return;
    }
    if ((*loca)->offsets)
        free((*loca)->offsets);
    free(*loca);
    *loca = NULL;
}

Offset32 TTFY_LOCAGetOffset(TTFY_LOCA *loca, uint16 ID)
{
    if (!loca)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_LOCA has been passed");
        return 0;
    }
    if (ID >= loca->numGlyphs)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_LOCA ID has been passed");
        return 0;
    }
    return loca->offsets[ID + 1] - loca->offsets[ID];
}