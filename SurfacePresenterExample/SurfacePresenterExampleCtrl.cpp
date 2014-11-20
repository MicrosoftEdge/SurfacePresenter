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
#include "stdafx.h"
#include "SurfacePresenterExample.h"
#include "SurfacePresenterExampleCtrl.h"
#include "D3D9HWRenderer.h"
#include "D3D9SWRenderer.h"
#include "D3D10SWRenderer.h"
#include "D3D10HWRenderer.h"
#include "WICBitmapRenderer.h"
#include "HDCRenderer.h"
#include "PrintRenderer.h"
#include "RenderOption.h"
#include "GDIPresenter.h"
#include "HiddenWindow.h"
#include "AccHelper.h"
#include "RootAccessible.h"
#include "RectAccessible.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CSurfacePresenterExampleCtrl, COleControl)

BEGIN_MESSAGE_MAP(CSurfacePresenterExampleCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
    ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

BEGIN_INTERFACE_MAP(CSurfacePresenterExampleCtrl, COleControl)
    INTERFACE_PART(CSurfacePresenterExampleCtrl, __uuidof(IObjectSafety), SafeScriptingObj)
    INTERFACE_PART(CSurfacePresenterExampleCtrl, __uuidof(IViewObjectPrint), PrintObj)
    INTERFACE_PART(CSurfacePresenterExampleCtrl, __uuidof(IAccessible), AccessibleObj)
    INTERFACE_PART(CSurfacePresenterExampleCtrl, __uuidof(IRectCollection), RectCollectionObj)
    INTERFACE_PART(CSurfacePresenterExampleCtrl, __uuidof(IViewObjectPresentNotify), ViewObjectPresentNotifyObj)
    INTERFACE_PART(CSurfacePresenterExampleCtrl, __uuidof(IBFCacheable), BFCacheableObj)
END_INTERFACE_MAP()    

BEGIN_DISPATCH_MAP(CSurfacePresenterExampleCtrl, COleControl)
    DISP_PROPERTY_NOTIFY(CSurfacePresenterExampleCtrl, "numRects", _numRects, OnRectsChange, VT_I4)
    DISP_PROPERTY_NOTIFY(CSurfacePresenterExampleCtrl, "d3dVersion", _d3dVersion, OnRendererPropertyChange, VT_I4)
    DISP_PROPERTY_NOTIFY(CSurfacePresenterExampleCtrl, "useSurfacePresenter", _fUseSurfacePresenter, OnRendererPropertyChange, VT_BOOL)
    DISP_PROPERTY_NOTIFY(CSurfacePresenterExampleCtrl, "useHardwareRasterize", _fUseHardwareRasterize, OnRendererPropertyChange, VT_BOOL)
END_DISPATCH_MAP()

BEGIN_EVENT_MAP(CSurfacePresenterExampleCtrl, COleControl)
END_EVENT_MAP()

BEGIN_PROPPAGEIDS(CSurfacePresenterExampleCtrl, 1)
END_PROPPAGEIDS(CSurfacePresenterExampleCtrl)

IMPLEMENT_OLECREATE_EX(CSurfacePresenterExampleCtrl, "SURFACEPRESENTER.SurfacePresenterCtrl.1", 0x0c85b239, 0x904a, 0x4adf, 0x84, 0x24, 0xf1, 0x92, 0x8b, 0x38, 0xf1, 0x2f)
IMPLEMENT_OLETYPELIB(CSurfacePresenterExampleCtrl, _tlid, _wVerMajor, _wVerMinor)

const IID BASED_CODE IID_DSurfacePresenterExample = { 0xc1dcde77, 0xf234, 0x44be, {0xa2, 0xa9, 0x30, 0x75, 0xc2, 0x89, 0x88, 0x43} };
const IID BASED_CODE IID_DSurfacePresenterExampleEvents = { 0xbb011432, 0x5350, 0x4758, {0x86, 0x66, 0xd1, 0x3e, 0xd4, 0xf1, 0x1c, 0x55} };

static const DWORD BASED_CODE _dwSurfacePresenterExampleOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CSurfacePresenterExampleCtrl, IDS_SURFACEPRESENTERDEMO, _dwSurfacePresenterExampleOleMisc)

BOOL CSurfacePresenterExampleCtrl::CSurfacePresenterExampleCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_SURFACEPRESENTERDEMO,
			IDB_SURFACEPRESENTERDEMO,
			afxRegApartmentThreading,
			_dwSurfacePresenterExampleOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}

