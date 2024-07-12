#include <TTFY_glyf.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    SIMPLE,
    COMPOSITE
} GLYPH_TYPE;

#define ON_CURVE_POINT 0b00000001
#define X_SHORT_VECTOR 0b00000010
#define Y_SHORT_VECTOR 0b00000100
#define REPEAT_FLAG 0b00001000
#define X_IS_SAME_OR_POSITIVE_X_SHORT_VECTOR 0b00010000
#define Y_IS_SAME_OR_POSITIVE_Y_SHORT_VECTOR 0b00100000
#define OVERLAP_SIMPLE 0b01000000

#define ARG_1_AND_2_ARE_WORDS 0x0001
#define ARGS_ARE_XY_VALUES 0x0002
#define ROUND_XY_TO_GRID 0x0004
#define WE_HAVE_A_SCALE 0x0008
#define MORE_COMPONENTS 0x0020
#define WE_HAVE_AN_X_AND_Y_SCALE 0x0040
#define WE_HAVE_A_TWO_BY_TWO 0x0080
#define WE_HAVE_INSTRUCTIONS 0x0100
#define USE_MY_METRICS 0x0200
#define OVERLAP_COMPOUND 0x0400
#define SCALED_COMPONENT_OFFSET 0x0800
#define UNSCALED_COMPONENT_OFFSET 0x1000

struct TTFY_GLYF
{
    TTFY_GLYFHeader **headers;
    TTFY_GLYFSimple **simple_glyfs;
    TTFY_GLYFComposite **composite_glyfs;
    uint16 numOfGlyps;
    uint16 simple_glyfsSize;
    uint16 composite_glyfsSize;
};

struct TTFY_GLYFHeader
{
    int16 numberOfContours;
    int16 xMin;
    int16 yMin;
    int16 xMax;
    int16 yMax;
    uint16 GLYPH_ID;
    GLYPH_TYPE TYPE;
};

struct TTFY_GLYFSimple
{
    uint16 HEADER_ID;
    int16 numberOfContours;
    uint16 *endPtsOfCountours;
    uint16 instructionLength;
    uint8 *instructions;
    uint16 flagsLength;
    uint8 *flags;
    int16 *xCoordinates;
    int16 *yCoordinates;
};

struct TTFY_GLYFComposite
{
    uint16 HEADER_ID;
    uint16 flags;
    uint16 glyphIndex;
    int32 argument1;
    int32 argument2;
    F2DOT14 xscale;
    F2DOT14 yscale;
    F2DOT14 scale01;
    F2DOT14 scale10;
    uint16 instructionLength;
    uint8 *intsuctions;
    TTFY_GLYFComposite *children;
    uint16 childernLength;
    uint16 MaxComponentElements;
    uint16 MaxComponentDepth;
};

