#ifndef TTFY_NAME_TABLE_H
#define TTFY_NAME_TABLE_H
#include "TTFY_TableDirectory.h"

typedef struct TTFY_NAME TTFY_NAME;
typedef struct TTFY_NameRecord TTFY_NameRecord;
typedef struct TTFY_LangTagRecord TTFY_LangTagRecord;

TTFY_API TTFY_NAME *TTFY_NAMECreate(TTFY_Buffer *buffer, TTFY_TableDirectory *directory);
TTFY_API void TTFY_NAMEDestroy(TTFY_NAME **name);

TTFY_API uint16 TTFY_NAMEGetVersion(TTFY_NAME *name);
TTFY_API uint16 TTFY_NAMEGetCount(TTFY_NAME *name);
TTFY_API Offset16 TTFY_NAMEGetStorageOffset(TTFY_NAME *name);
TTFY_API TTFY_NameRecord *TTFY_NAMEGetNameRecord(TTFY_NAME *name, uint16 ID);
TTFY_API uint16 TTFY_NAMEGetLangTagCount(TTFY_NAME *name);
TTFY_API TTFY_LangTagRecord *TTFY_NAMEGetLangTagRecord(TTFY_NAME *name, uint16 ID);

#endif