CSurfacePresenterExampleCtrl::CSurfacePresenterExampleCtrl()
{
	InitializeIIDs(&IID_DSurfacePresenterExample, &IID_DSurfacePresenterExampleEvents);

    // Pick a size that we will not get from the site so that the first SetObjectRects
    // will do what we want it to.
    _presenterSize.SetSize(-1, -1);
    _objectSize.SetSize(-1, -1);

    // Default property values
    _fUseSurfacePresenter = TRUE;
    _fUseHardwareRasterize = TRUE;
    _d3dVersion = 10;
    _numRects = 100;

    _fCoInit = false;
}

CSurfacePresenterExampleCtrl::~CSurfacePresenterExampleCtrl()
{
}

void CSurfacePresenterExampleCtrl::OnRendererPropertyChange()
{
    _spRenderer.Free();
    _spPresenter.Release();

    // Composition mode might need to be set
    SetCompositionMode();
}

void CSurfacePresenterExampleCtrl::OnRectsChange()
{
    ResetRectangles();
}

void CSurfacePresenterExampleCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));

    pPX->ExchangeProp(L"numRects", VT_I4, &_numRects);
    pPX->ExchangeProp(L"d3dVersion", VT_I4, &_d3dVersion);
    pPX->ExchangeProp(L"useSurfacePresenter", VT_BOOL, &_fUseSurfacePresenter);
    pPX->ExchangeProp(L"useHardwareRasterize", VT_BOOL, &_fUseHardwareRasterize);

	COleControl::DoPropExchange(pPX);

    // Composition mode needs to be set now that properties are set
    SetCompositionMode();
}

void CSurfacePresenterExampleCtrl::ResetRectangles()
{
    if (_objectSize.cx > 0 && _objectSize.cy > 0)
    {
        if (_numRects > 10000000)
        {
            _numRects = 10000000;
        }

        if (_numRects < 1)
        {
            _numRects = 1;
        }

        _rectPositions.SetSize(_numRects);
        for (int i = 0; i < _rectPositions.GetSize(); i++)
        {
            _rectPositions[i].Reset(_objectSize);

            if (_numRects < 10)
            {
                // Slow down if we have small rectangle count
                _rectPositions[i]._velocity.x /= 10;
                _rectPositions[i]._velocity.y /= 10;
            }
        }
    }
}

DWORD CSurfacePresenterExampleCtrl::GetControlFlags()
{
	DWORD dwFlags = COleControl::GetControlFlags();
	dwFlags |= windowlessActivate;
	return dwFlags;
}

void CSurfacePresenterExampleCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange
}

HRESULT CSurfacePresenterExampleCtrl::CreateRenderer()
{
    HRESULT hr;
    
    const static RenderOption options[] = {
        // Only one option for no presenter
        RenderOption(FALSE, &CreateTypedRenderer<HDCRenderer>),

        // Only one default for SW composition
        RenderOption(TRUE,  &CreateTypedRenderer<WICBitmapRenderer>),

        // D3D9 renderers
        RenderOption(TRUE,  FALSE, 9,  &CreateTypedRenderer<D3D9SWRenderer>),
        RenderOption(TRUE,  TRUE,  9,  &CreateTypedRenderer<D3D9HWRenderer>),

        // D3D10 renderers
        RenderOption(TRUE,  FALSE, 10, &CreateTypedRenderer<D3D10SWRenderer>),

        // Default for HW composition is D3D10 with HW rendering, so it is last with everything NULL
        RenderOption(TRUE,  TRUE,  10, &CreateTypedRenderer<D3D10HWRenderer>)
    };

    _spRenderer.Free();

    BOOL fHardware = FALSE;
    IFR( _spPresentSite->IsHardwareComposition(&fHardware) );

    RenderOption currentData(fHardware, _fUseSurfacePresenter, _fUseHardwareRasterize, _d3dVersion);

    for (int i = 0; i < ARRAYSIZE(options); i++)
    {
        BaseRenderer *pNewRenderer;

        if (SUCCEEDED(options[i].CreateIfMatching(currentData, m_hWnd, &pNewRenderer)))
        {
            _spRenderer.Attach(pNewRenderer);
            break;
        }
    }

    if (_spRenderer == NULL)
    {
        return E_FAIL;
    }

    return hr;
}

