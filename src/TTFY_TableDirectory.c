#include <TTFY_TableDirectory.h>
#include <stdio.h>
#include <stdlib.h>

struct TTFY_TableDirectory
{
    uint32 sfntVersion;
    uint16 numTables;
    uint16 searchRange;
    uint16 entrySelector;
    uint16 rangeShift;
    TTFY_TableRecord *tableRecords;
};

struct TTFY_TableRecord
{
    Tag tableTag;
    uint32 checksum;
    Offset32 offset;
    uint32 length;
};

void TTFY_TableRecordParseTableRecord(TTFY_Buffer *buffer, TTFY_TableRecord *record)
{
    if (!buffer)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_Buffer has been passed");
        return;
    }
    if (!record)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_TableRecord has been passed");
        return;
    }
    record->tableTag = malloc(5);
    if (!record->tableTag)
    {
        fprintf(stderr, "%s\n", "Failed To Allocate Memory For TableRecord Tag");
        return;
    }
    record->tableTag[0] = TTFY_BufferGetU8(buffer);
    record->tableTag[1] = TTFY_BufferGetU8(buffer);
    record->tableTag[2] = TTFY_BufferGetU8(buffer);
    record->tableTag[3] = TTFY_BufferGetU8(buffer);
    record->tableTag[4] = '\0';
    record->checksum = TTFY_BufferGetU32(buffer);
    record->offset = TTFY_BufferGetOffset32(buffer);
    record->length = TTFY_BufferGetU32(buffer);
}

TTFY_TableRecord *TTFY_TableDirectoryFindTable(TTFY_TableDirectory *tableDirectory, const char *tableName)
{
    if (!tableDirectory)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_TableDirectory has been passed");
        return NULL;
    }
    if (!tableName)
    {
        fprintf(stderr, "%s\n", "Invalid Table Name has been passed");
        return NULL;
    }
    for (uint32 i = 0; i < tableDirectory->numTables; ++i)
    {
        TTFY_TableRecord *record = &tableDirectory->tableRecords[i];
        if (record->tableTag[0] == tableName[0] &&
            record->tableTag[1] == tableName[1] &&
            record->tableTag[2] == tableName[2] &&
            record->tableTag[3] == tableName[3])
        {
            return record;
        }
    }
    return NULL;
}

TTFY_TableDirectory *TTFY_TableDirectoryCreate(TTFY_Buffer *buffer)
{
    if (!buffer)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_Buffer has been passed");
        return NULL;
    }
    TTFY_BufferSetPosition(buffer, 0);
    TTFY_TableDirectory *ret = malloc(sizeof(TTFY_TableDirectory));
    if (!ret)
    {
        fprintf(stderr, "%s\n", "Failed To Allocate Memory For TTFY_TableDirectory");
        return NULL;
    }
    ret->sfntVersion = TTFY_BufferGetU32(buffer);
    ret->numTables = TTFY_BufferGetU16(buffer);
    ret->searchRange = TTFY_BufferGetU16(buffer);
    ret->entrySelector = TTFY_BufferGetU16(buffer);
    ret->rangeShift = TTFY_BufferGetU16(buffer);
    if (!ret->numTables)
    {
        fprintf(stderr, "%s\n", "TTFY_TableDirectory number of table is 0");
        free(ret);
        return NULL;
    }

    ret->tableRecords = malloc(sizeof(TTFY_TableRecord) * ret->numTables);
    if (!ret->tableRecords)
    {
        fprintf(stderr, "%s\n", "Failed to Allocate Memory For TTFY_TableRecords");
        free(ret);
        return NULL;
    }
    for (uint32 i = 0; i < ret->numTables; ++i)
    {
        TTFY_TableRecordParseTableRecord(buffer, &ret->tableRecords[i]);
    }
    return ret;
}

void TTFY_TableDirectoryDestroy(TTFY_TableDirectory **tableDirectory)
{
    if (!tableDirectory)
    {
        fprintf(stderr, "%s\n", "Invalid Pointer to TTFY_TableDirectory has been passed");
        return;
    }
    if (!*tableDirectory)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_TableDirectory has been passed");
        return;
    }
    if ((*tableDirectory)->numTables)
    {
        for (uint32 i = 0; i < (*tableDirectory)->numTables; ++i)
        {
            free((*tableDirectory)->tableRecords[i].tableTag);
        }
        free((*tableDirectory)->tableRecords);
    }
    free(*tableDirectory);
    *tableDirectory = NULL;
}

uint32 TTFY_TableDirectoryGetSFNTVersion(TTFY_TableDirectory *tableDirectory)
{
    if (!tableDirectory)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_TableDirectory has been passed");
        return 0;
    }
    return tableDirectory->sfntVersion;
}

uint16 TTFY_TableDirectoryGetNumTables(TTFY_TableDirectory *tableDirectory)
{
    if (!tableDirectory)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_TableDirectory has been passed");
        return 0;
    }
    return tableDirectory->numTables;
}

uint16 TTFY_TableDirectoryGetSearchRange(TTFY_TableDirectory *tableDirectory)
{
    if (!tableDirectory)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_TableDirectory has been passed");
        return 0;
    }
    return tableDirectory->searchRange;
}

uint16 TTFY_TableDirectoryGetEntrySelector(TTFY_TableDirectory *tableDirectory)
{
    if (!tableDirectory)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_TableDirectory has been passed");
        return 0;
    }
    return tableDirectory->entrySelector;
}

uint16 TTFY_TableDirectoryGetRangeShift(TTFY_TableDirectory *tableDirectory)
{
    if (!tableDirectory)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_TableDirectory has been passed");
        return 0;
    }
    return tableDirectory->rangeShift;
}

TTFY_TableRecord *TTFY_TableDirectoryGetTableRecord(TTFY_TableDirectory *tableDirectory, TTFY_TableNameEnum tableName)
{
    if (!tableDirectory)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_TableDirectory has been passed");
        return NULL;
    }

    if (tableName == TTFY_TABLE_NAME_None)
    {
        fprintf(stderr, "%s\n", "TTFY_TableNameEnum is NONE");
        return NULL;
    }
    TTFY_TableRecord *record = NULL;
    switch (tableName)
    {
    case TTFY_TABLE_NAME_HEAD:
        record = TTFY_TableDirectoryFindTable(tableDirectory, "head");
        break;
    case TTFY_TABLE_NAME_HHEA:
        record = TTFY_TableDirectoryFindTable(tableDirectory, "hhea");
        break;
    default:
        return NULL;
        break;
    }

    if (!record)
    {
        fprintf(stderr, "%s\n", "Required Table Record Not found!");
        return NULL;
    }
    return record;
}

Tag TTFY_TableRecordGetTableTag(TTFY_TableRecord *record)
{
    if (!record)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_TableRecord has been passed");
        return 0;
    }
    return record->tableTag;
}

uint32 TTFY_TableRecordGetChecksum(TTFY_TableRecord *record)
{
    if (!record)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_TableRecord has been passed");
        return 0;
    }
    return record->checksum;
}

Offset32 TTFY_TableRecordGetOffset(TTFY_TableRecord *record)
{
    if (!record)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_TableRecord has been passed");
        return 0;
    }
    return record->offset;
}

uint32 TTFY_TableRecordGetLength(TTFY_TableRecord *record)
{
    if (!record)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_TableRecord has been passed");
        return 0;
    }
    return record->length;
}