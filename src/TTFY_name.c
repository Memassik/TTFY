#include <TTFY_name.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TTFY_NAME
{
    uint16 version;
    uint16 count;
    Offset16 storageOffset;
    TTFY_NameRecord *nameRecords;
    uint16 langTagCount;
    TTFY_LangTagRecord *langTagRecords;
    char **STRINGS;
};

struct TTFY_NameRecord
{
    uint16 platformID;
    uint16 encodingID;
    uint16 languageID;
    uint16 nameID;
    uint16 length;
    Offset16 stringOffset;
};

struct TTFY_LangTagRecord
{
    uint16 length;
    Offset16 langTagOffset;
};

TTFY_NAME *TTFY_NAMECreate(TTFY_Buffer *buffer, TTFY_TableDirectory *directory)
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

    TTFY_TableRecord *name_record = TTFY_TableDirectoryGetTableRecord(directory, TTFY_TABLE_NAME_NAME);
    if (!name_record)
    {
        fprintf(stderr, "%s\n", "Failed To Locate Name Table");
        return NULL;
    }

    TTFY_NAME *ret = malloc(sizeof(TTFY_NAME));
    if (!ret)
    {
        fprintf(stderr, "%s\n", "Failed To Allocate Memory For TTFY_NAME");
        return NULL;
    }

    TTFY_BufferSetPosition(buffer, TTFY_TableRecordGetOffset(name_record));
    ret->version = TTFY_BufferGetU16(buffer);
    ret->count = TTFY_BufferGetU16(buffer);
    if (!ret->count)
    {
        fprintf(stderr, "%s\n", "Invalid Count Number TTFY_NAME");
        free(ret);
        return NULL;
    }
    ret->storageOffset = TTFY_BufferGetOffset16(buffer);
    ret->nameRecords = malloc(sizeof(TTFY_NameRecord) * ret->count);
    if (!ret->nameRecords)
    {
        fprintf(stderr, "%s\n", "Failed To Allocate Memory For TTFY_NameRecords TTFY_NAME");
        free(ret);
        return NULL;
    }
    for (uint32 i = 0; i < ret->count; ++i)
    {
        ret->nameRecords[i].platformID = TTFY_BufferGetU16(buffer);
        ret->nameRecords[i].encodingID = TTFY_BufferGetU16(buffer);
        ret->nameRecords[i].languageID = TTFY_BufferGetU16(buffer);
        ret->nameRecords[i].nameID = TTFY_BufferGetU16(buffer);
        ret->nameRecords[i].length = TTFY_BufferGetU16(buffer);
        ret->nameRecords[i].stringOffset = TTFY_BufferGetOffset16(buffer);
    }

    if (ret->version == 0)
    {
    }
    else if (ret->version == 1)
    {
        ret->langTagCount = TTFY_BufferGetU16(buffer);
        if (!ret->langTagCount)
        {
            fprintf(stderr, "%s\n", "Invalid Lang Tag Count TTFY_NAME");
            free(ret);
            return NULL;
        }
        ret->langTagRecords = malloc(sizeof(TTFY_LangTagRecord) * ret->langTagCount);
        if (!ret->langTagRecords)
        {
            fprintf(stderr, "%s\n", "Failed To Allocate Memory For TTFY_LangTagRecords TTFY_NAME");
            free(ret);
            return NULL;
        }
        for (uint32 i = 0; i < ret->langTagCount; ++i)
        {
            ret->langTagRecords[i].length = TTFY_BufferGetU16(buffer);
            ret->langTagRecords[i].langTagOffset = TTFY_BufferGetOffset16(buffer);
        }
    }
    else
    {
        fprintf(stderr, "%s\n", "Invalid Version TTFY_NAME");
        free(ret);
        return NULL;
    }

    ret->STRINGS = malloc(sizeof(char *) * ret->count);
    if (!ret->STRINGS)
    {
        fprintf(stderr, "%s\n", "Failed To Allocate Memory For STRIGNS TTFY_NAME");
        free(ret);
        return NULL;
    }

    for (uint16 i = 0; i < ret->count; ++i)
    {
        ret->STRINGS[i] = malloc(ret->nameRecords[i].length + 1);
        if (!ret->STRINGS[i])
        {
            for (uint16 j = 0; j < i; ++j)
                free(ret->STRINGS[i]);
            fprintf(stderr, "%s\n", "Failed To Allocate Memory For STRIGNS TTFY_NAME");
            free(ret);
            return NULL;
        }
    }

    for (uint16 i = 0; i < ret->count; ++i)
    {
        TTFY_BufferSetPosition(buffer, TTFY_TableRecordGetOffset(name_record) + ret->storageOffset + ret->nameRecords[i].stringOffset);
        memcpy(ret->STRINGS[i], TTFY_BufferGetAddressUnderPos(buffer), ret->nameRecords[i].length);
        ret->STRINGS[i][ret->nameRecords[i].length] = '\0';
    }
    return ret;
}

void TTFY_NAMEDestroy(TTFY_NAME **name)
{
    if (!name)
    {
        fprintf(stderr, "%s\n", "Invalid Pointer to TTFY_NAME has been passed");
        return;
    }
    if (!*name)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_NAME has been passed");
        return;
    }
    if ((*name)->nameRecords)
        free((*name)->nameRecords);
    if ((*name)->version == 1)
        if ((*name)->langTagRecords)
            free((*name)->langTagRecords);

    for (uint16 i = 0; i < (*name)->count; ++i)
    {
        free((*name)->STRINGS[i]);
    }
    free((*name)->STRINGS);
    free(*name);
    *name = NULL;
}

uint16 TTFY_NAMEGetVersion(TTFY_NAME *name)
{
    if (!name)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_NAME has been passed");
        return 0;
    }
    return name->version;
}

uint16 TTFY_NAMEGetCount(TTFY_NAME *name)
{
    if (!name)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_NAME has been passed");
        return 0;
    }
    return name->count;
}

Offset16 TTFY_NAMEGetStorageOffset(TTFY_NAME *name)
{
    if (!name)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_NAME has been passed");
        return 0;
    }
    return name->storageOffset;
}

TTFY_NameRecord *TTFY_NAMEGetNameRecord(TTFY_NAME *name, uint16 ID)
{
    if (!name)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_NAME has been passed");
        return NULL;
    }
    if (ID >= name->count)
    {
        fprintf(stderr, "%s\n", "Invalid ID has been passed");
        return NULL;
    }
    return &name->nameRecords[ID];
}

uint16 TTFY_NAMEGetLangTagCount(TTFY_NAME *name)
{
    if (!name)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_NAME has been passed");
        return 0;
    }

    if (name->version == 0)
    {
        fprintf(stderr, "%s\n", "Font Doesnt Support LangTagRecords");
        return 0;
    }
    return name->langTagCount;
}

TTFY_LangTagRecord *TTFY_NAMEGetLangTagRecord(TTFY_NAME *name, uint16 ID)
{
    if (!name)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_NAME has been passed");
        return 0;
    }

    if (name->version == 0)
    {
        fprintf(stderr, "%s\n", "Font Doesnt Support LangTagRecords");
        return 0;
    }

    if (ID >= name->langTagCount)
    {
        fprintf(stderr, "%s\n", "Invalid ID has been passed");
        return 0;
    }

    return &name->langTagRecords[ID];
}