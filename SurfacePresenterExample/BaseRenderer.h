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

#include "BGRAPixel.h"

struct ISurfacePresenter;

// This sample shows how to render using many different methods. This base
// class describes the interface for programming against these renderers.
//
// Basically, they all have a Begin / End and can clear or fill a rect.
class BaseRenderer
{
public:
    virtual ~BaseRenderer() {}

    virtual HRESULT Initialize(HWND hWnd) = 0;
    virtual HRESULT SetBackBuffer(IUnknown *) = 0;
    virtual IUnknown *GetDevice() = 0;
    virtual HRESULT BeginDraw() = 0;
    virtual HRESULT EndDraw() = 0;
    virtual HRESULT SetColor(BGRAPixel color) = 0;
    virtual HRESULT FillRect(int uLeft, int uTop, int uRight, int uBottom) = 0;
    virtual HRESULT Clear(BGRAPixel color) = 0;
    virtual BGRAPixel GetBackground() = 0;
    virtual BGRAPixel GetForeground() = 0;
};

