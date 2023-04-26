#pragma once
#include <afxcmn.h>
class CListCtrlEx :
    public CListCtrl
{
public:
    DECLARE_DYNAMIC(CListCtrlEx)

public:
    CListCtrlEx(void);
    ~CListCtrlEx(void);
    int AddItem(LPCTSTR strItem, int nItem, int nSubItem = 0, UINT nState = -1, int nImageIndex = -1, long nParam = -1);
    

    // DECLARE_MESSAGE_MAP()
};

