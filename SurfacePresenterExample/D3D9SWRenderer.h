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

#include "SWRenderer.h"

// This is a renderer class that renders in SW to a D3D9 back buffer. The
// SW rasterization code from the SWRenderer still does the hard work.
class D3D9SWRenderer : public SWRenderer
{
public:
    D3D9SWRenderer() {}
    HRESULT Initialize(HWND hWnd);

    // BaseRenderer implementation that SWRenderer did not fill in
    HRESULT SetBackBuffer(IUnknown *pBuffer) override;
    IUnknown *GetDevice() override { return _spDevice; }
    HRESULT BeginDraw() override;
    HRESULT EndDraw() override;

    // D3D9 bitmap rendering done with green
    BGRAPixel GetForeground() override { return BGRAPixel(0, 255, 0, 255); }

private:
    D3DLOCKED_RECT _lockedRect;
    CComPtr<IDirect3D9Ex> _spD3D;
    CComPtr<IDirect3DDevice9Ex> _spDevice;
    CComPtr<IDirect3DTexture9> _spStaging;
    CComPtr<IDirect3DTexture9> _spBackBuffer;
};
