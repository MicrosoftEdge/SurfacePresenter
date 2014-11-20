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
#include "StdAfx.h"
#include "RootAccessible.h"
#include "RectAccessible.h"
#include "AccHelper.h"
#include "SurfacePresenterExampleCtrl.h"

CRootAccessible::CRootAccessible(void)
{
}

CRootAccessible::~CRootAccessible(void)
{
}

HRESULT CRootAccessible::Init(IAccessible *pParent, IRectCollection *pCollection)
{
    HRESULT hr;

    IFR( CBasicAccessible::Init(pParent) );

    _spCollection = pCollection;

    return S_OK;
}

STDMETHODIMP CRootAccessible::get_accChildCount( 
    /* [retval][out] */ __RPC__out long *pChildCount)
{
    // Each rectangle is a child
    *pChildCount = _spCollection->GetRectCount();

    return S_OK;
}

STDMETHODIMP CRootAccessible::get_accChild( 
    /* [in] */ VARIANT varChild,
    /* [retval][out] */ __RPC__deref_out_opt IDispatch **ppdispChild)
{
    HRESULT hr;
    int index;

    IFR( ::GetChildIndex(&varChild, &index) );

    // index is 1 based
    index--;

    if (index < 0 || index >= _spCollection->GetRectCount())
    {
        return E_INVALIDARG;
    }

    CComPtr<IAccessible> spAccRect;
    IFR( _spCollection->CreateAccessibleForRect(index, &spAccRect) );
    IFR( spAccRect->QueryInterface(ppdispChild) );
    
    return hr;
}

STDMETHODIMP CRootAccessible::get_accName( 
    /* [optional][in] */ VARIANT varChild,
    /* [retval][out] */ __RPC__deref_out_opt BSTR *pszName)
{
    HRESULT hr;

    IFR( ::CheckOnlySelf(&varChild) );

    *pszName = ::SysAllocString(L"SurfacePresenter Example Control Accessibility Root");

    return hr;
}

STDMETHODIMP CRootAccessible::accLocation( 
    /* [out] */ __RPC__out long *pxLeft,
    /* [out] */ __RPC__out long *pyTop,
    /* [out] */ __RPC__out long *pcxWidth,
    /* [out] */ __RPC__out long *pcyHeight,
    /* [optional][in] */ VARIANT varChild)
{
    HRESULT hr;

    IFR( CheckOnlySelf(&varChild) );

    // Same location as parent, because this node represents the whole control
    CComVariant varSelf(CHILDID_SELF);
    IFR( GetParent()->accLocation(pxLeft, pyTop, pcxWidth, pcyHeight, varSelf) );

    return hr;
}

STDMETHODIMP CRootAccessible::accHitTest( 
    /* [in] */ long xLeft,
    /* [in] */ long yTop,
    /* [retval][out] */ __RPC__out VARIANT *pvarChild)
{
    HRESULT hr = S_OK;

    // Find parent location
    long parentLeft, parentTop, parentWidth, parentHeight;
    CComVariant varSelf(CHILDID_SELF);
    IFR( GetParent()->accLocation(&parentLeft, &parentTop, &parentWidth, &parentHeight, varSelf) );

    // Convert input to local coordinates
    xLeft -= parentLeft;
    yTop -= parentTop;

    int index = _spCollection->HitTest(xLeft, yTop);

    if (index == -1)
    {
        pvarChild->vt = VT_I4;
        pvarChild->lVal = CHILDID_SELF;
    }
    else
    {
        pvarChild->vt = VT_DISPATCH;

        CComObject<CRectAccessible> *pNewAcc;
        IFR( CComObject<CRectAccessible>::CreateInstance(&pNewAcc) );

        CComPtr<IAccessible> spRoot;
        IFR( QueryInterface(IID_PPV_ARGS(&spRoot)) );
        IFR( pNewAcc->Init(spRoot, _spCollection, index) );
        IFR( pNewAcc->QueryInterface(&pvarChild->pdispVal) );
    }

    return S_OK;
}

STDMETHODIMP CRootAccessible::get_accRole( 
    /* [optional][in] */ VARIANT varChild,
    /* [retval][out] */ __RPC__out VARIANT *pvarRole)
{
    HRESULT hr;

    IFR( ::CheckOnlySelf(&varChild) );

    pvarRole->vt = VT_I4;
    pvarRole->lVal = ROLE_SYSTEM_CLIENT;

    return hr;
}

