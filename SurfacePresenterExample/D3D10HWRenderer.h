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

#include "BaseRenderer.h"

// This is an implementation of BaseRenderer that uses D3D10 to render. Textures
// are used as brushes with CopySubResource to implement rectangle fills.
class D3D10HWRenderer : public BaseRenderer
{
public:
    D3D10HWRenderer();

    // BaseRenderer implementation
    HRESULT Initialize(HWND hwndUnused) override;
    HRESULT SetBackBuffer(IUnknown *pBuffer) override;
    IUnknown *GetDevice() override { return _spDevice; }
    HRESULT SetColor(BGRAPixel color) override;
    HRESULT FillRect(int uLeft, int uTop, int uRight, int uBottom) override;
    HRESULT Clear(BGRAPixel color) override;
    HRESULT BeginDraw() override;
    HRESULT EndDraw() override;

    // HW rendering with a grey background
    BGRAPixel GetBackground() override { return BGRAPixel(63, 63, 63, 255); }

    // D3D10 bitmap rendering done with red
    BGRAPixel GetForeground() override { return BGRAPixel(255, 0, 0, 255); }

private:
    struct D3D10Brush
    {
        D3D10Brush()
        {
        }

        HRESULT SetColor(BGRAPixel color, ID3D10Device *pDevice)
        {
            HRESULT hr;

            CAutoVectorPtr<BGRAPixel> spInitData;
            spInitData.Attach(new BGRAPixel[STRIP_HEIGHT * 2048]);
            for (int i = 0; i < STRIP_HEIGHT * 2048; i++)
            {
                spInitData[i] = color;
            }

            CD3D10_TEXTURE2D_DESC desc(DXGI_FORMAT_B8G8R8A8_UNORM, 2048, STRIP_HEIGHT, 1, 1);

            D3D10_SUBRESOURCE_DATA data;
            data.pSysMem = spInitData;
            data.SysMemPitch = 2048 * 4;

            IFR( pDevice->CreateTexture2D(&desc, &data, &_spData) );

            _color = color;

            return hr;
        }

        CComPtr<ID3D10Texture2D> _spData;
        BGRAPixel _color;
    };

private:
    CComPtr<ID3D10Device1> _spDevice;
    CComPtr<ID3D10Texture2D> _spBackBuffer;
    D3D10_TEXTURE2D_DESC _backDesc;
    CComPtr<ID3D10RenderTargetView> _spView;
    CArray<D3D10Brush> _brushes;
    int _currentBrush;

    const static int STRIP_HEIGHT = 64;
};