TTFY_GLYFComposite *TTFY_GLYFCompositeCreate(TTFY_Buffer *buffer, TTFY_GLYFHeader *header, TTFY_MAXP *maxp)
{
    if (!buffer)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_Buffer has been passed");
        return NULL;
    }
    if (!header)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_GLYFHeader has been passed");
        return NULL;
    }
    if (!maxp)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_MAXP has been passed");
        return NULL;
    }

    TTFY_GLYFComposite *ret = malloc(sizeof(TTFY_GLYFComposite));
    if (!ret)
    {
        fprintf(stderr, "%s\n", "Failed To Allocate Memory For TTFY_GLYFComposite");
        return NULL;
    }
    ret->childernLength = 0;
    ret->MaxComponentElements = TTFY_MAXPGetMaxComponentElements(maxp);
    ret->MaxComponentDepth = TTFY_MAXPGetMaxComponentDepth(maxp);
    ret->HEADER_ID = 0;

    if (!ret->MaxComponentElements)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_TTFY_GLYFComposite MaxComponentElements has been passed");
        free(ret);
        return NULL;
    }

    ret->children = malloc(sizeof(TTFY_GLYFComposite) * ret->MaxComponentElements);
    if (!ret->children)
    {
        fprintf(stderr, "%s\n", "Failed To Allocate Memory For TTFY_GLYFComposite Children");
        free(ret);
        return NULL;
    }

    TTFY_GLYFComposite *this = ret;
    while (1)
    {
        this->flags = TTFY_BufferGetU16(buffer);
        this->glyphIndex = TTFY_BufferGetU16(buffer);
        if (this->flags & ARG_1_AND_2_ARE_WORDS)
        {
            if (this->flags & ARGS_ARE_XY_VALUES)
            {
                this->argument1 = TTFY_BufferGetFWord(buffer);
                this->argument2 = TTFY_BufferGetFWord(buffer);
            }
            else
            {
                this->argument1 = TTFY_BufferGetUFWord(buffer);
                this->argument2 = TTFY_BufferGetUFWord(buffer);
            }
        }
        else
        {
            if (this->flags & ARGS_ARE_XY_VALUES)
            {
                this->argument1 = TTFY_BufferGetI8(buffer);
                this->argument2 = TTFY_BufferGetI8(buffer);
            }
            else
            {
                this->argument1 = TTFY_BufferGetU8(buffer);
                this->argument2 = TTFY_BufferGetU8(buffer);
            }
        }
        if (this->flags & WE_HAVE_A_SCALE)
        {
            this->xscale = TTFY_BufferGetF2DOT14(buffer);
        }
        else if (this->flags & WE_HAVE_AN_X_AND_Y_SCALE)
        {
            this->xscale = TTFY_BufferGetF2DOT14(buffer);
            this->yscale = TTFY_BufferGetF2DOT14(buffer);
        }
        else if (this->flags & WE_HAVE_A_TWO_BY_TWO)
        {
            this->xscale = TTFY_BufferGetF2DOT14(buffer);
            this->scale01 = TTFY_BufferGetF2DOT14(buffer);
            this->scale10 = TTFY_BufferGetF2DOT14(buffer);
            this->yscale = TTFY_BufferGetF2DOT14(buffer);
        }

        if (this->flags & MORE_COMPONENTS)
        {
            this = &ret->children[ret->childernLength++];
        }
        else
        {
            break;
        }
    }
    if (ret->flags & WE_HAVE_INSTRUCTIONS)
    {
        ret->instructionLength = TTFY_BufferGetU16(buffer);
        if (!ret->instructionLength)
        {
            fprintf(stderr, "%s\n", "Invalid instructtion Length TTFY_GLYFComposite Children");
            free(ret->children);
            free(ret);
            return NULL;
        }
        ret->intsuctions = malloc(sizeof(uint8) * ret->instructionLength);
        if (!ret->intsuctions)
        {
            fprintf(stderr, "%s\n", "Failed To Allocate Memory For TTFY_GLYFComposite Children");
            free(ret->children);
            free(ret);
            return NULL;
        }
        for (uint16 i = 0; i < ret->instructionLength; ++i)
        {
            ret->intsuctions[i] = TTFY_BufferGetU8(buffer);
        }
    }
    else
    {
        ret->instructionLength = 0;
    }
    return ret;
}

void TTFY_GLYFCompositeDestroy(TTFY_GLYFComposite **composite_glyf)
{
    if (!composite_glyf)
    {
        fprintf(stderr, "%s\n", "Invalid Pointer to TTFY_TTFYComposite has been passed");
        return;
    }
    if (!*composite_glyf)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_GLYFComposite has been passed");
        return;
    }
    free((*composite_glyf)->children);
    if ((*composite_glyf)->instructionLength)
        free((*composite_glyf)->intsuctions);
    free(*composite_glyf);
    *composite_glyf = NULL;
}

uint16 TTFY_GLYFCompositeGetFlags(TTFY_GLYFComposite *composite_glyf)
{
    if (!composite_glyf)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_GLYFComposite has been passed");
        return 0;
    }

    return composite_glyf->flags;
}

uint16 TTFY_GLYFCompositeGetGlyphIndex(TTFY_GLYFComposite *composite_glyf)
{
    if (!composite_glyf)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_GLYFComposite has been passed");
        return 0;
    }
    return composite_glyf->glyphIndex;
}

int32 TTFY_GLYFCompositeGetArgument1(TTFY_GLYFComposite *composite_glyf)
{
    if (!composite_glyf)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_GLYFComposite has been passed");
        return 0;
    }
    return composite_glyf->argument1;
}

