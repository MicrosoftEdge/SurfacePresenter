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
#include "SWRenderer.h"

void SWRenderer::Initialize(void *pData, UINT uStride, UINT uWidth, UINT uHeight)
{
    _pData = reinterpret_cast<BYTE *>(pData);
    _uStride = uStride;
    _uWidth = uWidth;
    _uHeight = uHeight;
}

HRESULT SWRenderer::SetColor(BGRAPixel color)
{
    _currentColor = color;

    return S_OK;
}

HRESULT SWRenderer::FillRect(int uLeft, int uTop, int uRight, int uBottom)
{
    // Clip rectangle before drawing
    if (uLeft < 0) uLeft = 0;
    if (uTop < 0) uTop = 0;
    if (uRight > (int)_uWidth) uRight = _uWidth;
    if (uBottom > (int)_uHeight) uBottom = _uHeight;

    BYTE *pWalk = _pData + (uTop * _uStride);

    for (int y = uTop; y < uBottom; y++)
    {
        BGRAPixel *pScan = reinterpret_cast<BGRAPixel *>(pWalk);
        for (int x = uLeft; x < uRight; x++)
        {
            pScan[x] = _currentColor;
        }

        pWalk += _uStride;
    }

    return S_OK;
}

HRESULT SWRenderer::Clear(BGRAPixel color)
{
    BGRAPixel saveColor = _currentColor;
    _currentColor = color;
    FillRect(0, 0, _uWidth, _uHeight);
    color = _currentColor;
    return S_OK;
}
