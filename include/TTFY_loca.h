#ifndef TTFY_LOCA_TABLE_H
#define TTFY_LOCA_TABLE_H

#include "TTFY_head.h"
#include "TTFY_maxp.h"

typedef struct TTFY_LOCA TTFY_LOCA;

TTFY_LOCA *TTFY_LOCACreate(TTFY_Buffer *buffer, TTFY_TableDirectory *directory, TTFY_HEAD *head, TTFY_MAXP *maxp);
void TTFY_LOCADestroy(TTFY_LOCA **loca);

Offset32 TTFY_LOCAGetOffset(TTFY_LOCA *loca, uint16 ID);

#endif