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

class BaseRenderer;

typedef HRESULT (*PFNCreateRenderer)(HWND hWnd, BaseRenderer **ppRenderer);

// A render option is a combination of flag values that describes a way
// that rendering can be done in the sample. There is a table of them
// in the control describing the valid ways to render, and the current
// settings of the control are used to make an instance of this class
// to match with.
//
// Putting it into a class on its own takes the boring selection logic
// out of the control code.
class RenderOption
{
public:
    // Constructor for control data
    RenderOption(
        BOOL fHWComposition,
        BOOL fUseSurfacePresenter,
        BOOL fUseHardwareRasterization,
        int d3dVersion
        );

    // Constructor for HW composition options
    RenderOption(
        BOOL fUseSurfacePresenter,
        BOOL fUseHardwareRasterization,
        int d3dVersion,
        PFNCreateRenderer pfnCreateFunction
        );

    // Constructor for SW composition options
    RenderOption(
        BOOL fUseSurfacePresenter,
        PFNCreateRenderer pfnCreateFunction
        );

    HRESULT CreateIfMatching(const RenderOption &option, HWND hWnd, BaseRenderer **ppNewRenderer) const;

private:
    bool Matches(const RenderOption &other) const;

private:
    bool _fHWComposition;                   // Whether this option supports HW composition
    bool _fUseSurfacePresenter;             // Whether this option uses ISurfacePresenter
    bool _fUseHardwareRasterization;        // Whether this option rasterizes with HW
    int _d3dVersion;                        // Version of D3D used by this option
    PFNCreateRenderer _pfnCreateFunction;   // Function to create a renderer for this option
};

