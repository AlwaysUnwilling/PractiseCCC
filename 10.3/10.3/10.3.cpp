// MFCPaintView.cpp: CMFCPaintView ���ʵ��
//
#include"10.3.h"
#include<iostream>
#include<list>
#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MFCPaint.h"
#endif

#include "MFCPaintDoc.h"
#include "MFCPaintView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCPaintView

IMPLEMENT_DYNCREATE(CMFCPaintView, CView)

BEGIN_MESSAGE_MAP(CMFCPaintView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//	ON_WM_MOVE()
	ON_WM_MOUSEMOVE()
	//ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_CHAR()
END_MESSAGE_MAP()

// CMFCPaintView ����/����

CMFCPaintView::CMFCPaintView() noexcept
{
	// TODO: �ڴ˴���ӹ������

}

CMFCPaintView::~CMFCPaintView()
{
}

BOOL CMFCPaintView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMFCPaintView ��ͼ

void CMFCPaintView::OnDraw(CDC* pDC)
{
	CMFCPaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CPen pen(PS_DOT, 1, RGB(0, 255, 0));
	//HGDIOBJ hTmp=pDC->SelectObject(&pen);
	CPen* hTmp = pDC->SelectObject(&pen);
	// 	LOGPEN logpen;
	// 	hTmp->GetLogPen(&logpen);
	// 	TRACE("logpen.lopnStyle=%d\r\n,logpen.lopnColor=%08x\r\n,logpen.lopnWidth=%d\r\n",
	// 		logpen.lopnStyle, logpen.lopnColor, logpen.lopnWidth);//���Դ�ӡ��Ϣ
	auto it = lineList.begin();
	while (it != lineList.end())
	{
		pDC->MoveTo(it->first);
		pDC->LineTo(it->second);
		++it;
	}

	if (m_status)
	{
		pDC->MoveTo(m_start);
		pDC->LineTo(m_cur);
	}
	else
	{
		pDC->MoveTo(m_start);
		pDC->LineTo(m_stop);
	}
	pDC->SelectObject(hTmp);
	CBrush brush(RGB(255, 0, 0));
	CBrush* oldBrush = pDC->SelectObject(&brush);
	pDC->FillRect(CRect(m_start, m_cur), &brush);
	pDC->SelectObject(&oldBrush);
	/*pDC->TextOut(0, 0, m_strText); //textout��֧�ֶ�������*/
	CString sub = _T("");
	int y = 0;
	for (int i = 0; i < m_strText.GetLength(); ++i)
	{
		if (m_strText.GetAt(i) == '\n' || m_strText.GetAt(i) == '\r\n' || m_strText.GetAt(i) == '\r')
		{
			pDC->TextOutW(0, y, sub);
			CSize sz = pDC->GetTextExtent(sub);
			y += sz.cy + 2;
			sub.Empty();
			continue;
		}
		sub += m_strText.GetAt(i);
	}

	if (sub.IsEmpty() == FALSE)
	{
		pDC->TextOutW(0, y, sub);
	}
	CPoint pt;
	CSize sz = pDC->GetTextExtent(sub);
	pt.y = y;
	pt.x = sz.cx;
	SetCaretPos(pt);
	sub.Empty();
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}

void CMFCPaintView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCPaintView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCPaintView ���

#ifdef _DEBUG
void CMFCPaintView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCPaintView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCPaintDoc* CMFCPaintView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCPaintDoc)));
	return (CMFCPaintDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCPaintView ��Ϣ�������


void CMFCPaintView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_start = point;
	m_status = TRUE;

	CView::OnLButtonDown(nFlags, point);
}


void CMFCPaintView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_stop = point;
	// 	CDC* pDC = GetDC();
	// 	//ʲô��������
	// 	//ʲô���豸������
	// 	pDC->MoveTo(m_start);
	// 	pDC->LineTo(point);
	// 	ReleaseDC(pDC);
	m_status = FALSE;
	// 	InvalidateRect(NULL);
	lineList.push_back({ m_start,m_stop });
	CView::OnLButtonUp(nFlags, point);
}


//void CMFCPaintView::OnMove(int x, int y)
//{
//	CView::OnMove(x, y);
//
//	// TODO: �ڴ˴������Ϣ����������
//}


void CMFCPaintView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_status)
	{
		// 		CDC* pDC = GetDC();
		// 		//ʲô��������
		// 		//ʲô���豸������
		// 		pDC->MoveTo(m_start);
		// 		pDC->LineTo(point);
				//InvalidateRect(&recOldLine);  //�ػ�����OnDraw,OnDraw��������������»��Ƶ�������ʧ
		m_cur = point;
		recNewLine.right = m_cur.x;
		recNewLine.bottom = m_cur.y;
		// 		InvalidateRect(&recNewLine);  //�ػ�����OnDraw,OnDraw��������������»��Ƶ�������ʧ
		// 		recOldLine = recNewLine;
		InvalidateRect(NULL);
		/*		ReleaseDC(pDC);*/
	}
	CView::OnMouseMove(nFlags, point);
}


//void CMFCPaintView::OnPaint()
//{
//	CPaintDC dc(this); // device context for painting
//					   // TODO: �ڴ˴������Ϣ����������
//	
//					   // ��Ϊ��ͼ��Ϣ���� CView::OnPaint()
//
//}


BOOL CMFCPaintView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: �ڴ����ר�ô����/����û���

	return CView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


int CMFCPaintView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	CClientDC dc(this);
	TEXTMETRIC tm;

	dc.GetTextMetrics(&tm);
	CreateSolidCaret(2, tm.tmHeight);
	ShowCaret();
	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}


void CMFCPaintView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CClientDC dc(this);
	m_strText += (TCHAR)nChar;
	InvalidateRect(NULL);
	CView::OnChar(nChar, nRepCnt, nFlags);
}