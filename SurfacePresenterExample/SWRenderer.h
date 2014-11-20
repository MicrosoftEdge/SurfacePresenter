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

// All SW renderers use this class as their common base. The class
// implements a simple SW renderer using a very basic rectangle fill.
class SWRenderer : public BaseRenderer
{
public:
    void Initialize(void *pData, UINT uStride, UINT uWidth, UINT uHeight);

    // BaseRenderer implementation
    HRESULT SetColor(BGRAPixel color) override;
    HRESULT FillRect(int uLeft, int uTop, int uRight, int uBottom) override;
    HRESULT Clear(BGRAPixel color) override;

    // All SW rendering with a black background
    BGRAPixel GetBackground() override { return BGRAPixel(0, 0, 0, 255); }

private:
    BYTE *_pData;
    UINT _uWidth;
    UINT _uHeight;
    UINT _uStride;
    BGRAPixel _currentColor;
};
