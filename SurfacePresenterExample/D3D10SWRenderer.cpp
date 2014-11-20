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
#include "D3D10SWRenderer.h"
#include "SurfacePresenter.h"
#include "d3dhelper.h"

HRESULT D3D10SWRenderer::Initialize(HWND hWndUnused)
{
    return ::CreateD3D10Device(&_spDevice);
}

HRESULT D3D10SWRenderer::SetBackBuffer(IUnknown *pBuffer)
{
    HRESULT hr;

    IFR( pBuffer->QueryInterface(&_spBackBuffer) );

    D3D10_TEXTURE2D_DESC desc;
    _spBackBuffer->GetDesc(&desc);

    // Mutate the struct into what we need to make a staging texture
    desc.BindFlags = 0;
    desc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE | D3D10_CPU_ACCESS_READ;
    desc.MiscFlags = 0;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Usage = D3D10_USAGE_STAGING;
    IFR( _spDevice->CreateTexture2D(&desc, NULL, &_spStaging) );

    return hr;
}

HRESULT D3D10SWRenderer::BeginDraw()
{
    HRESULT hr;

    D3D10_TEXTURE2D_DESC desc;
    _spStaging->GetDesc(&desc);

    // Lock it to get the bits out
    IFR( _spStaging->Map(0, D3D10_MAP_READ_WRITE, 0, &_mapped) );

    SWRenderer::Initialize(_mapped.pData, _mapped.RowPitch, desc.Width, desc.Height);

    return hr;
}

HRESULT D3D10SWRenderer::EndDraw()
{
    _spStaging->Unmap(0);
    _spDevice->CopyResource(_spBackBuffer, _spStaging);

    return S_OK;
}
\