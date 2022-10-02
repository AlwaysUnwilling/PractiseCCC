
// MFCPaintView.h: CMFCPaintView 类的接口
//

#pragma once
#include<iostream>
#include<list>


class CMFCPaintView : public CView
{
protected: // 仅从序列化创建
	CMFCPaintView() noexcept;
	DECLARE_DYNCREATE(CMFCPaintView)

// 特性
public:
	CMFCPaintDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	CPoint m_start{0,0};     //起始点，用于绘制线条时的起始点
	CPoint m_stop{0,0};      //结束点，用于绘制线条时的结束点
	BOOL m_status=FALSE;      //绘制状态，用于绘制线条
	CPoint m_cur{0,0};         //实时点，用于绘制线条
	std::list<std::pair<CPoint, CPoint>> lineList; //储存线条的链表
	std::pair<CPoint, CPoint> CPPair;   //记录每条线的起始点和终止点
	RECT recOldLine = {m_start.x,m_start.y,m_cur.x,m_cur.y};
	RECT recNewLine = {m_start.x,m_start.y,m_cur.x,m_cur.y};
	CString m_strText;  //用户输入的字符串
// 实现
public:
	virtual ~CMFCPaintView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // MFCPaintView.cpp 中的调试版本
inline CMFCPaintDoc* CMFCPaintView::GetDocument() const
   { return reinterpret_cast<CMFCPaintDoc*>(m_pDocument); }
#endif

