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
#include "GDIPresenter.h"
#include "GDIPresenterBuffer.h"

GDIPresenter::GDIPresenter()
{
    _hBitmap = NULL;
    _hMemoryDC = NULL;
    _hTargetDC = NULL;
    _pvBits = NULL;
}

GDIPresenter::~GDIPresenter()
{
    ::DeleteObject(_hBitmap);
    ::DeleteDC(_hMemoryDC);
}

HRESULT GDIPresenter::Initialize(UINT uWidth, UINT uHeight)
{
    HRESULT hr;

    _hMemoryDC = ::CreateCompatibleDC(NULL);

    BITMAPINFO info = { 0 };
    info.bmiHeader.biBitCount = 32;
    info.bmiHeader.biCompression = BI_RGB;
    info.bmiHeader.biHeight = uWidth;
    info.bmiHeader.biWidth = uHeight;
    info.bmiHeader.biPlanes = 1;
    info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);

    _hBitmap = ::CreateDIBSection(NULL, &info, DIB_RGB_COLORS, &_pvBits, NULL, 0);

    ::SelectObject(_hMemoryDC, _hBitmap);

    CComObject<GDIPresenterBuffer> *pBuffer = NULL;
    IFR( CComObject<GDIPresenterBuffer>::CreateInstance(&pBuffer) );
    pBuffer->Initialize(CSize(uWidth, uHeight), _pvBits);
    IFR( pBuffer->QueryInterface(&_spBuffer) );

    return hr;
}

// IGDIPresenter
void GDIPresenter::SetDC(HDC hDC, const CPoint &offset) 
{
    _hTargetDC = hDC;
    _offset = offset;

    ::BitBlt(_hMemoryDC, 0, 0, _spBuffer->GetSize().cx, _spBuffer->GetSize().cy, _hTargetDC, _offset.x, _offset.y, SRCCOPY);
}

// ISurfacePresenter
HRESULT GDIPresenter::Present(UINT uBuffer, RECT *pDirty)
{
    ::BitBlt(_hTargetDC, _offset.x, _offset.y, _spBuffer->GetSize().cx, _spBuffer->GetSize().cy, _hMemoryDC, 0, 0, SRCCOPY);

    return S_OK;
}

HRESULT GDIPresenter::GetBuffer(UINT backBufferIndex, REFIID riid, void **ppBuffer)
{
    return _spBuffer->QueryInterface(riid, ppBuffer);
}

HRESULT GDIPresenter::IsCurrent(BOOL *pIsCurrent)
{
    (*pIsCurrent) = TRUE;
    return S_OK;
}
