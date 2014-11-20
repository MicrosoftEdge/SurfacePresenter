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

struct __declspec(uuid("b5d3b95c-9e0b-4fde-b6f1-28f20a972592"))
IGDIPresenterBuffer : public IUnknown
{
    virtual void Initialize(const CSize &size, void *pBits) = 0;
    virtual CSize GetSize() = 0;
    virtual void *GetBits() = 0;
};

// Helper class used to implement GDIPresenter. ISurfacePresenter
// has a method that returns a buffer, and this is the implementation
// of what GDIPresenter returns.
class GDIPresenterBuffer : 
    public CComObjectRootEx<CComMultiThreadModelNoCS>,
    public IGDIPresenterBuffer
{
public:
    BEGIN_COM_MAP(GDIPresenterBuffer)
        COM_INTERFACE_ENTRY(IGDIPresenterBuffer)
    END_COM_MAP()

    GDIPresenterBuffer()
    {
        _pBits = NULL;
    }

    // Implementation of IGDIPresenterBuffer
    void Initialize(const CSize &size, void *pBits) override
    {
        _size = size;
        _pBits = pBits;
    }

    CSize GetSize() override { return _size; }
    void *GetBits() override { return _pBits; }

private:
    CSize _size;
    void *_pBits;
};