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
#include "RectAccessible.h"
#include "AccHelper.h"
#include "SurfacePresenterExampleCtrl.h"

CRectAccessible::CRectAccessible(void)
{
}

CRectAccessible::~CRectAccessible(void)
{
}

HRESULT CRectAccessible::Init(IAccessible *pParent, IRectCollection *pCollection, int index)
{
    HRESULT hr;

    IFR( CBasicAccessible::Init(pParent) );

    _index = index;
    _spCollection = pCollection;

    return hr;
}

STDMETHODIMP CRectAccessible::get_accChildCount( 
    /* [retval][out] */ __RPC__out long *pChildCount)
{
    // The rectangles have no children
    *pChildCount = 0;
    return S_OK;
}

STDMETHODIMP CRectAccessible::get_accChild( 
    /* [in] */ VARIANT varChild,
    /* [retval][out] */ __RPC__deref_out_opt IDispatch **ppdispChild)
{
    // The rectangles have no children
    return E_INVALIDARG;
}

STDMETHODIMP CRectAccessible::get_accName( 
    /* [optional][in] */ VARIANT varChild,
    /* [retval][out] */ __RPC__deref_out_opt BSTR *pszName)
{;
    HRESULT hr;

    IFR( ::CheckOnlySelf(&varChild) );

    CString nameString;
    nameString.Format(L"Surface Presenter Demo Rectangle %d", _index);

    *pszName = ::SysAllocString(nameString);

    return hr;
}

STDMETHODIMP CRectAccessible::accLocation( 
    /* [out] */ __RPC__out long *pxLeft,
    /* [out] */ __RPC__out long *pyTop,
    /* [out] */ __RPC__out long *pcxWidth,
    /* [out] */ __RPC__out long *pcyHeight,
    /* [optional][in] */ VARIANT varChild)
{
    HRESULT hr;

    IFR( CheckOnlySelf(&varChild) );

    // We are offset from our parent, so get its rectangle
    CComVariant varSelf(CHILDID_SELF);
    IFR( GetParent()->accLocation(pxLeft, pyTop, pcxWidth, pcyHeight, varSelf) );

    RectSprite sprite = _spCollection->GetRect(_index);

    (*pxLeft) += sprite._position.x;
    (*pyTop) += sprite._position.y;
    *pcxWidth = RectSprite::Size;
    *pcyHeight = RectSprite::Size;

    return hr;
}

STDMETHODIMP CRectAccessible::accHitTest( 
    /* [in] */ long xLeft,
    /* [in] */ long yTop,
    /* [retval][out] */ __RPC__out VARIANT *pvarChild)
{
    pvarChild->vt = VT_I4;
    pvarChild->lVal = CHILDID_SELF;

    return S_OK;
}

STDMETHODIMP CRectAccessible::get_accRole( 
    /* [optional][in] */ VARIANT varChild,
    /* [retval][out] */ __RPC__out VARIANT *pvarRole)
{
    HRESULT hr;

    IFR( ::CheckOnlySelf(&varChild) );

    pvarRole->vt = VT_I4;
    pvarRole->lVal = ROLE_SYSTEM_GRAPHIC;

    return hr;
}

STDMETHODIMP CRectAccessible::get_accDefaultAction( 
    /* [optional][in] */ VARIANT varChild,
    /* [retval][out] */ __RPC__deref_out_opt BSTR *pszDefaultAction)
{
    HRESULT hr;

    IFR( ::CheckOnlySelf(&varChild) );

    *pszDefaultAction = SysAllocString(L"click");

    return hr;
}

STDMETHODIMP CRectAccessible::accDoDefaultAction( 
    /* [optional][in] */ VARIANT varChild)
{
    // There isn't an action implemented in this sample,
    // but we did return a default action description ("click")
    // above, so we should return a success code here.
    // If we had returned no string for the default action
    // we would return DISP_E_MEMBERNOTFOUND here.
    return S_OK;
}
