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

#include "SurfacePresenter.h"
#include "BaseRenderer.h"
#include "RectSprite.h"

class CHiddenWindow;

struct __declspec(uuid("b50c85b2-e724-4613-b94e-f6cd4285b072"))
IRectCollection : public IUnknown
{
    virtual int GetRectCount() = 0;
    virtual RectSprite GetRect(int index) = 0;
    virtual int HitTest(int left, int top) = 0;
    virtual HRESULT CreateAccessibleForRect(int index, IAccessible **) = 0;
};

class CSurfacePresenterExampleCtrl : public COleControl
{
    DECLARE_DYNCREATE(CSurfacePresenterExampleCtrl)

public:
    CSurfacePresenterExampleCtrl();

public:
    void OnDraw(CDC* pDC, const CRect& rcBounds, const CRect& rcInvalid) override;
    BOOL OnSetObjectRects(LPCRECT lpRectPos, LPCRECT lpRectClip) override;
    void OnSetClientSite() override;
    void DoPropExchange(CPropExchange* pPX) override;
    void OnResetState() override;
    DWORD GetControlFlags() override;
    IAccessible *GetRootAccessible();
    void Tick();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

protected:
    ~CSurfacePresenterExampleCtrl();

    DECLARE_OLECREATE_EX(CSurfacePresenterExampleCtrl)    // Class factory and guid
    DECLARE_OLETYPELIB(CSurfacePresenterExampleCtrl)      // GetTypeInfo
    DECLARE_PROPPAGEIDS(CSurfacePresenterExampleCtrl)     // Property page IDs
    DECLARE_OLECTLTYPE(CSurfacePresenterExampleCtrl)		// Type name and misc status

    // Interface map
    DECLARE_INTERFACE_MAP()

    // Message maps
    DECLARE_MESSAGE_MAP()

    // Dispatch maps
    DECLARE_DISPATCH_MAP()

    // Event maps
    DECLARE_EVENT_MAP()

    BEGIN_INTERFACE_PART(ViewObjectPresentNotifyObj, IViewObjectPresentNotify)
        STDMETHOD(OnPreRender)();
    END_INTERFACE_PART(ViewObjectPresentNotifyObj)

    BEGIN_INTERFACE_PART(BFCacheableObj, IBFCacheable)
        STDMETHOD(EnterBFCache)();
        STDMETHOD(ExitBFCache)();
    END_INTERFACE_PART(BFCacheableObj)

    BEGIN_INTERFACE_PART(PrintObj, IViewObjectPrint)
        STDMETHOD(GetPrintBitmap)( 
            /* [out][retval] */ __RPC__deref_out_opt IUnknown **ppPrintBitmap);

    END_INTERFACE_PART(PrintObj)

    // IRectCollection implementation
    BEGIN_INTERFACE_PART(RectCollectionObj, IRectCollection)
        int GetRectCount();
        RectSprite GetRect(int index);
        int HitTest(int left, int top);
        HRESULT CreateAccessibleForRect(int index, IAccessible **ppRectAcc);
    END_INTERFACE_PART(RectCollectionObj)

    // IObjectSafety implementation
    BEGIN_INTERFACE_PART(SafeScriptingObj, IObjectSafety)
        STDMETHOD(GetInterfaceSafetyOptions)( 
            /* [in]  */ REFIID riid,
            /* [out] */ DWORD __RPC_FAR *pdwSupportedOptions,
            /* [out] */ DWORD __RPC_FAR *pdwEnabledOptions);

        STDMETHOD(SetInterfaceSafetyOptions)( 
            /* [in] */ REFIID riid,
            /* [in] */ DWORD dwOptionSetMask,
            /* [in] */ DWORD dwEnabledOptions);
    END_INTERFACE_PART(SafeScriptingObj)

    // IAccessible implementation
    BEGIN_INTERFACE_PART(AccessibleObj, IAccessible)
        STDMETHOD(get_accParent)( 
            /* [retval][out] */ __RPC__deref_out_opt IDispatch **ppdispParent);
        
        STDMETHOD(get_accChildCount)( 
            /* [retval][out] */ __RPC__out long *pcountChildren);
        
        STDMETHOD(get_accChild)( 
            /* [in] */ VARIANT varChild,
            /* [retval][out] */ __RPC__deref_out_opt IDispatch **ppdispChild);
        
        STDMETHOD(get_accName)( 
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *pszName);
        
        STDMETHOD(get_accValue)( 
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *pszValue);
        
        STDMETHOD(get_accDescription)( 
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *pszDescription);
        
        STDMETHOD(get_accRole)( 
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ __RPC__out VARIANT *pvarRole);
        
        STDMETHOD(get_accState)( 
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ __RPC__out VARIANT *pvarState);
        
