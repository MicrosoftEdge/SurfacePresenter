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
#include "D3D9SWRenderer.h"
#include "SurfacePresenter.h"
#include "D3DHelper.h"

HRESULT D3D9SWRenderer::Initialize(HWND hWnd)
{
    return GetDirect3D9(hWnd, &_spD3D, &_spDevice);
}

HRESULT D3D9SWRenderer::SetBackBuffer(IUnknown *pBuffer)
{
    HRESULT hr;

    IFR( pBuffer->QueryInterface(&_spBackBuffer) );

    D3DSURFACE_DESC desc;
    IFR( _spBackBuffer->GetLevelDesc(0, &desc) );

    IFR( _spDevice->CreateTexture(desc.Width, desc.Height, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &_spStaging, NULL) );

    return hr;
}

HRESULT D3D9SWRenderer::BeginDraw() 
{
    HRESULT hr;

    D3DSURFACE_DESC desc;
    IFR( _spStaging->GetLevelDesc(0, &desc) );

    // Lock it to get the bits out
    IFR( _spStaging->LockRect(0, &_lockedRect, NULL, 0) );

    SWRenderer::Initialize(_lockedRect.pBits, _lockedRect.Pitch, desc.Width, desc.Height);

    return hr;
}

HRESULT D3D9SWRenderer::EndDraw() 
{
    HRESULT hr;

    IFR( _spStaging->UnlockRect(0) );
    IFR( _spDevice->UpdateTexture(_spStaging, _spBackBuffer) );

    return hr;
}
