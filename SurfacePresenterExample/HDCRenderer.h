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
#include "GDIPresenter.h"
#include "GDIPresenterBuffer.h"

// The HDC renderer uses an implementation of ISurfacePresenter that
// is implemented by this sample rather than MSHTML. This allows it
// to fit in to the same pattern as the other renderers. It uses
// the same SW renderer as the other SW rendering classes.
class HDCRenderer : public SWRenderer
{
public:
    HDCRenderer() {}
    ~HDCRenderer() {}

    // BaseRender overrides
    HRESULT Initialize(HWND hWndUnused) { return S_OK; }
    HRESULT SetBackBuffer(IUnknown *pBuffer) override;
    IUnknown *GetDevice() override { return NULL;}
    HRESULT BeginDraw() override { return S_OK; }
    HRESULT EndDraw() override { return S_OK; }

    // GDI rendering represented with yellow
    BGRAPixel GetForeground() override { return BGRAPixel(255, 255, 0, 255); }
};
