#pragma once
#include <afx.h>
class CFileFindEx :
    public CFileFind
{
public:
    CFileFindEx(void);
    ~CFileFindEx(void);
    CString GetLengthString(); // 颇老 农扁
    CString GetCreationTimeString(CString strTmp = _T("-")); // 颇老 积己 矫埃
};