int32 TTFY_GLYFCompositeGetArgument2(TTFY_GLYFComposite *composite_glyf)
{
    if (!composite_glyf)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_GLYFComposite has been passed");
        return 0;
    }
    return composite_glyf->argument2;
}

TTFY_GLYFSimple *TTFY_GLYFCompositeToGLYFSimple(TTFY_GLYFSimple *simple_glyf)
{
    assert(0 && "NOT IMPL");
    return NULL;
}

TTFY_GLYF *TTFY_GLYFCreate(TTFY_Buffer *buffer, TTFY_TableDirectory *directory, TTFY_MAXP *maxp, TTFY_LOCA *loca)
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
    if (!loca)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_LOCA has been passed");
        return NULL;
    }
    if (!maxp)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_MAXP has been passed");
        return NULL;
    }

    TTFY_TableRecord *glyf_record = TTFY_TableDirectoryGetTableRecord(directory, TTFY_TABLE_NAME_GLYF);
    if (!glyf_record)
    {
        fprintf(stderr, "%s\n", "Failed To Locate TTFY_GLYF");
        return NULL;
    }

    TTFY_GLYF *ret = malloc(sizeof(TTFY_GLYF));
    if (!ret)
    {
        fprintf(stderr, "%s\n", "Failed To Allocate Memory For TTFY_GLYF");
        return NULL;
    }

    ret->numOfGlyps = TTFY_MAXPGetNumGlyphs(maxp);
    if (!ret->numOfGlyps)
    {
        fprintf(stderr, "%s\n", "Invalid Num Of Glyphs For TTFY_GLYF");
        free(ret);
        return NULL;
    }

    ret->headers = malloc(sizeof(TTFY_GLYFHeader *) * ret->numOfGlyps);
    if (!ret->headers)
    {
        fprintf(stderr, "%s\n", "Failed To Allocate Memory For Headers TTFY_GLYF");
        free(ret);
        return NULL;
    }

    ret->simple_glyfs = malloc(sizeof(TTFY_GLYFSimple *) * ret->numOfGlyps);
    if (!ret->simple_glyfs)
    {
        fprintf(stderr, "%s\n", "Failed To Allocate Memory For Simple Glyphs TTFY_GLYF");
        free(ret->headers);
        free(ret);
        return NULL;
    }

    ret->composite_glyfs = malloc(sizeof(TTFY_GLYFComposite *) * ret->numOfGlyps);
    if (!ret->simple_glyfs)
    {
        fprintf(stderr, "%s\n", "Failed To Allocate Memory For Composite Glyphs TTFY_GLYF");
        free(ret->headers);
        free(ret->simple_glyfs);
        free(ret);
        return NULL;
    }

    ret->simple_glyfsSize = 0;
    ret->composite_glyfsSize = 0;

    TTFY_BufferSetPosition(buffer, TTFY_TableRecordGetOffset(glyf_record));
    uint64_t headerPos = TTFY_BufferGetPosition(buffer);
    for (uint16 i = 0; i < ret->numOfGlyps; ++i)
    {
        TTFY_BufferSetPosition(buffer, headerPos);
        TTFY_GLYFHeader *header = TTFY_GLYFHeaderCreate(buffer, directory);
        if (!header)
        {
            fprintf(stderr, "%s\n", "Failed To Create GLYF HEADER");
            for (uint16 j = 0; j < ret->simple_glyfsSize; ++j)
            {
                TTFY_GLYFSimpleDestroy(&ret->simple_glyfs[j]);
            }
            for (uint16 j = 0; j < ret->composite_glyfsSize; ++j)
            {
                TTFY_GLYFCompositeDestroy(&ret->composite_glyfs[j]);
            }
            for (uint16 j = 0; j < i; ++j)
            {
                TTFY_GLYFHeaderDestroy(&ret->headers[j]);
            }
            free(ret->composite_glyfs);
            free(ret->simple_glyfs);
            free(ret->headers);
            free(ret);
            return NULL;
        }
        ret->headers[i] = header;
        void *glyf = NULL;
        if (ret->headers[i]->numberOfContours == -1)
        {
            glyf = TTFY_GLYFCompositeCreate(buffer, ret->headers[i], maxp);
            if (!glyf)
            {
                fprintf(stderr, "%s\n", "Failed To Create GLYF");
                for (uint16 j = 0; j < ret->simple_glyfsSize; ++j)
                {
                    TTFY_GLYFSimpleDestroy(&ret->simple_glyfs[j]);
                }
                for (uint16 j = 0; j < ret->composite_glyfsSize; ++j)
                {
                    TTFY_GLYFCompositeDestroy(&ret->composite_glyfs[j]);
                }
                for (uint16 j = 0; j < i; ++j)
                {
                    TTFY_GLYFHeaderDestroy(&ret->headers[j]);
                }
                free(ret->composite_glyfs);
                free(ret->simple_glyfs);
                free(ret->headers);
                free(ret);
                return NULL;
            }
            ret->composite_glyfs[ret->composite_glyfsSize] = glyf;
            ret->composite_glyfs[ret->composite_glyfsSize]->HEADER_ID = i;
            ret->headers[i]->GLYPH_ID = ret->composite_glyfsSize;
            ret->headers[i]->TYPE = COMPOSITE;
            ret->composite_glyfsSize++;
        }
        else
        {
            glyf = TTFY_GLYFSimpleCreate(buffer, ret->headers[i]);
            if (!glyf)
            {
                fprintf(stderr, "%s\n", "Failed To Create GLYF");
                for (uint16 j = 0; j < ret->simple_glyfsSize; ++j)
                {
                    TTFY_GLYFSimpleDestroy(&ret->simple_glyfs[j]);
                }
                for (uint16 j = 0; j < ret->composite_glyfsSize; ++j)
                {
                    TTFY_GLYFCompositeDestroy(&ret->composite_glyfs[j]);
                }
                for (uint16 j = 0; j < i; ++j)
                {
                    TTFY_GLYFHeaderDestroy(&ret->headers[j]);
                }
                free(ret->composite_glyfs);
                free(ret->simple_glyfs);
                free(ret->headers);
                free(ret);
                return NULL;
            }
            ret->simple_glyfs[ret->simple_glyfsSize] = glyf;
            ret->simple_glyfs[ret->simple_glyfsSize]->HEADER_ID = i;
            ret->headers[i]->GLYPH_ID = ret->simple_glyfsSize;
            ret->headers[i]->TYPE = SIMPLE;
            ret->simple_glyfsSize++;
        }
        headerPos += TTFY_LOCAGetOffset(loca, i);
    }
    return ret;
}

