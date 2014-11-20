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
#include "HiddenWindow.h"
#include "SurfacePresenterExampleCtrl.h"

IMPLEMENT_DYNAMIC(CHiddenWindow, CWnd)

CHiddenWindow::CHiddenWindow()
{
    _pControl = NULL;
}

BOOL CHiddenWindow::Create(CSurfacePresenterExampleCtrl *pControl, LPCWSTR pszName, UINT nID)
{
    _pControl = pControl;

    CComPtr<IOleWindow> spOleWindow;
    _pControl->GetClientSite()->QueryInterface(&spOleWindow);

    HWND hParentWindow;
    spOleWindow->GetWindow(&hParentWindow);

    if (!CWnd::Create(NULL, pszName, WS_CHILD, CRect(0, 0, 0, 0), CWnd::FromHandle(hParentWindow), nID))
    {
        return FALSE;
    }

    return TRUE;
}

BEGIN_MESSAGE_MAP(CHiddenWindow, CWnd)
    ON_MESSAGE(WM_GETOBJECT, &CHiddenWindow::OnGetObject)
END_MESSAGE_MAP()

LRESULT CHiddenWindow::OnGetObject(WPARAM wParam, LPARAM lParam)
{
    if ((DWORD)lParam == OBJID_CLIENT)
    {
        IAccessible *pRoot = _pControl->GetRootAccessible();
        if (pRoot)
        {
            return ::LresultFromObject(__uuidof(IAccessible), wParam, pRoot);
        }
    }
    else
    {
        CComPtr<IRectCollection> spCollection;
        if (SUCCEEDED(_pControl->GetIDispatch(FALSE)->QueryInterface(&spCollection)))
        {
            int index = (int)(lParam - 1);
            CComPtr<IAccessible> spAcc;
            if (SUCCEEDED(spCollection->CreateAccessibleForRect(index, &spAcc)))
            {
                return ::LresultFromObject(__uuidof(IAccessible), wParam, spAcc);
            }
        }
    }

    return 0;
}