HRESULT CSurfacePresenterExampleCtrl::RenderSceneImpl(BaseRenderer *pRenderer, bool fClear)
{
    HRESULT hr;

    // Draw and present a frame
    IFR( pRenderer->BeginDraw() );

    if (fClear)
    {
        // Clear the frame buffer for surface presenter
        IFR( pRenderer->Clear(BGRAPixel(0, 0, 0, 0)) );
    }

    // Draw the border
    pRenderer->SetColor(pRenderer->GetBackground());
    IFR( pRenderer->FillRect(0, 0, _presenterSize.cx, 20) );
    IFR( pRenderer->FillRect(0, 0, 20, _presenterSize.cy) );
    IFR( pRenderer->FillRect(_presenterSize.cx - 20, 0, _presenterSize.cx, _presenterSize.cy) );
    IFR( pRenderer->FillRect(0, _presenterSize.cy - 20, _presenterSize.cx, _presenterSize.cy) );

    // Draw all of the rectangles
    pRenderer->SetColor(pRenderer->GetForeground());
    for (int i = 0; i < _rectPositions.GetSize(); i++)
    {
        CPoint pos = _rectPositions[i]._position;
        IFR( pRenderer->FillRect(pos.x, pos.y, pos.x + RectSprite::Size, pos.y + RectSprite::Size) );
    }

    IFR( pRenderer->EndDraw() );

    return hr;
}

HRESULT CSurfacePresenterExampleCtrl::RenderScene()
{
    HRESULT hr;

    IFR( CreateRenderingObjects() );
    IFR( RenderSceneImpl(_spRenderer, _fUseSurfacePresenter != FALSE) );
    IFR( _spPresenter->Present(0, NULL) );

    return hr;
}

void CSurfacePresenterExampleCtrl::Tick()
{
    // This method is called after painting to change the positions of the objects
    // and schedule another paint right away. A real control will probably have a 
    // more complex system, since this method always keeps painting when the control
    // is visible, and it does not tick when the control is not visible.
    if (_spRenderer != NULL)
    {
        for (int i = 0; i < _rectPositions.GetSize(); i++)
        {
            _rectPositions[i].Tick(_objectSize);
        }

        if (_fUseSurfacePresenter)
        {
            // If we are using ISurfacePresenter, we want to sync to the rendering
            // of MSHTML. So we call in here and ask for a paint. When MSHTML is
            // about to figure out what to paint we will get a chance to Present
            // in OnPreRender.
            _spPresentSite->RequestFrame();
        }
        else
        {
            // If we are using windowless ActiveX, we InvalidateRect here and
            // we are called back to draw in OnDraw. The scene is drawn then.
            CComQIPtr<IOleInPlaceSiteWindowless> spSiteWindowless(GetClientSite());
            spSiteWindowless->InvalidateRect(NULL, TRUE);
        }
    }
}

HRESULT CSurfacePresenterExampleCtrl::CreateRenderingObjects()
{
    HRESULT hr = S_OK;

    if (_objectSize.cx < 0 || _objectSize.cy < 0)
    {
        // We don't have a valid size yet
        return E_FAIL;
    }

    // If we don't have the renderering stuff made, or the size is wrong, then recreate
    if (_objectSize != _presenterSize || _spPresenter == NULL || _spRenderer == NULL)
    {
        // Need a new presenter and renderer, free the old one
        _spPresenter.Release();

        IFR( CreateRenderer() );

        if (_fUseSurfacePresenter)
        {
            // Create a surface presenter with the size matching the control size. _spDevice will
            // be NULL for SW, which is the correct parameter to specify SW buffers from the
            // surface presenter.
            IFR( _spPresentSite->CreateSurfacePresenter(
                _spRenderer->GetDevice(), 
                _objectSize.cx, 
                _objectSize.cy, 
                1, 
                DXGI_FORMAT_B8G8R8A8_UNORM, 
                VIEW_OBJECT_ALPHA_MODE_PREMULTIPLIED, 
                &_spPresenter
                ) );
        }
        else
        {
            // Use our surface presenter simulator object for GDI windowless rendering
            CComObject<GDIPresenter> *pPresenter = NULL;
            IFR( CComObject<GDIPresenter>::CreateInstance(&pPresenter) );
            IFR( pPresenter->Initialize(_objectSize.cx, _objectSize.cy) );
            IFR( pPresenter->QueryInterface(&_spPresenter) );
        }

        _presenterSize = _objectSize;

        CComPtr<IUnknown> spBackBuffer;
        IFR( _spPresenter->GetBuffer(0, IID_PPV_ARGS(&spBackBuffer)) );
        IFR( _spRenderer->SetBackBuffer(spBackBuffer) );

        ResetRectangles();
    }

    return hr;
}

BOOL CSurfacePresenterExampleCtrl::OnSetObjectRects(LPCRECT lpRectPos, LPCRECT lpRectClip)
{
    CRect objectRect = (*lpRectPos);

    _objectSize = objectRect.Size();

    if (FAILED(RenderScene()))
    {
        return FALSE;
    }

    return COleControl::OnSetObjectRects(lpRectPos, lpRectClip);
}

