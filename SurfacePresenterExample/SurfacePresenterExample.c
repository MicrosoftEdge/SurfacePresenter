

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Tue Nov 30 13:34:13 2010
 */
/* Compiler settings for SurfacePresenterExample.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_SurfacePresenterExampleLib,0xe320edab,0x77b5,0x49b8,0x89,0x37,0x9f,0xae,0x52,0xcc,0x46,0x72);


MIDL_DEFINE_GUID(IID, DIID__DSurfacePresenterExample,0xc1dcde77,0xf234,0x44be,0xa2,0xa9,0x30,0x75,0xc2,0x89,0x88,0x43);


MIDL_DEFINE_GUID(IID, DIID__DSurfacePresenterExampleEvents,0xbb011432,0x5350,0x4758,0x86,0x66,0xd1,0x3e,0xd4,0xf1,0x1c,0x55);


MIDL_DEFINE_GUID(CLSID, CLSID_SurfacePresenterExample,0x0c85b239,0x904a,0x4adf,0x84,0x24,0xf1,0x92,0x8b,0x38,0xf1,0x2f);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



