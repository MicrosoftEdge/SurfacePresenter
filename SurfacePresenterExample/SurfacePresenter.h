/*=====================================================================
  Microsoft
  ISurfacePresenter Code Sample.

  Copyright (C) 2010 Microsoft Corporation.  All rights reserved.

This source code is intended only as a supplement to Microsoft
Development Tools and/or on-line documentation.  See these other
materials for detailed information regarding Microsoft code samples.

THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.
=====================================================================*/
#pragma once

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

/* verify that the <rpcsal.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCSAL_H_VERSION__
#define __REQUIRED_RPCSAL_H_VERSION__ 100
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __oledxgi_int_h__
#define __oledxgi_int_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */

#ifndef __IViewObjectPresentSite_FWD_DEFINED__
#define __IViewObjectPresentSite_FWD_DEFINED__
typedef interface IViewObjectPresentSite IViewObjectPresentSite;
#endif 	/* __IViewObjectPresentSite_FWD_DEFINED__ */


#ifndef __ISurfacePresenter_FWD_DEFINED__
#define __ISurfacePresenter_FWD_DEFINED__
typedef interface ISurfacePresenter ISurfacePresenter;
#endif 	/* __ISurfacePresenter_FWD_DEFINED__ */


#ifndef __IViewObjectPrint_FWD_DEFINED__
#define __IViewObjectPrint_FWD_DEFINED__
typedef interface IViewObjectPrint IViewObjectPrint;
#endif 	/* __IViewObjectPrint_FWD_DEFINED__ */


#ifndef __IViewObjectPresentNotifySite_FWD_DEFINED__
#define __IViewObjectPresentNotifySite_FWD_DEFINED__
typedef interface IViewObjectPresentNotifySite IViewObjectPresentNotifySite;
#endif 	/* __IViewObjectPresentNotifySite_FWD_DEFINED__ */


#ifndef __IViewObjectPresentNotify_FWD_DEFINED__
#define __IViewObjectPresentNotify_FWD_DEFINED__
typedef interface IViewObjectPresentNotify IViewObjectPresentNotify;
#endif 	/* __IViewObjectPresentNotify_FWD_DEFINED__ */

#ifndef __IBFCacheable_FWD_DEFINED__
#define __IBFCacheable_FWD_DEFINED__
typedef interface IBFCacheable IBFCacheable;
#endif 	/* __IBFCacheable_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "prsht.h"
#include "dxgitype.h"

#ifdef __cplusplus
extern "C"{
#endif


/* interface __MIDL_itf_oledxgi_int_0000_0000 */
/* [local] */

//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//--------------------------------------------------------------------------
#if ( _MSC_VER >= 800 )
#pragma warning(disable:4201)
#endif
typedef
enum _VIEW_OBJECT_ALPHA_MODE
    {	VIEW_OBJECT_ALPHA_MODE_IGNORE	= 0,
	VIEW_OBJECT_ALPHA_MODE_PREMULTIPLIED	= 1,
	VIEW_OBJECT_ALPHA_MODE_Max	= 2147483647L
    } 	VIEW_OBJECT_ALPHA_MODE;

typedef
enum _VIEW_OBJECT_COMPOSITION_MODE
    {	VIEW_OBJECT_COMPOSITION_MODE_LEGACY	= 0,
	VIEW_OBJECT_COMPOSITION_MODE_SURFACEPRESENTER	= 1,
	VIEW_OBJECT_COMPOSITION_MODE_Max	= 2147483647L
    } 	VIEW_OBJECT_COMPOSITION_MODE;




extern RPC_IF_HANDLE __MIDL_itf_oledxgi_int_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_oledxgi_int_0000_0000_v0_0_s_ifspec;

#ifndef __IViewObjectPresentSite_INTERFACE_DEFINED__
#define __IViewObjectPresentSite_INTERFACE_DEFINED__

/* interface IViewObjectPresentSite */
/* [uuid][unique][object] */


EXTERN_C const IID IID_IViewObjectPresentSite;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("305106e1-98b5-11cf-bb82-00aa00bdce0b")
    IViewObjectPresentSite : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CreateSurfacePresenter(
            /* [in] */ __RPC__in_opt IUnknown *pDevice,
            /* [in] */ UINT width,
            /* [in] */ UINT height,
            /* [in] */ UINT backBufferCount,
            /* [in] */ DXGI_FORMAT format,
            /* [in] */ VIEW_OBJECT_ALPHA_MODE mode,
            /* [out][retval] */ __RPC__deref_out_opt ISurfacePresenter **ppQueue) = 0;

        virtual HRESULT STDMETHODCALLTYPE IsHardwareComposition(
            /* [out][retval] */ __RPC__out BOOL *pIsHardwareComposition) = 0;

        virtual HRESULT STDMETHODCALLTYPE SetCompositionMode(
            /* [in] */ VIEW_OBJECT_COMPOSITION_MODE mode) = 0;

    };