void TTFY_GLYFDestroy(TTFY_GLYF **glyf)
{
    if (!glyf)
    {
        fprintf(stderr, "%s\n", "Invalid Pointer to TTFY_GLYF has been passed");
        return;
    }
    if (!*glyf)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_GLYF has been passed");
        return;
    }

    if ((*glyf)->simple_glyfs)
        for (uint16 j = 0; j < (*glyf)->simple_glyfsSize; ++j)
        {
            TTFY_GLYFSimpleDestroy(&(*glyf)->simple_glyfs[j]);
        }
    if ((*glyf)->composite_glyfs)
        for (uint16 j = 0; j < (*glyf)->composite_glyfsSize; ++j)
        {
            TTFY_GLYFCompositeDestroy(&(*glyf)->composite_glyfs[j]);
        }
    if ((*glyf)->headers)
        for (uint16 j = 0; j < (*glyf)->numOfGlyps; ++j)
        {
            TTFY_GLYFHeaderDestroy(&(*glyf)->headers[j]);
        }

    free((*glyf)->composite_glyfs);
    free((*glyf)->simple_glyfs);
    free((*glyf)->headers);
    free(*glyf);
    *glyf = NULL;
}

TTFY_GLYFSimple *TTFY_GLYFGetSimpleGlyf(TTFY_GLYF *glyf, uint16 ID)
{
    if (!glyf)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_GLYF has been passed");
        return NULL;
    }
    if (ID >= glyf->numOfGlyps)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_GLYF ID has been passed");
        return NULL;
    }
    if (glyf->headers[ID]->TYPE != SIMPLE)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_GLYF TYPE has been passed");
        return NULL;
    }
    return glyf->simple_glyfs[glyf->headers[ID]->GLYPH_ID];
}

