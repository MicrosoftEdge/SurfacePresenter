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

#include "WICBitmapRenderer.h"

// This is a renderer class that renders in SW to a WIC bitmap for
// doing printing. The resolution is 3x normal (close to 300DPI assuming
// that 96 DPI is what is being done for the screen). SW rasterization 
// code from the SWRenderer still does the hard work.
class PrintRenderer : public WICBitmapRenderer
{
public:
    PrintRenderer() {}

    // Override drawing API
    HRESULT FillRect(int uLeft, int uTop, int uRight, int uBottom) override { return WICBitmapRenderer::FillRect(uLeft * 3, uTop * 3, uRight * 3, uBottom * 3); }
};
