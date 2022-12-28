#pragma once


// CMyButton

class CMyButton : public CButton
{
	DECLARE_DYNAMIC(CMyButton)

public:
	CMyButton();
	virtual ~CMyButton();

protected:
	DECLARE_MESSAGE_MAP()
	
public:
	CMyButton* m_pButton;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};


