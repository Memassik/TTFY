#ifndef TTFY_NAME_TABLE_H
#define TTFY_NAME_TABLE_H
#include "TTFY_TableDirectory.h"

typedef struct TTFY_NAME TTFY_NAME;
typedef struct TTFY_NameRecord TTFY_NameRecord;
typedef struct TTFY_LangTagRecord TTFY_LangTagRecord;

TTFY_NAME *TTFY_NAMECreate(TTFY_Buffer *buffer, TTFY_TableDirectory *directory);
void TTFY_NAMEDestroy(TTFY_NAME **name);

uint16 TTFY_NAMEGetVersion(TTFY_NAME *name);
uint16 TTFY_NAMEGetCount(TTFY_NAME *name);
Offset16 TTFY_NAMEGetStorageOffset(TTFY_NAME *name);
TTFY_NameRecord *TTFY_NAMEGetNameRecord(TTFY_NAME *name, uint16 ID);
uint16 TTFY_NAMEGetLangTagCount(TTFY_NAME *name);
TTFY_LangTagRecord *TTFY_NAMEGetLangTagRecord(TTFY_NAME *name, uint16 ID);

#endif