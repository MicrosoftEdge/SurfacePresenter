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

class CSurfacePresenterExampleCtrl;

// Even though this sample demonstrates windowless rendering, a window
// is still used for non-rendering purposes. Specifically, a WM_TIMER
// is used to notify the control when to render.
class CHiddenWindow : public CWnd
{
public:
    CHiddenWindow();

    BOOL Create(CSurfacePresenterExampleCtrl *pControl, LPCWSTR pszName, UINT nID);

protected:
    DECLARE_MESSAGE_MAP()

private:
    DECLARE_DYNAMIC(CHiddenWindow)

    afx_msg LRESULT OnGetObject(WPARAM wParam, LPARAM lParam);

private:
    CSurfacePresenterExampleCtrl *_pControl;
};