#else 	/* C style interface */

    typedef struct IViewObjectPresentSiteVtbl
    {
        BEGIN_INTERFACE

        HRESULT ( STDMETHODCALLTYPE *QueryInterface )(
            __RPC__in IViewObjectPresentSite * This,
            /* [in] */ __RPC__in REFIID riid,
            /* [annotation][iid_is][out] */
            __RPC__deref_out  void **ppvObject);

        ULONG ( STDMETHODCALLTYPE *AddRef )(
            __RPC__in IViewObjectPresentSite * This);

        ULONG ( STDMETHODCALLTYPE *Release )(
            __RPC__in IViewObjectPresentSite * This);

        HRESULT ( STDMETHODCALLTYPE *CreateSurfacePresenter )(
            __RPC__in IViewObjectPresentSite * This,
            /* [in] */ __RPC__in_opt IUnknown *pDevice,
            /* [in] */ UINT width,
            /* [in] */ UINT height,
            /* [in] */ UINT backBufferCount,
            /* [in] */ DXGI_FORMAT format,
            /* [in] */ VIEW_OBJECT_ALPHA_MODE mode,
            /* [out][retval] */ __RPC__deref_out_opt ISurfacePresenter **ppQueue);

        HRESULT ( STDMETHODCALLTYPE *IsHardwareComposition )(
            __RPC__in IViewObjectPresentSite * This,
            /* [out][retval] */ __RPC__out BOOL *pIsHardwareComposition);

        HRESULT ( STDMETHODCALLTYPE *SetCompositionMode )(
            __RPC__in IViewObjectPresentSite * This,
            /* [in] */ VIEW_OBJECT_COMPOSITION_MODE mode);

        END_INTERFACE
    } IViewObjectPresentSiteVtbl;

    interface IViewObjectPresentSite
    {
        CONST_VTBL struct IViewObjectPresentSiteVtbl *lpVtbl;
    };



#ifdef COBJMACROS


#define IViewObjectPresentSite_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) )

#define IViewObjectPresentSite_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) )

#define IViewObjectPresentSite_Release(This)	\
    ( (This)->lpVtbl -> Release(This) )


#define IViewObjectPresentSite_CreateSurfacePresenter(This,pDevice,width,height,backBufferCount,format,mode,ppQueue)	\
    ( (This)->lpVtbl -> CreateSurfacePresenter(This,pDevice,width,height,backBufferCount,format,mode,ppQueue) )

#define IViewObjectPresentSite_IsHardwareComposition(This,pIsHardwareComposition)	\
    ( (This)->lpVtbl -> IsHardwareComposition(This,pIsHardwareComposition) )

#define IViewObjectPresentSite_SetCompositionMode(This,mode)	\
    ( (This)->lpVtbl -> SetCompositionMode(This,mode) )

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IViewObjectPresentSite_INTERFACE_DEFINED__ */


#ifndef __ISurfacePresenter_INTERFACE_DEFINED__
#define __ISurfacePresenter_INTERFACE_DEFINED__

/* interface ISurfacePresenter */
/* [uuid][unique][object] */


EXTERN_C const IID IID_ISurfacePresenter;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("305106e2-98b5-11cf-bb82-00aa00bdce0b")
    ISurfacePresenter : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Present(
            /* [in] */ UINT uBuffer,
            /* [in] */ __RPC__in RECT *pDirty) = 0;

        virtual HRESULT STDMETHODCALLTYPE GetBuffer(
            /* [in] */ UINT backBufferIndex,
            /* [in] */ __RPC__in REFIID riid,
            /* [iid_is][out][retval] */ __RPC__deref_out_opt void **ppBuffer) = 0;

        virtual HRESULT STDMETHODCALLTYPE IsCurrent(
            /* [out][retval] */ __RPC__out BOOL *pIsCurrent) = 0;

    };