void CSurfacePresenterExampleCtrl::OnSetClientSite()
{
    IOleClientSite *pSite = GetClientSite();

    if (pSite)
    {
        HRESULT hr;

        IFRV( ::CoInitialize(NULL) );
        _fCoInit = true;

        // Query for the client site
        CComPtr<IOleControlSite> spControlSite;
        IFRV( pSite->QueryInterface(&spControlSite) );

        CComPtr<IDispatch> spControlDispatch;
        IFRV( spControlSite->GetExtendedControl(&spControlDispatch) );
        IFRV( spControlDispatch->QueryInterface(&_spElement) );

        // Grab the new present site interface
        IFRV( pSite->QueryInterface(&_spPresentSite) );

        // Create our hidden window
        _window.Attach(new CHiddenWindow);
        if (!_window->Create(this, L"DemoCtrl", 1))
        {
            IFRV(E_FAIL);
        }
        
        // Make our WIC factory
        IFRV( ::CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_spWICFactory)) );
    }
    else
    {
        // If the client site is being set to NULL it means everything is being detached,
        // so we free everything here.
        _spPresentSite.Release();
        _spPresenter.Release();
        _spRenderer.Free();
        _spWICFactory.Release();

        if (_fCoInit)
        {
            _fCoInit = false;
            ::CoUninitialize();
        }
    }

    COleControl::OnSetClientSite();
}

void CSurfacePresenterExampleCtrl::SetCompositionMode()
{
    // Make sure that rendering objects get recreated
    _spPresenter.Release();
    _spRenderer.Free();

    if (_fUseSurfacePresenter)
    {
        _spPresentSite->SetCompositionMode(VIEW_OBJECT_COMPOSITION_MODE_SURFACEPRESENTER);

        // Render the scene since mshtml will not call back. This might fail if the
        // object size / position is not yet known, but that is OK since SetObjectRects
        // will eventually come in.
        RenderScene();
    }
    else
    {
        _spPresentSite->SetCompositionMode(VIEW_OBJECT_COMPOSITION_MODE_LEGACY);
    }
}

void CSurfacePresenterExampleCtrl::OnDraw(CDC* pDC, const CRect& rcBounds, const CRect& rcInvalid)
{
    _objectSize = rcBounds.Size();

    // Need rendering objects so that presenter DC can be set
    CreateRenderingObjects();

    // Set up the GDI presenter so that it will work
    CComQIPtr<IGDIPresenter> spGDIPresenter(_spPresenter);
    spGDIPresenter->SetDC(pDC->m_hDC, rcBounds.TopLeft());

    // Draw a frame
    RenderScene();

    // Animate the scene
    Tick();
}

HRESULT CSurfacePresenterExampleCtrl::EnsureAccRoot()
{
    HRESULT hr = S_OK;

    if (_spAccRoot == NULL)
    {
        // Make an accessibility object that is the root node under the
        // ActiveX control - first construct the object.
        CComObject<CRootAccessible> *pNewAcc;
        IFR( CComObject<CRootAccessible>::CreateInstance(&pNewAcc) );

        // Get the IAccessible of the object element, because that is
        // the parent of the new object we are making here.
        CComPtr<IServiceProvider> spSP;
        IFR( _spElement->QueryInterface(&spSP) );

        CComPtr<IAccessible> spParent;
        IFR( spSP->QueryService(IID_IAccessible, IID_PPV_ARGS(&spParent)) );

        CComPtr<IRectCollection> spCollection;
        IFR( GetIDispatch(FALSE)->QueryInterface(&spCollection) );

        IFR( pNewAcc->Init(spParent, spCollection) );
        IFR( pNewAcc->QueryInterface(&_spAccRoot) );
    }

    return S_OK;
}

IAccessible *CSurfacePresenterExampleCtrl::GetRootAccessible()
{
    EnsureAccRoot();

    return _spAccRoot;
}

void CSurfacePresenterExampleCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
    // Did we hit something?
    int index = m_xRectCollectionObj.HitTest(point.x, point.y);
    if (index != -1)
    {
        ::NotifyWinEvent(EVENT_OBJECT_INVOKED, _window->m_hWnd, index + 1, CHILDID_SELF);
    }
}

ULONG FAR EXPORT CSurfacePresenterExampleCtrl::XRectCollectionObj::AddRef()
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, RectCollectionObj)
    return pThis->ExternalAddRef();
}

ULONG FAR EXPORT CSurfacePresenterExampleCtrl::XRectCollectionObj::Release()
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, RectCollectionObj)
    return pThis->ExternalRelease();
}

HRESULT FAR EXPORT CSurfacePresenterExampleCtrl::XRectCollectionObj::QueryInterface(REFIID iid, void FAR* FAR* ppvObj)
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, RectCollectionObj)
    return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);
}

