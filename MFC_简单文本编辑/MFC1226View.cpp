
// MFC1226View.cpp: CMFCView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFC1226.h"
#endif

#include "MFC1226Doc.h"
#include "MFC1226View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCView

IMPLEMENT_DYNCREATE(CMFCView, CView)

BEGIN_MESSAGE_MAP(CMFCView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
//	ON_WM_CREATE()
ON_WM_CREATE()
ON_WM_CHAR()
END_MESSAGE_MAP()

// CMFCView 构造/析构

CMFCView::CMFCView() noexcept
{
	// TODO: 在此处添加构造代码
	m_start = { 0 };
	m_end = { 0 };
	m_cur = { 0 };
}

CMFCView::~CMFCView()
{
}

BOOL CMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCView 绘图

void CMFCView::OnDraw(CDC* pDC)
{
	CMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CPen pen(PS_SOLID, 5, RGB(255, 0, 0));
	HGDIOBJ oldPen = pDC->SelectObject(&pen);
	if (doDrawLine)
	{
		pDC->MoveTo(m_start);
		pDC->LineTo(m_cur);
	}
	else
	{
		pDC->MoveTo(m_start);
		pDC->MoveTo(m_end);
	}
	pDC->SelectObject(oldPen);
	
	CBrush brush(RGB(0, 255, 0));
	HGDIOBJ oldBrush=pDC->SelectObject(&brush);
	pDC->FillRect(CRect(m_start,m_end),NULL);
	pDC->SelectObject(oldBrush);

	CString sub = _T("");
	int y = 0;
	for (int i = 0; i < m_string.GetLength(); ++i)
	{
		if(m_string.GetAt(i)=='\n' || m_string.GetAt(i) == '\r')
		{
			pDC->TextOutW(0, y, sub);
			sub.Empty();
			y += 20;
			continue;
		}
		sub += m_string.GetAt(i);
	}
	if(!sub.IsEmpty())
		pDC->TextOutW(0, y, sub);

	CPoint pt;
	pt.y = y;
	CSize cs=pDC->GetTextExtent(sub);
	pt.x = cs.cx;
	SetCaretPos(pt);
	// TODO: 在此处为本机数据添加绘制代码
}

void CMFCView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCView 诊断

#ifdef _DEBUG
void CMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCDoc* CMFCView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCDoc)));
	return (CMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCView 消息处理程序


void CMFCView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_start = point;
	doDrawLine = TRUE;
	TRACE("m_start:x=%d,y=%d\n", m_start.x, m_start.y);
	CView::OnLButtonDown(nFlags, point);
}


void CMFCView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_end = point;
	doDrawLine = FALSE;
	TRACE("m_end:x=%d,y=%d\n", m_end.x, m_end.y);
	CView::OnLButtonUp(nFlags, point);
}


void CMFCView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (doDrawLine)
	{
		m_cur = point;
		Invalidate(TRUE);
	}
	CView::OnMouseMove(nFlags, point);
}


//int CMFCView::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//	if (CView::OnCreate(lpCreateStruct) == -1)
//		return -1;
//
//	// TODO:  在此添加您专用的创建代码
//
//	return 0;
//}


//BOOL CMFCView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
//{
//	// TODO: 在此添加专用代码和/或调用基类
//	
//	return CView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
//}


int CMFCView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CClientDC dc(this);
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
	CreateSolidCaret(2, tm.tmHeight);
	ShowCaret();
	return 0;
}


void CMFCView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);
	m_string += (TCHAR)nChar;
	InvalidateRect(NULL);
	CView::OnChar(nChar, nRepCnt, nFlags);
}
