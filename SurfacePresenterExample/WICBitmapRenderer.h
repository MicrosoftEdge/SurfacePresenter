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

// SW renderer that uses a WIC bitmap for the back buffer.
class WICBitmapRenderer : public SWRenderer
{
public:
    WICBitmapRenderer() {}

    // BaseRenderer implementation that SWRenderer did not fill in
    HRESULT Initialize(HWND hWndUnused) override { return S_OK; }
    HRESULT SetBackBuffer(IUnknown *pBuffer) override;
    IUnknown *GetDevice() override { return NULL; }
    HRESULT BeginDraw() override;
    HRESULT EndDraw() override;

    // WIC bitmap rendering done with blue
    BGRAPixel GetForeground() override { return BGRAPixel(0, 0, 255, 255); }

private:
    CComPtr<IWICBitmapLock> _spBitmapLock;
    CComPtr<IWICBitmap> _spBitmap;
};
