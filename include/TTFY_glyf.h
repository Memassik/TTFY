#ifndef TTFY_GLYF_TABLE_H
#define TTFY_GLYF_TABLE_H

#include "TTFY_loca.h"

typedef struct TTFY_GLYF TTFY_GLYF;
typedef struct TTFY_GLYFHeader TTFY_GLYFHeader;
typedef struct TTFY_GLYFSimple TTFY_GLYFSimple;
typedef struct TTFY_GLYFComposite TTFY_GLYFComposite;

TTFY_API TTFY_GLYF *TTFY_GLYFCreate(TTFY_Buffer *buffer, TTFY_TableDirectory *directory, TTFY_MAXP *maxp, TTFY_LOCA *loca);
TTFY_API void TTFY_GLYFDestroy(TTFY_GLYF **glyf);

TTFY_API TTFY_GLYFSimple *TTFY_GLYFGetSimpleGlyf(TTFY_GLYF *glyf, uint16 ID);
TTFY_API TTFY_GLYFComposite *TTFY_GLYFGetCompositeGlyf(TTFY_GLYF *glyf, uint16 ID);

TTFY_API TTFY_GLYFHeader *TTFY_GLYFHeaderCreate(TTFY_Buffer *buffer, TTFY_TableDirectory *directory);
TTFY_API void TTFY_GLYFHeaderDestroy(TTFY_GLYFHeader **glyf_header);
TTFY_API int16 TTFY_GLYFHeaderGetNumOfCountours(TTFY_GLYFHeader *glyf_header);
TTFY_API int16 TTFY_GLYFHeaderGetXMin(TTFY_GLYFHeader *glyf_header);
TTFY_API int16 TTFY_GLYFHeaderGetYMin(TTFY_GLYFHeader *glyf_header);
TTFY_API int16 TTFY_GLYFHeaderGetXMax(TTFY_GLYFHeader *glyf_header);
TTFY_API int16 TTFY_GLYFHeaderGetYMax(TTFY_GLYFHeader *glyf_header);

TTFY_API TTFY_GLYFSimple *TTFY_GLYFSimpleCreate(TTFY_Buffer *buffer, TTFY_GLYFHeader *header);
TTFY_API void TTFY_GLYFSimpleDestroy(TTFY_GLYFSimple **simple_glyf);
TTFY_API uint16 TTFY_GLYFSimpleGetEndPtOfCountour(TTFY_GLYFSimple *simple_glyf, uint16 ID);
TTFY_API uint16 TTFY_GLYFSimpleGetInstructionLength(TTFY_GLYFSimple *simple_glyf);
TTFY_API uint8 TTFY_GLYFSimpleGetInstruction(TTFY_GLYFSimple *simple_glyf, uint16 ID);
TTFY_API uint8 TTFY_GLYFSimpleGetFlags(TTFY_GLYFSimple *simple_glyf, uint16 ID);
TTFY_API int16 TTFY_GLYFSimpleGetXCoordinate(TTFY_GLYFSimple *simple_glyf, uint16 ID);
TTFY_API int16 TTFY_GLYFSimpleGetYCoordinate(TTFY_GLYFSimple *simple_glyf, uint16 ID);

TTFY_API TTFY_GLYFComposite *TTFY_GLYFCompositeCreate(TTFY_Buffer *buffer, TTFY_GLYFHeader *header, TTFY_MAXP *maxp);
TTFY_API void TTFY_GLYFCompositeDestroy(TTFY_GLYFComposite **composite_glyf);
TTFY_API uint16 TTFY_GLYFCompositeGetFlags(TTFY_GLYFComposite *composite_glyf);
TTFY_API uint16 TTFY_GLYFCompositeGetGlyphIndex(TTFY_GLYFComposite *composite_glyf);
TTFY_API int32 TTFY_GLYFCompositeGetArgument1(TTFY_GLYFComposite *composite_glyf);
TTFY_API int32 TTFY_GLYFCompositeGetArgument2(TTFY_GLYFComposite *composite_glyf);

TTFY_API TTFY_GLYFSimple *TTFY_GLYFCompositeToGLYFSimple(TTFY_GLYFSimple *simple_glyf);

#endif