TTFY_GLYFComposite *TTFY_GLYFGetCompositeGlyf(TTFY_GLYF *glyf, uint16 ID)
{
    if (!glyf)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_GLYF has been passed");
        return NULL;
    }
    if (ID >= glyf->numOfGlyps)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_GLYF ID has been passed");
        return NULL;
    }
    if (glyf->headers[ID]->TYPE != COMPOSITE)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_GLYF TYPE has been passed");
        return NULL;
    }
    return glyf->composite_glyfs[glyf->headers[ID]->GLYPH_ID];
}

TTFY_GLYFHeader *TTFY_GLYFHeaderCreate(TTFY_Buffer *buffer, TTFY_TableDirectory *directory)
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

    TTFY_GLYFHeader *ret = malloc(sizeof(TTFY_GLYFHeader));
    if (!ret)
    {
        fprintf(stderr, "%s\n", "Failed To Allocate Memory For TTFY_GLYFHeader");
        return NULL;
    }

    ret->numberOfContours = TTFY_BufferGetI16(buffer);
    ret->xMin = TTFY_BufferGetI16(buffer);
    ret->yMin = TTFY_BufferGetI16(buffer);
    ret->xMax = TTFY_BufferGetI16(buffer);
    ret->yMax = TTFY_BufferGetI16(buffer);

    return ret;
}

void TTFY_GLYFHeaderDestroy(TTFY_GLYFHeader **glyf_header)
{
    if (!glyf_header)
    {
        fprintf(stderr, "%s\n", "Invalid Pointer to TTFY_GLYFHeader has been passed");
        return;
    }
    if (!*glyf_header)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_GLYHeader has been passed");
        return;
    }
    free(*glyf_header);
    *glyf_header = NULL;
}

int16 TTFY_GLYFHeaderGetNumOfCountours(TTFY_GLYFHeader *glyf_header)
{
    if (!glyf_header)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_GLYHeader has been passed");
        return 0;
    }
    return glyf_header->numberOfContours;
}

int16 TTFY_GLYFHeaderGetXMin(TTFY_GLYFHeader *glyf_header)
{
    if (!glyf_header)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_GLYHeader has been passed");
        return 0;
    }
    return glyf_header->xMin;
}

int16 TTFY_GLYFHeaderGetYMin(TTFY_GLYFHeader *glyf_header)
{
    if (!glyf_header)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_GLYHeader has been passed");
        return 0;
    }
    return glyf_header->yMin;
}

int16 TTFY_GLYFHeaderGetXMax(TTFY_GLYFHeader *glyf_header)
{
    if (!glyf_header)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_GLYHeader has been passed");
        return 0;
    }
    return glyf_header->xMax;
}

int16 TTFY_GLYFHeaderGetYMax(TTFY_GLYFHeader *glyf_header)
{
    if (!glyf_header)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_GLYHeader has been passed");
        return 0;
    }
    return glyf_header->yMax;
}

