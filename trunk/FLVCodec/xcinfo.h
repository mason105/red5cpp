//**********************************************************************************
// Filename: xcinfo.h
//
// ViXS Systems Confidential and Proprietary
//
//*********************************************************************************

#ifndef __XCINFO_H__
#define __XCINFO_H__


///////////////////////////////////////////////////////////////////////////////
// Info/Cmd I/F


//
// Property GUID
//
#define STATIC_XC_INFO \
    0xA0B600B4, 0xC180, 0x4814, 0x91, 0x23, 0x7D, 0x8C, 0xBE, 0x04, 0x3D, 0x3F
DEFINE_GUIDSTRUCT("A0B600B4-C180-4814-9123-7D8CBE043D3F", XC_INFO);
#define XC_INFO DEFINE_GUIDNAMED(XC_INFO)

//
// Property ID
//
enum
{
    XCINFO_FLUSH = 1,
    XCINFO_MDAT_SIZE,
    XCINFO_RUN_MIRROR
};

//
// Property Data
//
typedef struct
{
    ULONG   id;
} XCINFO_HEAD, *PXCINFO_HEAD;

typedef struct
{
    XCINFO_HEAD Head;
    BOOLEAN     Flush;
} XCINFO_FLUSH_S, *PXCINFO_FLUSH_S;

typedef struct
{
    XCINFO_HEAD Head;
    ULONG       Offset;
    ULONGLONG   Size;
} XCINFO_MDAT_SIZE_S, *PXCINFO_MDAT_SIZE_S;

typedef struct
{
    XCINFO_HEAD Head;
    BOOLEAN     bRunMirror;
} XCINFO_RUN_MIRROR_S, *PXCINFO_RUN_MIRROR_S;


///////////////////////////////////////////////////////////////////////////////
// On-Chip Noise/Comb Filters I/F

//VNE Filter Property
#define STATIC_XC_FILTER_CTRL_INFO \
0x33882465, 0xDC6C, 0x4830, 0xA1, 0x71, 0x65, 0x8F, 0xA4, 0x82, 0xD2, 0xA4
DEFINE_GUIDSTRUCT("33882465-DC6C-4830-A171-658FA482D2A4", XC_FILTER_CTRL_INFO);
#define XC_FILTER_CTRL_INFO DEFINE_GUIDNAMED(XC_FILTER_CTRL_INFO)


typedef struct _XC_FILTER_CTRL_S
{
    ULONG   ulFlags;
    ULONG   ulTemporalLevel;
    ULONG   ulTemporalLuma;
    ULONG   ulTemporalChroma;
    ULONG   ulSpatialLevel;
    ULONG   ulSpatialLuma;
    ULONG   ulSpatialChroma;
    ULONG   ulSpatialStrength;
    ULONG   ulCombLuma;
    ULONG   ulCombChroma;

} XC_FILTER_CTRL_S, *PXC_FILTER_CTRL_S;


#endif
