#ifndef TTFY_TABLE_DIRECTORY_H
#define TTFY_TABLE_DIRECTORY_H

#include "TTFY_buffer.h"
#include "TTFY_TABLE_NAMES.h"

typedef struct TTFY_TableDirectory TTFY_TableDirectory;
typedef struct TTFY_TableRecord TTFY_TableRecord;

TTFY_API TTFY_TableDirectory *TTFY_TableDirectoryCreate(TTFY_Buffer *buffer);
TTFY_API void TTFY_TableDirectoryDestroy(TTFY_TableDirectory **tableDirectory);
TTFY_API uint32 TTFY_TableDirectoryGetSFNTVersion(TTFY_TableDirectory *tableDirectory);
TTFY_API uint16 TTFY_TableDirectoryGetNumTables(TTFY_TableDirectory *tableDirectory);
TTFY_API uint16 TTFY_TableDirectoryGetSearchRange(TTFY_TableDirectory *tableDirectory);
TTFY_API uint16 TTFY_TableDirectoryGetEntrySelector(TTFY_TableDirectory *tableDirectory);
TTFY_API uint16 TTFY_TableDirectoryGetRangeShift(TTFY_TableDirectory *tableDirectory);
TTFY_API TTFY_TableRecord *TTFY_TableDirectoryGetTableRecord(TTFY_TableDirectory *tableDirectory, TTFY_TableNameEnum tableName);
TTFY_API Tag TTFY_TableRecordGetTableTag(TTFY_TableRecord *record);
TTFY_API uint32 TTFY_TableRecordGetChecksum(TTFY_TableRecord *record);
TTFY_API Offset32 TTFY_TableRecordGetOffset(TTFY_TableRecord *record);
TTFY_API uint32 TTFY_TableRecordGetLength(TTFY_TableRecord *record);

#endif