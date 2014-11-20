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
#include "D3D10HWRenderer.h"
#include "SurfacePresenter.h"
#include "d3dhelper.h"

D3D10HWRenderer::D3D10HWRenderer()
{
    _currentBrush = -1;
}

HRESULT D3D10HWRenderer::Initialize(HWND hwndUnused)
{
    return ::CreateD3D10Device(&_spDevice);
}

HRESULT D3D10HWRenderer::SetBackBuffer(IUnknown *pBuffer)
{
    HRESULT hr;

    // The buffer is a D3D10 surface
    IFR( pBuffer->QueryInterface(&_spBackBuffer) );
    _spBackBuffer->GetDesc(&_backDesc);

    IFR( _spDevice->CreateRenderTargetView(_spBackBuffer, NULL, &_spView) );

    ID3D10RenderTargetView *pViews[1] = { _spView };

    // Set the render target to the presenter texture
    _spDevice->OMSetRenderTargets(1, pViews, NULL);

    return hr;
}

HRESULT D3D10HWRenderer::SetColor(BGRAPixel color)
{
    HRESULT hr = S_OK;

    for (INT_PTR i = 0; i < _brushes.GetCount(); i++)
    {
        if (color == _brushes[i]._color)
        {
            _currentBrush = i;
            return hr;
        }
    }

    D3D10Brush newBrush;
    IFR( newBrush.SetColor(color, _spDevice) );

    _currentBrush = _brushes.Add(newBrush);

    return hr;
}

HRESULT D3D10HWRenderer::FillRect(int uLeft, int uTop, int uRight, int uBottom)
{
    // Clip rectangle before drawing
    if (uLeft < 0) uLeft = 0;
    if (uTop < 0) uTop = 0;
    if (uRight > (int)_backDesc.Width) uRight = _backDesc.Width;
    if (uBottom > (int)_backDesc.Height) uBottom = _backDesc.Height;

    for (int start = uTop; start < uBottom; start += STRIP_HEIGHT)
    {
        int copyHeight = (uBottom - start) >= STRIP_HEIGHT ? STRIP_HEIGHT : (uBottom - start);

        D3D10_BOX copyBox;
        copyBox.front = 0;
        copyBox.back = 1;
        copyBox.left = 0;
        copyBox.right = (uRight - uLeft);
        copyBox.top = 0;
        copyBox.bottom = copyHeight;

        _spDevice->CopySubresourceRegion(_spBackBuffer, 0, uLeft, start, 0, _brushes[_currentBrush]._spData, 0, &copyBox);
    }

    return S_OK;
}

HRESULT D3D10HWRenderer::Clear(BGRAPixel color)
{
    float clearColor[4] = {
        (float)color.comp.r / 255.0f, 
        (float)color.comp.g / 255.0f, 
        (float)color.comp.b / 255.0f, 
        (float)color.comp.a / 255.0f
    };

    _spDevice->ClearRenderTargetView(_spView, clearColor);

    return S_OK;
}

HRESULT D3D10HWRenderer::BeginDraw()
{
    return S_OK;
}

HRESULT D3D10HWRenderer::EndDraw()
{
    return S_OK;
}