int CSurfacePresenterExampleCtrl::XRectCollectionObj::GetRectCount()
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, RectCollectionObj)

    return pThis->_rectPositions.GetCount();
}

RectSprite CSurfacePresenterExampleCtrl::XRectCollectionObj::GetRect(int index)
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, RectCollectionObj)

    return pThis->_rectPositions[index];
}

int CSurfacePresenterExampleCtrl::XRectCollectionObj::HitTest(int left, int top)
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, RectCollectionObj)

    int index = -1;
    for (int i = 0; i < GetRectCount(); i++)
    {
        if (left >= GetRect(i)._position.x && 
            left < GetRect(i)._position.x + 64 &&
            top >= GetRect(i)._position.y && 
            top < GetRect(i)._position.y + 64)
        {
            index = i;
        }
    }

    return index;
}

HRESULT CSurfacePresenterExampleCtrl::XRectCollectionObj::CreateAccessibleForRect(int index, IAccessible **ppRectAcc)
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, RectCollectionObj)

    if (index < 0 || index >= GetRectCount())
    {
        return E_INVALIDARG;
    }

    HRESULT hr;

    IFR( pThis->EnsureAccRoot() );

    CComPtr<IRectCollection> spCollection;
    IFR( pThis->GetIDispatch(FALSE)->QueryInterface(&spCollection) );

    CComObject<CRectAccessible> *pNewAcc;
    IFR( CComObject<CRectAccessible>::CreateInstance(&pNewAcc) );
    IFR( pNewAcc->Init(pThis->_spAccRoot, spCollection, index) );
    IFR( pNewAcc->QueryInterface(ppRectAcc) );

    return hr;
}

ULONG FAR EXPORT CSurfacePresenterExampleCtrl::XSafeScriptingObj::AddRef()
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, SafeScriptingObj)
    return pThis->ExternalAddRef();
}

ULONG FAR EXPORT CSurfacePresenterExampleCtrl::XSafeScriptingObj::Release()
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, SafeScriptingObj)
    return pThis->ExternalRelease();
}

HRESULT FAR EXPORT CSurfacePresenterExampleCtrl::XSafeScriptingObj::QueryInterface(REFIID iid, void FAR* FAR* ppvObj)
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, SafeScriptingObj)
    return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP CSurfacePresenterExampleCtrl::XSafeScriptingObj::GetInterfaceSafetyOptions( 
    REFIID riid,
    DWORD __RPC_FAR *pdwSupportedOptions,
    DWORD __RPC_FAR *pdwEnabledOptions
    )
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, SafeScriptingObj)

    (*pdwSupportedOptions) = 3;
    (*pdwEnabledOptions) = 3;

    return S_OK;
}

STDMETHODIMP CSurfacePresenterExampleCtrl::XSafeScriptingObj::SetInterfaceSafetyOptions( 
    REFIID riid,
    DWORD dwOptionSetMask,
    DWORD dwEnabledOptions
    )
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, SafeScriptingObj)

    return S_OK;
}

ULONG FAR EXPORT CSurfacePresenterExampleCtrl::XPrintObj::AddRef()
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, PrintObj)
    return pThis->ExternalAddRef();
}

ULONG FAR EXPORT CSurfacePresenterExampleCtrl::XPrintObj::Release()
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, PrintObj)
    return pThis->ExternalRelease();
}

HRESULT FAR EXPORT CSurfacePresenterExampleCtrl::XPrintObj::QueryInterface(REFIID iid, void FAR* FAR* ppvObj)
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, PrintObj)
    return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP CSurfacePresenterExampleCtrl::XPrintObj::GetPrintBitmap( 
    IUnknown **ppPrintBitmap)
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, PrintObj)

    if (pThis->_spRenderer != NULL)
    {
        HRESULT hr = S_OK;

        CComPtr<IWICBitmap> spPrintBitmap;
        IFR( pThis->_spWICFactory->CreateBitmap(
            pThis->_presenterSize.cx * 3,
            pThis->_presenterSize.cy * 3,
            GUID_WICPixelFormat32bppPBGRA,
            WICBitmapCacheOnLoad,
            &spPrintBitmap) );

        CAutoPtr<PrintRenderer> spPrintRenderer;
        spPrintRenderer.Attach(new PrintRenderer);
        if (spPrintRenderer == NULL)
        {
            return E_OUTOFMEMORY;
        }

        IFR( spPrintRenderer->SetBackBuffer(spPrintBitmap) );
        IFR( pThis->RenderSceneImpl(spPrintRenderer, true) );

        (*ppPrintBitmap) = spPrintBitmap;
        (*ppPrintBitmap)->AddRef();

        return S_OK;
    }
    else
    {
        return E_UNEXPECTED;
    }
}

