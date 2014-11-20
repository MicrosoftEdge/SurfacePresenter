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
#include "AccHelper.h"

HRESULT CheckOnlySelf(VARIANT *pChild)
{
    // Only support getting name for self
    if (pChild->vt != VT_I4 || pChild->lVal != CHILDID_SELF)
    {
        return E_INVALIDARG;
    }
    
    return S_OK;
}

HRESULT GetChildIndex(VARIANT *pChild, int *pIndex)
{
    // Only support getting name for self
    if (pChild->vt != VT_I4)
    {
        return E_INVALIDARG;
    }

    (*pIndex) = pChild->lVal;
    
    return S_OK;
}