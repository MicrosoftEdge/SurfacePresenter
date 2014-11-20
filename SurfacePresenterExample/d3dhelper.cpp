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

HRESULT GetDirect3D9(HWND hWnd, IDirect3D9Ex **ppD3D, IDirect3DDevice9Ex **ppDevice)
{
    HRESULT hr;

    D3DPRESENT_PARAMETERS pparams;
    pparams.BackBufferWidth = 1;
    pparams.BackBufferHeight = 1;
    pparams.BackBufferCount = 1;
    pparams.BackBufferFormat = D3DFMT_A8R8G8B8;
    pparams.AutoDepthStencilFormat = D3DFMT_UNKNOWN;
    pparams.EnableAutoDepthStencil = FALSE;
    pparams.Flags = 0;
    pparams.FullScreen_RefreshRateInHz = 0;
    pparams.hDeviceWindow = hWnd;
    pparams.MultiSampleQuality = 0;
    pparams.MultiSampleType = D3DMULTISAMPLE_NONE;
    pparams.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
    pparams.SwapEffect = D3DSWAPEFFECT_COPY;
    pparams.Windowed = TRUE;

    IFR( ::Direct3DCreate9Ex(D3D_SDK_VERSION, ppD3D) );
    IFR( (*ppD3D)->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &pparams, NULL, ppDevice) );

    return hr;
}

HRESULT CreateD3D10Device(ID3D10Device1 **ppDevice)
{
    HRESULT hr;

    D3D10_FEATURE_LEVEL1 levels[] = {
        D3D10_FEATURE_LEVEL_10_0, 
        D3D10_FEATURE_LEVEL_9_1
    };

    // We explicitly create a factory because ISurfacePresenter
    // requires DXGI 1.1 factory created devices to work.    
    CComPtr<IDXGIFactory1> spFactory1;
    IFR( ::CreateDXGIFactory1(IID_PPV_ARGS(&spFactory1)) );

    CComPtr<IDXGIAdapter> spAdapter;
    IFR( spFactory1->EnumAdapters(0, &spAdapter) );

    int i;
    for (i = 0; i < ARRAYSIZE(levels); i++)
    {
        if (SUCCEEDED(::D3D10CreateDevice1(
            spAdapter, 
            D3D10_DRIVER_TYPE_HARDWARE, 
            NULL, 
            D3D10_CREATE_DEVICE_BGRA_SUPPORT, 
            levels[i], 
            D3D10_1_SDK_VERSION, 
            ppDevice
            )))
        {
            break;
        }
    }

    if (i == ARRAYSIZE(levels))
    {
        return E_FAIL;
    }

    return S_OK;
}