TTFY_GLYFSimple *TTFY_GLYFSimpleCreate(TTFY_Buffer *buffer, TTFY_GLYFHeader *header)
{
    if (!buffer)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_Buffer has been passed");
        return NULL;
    }

    if (!header)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_GLYFHeader has been passed");
        return NULL;
    }

    TTFY_GLYFSimple *ret = malloc(sizeof(TTFY_GLYFSimple));
    if (!ret)
    {
        fprintf(stderr, "%s\n", "Failed To Allocate Memory For TTFY_GLYFSimple");
        return NULL;
    }

    ret->numberOfContours = TTFY_GLYFHeaderGetNumOfCountours(header);
    if (!ret->numberOfContours)
    {
        fprintf(stderr, "%s\n", "Invalid Number Of Contours TTFY_GLYFHeader has been passed");
        return NULL;
    }

    ret->endPtsOfCountours = malloc(sizeof(uint16) * ret->numberOfContours);
    if (!ret->endPtsOfCountours)
    {
        fprintf(stderr, "%s\n", "Failed To Allocate Memory For TTFY_GLYFSimple endPtsOfContours");
        free(ret);
        return NULL;
    }

    for (uint16 i = 0; i < ret->numberOfContours; ++i)
    {
        ret->endPtsOfCountours[i] = TTFY_BufferGetU16(buffer);
    }
    ret->instructionLength = TTFY_BufferGetU16(buffer);
    if (ret->instructionLength)
    {
        ret->instructions = malloc(sizeof(uint8) * ret->instructionLength);
        if (!ret->instructionLength)
        {
            fprintf(stderr, "%s\n", "Failed To Allocate Memory For TTFY_GLYFSimple instructions");
            free(ret->endPtsOfCountours);
            free(ret);
            return NULL;
        }
        for (uint16 i = 0; i < ret->instructionLength; ++i)
        {
            ret->instructions[i] = TTFY_BufferGetU8(buffer);
        }
    }
    else
    {
        ret->instructions = NULL;
    }

    ret->flagsLength = ret->endPtsOfCountours[ret->numberOfContours - 1];
    if (!ret->flagsLength)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_GLYFSimple Flags Length");
        free(ret->endPtsOfCountours);
        if (ret->instructions != 0)
            free(ret->instructions);
        free(ret);
        return NULL;
    }

    ret->flags = malloc(sizeof(uint8) * ret->flagsLength);
    if (!ret->flags)
    {
        fprintf(stderr, "%s\n", "Failed To Allocate Memory TTFY_GLYFSimple Flags");
        free(ret->endPtsOfCountours);
        if (ret->instructions != 0)
            free(ret->instructions);
        free(ret);
        return NULL;
    }

    for (uint16 i = 0; i < ret->flagsLength; ++i)
    {
        ret->flags[i] = TTFY_BufferGetU8(buffer);
        if (ret->flags[i] & REPEAT_FLAG)
        {
            uint8 r = TTFY_BufferGetU8(buffer);
            for (uint8 j = 0; j < r; ++j)
            {

                ret->flags[i + j + 1] = ret->flags[i];
            }
            i += r;
        }
    }

    ret->xCoordinates = malloc(sizeof(int16) * ret->flagsLength);
    if (!ret->xCoordinates)
    {
        fprintf(stderr, "%s\n", "Failed To Allocate Memory TTFY_GLYFSimple XCoordinates");
        free(ret->endPtsOfCountours);
        if (ret->instructions != 0)
            free(ret->instructions);
        free(ret->flags);
        free(ret);
        return NULL;
    }

    for (uint16 i = 0; i < ret->flagsLength; ++i)
    {
        if (!(ret->flags[i] & X_SHORT_VECTOR) && !(ret->flags[i] & X_IS_SAME_OR_POSITIVE_X_SHORT_VECTOR))
        {
            ret->xCoordinates[i] = TTFY_BufferGetI16(buffer);
        }
        else if (!(ret->flags[i] & X_SHORT_VECTOR) && (ret->flags[i] & X_IS_SAME_OR_POSITIVE_X_SHORT_VECTOR))
        {
            ret->xCoordinates[i] = ret->xCoordinates[i - 1];
        }
        else if ((ret->flags[i] & X_SHORT_VECTOR) && (ret->flags[i] & X_IS_SAME_OR_POSITIVE_X_SHORT_VECTOR))
        {
            ret->xCoordinates[i] = TTFY_BufferGetU8(buffer);
        }
        else if ((ret->flags[i] & X_SHORT_VECTOR) && !(ret->flags[i] & X_IS_SAME_OR_POSITIVE_X_SHORT_VECTOR))
        {
            ret->xCoordinates[i] = -TTFY_BufferGetU8(buffer);
        }
    }

    ret->yCoordinates = malloc(sizeof(int16) * ret->flagsLength);
    if (!ret->yCoordinates)
    {
        fprintf(stderr, "%s\n", "Failed To Allocate Memory TTFY_GLYFSimple YCoordinates");
        free(ret->endPtsOfCountours);
        if (ret->instructions != 0)
            free(ret->instructions);
        free(ret->flags);
        free(ret->xCoordinates);
        free(ret);
        return NULL;
    }

    for (uint16 i = 0; i < ret->flagsLength; ++i)
    {
        if (!(ret->flags[i] & Y_SHORT_VECTOR) && !(ret->flags[i] & Y_IS_SAME_OR_POSITIVE_Y_SHORT_VECTOR))
        {
            ret->yCoordinates[i] = TTFY_BufferGetI16(buffer);
        }
        else if (!(ret->flags[i] & Y_SHORT_VECTOR) && (ret->flags[i] & Y_IS_SAME_OR_POSITIVE_Y_SHORT_VECTOR))
        {
            ret->yCoordinates[i] = ret->yCoordinates[i - 1];
        }
        else if ((ret->flags[i] & Y_SHORT_VECTOR) && (ret->flags[i] & Y_IS_SAME_OR_POSITIVE_Y_SHORT_VECTOR))
        {
            ret->yCoordinates[i] = TTFY_BufferGetU8(buffer);
        }
        else if ((ret->flags[i] & Y_SHORT_VECTOR) && !(ret->flags[i] & Y_IS_SAME_OR_POSITIVE_Y_SHORT_VECTOR))
        {
            ret->yCoordinates[i] = -TTFY_BufferGetU8(buffer);
        }
    }
    return ret;
}