ULONG FAR EXPORT CSurfacePresenterExampleCtrl::XAccessibleObj::AddRef()
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, AccessibleObj)
    return pThis->ExternalAddRef();
}

ULONG FAR EXPORT CSurfacePresenterExampleCtrl::XAccessibleObj::Release()
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, AccessibleObj)
    return pThis->ExternalRelease();
}

HRESULT FAR EXPORT CSurfacePresenterExampleCtrl::XAccessibleObj::QueryInterface(REFIID iid, void FAR* FAR* ppvObj)
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, AccessibleObj)
    return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP CSurfacePresenterExampleCtrl::XAccessibleObj::get_accParent( 
    /* [retval][out] */ __RPC__deref_out_opt IDispatch **ppdispParent)
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, AccessibleObj)

    // The host handles this, so it will never call the control to get
    // help with it. So we can safely return E_NOTIMPL here.
    return E_NOTIMPL;
}

STDMETHODIMP CSurfacePresenterExampleCtrl::XAccessibleObj::get_accChildCount( 
    /* [retval][out] */ __RPC__out long *pChildCount)
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, AccessibleObj)

    // We have a single child from here which is the accessible root for the control
    (*pChildCount) = 1;

    return S_OK;
}

STDMETHODIMP CSurfacePresenterExampleCtrl::XAccessibleObj::get_accChild( 
    /* [in] */ VARIANT varChild,
    /* [retval][out] */ __RPC__deref_out_opt IDispatch **ppdispChild)
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, AccessibleObj)

    HRESULT hr;
    int index;

    IFR( ::GetChildIndex(&varChild, &index) );

    // Children are 1 based in IAccessible land. We don't handle
    // CHILDID_SELF here either.
    if (index != 1)
    {
        return E_INVALIDARG;
    }

    IFR( pThis->EnsureAccRoot() );
    IFR( pThis->_spAccRoot->QueryInterface(ppdispChild) );
    
    return hr;
}

STDMETHODIMP CSurfacePresenterExampleCtrl::XAccessibleObj::get_accName( 
    /* [optional][in] */ VARIANT varChild,
    /* [retval][out] */ __RPC__deref_out_opt BSTR *pszName)
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, AccessibleObj)

    // Leave the default MSHTML name on this node
    (*pszName) = NULL;

    return S_FALSE;
}

STDMETHODIMP CSurfacePresenterExampleCtrl::XAccessibleObj::get_accValue( 
    /* [optional][in] */ VARIANT varChild,
    /* [retval][out] */ __RPC__deref_out_opt BSTR *pszValue)
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, AccessibleObj)

    // This control has no value, but it can return one if it likes. Since
    // there is an accessible root object for the control that might
    // be a more appropropriate place to return a value.
    (*pszValue) = NULL;

    return S_FALSE;
}

STDMETHODIMP CSurfacePresenterExampleCtrl::XAccessibleObj::get_accDescription( 
    /* [optional][in] */ VARIANT varChild,
    /* [retval][out] */ __RPC__deref_out_opt BSTR *pszDescription)
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, AccessibleObj)

    // Leave the default MSHTML description on this node
    (*pszDescription) = NULL;
    
    return S_FALSE;
}

STDMETHODIMP CSurfacePresenterExampleCtrl::XAccessibleObj::get_accRole( 
    /* [optional][in] */ VARIANT varChild,
    /* [retval][out] */ __RPC__out VARIANT *pvarRole)
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, AccessibleObj)

    HRESULT hr;

    IFR( ::CheckOnlySelf(&varChild) );

    // Return the default role
    pvarRole->vt = VT_I4;
    pvarRole->lVal = ROLE_SYSTEM_CLIENT;

    return hr;
}

STDMETHODIMP CSurfacePresenterExampleCtrl::XAccessibleObj::get_accState( 
    /* [optional][in] */ VARIANT varChild,
    /* [retval][out] */ __RPC__out VARIANT *pvarState)
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, AccessibleObj)

    HRESULT hr;

    IFR( ::CheckOnlySelf(&varChild) );

    pvarState->vt = VT_I4;
    pvarState->lVal = 0;

    return hr;
}

STDMETHODIMP CSurfacePresenterExampleCtrl::XAccessibleObj::get_accHelp( 
    /* [optional][in] */ VARIANT varChild,
    /* [retval][out] */ __RPC__deref_out_opt BSTR *pszHelp)
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, AccessibleObj)

    // Help not implemented for this sample
    (*pszHelp) = NULL;
    return S_FALSE;
}

