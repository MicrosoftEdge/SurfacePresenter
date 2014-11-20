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

// Simple class that stores pixel data in BGRA order
union BGRAPixel
{
    struct
    {
        BYTE b;
        BYTE g;
        BYTE r;
        BYTE a;
    } comp;
    DWORD agg; 

    BGRAPixel()
    {
    }

    BGRAPixel(BYTE x, BYTE y, BYTE z, BYTE w)
    {
        comp.r = x;
        comp.g = y;
        comp.b = z;
        comp.a = w;
    }
    
    bool operator==(const BGRAPixel &other)
    {
        return agg == other.agg;
    }
};