#else 	/* C style interface */

    typedef struct ISurfacePresenterVtbl
    {
        BEGIN_INTERFACE

        HRESULT ( STDMETHODCALLTYPE *QueryInterface )(
            __RPC__in ISurfacePresenter * This,
            /* [in] */ __RPC__in REFIID riid,
            /* [annotation][iid_is][out] */
            __RPC__deref_out  void **ppvObject);

        ULONG ( STDMETHODCALLTYPE *AddRef )(
            __RPC__in ISurfacePresenter * This);

        ULONG ( STDMETHODCALLTYPE *Release )(
            __RPC__in ISurfacePresenter * This);

        HRESULT ( STDMETHODCALLTYPE *Present )(
            __RPC__in ISurfacePresenter * This,
            /* [in] */ UINT uBuffer,
            /* [in] */ __RPC__in RECT *pDirty);

        HRESULT ( STDMETHODCALLTYPE *GetBuffer )(
            __RPC__in ISurfacePresenter * This,
            /* [in] */ UINT backBufferIndex,
            /* [in] */ __RPC__in REFIID riid,
            /* [iid_is][out][retval] */ __RPC__deref_out_opt void **ppBuffer);

        HRESULT ( STDMETHODCALLTYPE *IsCurrent )(
            __RPC__in ISurfacePresenter * This,
            /* [out][retval] */ __RPC__out BOOL *pIsCurrent);

        END_INTERFACE
    } ISurfacePresenterVtbl;

    interface ISurfacePresenter
    {
        CONST_VTBL struct ISurfacePresenterVtbl *lpVtbl;
    };



#ifdef COBJMACROS


#define ISurfacePresenter_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) )

#define ISurfacePresenter_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) )

#define ISurfacePresenter_Release(This)	\
    ( (This)->lpVtbl -> Release(This) )


#define ISurfacePresenter_Present(This,uBuffer,pDirty)	\
    ( (This)->lpVtbl -> Present(This,uBuffer,pDirty) )

#define ISurfacePresenter_GetBuffer(This,backBufferIndex,riid,ppBuffer)	\
    ( (This)->lpVtbl -> GetBuffer(This,backBufferIndex,riid,ppBuffer) )

#define ISurfacePresenter_IsCurrent(This,pIsCurrent)	\
    ( (This)->lpVtbl -> IsCurrent(This,pIsCurrent) )

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISurfacePresenter_INTERFACE_DEFINED__ */




#ifndef __IViewObjectPrint_INTERFACE_DEFINED__
#define __IViewObjectPrint_INTERFACE_DEFINED__

/* interface IViewObjectPrint */
/* [uuid][unique][object] */


EXTERN_C const IID IID_IViewObjectPrint;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("305106e3-98b5-11cf-bb82-00aa00bdce0b")
    IViewObjectPrint : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetPrintBitmap(
            /* [out][retval] */ __RPC__deref_out_opt IUnknown **ppPrintBitmap) = 0;

    };

#else 	/* C style interface */

    typedef struct IViewObjectPrintVtbl
    {
        BEGIN_INTERFACE

        HRESULT ( STDMETHODCALLTYPE *QueryInterface )(
            __RPC__in IViewObjectPrint * This,
            /* [in] */ __RPC__in REFIID riid,
            /* [annotation][iid_is][out] */
            __RPC__deref_out  void **ppvObject);

        ULONG ( STDMETHODCALLTYPE *AddRef )(
            __RPC__in IViewObjectPrint * This);

        ULONG ( STDMETHODCALLTYPE *Release )(
            __RPC__in IViewObjectPrint * This);

        HRESULT ( STDMETHODCALLTYPE *GetPrintBitmap )(
            __RPC__in IViewObjectPrint * This,
            /* [out][retval] */ __RPC__deref_out_opt IUnknown **ppPrintBitmap);

        END_INTERFACE
    } IViewObjectPrintVtbl;

    interface IViewObjectPrint
    {
        CONST_VTBL struct IViewObjectPrintVtbl *lpVtbl;
    };



