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

#include "SurfacePresenter.h"

struct IGDIPresenterBuffer;

struct __declspec(uuid("c0bc3448-4e56-4973-bf86-6b15c614388c"))
IGDIPresenter : public IUnknown
{
    virtual void SetDC(HDC hDC, const CPoint &offset) = 0;
};

// This is a class that implements ISurfacePresenter but actually draws to a DC
// when doing rendering. This is purely to allow the rest of the code in the
// project to have a consistent interface to talk to in order to do its work.
class GDIPresenter : 
    public CComObjectRootEx<CComMultiThreadModelNoCS>,
    public ISurfacePresenter,
    public IGDIPresenter
{
public:
    BEGIN_COM_MAP(GDIPresenter)
        COM_INTERFACE_ENTRY(ISurfacePresenter)
        COM_INTERFACE_ENTRY(IGDIPresenter)
    END_COM_MAP()

    GDIPresenter();
    ~GDIPresenter();
    HRESULT Initialize(UINT uWidth, UINT uHeight);

    // IGDIPresenter implementation
    void SetDC(HDC hDC, const CPoint &offset) override;

    // ISurfacePresenter implementation
    STDMETHOD(Present)(UINT uBuffer, RECT *pDirty);        
    STDMETHOD(GetBuffer)(UINT backBufferIndex, REFIID riid, void **ppBuffer);
    STDMETHOD(IsCurrent)(BOOL *pIsCurrent);

private:
    CComPtr<IGDIPresenterBuffer> _spBuffer;
    CPoint _offset;
    HDC _hTargetDC;
    HDC _hMemoryDC;
    HBITMAP _hBitmap;
    void *_pvBits;
};
