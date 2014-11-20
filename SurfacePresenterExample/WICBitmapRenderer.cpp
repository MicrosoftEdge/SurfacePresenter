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
#include "WICBitmapRenderer.h"
#include "SurfacePresenter.h"

HRESULT WICBitmapRenderer::SetBackBuffer(IUnknown *pBuffer)
{
    return pBuffer->QueryInterface(&_spBitmap);
}

HRESULT WICBitmapRenderer::BeginDraw()
{
    HRESULT hr;

    UINT uWidth, uHeight;
    IFR( _spBitmap->GetSize(&uWidth, &uHeight) );

    // Lock it to get the bits out
    WICRect rect = { 0, 0, uWidth, uHeight };
    IFR( _spBitmap->Lock(&rect, WICBitmapLockRead | WICBitmapLockWrite, &_spBitmapLock) );

    UINT uStride;
    IFR( _spBitmapLock->GetStride(&uStride) );

    // We expect 32bpp, so if the stride is smaller than 4 x width then don't bother
    if (uStride < 4 * uWidth)
    {
        return E_UNEXPECTED;
    }

    BYTE *pDataPointer = NULL;
    UINT uBufferSize;
    IFR( _spBitmapLock->GetDataPointer(&uBufferSize, &pDataPointer) );

    SWRenderer::Initialize(pDataPointer, uStride, uWidth, uHeight);

    return S_OK;
}

HRESULT WICBitmapRenderer::EndDraw()
{
    _spBitmapLock.Release();
    return S_OK;
}