STDMETHODIMP CSurfacePresenterExampleCtrl::XAccessibleObj::get_accHelpTopic( 
    /* [out] */ __RPC__deref_out_opt BSTR *pszHelpFile,
    /* [optional][in] */ VARIANT varChild,
    /* [retval][out] */ __RPC__out long *pidTopic)
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, AccessibleObj)

    // The host handles this, so it will never call the control to get
    // help with it. So we can safely return E_NOTIMPL here.
    return E_NOTIMPL;
}

STDMETHODIMP CSurfacePresenterExampleCtrl::XAccessibleObj::get_accKeyboardShortcut( 
    /* [optional][in] */ VARIANT varChild,
    /* [retval][out] */ __RPC__deref_out_opt BSTR *pszKeyboardShortcut)
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, AccessibleObj)

    // No shortcut for this control
    (*pszKeyboardShortcut) = NULL;
    return S_FALSE;
}

STDMETHODIMP CSurfacePresenterExampleCtrl::XAccessibleObj::get_accFocus( 
    /* [retval][out] */ __RPC__out VARIANT *pvarChild)
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, AccessibleObj)

    pvarChild->vt = VT_EMPTY;
    return S_FALSE;
}

STDMETHODIMP CSurfacePresenterExampleCtrl::XAccessibleObj::get_accSelection( 
    /* [retval][out] */ __RPC__out VARIANT *pvarChildren)
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, AccessibleObj)

    // No selections in this object
    pvarChildren->vt = VT_EMPTY;
    return S_OK;
}

STDMETHODIMP CSurfacePresenterExampleCtrl::XAccessibleObj::get_accDefaultAction( 
    /* [optional][in] */ VARIANT varChild,
    /* [retval][out] */ __RPC__deref_out_opt BSTR *pszDefaultAction)
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, AccessibleObj)

    // No default action
    (*pszDefaultAction) = NULL;
    return S_FALSE;
}

STDMETHODIMP CSurfacePresenterExampleCtrl::XAccessibleObj::accSelect( 
    /* [in] */ long flagsSelect,
    /* [optional][in] */ VARIANT varChild)
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, AccessibleObj)

    return E_NOTIMPL;
}

STDMETHODIMP CSurfacePresenterExampleCtrl::XAccessibleObj::accLocation( 
    /* [out] */ __RPC__out long *pxLeft,
    /* [out] */ __RPC__out long *pyTop,
    /* [out] */ __RPC__out long *pcxWidth,
    /* [out] */ __RPC__out long *pcyHeight,
    /* [optional][in] */ VARIANT varChild)
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, AccessibleObj)

    HRESULT hr;

    int index;
    IFR( ::GetChildIndex(&varChild, &index) );

    // The host should only call this with child index values, and we
    // only have a single child.
    if (index != 1)
    {
        return E_INVALIDARG;
    }

    IFR( pThis->EnsureAccRoot() );

    CComVariant varSelf(CHILDID_SELF);
    IFR( pThis->_spAccRoot->accLocation(pxLeft, pyTop, pcxWidth, pcyHeight, varSelf) );

    return hr;
}

STDMETHODIMP CSurfacePresenterExampleCtrl::XAccessibleObj::accNavigate( 
    /* [in] */ long navDir,
    /* [optional][in] */ VARIANT varStart,
    /* [retval][out] */ __RPC__out VARIANT *pvarEndUpAt)
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, AccessibleObj)

    HRESULT hr;

    IFR( ::CheckOnlySelf(&varStart) );

    int index = -1;
    pvarEndUpAt->vt = VT_EMPTY;

    if (navDir != NAVDIR_FIRSTCHILD && navDir != NAVDIR_LASTCHILD)
    {
        return S_FALSE;
    }

    IFR( pThis->EnsureAccRoot() );
    IFR( pThis->_spAccRoot->QueryInterface(&pvarEndUpAt->pdispVal) );
    pvarEndUpAt->vt = VT_DISPATCH;

    return hr;
}

STDMETHODIMP CSurfacePresenterExampleCtrl::XAccessibleObj::accHitTest( 
    /* [in] */ long xLeft,
    /* [in] */ long yTop,
    /* [retval][out] */ __RPC__out VARIANT *pvarChild)
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, AccessibleObj)

    HRESULT hr;

    // The control is covered by the root accessible object
    IFR( pThis->EnsureAccRoot() );
    IFR( pThis->_spAccRoot->QueryInterface(&pvarChild->pdispVal) );
    pvarChild->vt = VT_DISPATCH;

    return hr;
}

STDMETHODIMP CSurfacePresenterExampleCtrl::XAccessibleObj::accDoDefaultAction( 
    /* [optional][in] */ VARIANT varChild)
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, AccessibleObj)

    // This control has no default action
    return DISP_E_MEMBERNOTFOUND;
}

