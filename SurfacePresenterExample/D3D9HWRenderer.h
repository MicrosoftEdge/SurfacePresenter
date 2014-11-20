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
#include "D3D9Helper.h"

// This is an implementation of BaseRenderer that uses D3D9 to render. Since
// Clear is so expressive in D3D9, it is used to implement the drawing commands.
class D3D9HWRenderer : public BaseRenderer
{
public:
    HRESULT Initialize(HWND hWnd);

    // BaseRenderer implementation
    HRESULT SetBackBuffer(IUnknown *pBuffer) override;
    IUnknown *GetDevice() override;
    HRESULT SetColor(BGRAPixel color) override;
    HRESULT FillRect(int uLeft, int uTop, int uRight, int uBottom) override;
    HRESULT Clear(BGRAPixel color) override;
    HRESULT BeginDraw() override;
    HRESULT EndDraw() override;

    // HW rendering with a grey background
    BGRAPixel GetBackground() override { return BGRAPixel(63, 63, 63, 255); }

    // D3D9 bitmap rendering done with green
    BGRAPixel GetForeground() override { return BGRAPixel(0, 255, 0, 255); }

private:
    CComPtr<IDirect3D9Ex> _spD3D;
    CComPtr<IDirect3DDevice9Ex> _spDevice;
    D3DCOLOR _currentColor;
    UINT _uWidth, _uHeight;
};
