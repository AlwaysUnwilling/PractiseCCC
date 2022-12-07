
// MFCDrawView.cpp: CMFCDrawView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCDraw.h"
#endif

#include "MFCDrawDoc.h"
#include "MFCDrawView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCDrawView

IMPLEMENT_DYNCREATE(CMFCDrawView, CView)

BEGIN_MESSAGE_MAP(CMFCDrawView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
	ON_COMMAND(ID_CLiENT, &CMFCDrawView::OnClient)
	ON_COMMAND(ID_BITMAP, &CMFCDrawView::OnBitmap)
	ON_COMMAND(ID_BRUSH, &CMFCDrawView::OnBrush)
	ON_COMMAND(ID_PEN, &CMFCDrawView::OnPen)
	ON_COMMAND(ID_FONT, &CMFCDrawView::OnFont)
END_MESSAGE_MAP()

// CMFCDrawView 构造/析构

CMFCDrawView::CMFCDrawView() noexcept
{
	// TODO: 在此处添加构造代码

}

CMFCDrawView::~CMFCDrawView()
{
}

BOOL CMFCDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCDrawView 绘图

void CMFCDrawView::OnDraw(CDC* /*pDC*/)
{
	CMFCDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMFCDrawView 打印

BOOL CMFCDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCDrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCDrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMFCDrawView 诊断

#ifdef _DEBUG
void CMFCDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCDrawDoc* CMFCDrawView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCDrawDoc)));
	return (CMFCDrawDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCDrawView 消息处理程序


void CMFCDrawView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CView::OnPaint()
	//dc.Rectangle(100, 100, 300, 300);
}


void CMFCDrawView::OnClient()
{
	// TODO: 在此添加命令处理程序代码
	CClientDC dc(this);
	dc.Ellipse(300, 300, 500, 500);
}


void CMFCDrawView::OnBitmap()
{
	//添加位图资源
	//创建一个和当前DC相匹配的内存DC
	CClientDC dc(this);
	CDC memdc;
	memdc.CreateCompatibleDC(&dc);
	//将位图的数据送给内存DC
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP1);
	CBitmap* oldbmp=memdc.SelectObject(&bmp);
	//成像
	dc.BitBlt(700, 700, 1052, 1001, &memdc, 0, 0, SRCCOPY);
	//将位图数据要回来
	memdc.SelectObject(oldbmp);
	//销毁位图
	bmp.DeleteObject();
	//销毁内存DC
	memdc.DeleteDC();
}


void CMFCDrawView::OnBrush()
{
	// TODO: 在此添加命令处理程序代码
	CClientDC dc(this);
	CBrush brush(RGB(0, 255, 0));
	CBrush* oldbrush=dc.SelectObject(&brush);
	dc.Rectangle(100, 100, 300, 300);
	dc.SelectObject(oldbrush);
	brush.DeleteObject();
}


void CMFCDrawView::OnPen()
{
	// TODO: 在此添加命令处理程序代码
	CClientDC dc(this);
	CPen pen(PS_SOLID, 2, RGB(255, 0, 0));
	CPen* oldpen= dc.SelectObject(&pen);
	dc.Rectangle(100, 100, 300, 300);
	dc.SelectObject(oldpen);
	pen.DeleteObject();
}


void CMFCDrawView::OnFont()
{
	// TODO: 在此添加命令处理程序代码
	CClientDC dc(this);
	CFont font;
	font.CreatePointFont(300,"微软雅黑");
	CFont* oldfont = dc.SelectObject(&font);
	dc.TextOutA(400, 400, "你好啊");
	dc.SelectObject(oldfont);
	font.DeleteObject();
}