void TTFY_GLYFSimpleDestroy(TTFY_GLYFSimple **simple_glyf)
{
    if (!simple_glyf)
    {
        fprintf(stderr, "%s\n", "Invalid Pointer to TTFY_GLYFSimple has been passed");
        return;
    }
    if (!*simple_glyf)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_GLYFSimple has been passed");
        return;
    }
    TTFY_GLYFSimple *g = *simple_glyf;
    free(g->endPtsOfCountours);
    free(g->flags);
    if (g->instructions)
        free(g->instructions);
    free(g->xCoordinates);
    free(g->yCoordinates);
    free(*simple_glyf);
    *simple_glyf = NULL;
}

uint16 TTFY_GLYFSimpleGetEndPtOfCountour(TTFY_GLYFSimple *simple_glyf, uint16 ID)
{
    if (!simple_glyf)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_GLYFSimple has been passed");
        return 0;
    }
    if (ID >= simple_glyf->numberOfContours)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_GLYFSimple ID has been passed");
        return 0;
    }
    return simple_glyf->endPtsOfCountours[ID];
}

uint16 TTFY_GLYFSimpleGetInstructionLength(TTFY_GLYFSimple *simple_glyf)
{
    if (!simple_glyf)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_GLYFSimple has been passed");
        return 0;
    }
    return simple_glyf->instructionLength;
}

uint8 TTFY_GLYFSimpleGetInstruction(TTFY_GLYFSimple *simple_glyf, uint16 ID)
{
    if (!simple_glyf)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_GLYFSimple has been passed");
        return 0;
    }
    if (ID >= simple_glyf->instructionLength)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_GLYFSimple ID has been passed");
        return 0;
    }
    return simple_glyf->instructions[ID];
}

uint8 TTFY_GLYFSimpleGetFlags(TTFY_GLYFSimple *simple_glyf, uint16 ID)
{
    if (!simple_glyf)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_GLYFSimple has been passed");
        return 0;
    }
    if (ID >= simple_glyf->flagsLength)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_GLYFSimple ID has been passed");
        return 0;
    }
    return simple_glyf->flags[ID];
}

int16 TTFY_GLYFSimpleGetXCoordinate(TTFY_GLYFSimple *simple_glyf, uint16 ID)
{
    if (!simple_glyf)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_GLYFSimple has been passed");
        return 0;
    }
    if (ID >= simple_glyf->flagsLength)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_GLYFSimple ID has been passed");
        return 0;
    }
    return simple_glyf->xCoordinates[ID];
}

int16 TTFY_GLYFSimpleGetYCoordinate(TTFY_GLYFSimple *simple_glyf, uint16 ID)
{
    if (!simple_glyf)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_GLYFSimple has been passed");
        return 0;
    }
    if (ID >= simple_glyf->flagsLength)
    {
        fprintf(stderr, "%s\n", "Invalid TTFY_GLYFSimple ID has been passed");
        return 0;
    }
    return simple_glyf->yCoordinates[ID];
}
