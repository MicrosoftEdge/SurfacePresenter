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
#include "HDCRenderer.h"
#include "SurfacePresenter.h"

HRESULT HDCRenderer::SetBackBuffer(IUnknown *pBuffer)
{
    HRESULT hr;

    CComPtr<IGDIPresenterBuffer> spBuffer;
    IFR( pBuffer->QueryInterface(&spBuffer) );

    SWRenderer::Initialize(spBuffer->GetBits(), spBuffer->GetSize().cx * 4, spBuffer->GetSize().cx, spBuffer->GetSize().cy);

    return hr;
}
