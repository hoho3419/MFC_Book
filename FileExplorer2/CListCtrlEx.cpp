#include "pch.h"
#include "CListCtrlEx.h"

IMPLEMENT_DYNAMIC(CListCtrlEx, CListCtrl)

CListCtrlEx::CListCtrlEx(void)
{

}

CListCtrlEx::~CListCtrlEx(void)
{

}

int CListCtrlEx::AddItem(LPCTSTR strItem, int nItem, int nSubItem, UINT nState, int nImageIndex, long nParam)
{
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = nItem;
	lvItem.iSubItem = nSubItem;
	lvItem.pszText = (LPTSTR)strItem;

	if (nState != -1) {
		lvItem.mask |= LVIF_STATE;
		lvItem.state = nState;
	}
	if (nImageIndex != 1) {
		lvItem.mask |= LVIF_IMAGE;
		lvItem.iImage = nImageIndex;
	}
	if (nParam != -1) {
		lvItem.mask |= LVIF_PARAM;
		lvItem.lParam = nParam;
	}

	if (nSubItem == 0) {
		return InsertItem(&lvItem);
	}
	else {
		return SetItem(&lvItem);
	}
}