#ifdef COBJMACROS


#define IViewObjectPrint_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) )

#define IViewObjectPrint_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) )

#define IViewObjectPrint_Release(This)	\
    ( (This)->lpVtbl -> Release(This) )


#define IViewObjectPrint_GetPrintBitmap(This,ppPrintBitmap)	\
    ( (This)->lpVtbl -> GetPrintBitmap(This,ppPrintBitmap) )

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IViewObjectPrint_INTERFACE_DEFINED__ */


#ifndef __IViewObjectPresentNotifySite_INTERFACE_DEFINED__
#define __IViewObjectPresentNotifySite_INTERFACE_DEFINED__

/* interface IViewObjectPresentNotifySite */
/* [uuid][unique][object] */


EXTERN_C const IID IID_IViewObjectPresentNotifySite;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("305107fa-98b5-11cf-bb82-00aa00bdce0b")
    IViewObjectPresentNotifySite : public IViewObjectPresentSite
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE RequestFrame( void) = 0;

    };

#else 	/* C style interface */

    typedef struct IViewObjectPresentNotifySiteVtbl
    {
        BEGIN_INTERFACE

        HRESULT ( STDMETHODCALLTYPE *QueryInterface )(
            __RPC__in IViewObjectPresentNotifySite * This,
            /* [in] */ __RPC__in REFIID riid,
            /* [annotation][iid_is][out] */
            __RPC__deref_out  void **ppvObject);

        ULONG ( STDMETHODCALLTYPE *AddRef )(
            __RPC__in IViewObjectPresentNotifySite * This);

        ULONG ( STDMETHODCALLTYPE *Release )(
            __RPC__in IViewObjectPresentNotifySite * This);

        HRESULT ( STDMETHODCALLTYPE *CreateSurfacePresenter )(
            __RPC__in IViewObjectPresentNotifySite * This,
            /* [in] */ __RPC__in_opt IUnknown *pDevice,
            /* [in] */ UINT width,
            /* [in] */ UINT height,
            /* [in] */ UINT backBufferCount,
            /* [in] */ DXGI_FORMAT format,
            /* [in] */ VIEW_OBJECT_ALPHA_MODE mode,
            /* [out][retval] */ __RPC__deref_out_opt ISurfacePresenter **ppQueue);

        HRESULT ( STDMETHODCALLTYPE *IsHardwareComposition )(
            __RPC__in IViewObjectPresentNotifySite * This,
            /* [out][retval] */ __RPC__out BOOL *pIsHardwareComposition);

        HRESULT ( STDMETHODCALLTYPE *SetCompositionMode )(
            __RPC__in IViewObjectPresentNotifySite * This,
            /* [in] */ VIEW_OBJECT_COMPOSITION_MODE mode);

        HRESULT ( STDMETHODCALLTYPE *RequestFrame )(
            __RPC__in IViewObjectPresentNotifySite * This);

        END_INTERFACE
    } IViewObjectPresentNotifySiteVtbl;

    interface IViewObjectPresentNotifySite
    {
        CONST_VTBL struct IViewObjectPresentNotifySiteVtbl *lpVtbl;
    };



#ifdef COBJMACROS


#define IViewObjectPresentNotifySite_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) )

#define IViewObjectPresentNotifySite_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) )

#define IViewObjectPresentNotifySite_Release(This)	\
    ( (This)->lpVtbl -> Release(This) )


#define IViewObjectPresentNotifySite_CreateSurfacePresenter(This,pDevice,width,height,backBufferCount,format,mode,ppQueue)	\
    ( (This)->lpVtbl -> CreateSurfacePresenter(This,pDevice,width,height,backBufferCount,format,mode,ppQueue) )

#define IViewObjectPresentNotifySite_IsHardwareComposition(This,pIsHardwareComposition)	\
    ( (This)->lpVtbl -> IsHardwareComposition(This,pIsHardwareComposition) )

#define IViewObjectPresentNotifySite_SetCompositionMode(This,mode)	\
    ( (This)->lpVtbl -> SetCompositionMode(This,mode) )


