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

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

#include <afxctl.h>         // MFC support for ActiveX Controls
#include <afxext.h>         // MFC extensions
#include <d3d9.h>
#include <d3d10_1.h>
#include <d3d10effect.h>
#include <mshtml.h>
#include <ObjSafe.h>
#include <atlcom.h>
#include <afxwin.h>
#include <wincodec.h>

// Some macros to help with boilerplate error handling
#define IFRV(x) { hr = (x); if (FAILED(hr)) return; }
#define IFR(x) { hr = (x); if (FAILED(hr)) return hr; }

// Helper class for critical sections
class CSLock
{
public:
    CSLock(CRITICAL_SECTION *pCS)
    {
        _pCS = pCS;
        ::EnterCriticalSection(_pCS);
    }

    ~CSLock()
    {
        ::LeaveCriticalSection(_pCS);
    }

private:
    CRITICAL_SECTION *_pCS;
};