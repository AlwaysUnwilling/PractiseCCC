#pragma once
// MFCPaintView.h: CMFCPaintView ��Ľӿ�
//

#include<iostream>
#include<list>


class CMFCPaintView : public CView
{
protected: // �������л�����
	CMFCPaintView() noexcept;
	DECLARE_DYNCREATE(CMFCPaintView)

	// ����
public:
	CMFCPaintDoc* GetDocument() const;

	// ����
public:

	// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	CPoint m_start{ 0,0 };     //��ʼ�㣬���ڻ�������ʱ����ʼ��
	CPoint m_stop{ 0,0 };      //�����㣬���ڻ�������ʱ�Ľ�����
	BOOL m_status = FALSE;      //����״̬�����ڻ�������
	CPoint m_cur{ 0,0 };         //ʵʱ�㣬���ڻ�������
	std::list<std::pair<CPoint, CPoint>> lineList; //��������������
	std::pair<CPoint, CPoint> CPPair;   //��¼ÿ���ߵ���ʼ�����ֹ��
	RECT recOldLine = { m_start.x,m_start.y,m_cur.x,m_cur.y };
	RECT recNewLine = { m_start.x,m_start.y,m_cur.x,m_cur.y };
	CString m_strText;  //�û�������ַ���
// ʵ��
public:
	virtual ~CMFCPaintView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//	afx_msg void OnMove(int x, int y);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//	afx_msg void OnPaint();
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // MFCPaintView.cpp �еĵ��԰汾
inline CMFCPaintDoc* CMFCPaintView::GetDocument() const
{
	return reinterpret_cast<CMFCPaintDoc*>(m_pDocument);
}
#endif
