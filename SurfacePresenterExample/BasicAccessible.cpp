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

CBasicAccessible::CBasicAccessible(void)
{
}

CBasicAccessible::~CBasicAccessible(void)
{
}

HRESULT CBasicAccessible::Init(IAccessible *pParent)
{
    _spParent = pParent;

    return S_OK;
}

STDMETHODIMP CBasicAccessible::get_accParent( 
    /* [retval][out] */ __RPC__deref_out_opt IDispatch **ppdispParent)
{
    // Return the object element as the parent
    return _spParent->QueryInterface(ppdispParent);
}

STDMETHODIMP CBasicAccessible::get_accValue( 
    /* [optional][in] */ VARIANT varChild,
    /* [retval][out] */ __RPC__deref_out_opt BSTR *pszValue)
{
    HRESULT hr;

    IFR( ::CheckOnlySelf(&varChild) );

    // No value
    (*pszValue) = NULL;

    return S_FALSE;
}

STDMETHODIMP CBasicAccessible::get_accDescription( 
    /* [optional][in] */ VARIANT varChild,
    /* [retval][out] */ __RPC__deref_out_opt BSTR *pszDescription)
{
    HRESULT hr;

    IFR( ::CheckOnlySelf(&varChild) );

    // No description
    (*pszDescription) = NULL;
    
    return hr;
}

STDMETHODIMP CBasicAccessible::get_accState( 
    /* [optional][in] */ VARIANT varChild,
    /* [retval][out] */ __RPC__out VARIANT *pvarState)
{
    HRESULT hr;

    IFR( ::CheckOnlySelf(&varChild) );

    pvarState->vt = VT_I4;
    pvarState->lVal = 0;

    return hr;
}

STDMETHODIMP CBasicAccessible::get_accHelp( 
    /* [optional][in] */ VARIANT varChild,
    /* [retval][out] */ __RPC__deref_out_opt BSTR *pszHelp)
{
    // Help not implemented for this sample
    (*pszHelp) = NULL;
    return S_FALSE;
}

STDMETHODIMP CBasicAccessible::get_accHelpTopic( 
    /* [out] */ __RPC__deref_out_opt BSTR *pszHelpFile,
    /* [optional][in] */ VARIANT varChild,
    /* [retval][out] */ __RPC__out long *pidTopic)
{
    // Help not implemented for this sample
    (*pszHelpFile) = NULL;
    (*pidTopic) = 0;
    return S_FALSE;
}

STDMETHODIMP CBasicAccessible::get_accKeyboardShortcut( 
    /* [optional][in] */ VARIANT varChild,
    /* [retval][out] */ __RPC__deref_out_opt BSTR *pszKeyboardShortcut)
{
    // No shortcuts for this sample
    (*pszKeyboardShortcut) = NULL;
    return S_FALSE;
}

STDMETHODIMP CBasicAccessible::get_accFocus( 
    /* [retval][out] */ __RPC__out VARIANT *pvarChild)
{
    // No focus support
    pvarChild->vt = VT_EMPTY;
    return S_FALSE;
}

STDMETHODIMP CBasicAccessible::get_accSelection( 
    /* [retval][out] */ __RPC__out VARIANT *pvarChildren)
{
    // No selections in this object
    pvarChildren->vt = VT_EMPTY;
    return S_OK;
}

STDMETHODIMP CBasicAccessible::get_accDefaultAction( 
    /* [optional][in] */ VARIANT varChild,
    /* [retval][out] */ __RPC__deref_out_opt BSTR *pszDefaultAction)
{
    // No default action
    (*pszDefaultAction) = NULL;
    return S_FALSE;
}

STDMETHODIMP CBasicAccessible::accSelect( 
    /* [in] */ long flagsSelect,
    /* [optional][in] */ VARIANT varChild)
{
    return E_NOTIMPL;
}

STDMETHODIMP CBasicAccessible::accNavigate( 
    /* [in] */ long navDir,
    /* [optional][in] */ VARIANT varStart,
    /* [retval][out] */ __RPC__out VARIANT *pvarEndUpAt)
{
    // No children
    pvarEndUpAt->vt = VT_EMPTY;
    return S_FALSE;
}

STDMETHODIMP CBasicAccessible::accDoDefaultAction( 
    /* [optional][in] */ VARIANT varChild)
{
    return DISP_E_MEMBERNOTFOUND;
}

STDMETHODIMP CBasicAccessible::put_accName( 
    /* [optional][in] */ VARIANT varChild,
    /* [in] */ __RPC__in BSTR szName)
{
    return E_NOTIMPL;
}

STDMETHODIMP CBasicAccessible::put_accValue( 
    /* [optional][in] */ VARIANT varChild,
    /* [in] */ __RPC__in BSTR szValue)
{
    return DISP_E_MEMBERNOTFOUND;
}

STDMETHODIMP CBasicAccessible::GetTypeInfoCount( 
    /* [out] */ __RPC__out UINT *pctinfo)
{
    return E_NOTIMPL;
}

STDMETHODIMP CBasicAccessible::GetTypeInfo( 
    /* [in] */ UINT iTInfo,
    /* [in] */ LCID lcid,
    /* [out] */ __RPC__deref_out_opt ITypeInfo **ppTInfo)
{
    return E_NOTIMPL;
}

STDMETHODIMP CBasicAccessible::GetIDsOfNames( 
    /* [in] */ __RPC__in REFIID riid,
    /* [size_is][in] */ __RPC__in_ecount_full(cNames) LPOLESTR *rgszNames,
    /* [range][in] */ __RPC__in_range(0,16384) UINT cNames,
    /* [in] */ LCID lcid,
    /* [size_is][out] */ __RPC__out_ecount_full(cNames) DISPID *rgDispId)
{
    return E_NOTIMPL;
}

STDMETHODIMP CBasicAccessible::Invoke( 
    /* [in] */ DISPID dispIdMember,
    /* [in] */ REFIID riid,
    /* [in] */ LCID lcid,
    /* [in] */ WORD wFlags,
    /* [out][in] */ DISPPARAMS *pDispParams,
    /* [out] */ VARIANT *pVarResult,
    /* [out] */ EXCEPINFO *pExcepInfo,
    /* [out] */ UINT *puArgErr)
{
    return E_NOTIMPL;
}
