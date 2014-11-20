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

// This is the root IAccessible for the control. The control itself does not implement this
// because its IAccessible implementation is used to augment the site of the ActiveX
// control
class CBasicAccessible : 
    public CComObjectRootEx<CComMultiThreadModelNoCS>,
    public IAccessible
{
public:
    BEGIN_COM_MAP(CBasicAccessible)
        COM_INTERFACE_ENTRY(IAccessible)
        COM_INTERFACE_ENTRY(IDispatch)
    END_COM_MAP()

    CBasicAccessible();
    ~CBasicAccessible();

    HRESULT Init(IAccessible *pParent);

    // IAcccessible implementation
    STDMETHOD(get_accParent)( 
        /* [retval][out] */ __RPC__deref_out_opt IDispatch **ppdispParent);

    STDMETHOD(get_accValue)( 
        /* [optional][in] */ VARIANT varChild,
        /* [retval][out] */ __RPC__deref_out_opt BSTR *pszValue);

    STDMETHOD(get_accDescription)( 
        /* [optional][in] */ VARIANT varChild,
        /* [retval][out] */ __RPC__deref_out_opt BSTR *pszDescription);

    STDMETHOD(get_accState)( 
        /* [optional][in] */ VARIANT varChild,
        /* [retval][out] */ __RPC__out VARIANT *pvarState);

    STDMETHOD(get_accHelp)( 
        /* [optional][in] */ VARIANT varhild,
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

    STDMETHOD(accNavigate)( 
        /* [in] */ long navDir,
        /* [optional][in] */ VARIANT varStart,
        /* [retval][out] */ __RPC__out VARIANT *pvarEndUpAt);

    STDMETHOD(get_accDefaultAction)( 
        /* [optional][in] */ VARIANT varChild,
        /* [retval][out] */ __RPC__deref_out_opt BSTR *pszDefaultAction);

    STDMETHOD(accSelect)( 
        /* [in] */ long flagsSelect,
        /* [optional][in] */ VARIANT varChild);

    STDMETHOD(accDoDefaultAction)( 
        /* [optional][in] */ VARIANT varChild);

    STDMETHOD(put_accName)( 
        /* [optional][in] */ VARIANT varChild,
        /* [in] */ __RPC__in BSTR szName);

    STDMETHOD(put_accValue)( 
        /* [optional][in] */ VARIANT varChild,
        /* [in] */ __RPC__in BSTR szValue);

    // IDispatch implementation
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

protected:
    IAccessible *GetParent() const { return _spParent; }

private:
    CComPtr<IAccessible> _spParent;
};
