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
#include "D3D9HWRenderer.h"
#include "SurfacePresenter.h"
#include "d3dhelper.h"

HRESULT D3D9HWRenderer::Initialize(HWND hWnd)
{
    return GetDirect3D9(hWnd, &_spD3D, &_spDevice);
}

HRESULT D3D9HWRenderer::SetBackBuffer(IUnknown *pBuffer)
{
    HRESULT hr;

    CComPtr<IDirect3DTexture9> spTexture;
    IFR( pBuffer->QueryInterface(&spTexture) );

    CComPtr<IDirect3DSurface9> spSurface;
    IFR( spTexture->GetSurfaceLevel(0, &spSurface) );
    IFR( _spDevice->SetRenderTarget(0, spSurface) );

    D3DSURFACE_DESC desc;
    IFR( spTexture->GetLevelDesc(0, &desc) );

    _uWidth = desc.Width;
    _uHeight = desc.Height;

    return S_OK;
}

IUnknown *D3D9HWRenderer::GetDevice()
{
    return _spDevice;
}

HRESULT D3D9HWRenderer::SetColor(BGRAPixel color)
{
    _currentColor = D3DCOLOR_RGBA(color.comp.r, color.comp.g, color.comp.b, color.comp.a);

    return S_OK;
}

HRESULT D3D9HWRenderer::FillRect(int uLeft, int uTop, int uRight, int uBottom)
{
    D3DRECT clearRect = { uLeft, uTop, uRight, uBottom };
    return _spDevice->Clear(1, &clearRect, D3DCLEAR_TARGET, _currentColor, 0, 0);
}

HRESULT D3D9HWRenderer::Clear(BGRAPixel color)
{
    D3DCOLOR saveColor = _currentColor;
    _currentColor = D3DCOLOR_RGBA(color.comp.r, color.comp.g, color.comp.b, color.comp.a);
    HRESULT hr = FillRect(0, 0, _uWidth, _uHeight);
    _currentColor = saveColor;
    return hr;
}

HRESULT D3D9HWRenderer::BeginDraw()
{
    return _spDevice->BeginScene();
}

HRESULT D3D9HWRenderer::EndDraw()
{
    return _spDevice->EndScene();
}