#define IViewObjectPresentNotifySite_RequestFrame(This)	\
    ( (This)->lpVtbl -> RequestFrame(This) )

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IViewObjectPresentNotifySite_INTERFACE_DEFINED__ */


#ifndef __IViewObjectPresentNotify_INTERFACE_DEFINED__
#define __IViewObjectPresentNotify_INTERFACE_DEFINED__

/* interface IViewObjectPresentNotify */
/* [uuid][unique][object] */


EXTERN_C const IID IID_IViewObjectPresentNotify;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("305107f8-98b5-11cf-bb82-00aa00bdce0b")
    IViewObjectPresentNotify : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnPreRender( void) = 0;

    };

#else 	/* C style interface */

    typedef struct IViewObjectPresentNotifyVtbl
    {
        BEGIN_INTERFACE

        HRESULT ( STDMETHODCALLTYPE *QueryInterface )(
            __RPC__in IViewObjectPresentNotify * This,
            /* [in] */ __RPC__in REFIID riid,
            /* [annotation][iid_is][out] */
            __RPC__deref_out  void **ppvObject);

        ULONG ( STDMETHODCALLTYPE *AddRef )(
            __RPC__in IViewObjectPresentNotify * This);

        ULONG ( STDMETHODCALLTYPE *Release )(
            __RPC__in IViewObjectPresentNotify * This);

        HRESULT ( STDMETHODCALLTYPE *OnPreRender )(
            __RPC__in IViewObjectPresentNotify * This);

        END_INTERFACE
    } IViewObjectPresentNotifyVtbl;

    interface IViewObjectPresentNotify
    {
        CONST_VTBL struct IViewObjectPresentNotifyVtbl *lpVtbl;
    };



#ifdef COBJMACROS


#define IViewObjectPresentNotify_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) )

#define IViewObjectPresentNotify_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) )

#define IViewObjectPresentNotify_Release(This)	\
    ( (This)->lpVtbl -> Release(This) )


#define IViewObjectPresentNotify_OnPreRender(This)	\
    ( (This)->lpVtbl -> OnPreRender(This) )

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IViewObjectPresentNotify_INTERFACE_DEFINED__ */

#ifndef __IBFCacheable_INTERFACE_DEFINED__
#define __IBFCacheable_INTERFACE_DEFINED__

/* interface IBFCacheable */
/* [uuid][unique][object] */


EXTERN_C const IID IID_IBFCacheable;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("30510861-98b5-11cf-bb82-00aa00bdce0b")
    IBFCacheable : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE EnterBFCache( void) = 0;

        virtual HRESULT STDMETHODCALLTYPE ExitBFCache( void) = 0;

    };


#else 	/* C style interface */

    typedef struct IBFCacheableVtbl
    {
        BEGIN_INTERFACE

        HRESULT ( STDMETHODCALLTYPE *QueryInterface )(
            __RPC__in IBFCacheable * This,
            /* [in] */ __RPC__in REFIID riid,
            /* [annotation][iid_is][out] */
            _COM_Outptr_  void **ppvObject);

        ULONG ( STDMETHODCALLTYPE *AddRef )(
            __RPC__in IBFCacheable * This);

        ULONG ( STDMETHODCALLTYPE *Release )(
            __RPC__in IBFCacheable * This);

        HRESULT ( STDMETHODCALLTYPE *EnterBFCache )(
            __RPC__in IBFCacheable * This);

        HRESULT ( STDMETHODCALLTYPE *ExitBFCache )(
            __RPC__in IBFCacheable * This);

        END_INTERFACE
    } IBFCacheableVtbl;

    interface IBFCacheable
    {
        CONST_VTBL struct IBFCacheableVtbl *lpVtbl;
    };



#ifdef COBJMACROS


#define IBFCacheable_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) )

#define IBFCacheable_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) )

#define IBFCacheable_Release(This)	\
    ( (This)->lpVtbl -> Release(This) )


#define IBFCacheable_EnterBFCache(This)	\
    ( (This)->lpVtbl -> EnterBFCache(This) )

#define IBFCacheable_ExitBFCache(This)	\
    ( (This)->lpVtbl -> ExitBFCache(This) )

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBFCacheable_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