        STDMETHOD(get_accHelp)( 
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *pszHelp);
        
        STDMETHOD(get_accHelpTopic)( 
            /* [out] */ __RPC__deref_out_opt BSTR *pszHelpFile,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ __RPC__out long *pidTopic);
        
        STDMETHOD(get_accKeyboardShortcut)( 
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *pszKeyboardShortcut);
        
        STDMETHOD(get_accFocus)( 
            /* [retval][out] */ __RPC__out VARIANT *pvarChild);
        
        STDMETHOD(get_accSelection)( 
            /* [retval][out] */ __RPC__out VARIANT *pvarChildren);
        
        STDMETHOD(get_accDefaultAction)( 
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ __RPC__deref_out_opt BSTR *pszDefaultAction);
        
        STDMETHOD(accSelect)( 
            /* [in] */ long flagsSelect,
            /* [optional][in] */ VARIANT varChild);
        
        STDMETHOD(accLocation)( 
            /* [out] */ __RPC__out long *pxLeft,
            /* [out] */ __RPC__out long *pyTop,
            /* [out] */ __RPC__out long *pcxWidth,
            /* [out] */ __RPC__out long *pcyHeight,
            /* [optional][in] */ VARIANT varChild);
        
        STDMETHOD(accNavigate)( 
            /* [in] */ long navDir,
            /* [optional][in] */ VARIANT varStart,
            /* [retval][out] */ __RPC__out VARIANT *pvarEndUpAt);
        
        STDMETHOD(accHitTest)( 
            /* [in] */ long xLeft,
            /* [in] */ long yTop,
            /* [retval][out] */ __RPC__out VARIANT *pvarChild);
        
        STDMETHOD(accDoDefaultAction)( 
            /* [optional][in] */ VARIANT varChild);
        
        STDMETHOD(put_accName)( 
            /* [optional][in] */ VARIANT varChild,
            /* [in] */ __RPC__in BSTR szName);
        
        STDMETHOD(put_accValue)( 
            /* [optional][in] */ VARIANT varChild,
            /* [in] */ __RPC__in BSTR szValue);

        STDMETHOD(GetTypeInfoCount)( 
            /* [out] */ __RPC__out UINT *pctinfo);
        
        STDMETHOD(GetTypeInfo)( 
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ __RPC__deref_out_opt ITypeInfo **ppTInfo);
        
        STDMETHOD(GetIDsOfNames)( 
            /* [in] */ __RPC__in REFIID riid,
            /* [size_is][in] */ __RPC__in_ecount_full(cNames) LPOLESTR *rgszNames,
            /* [range][in] */ __RPC__in_range(0,16384) UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ __RPC__out_ecount_full(cNames) DISPID *rgDispId);
        
        STDMETHOD(Invoke)( 
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);

    END_INTERFACE_PART(AccessibleObj)

private:
    HRESULT CreateRenderingObjects();
    HRESULT CreateRenderer();
    HRESULT RenderSceneImpl(BaseRenderer *pRenderer, bool fClear);
    HRESULT RenderScene();

    void OnRendererPropertyChange();
    void OnRectsChange();
    void SetCompositionMode();
    void ResetRectangles();

    template<typename T>
    static HRESULT CreateTypedRenderer(HWND hWnd, BaseRenderer **ppRenderer)
    {
        HRESULT hr;

        BaseRenderer *pNewRenderer = new T();
        if (pNewRenderer == NULL)
        {
            return E_OUTOFMEMORY;
        }

        IFR( pNewRenderer->Initialize(hWnd) );

        (*ppRenderer) = pNewRenderer;

        return hr;
    }

    HRESULT EnsureAccRoot();

private:
    // The interface on the client site that gives us ISurfacePresenter
    CComPtr<IViewObjectPresentNotifySite> _spPresentSite;

    // The surface presenter we are drawing to
    CComPtr<ISurfacePresenter> _spPresenter;

    // The object element we are sited in
    CComPtr<IHTMLObjectElement> _spElement;

    // The accessible root of the control
    CComPtr<IAccessible> _spAccRoot;

    // The size of the control
    CSize _objectSize;

    // The size we created the presenter with
    CSize _presenterSize;

    // Renderer and attributes used to choose the renderer
    CAutoPtr<BaseRenderer> _spRenderer;
    int _d3dVersion;
    BOOL _fUseSurfacePresenter;
    BOOL _fUseHardwareRasterize;

    // Property for rectangles and their data
    int _numRects;
    CArray<RectSprite> _rectPositions;

    // Our hidden window used for doing stuff that has to have a window
    CAutoPtr<CHiddenWindow> _window;

    // Our WIC factory
    CComPtr<IWICImagingFactory> _spWICFactory;
    bool _fCoInit;
};
