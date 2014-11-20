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
#include "RenderOption.h"

RenderOption::RenderOption(
    BOOL fHWComposition,
    BOOL fUseSurfacePresenter,
    BOOL fUseHardwareRasterization,
    int d3dVersion
    )
{
    _fHWComposition = (fHWComposition != FALSE);
    _fUseSurfacePresenter = (fUseSurfacePresenter != FALSE);
    _fUseHardwareRasterization = (fUseHardwareRasterization != FALSE);
    _d3dVersion = d3dVersion;
    _pfnCreateFunction = NULL;
}

// Constructor for HW composition options
RenderOption::RenderOption(
    BOOL fUseSurfacePresenter,
    BOOL fUseHardwareRasterization,
    int d3dVersion,
    PFNCreateRenderer pfnCreateFunction
    )
{
    _fHWComposition = true;
    _fUseSurfacePresenter = (fUseSurfacePresenter != FALSE);
    _fUseHardwareRasterization = (fUseHardwareRasterization != FALSE),
        _d3dVersion = d3dVersion,
        _pfnCreateFunction = pfnCreateFunction;
}

// Constructor for SW composition options
RenderOption::RenderOption(
    BOOL fUseSurfacePresenter,
    PFNCreateRenderer pfnCreateFunction
    )
{
    _fHWComposition = false;
    _fUseSurfacePresenter = (fUseSurfacePresenter != FALSE);
    _fUseHardwareRasterization = false;
    _d3dVersion = 0,
        _pfnCreateFunction = pfnCreateFunction;
}

bool RenderOption::Matches(const RenderOption &other) const
{
    if (_fUseSurfacePresenter != other._fUseSurfacePresenter)
    {
        return false;
    }

    // The rest only apply if surface presenter is used
    if (_fUseSurfacePresenter)
    {
        if (_fHWComposition != other._fHWComposition)
        {
            return false;
        }

        // These only apply if we have HW composition
        if (_fHWComposition)
        {
            if (_fUseHardwareRasterization != other._fUseHardwareRasterization)
            {
                return false;
            }

            if (_d3dVersion != other._d3dVersion)
            {
                return false;
            }
        }
    }

    return true;
}

HRESULT RenderOption::CreateIfMatching(const RenderOption &option, HWND hWnd, BaseRenderer **ppNewRenderer) const
{
    HRESULT hr;

    if (!Matches(option))
    {
        return E_FAIL;
    }

    if (_pfnCreateFunction == NULL)
    {
        return E_UNEXPECTED;
    }

    IFR( (*_pfnCreateFunction)(hWnd, ppNewRenderer) );

    return hr;
}
