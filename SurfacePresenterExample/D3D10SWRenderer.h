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

// This is a renderer class that renders in SW to a D3D10 back buffer. The
// SW rasterization code from the SWRenderer still does the hard work.
class D3D10SWRenderer : public SWRenderer
{
public:
    D3D10SWRenderer() {}

    // BaseRenderer implementation that SWRenderer did not fill in
    HRESULT Initialize(HWND hWndUnused) override;
    HRESULT SetBackBuffer(IUnknown *pBuffer) override;
    IUnknown *GetDevice() override { return _spDevice; }
    HRESULT BeginDraw() override;
    HRESULT EndDraw() override;

    // D3D10 bitmap rendering done with red
    BGRAPixel GetForeground() override { return BGRAPixel(255, 0, 0, 255); }

private:
    D3D10_MAPPED_TEXTURE2D _mapped;
    CComPtr<ID3D10Device1> _spDevice;
    CComPtr<ID3D10Texture2D> _spStaging;
    CComPtr<ID3D10Texture2D> _spBackBuffer;
};
