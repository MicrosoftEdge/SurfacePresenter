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

#include "BasicAccessible.h"

struct IRectCollection;

// This is the root IAccessible for the control. The control itself does not implement this
// because its IAccessible implementation is used to augment the site of the ActiveX
// control
class CRootAccessible : public CBasicAccessible
{
public:
    CRootAccessible();
    ~CRootAccessible();

    HRESULT Init(IAccessible *pParent, IRectCollection *pCollection);

    // IAcccessible implementation that the basic accessibility object
    // did not provide.
    STDMETHOD(get_accChildCount)( 
        /* [retval][out] */ __RPC__out long *pcountChildren);

    STDMETHOD(get_accChild)( 
        /* [in] */ VARIANT varChild,
        /* [retval][out] */ __RPC__deref_out_opt IDispatch **ppdispChild);

    STDMETHOD(get_accName)( 
        /* [optional][in] */ VARIANT varChild,
        /* [retval][out] */ __RPC__deref_out_opt BSTR *pszName);

    STDMETHOD(accLocation)( 
        /* [out] */ __RPC__out long *pxLeft,
        /* [out] */ __RPC__out long *pyTop,
        /* [out] */ __RPC__out long *pcxWidth,
        /* [out] */ __RPC__out long *pcyHeight,
        /* [optional][in] */ VARIANT varChild);

    STDMETHOD(accHitTest)( 
        /* [in] */ long xLeft,
        /* [in] */ long yTop,
        /* [retval][out] */ __RPC__out VARIANT *pvarChild);

    STDMETHOD(get_accRole)( 
        /* [optional][in] */ VARIANT varChild,
        /* [retval][out] */ __RPC__out VARIANT *pvarRole);

private:
    CComPtr<IRectCollection> _spCollection;
};