STDMETHODIMP CSurfacePresenterExampleCtrl::XAccessibleObj::put_accName( 
    /* [optional][in] */ VARIANT varChild,
    /* [in] */ __RPC__in BSTR szName)
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, AccessibleObj)

    return E_NOTIMPL;
}

STDMETHODIMP CSurfacePresenterExampleCtrl::XAccessibleObj::put_accValue( 
    /* [optional][in] */ VARIANT varChild,
    /* [in] */ __RPC__in BSTR szValue)
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, AccessibleObj)

    return DISP_E_MEMBERNOTFOUND;
}

STDMETHODIMP CSurfacePresenterExampleCtrl::XAccessibleObj::GetTypeInfoCount( 
    /* [out] */ __RPC__out UINT *pctinfo)
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, AccessibleObj)

    return E_NOTIMPL;
}

STDMETHODIMP CSurfacePresenterExampleCtrl::XAccessibleObj::GetTypeInfo( 
    /* [in] */ UINT iTInfo,
    /* [in] */ LCID lcid,
    /* [out] */ __RPC__deref_out_opt ITypeInfo **ppTInfo)
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, AccessibleObj)

    return E_NOTIMPL;
}

STDMETHODIMP CSurfacePresenterExampleCtrl::XAccessibleObj::GetIDsOfNames( 
    /* [in] */ __RPC__in REFIID riid,
    /* [size_is][in] */ __RPC__in_ecount_full(cNames) LPOLESTR *rgszNames,
    /* [range][in] */ __RPC__in_range(0,16384) UINT cNames,
    /* [in] */ LCID lcid,
    /* [size_is][out] */ __RPC__out_ecount_full(cNames) DISPID *rgDispId)
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, AccessibleObj)

    return E_NOTIMPL;
}

STDMETHODIMP CSurfacePresenterExampleCtrl::XAccessibleObj::Invoke( 
    /* [in] */ DISPID dispIdMember,
    /* [in] */ REFIID riid,
    /* [in] */ LCID lcid,
    /* [in] */ WORD wFlags,
    /* [out][in] */ DISPPARAMS *pDispParams,
    /* [out] */ VARIANT *pVarResult,
    /* [out] */ EXCEPINFO *pExcepInfo,
    /* [out] */ UINT *puArgErr)
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, AccessibleObj)

    return E_NOTIMPL;
}

ULONG FAR EXPORT CSurfacePresenterExampleCtrl::XViewObjectPresentNotifyObj::AddRef()
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, ViewObjectPresentNotifyObj)
    return pThis->ExternalAddRef();
}

ULONG FAR EXPORT CSurfacePresenterExampleCtrl::XViewObjectPresentNotifyObj::Release()
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, ViewObjectPresentNotifyObj)
    return pThis->ExternalRelease();
}

HRESULT FAR EXPORT CSurfacePresenterExampleCtrl::XViewObjectPresentNotifyObj::QueryInterface(REFIID iid, void FAR* FAR* ppvObj)
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, ViewObjectPresentNotifyObj)
    return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP CSurfacePresenterExampleCtrl::XViewObjectPresentNotifyObj::OnPreRender()
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, ViewObjectPresentNotifyObj)

    // This callback is only called if we are using the surface presenter. It means
    // that we can just draw now and present to MSHTML.
    pThis->RenderScene();

    // We tick each render in the sample. A real control would probably
    // have a more complex way to manage time so that varying frame
    // rates and the window being hidden could be handled.
    pThis->Tick();

    return S_OK;
}

ULONG FAR EXPORT CSurfacePresenterExampleCtrl::XBFCacheableObj::AddRef()
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, BFCacheableObj)
    return pThis->ExternalAddRef();
}

ULONG FAR EXPORT CSurfacePresenterExampleCtrl::XBFCacheableObj::Release()
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, BFCacheableObj)
    return pThis->ExternalRelease();
}

HRESULT FAR EXPORT CSurfacePresenterExampleCtrl::XBFCacheableObj::QueryInterface(REFIID iid, void FAR* FAR* ppvObj)
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, BFCacheableObj)
    return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP CSurfacePresenterExampleCtrl::XBFCacheableObj::EnterBFCache()
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, BFCacheableObj)
    static int s_cCacheAttemptsRemaining = 3;
    
    return (s_cCacheAttemptsRemaining-- > 0 ? S_OK : E_FAIL);
}

STDMETHODIMP CSurfacePresenterExampleCtrl::XBFCacheableObj::ExitBFCache()
{
    METHOD_PROLOGUE(CSurfacePresenterExampleCtrl, BFCacheableObj)
    return S_OK;
}
