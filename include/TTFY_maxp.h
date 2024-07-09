#ifndef TTFY_MAXP_TABLE_H
#define TTFY_MAXP_TABLE_H
#include <TTFY_TableDirectory.h>

typedef struct TTFY_MAXP TTFY_MAXP;

TTFY_MAXP *TTFY_MAXPCreate(TTFY_Buffer *buffer, TTFY_TableDirectory *directory);
void TTFY_MAXPDestroy(TTFY_MAXP **maxp);

Version16Dot16 TTFY_MAXPGetVersion(TTFY_MAXP *maxp);
uint16 TTFY_MAXPGetNumGlyphs(TTFY_MAXP *maxp);
uint16 TTFY_MAXPGetMaxPoints(TTFY_MAXP *maxp);
uint16 TTFY_MAXPGetMaxContours(TTFY_MAXP *maxp);
uint16 TTFY_MAXPGetMaxCompositePoints(TTFY_MAXP *maxp);
uint16 TTFY_MAXPGetMaxCompositeContours(TTFY_MAXP *maxp);
uint16 TTFY_MAXPGetMaxZones(TTFY_MAXP *maxp);
uint16 TTFY_MAXPGetMaxTwilightPoints(TTFY_MAXP *maxp);
uint16 TTFY_MAXPGetMaxStorage(TTFY_MAXP *maxp);
uint16 TTFY_MAXPGetMaxFunctionDefs(TTFY_MAXP *maxp);
uint16 TTFY_MAXPGetMaxInstructionsDefs(TTFY_MAXP *maxp);
uint16 TTFY_MAXPGetMaxStackElements(TTFY_MAXP *maxp);
uint16 TTFY_MAXPGetMaxSizeOfInstructions(TTFY_MAXP *maxp);
uint16 TTFY_MAXPGetMaxComponentElements(TTFY_MAXP *maxp);
uint16 TTFY_MAXPGetMaxComponentDepth(TTFY_MAXP *maxp);

#endif