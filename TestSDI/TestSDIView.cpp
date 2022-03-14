
// TestSDIView.cpp: CTestSDIView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "TestSDI.h"
#endif

#include "TestSDIDoc.h"
#include "TestSDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestSDIView

IMPLEMENT_DYNCREATE(CTestSDIView, CView)

BEGIN_MESSAGE_MAP(CTestSDIView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTestSDIView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_COMMAND(ID_ANIMATE_ANIMATE, &CTestSDIView::OnAnimateAnimate)
END_MESSAGE_MAP()

// CTestSDIView 构造/析构

CTestSDIView::CTestSDIView() noexcept
{
	// TODO: 在此处添加构造代码
	bPlay = false;
	sphere.R = GetSystemMetrics(SM_CXFULLSCREEN) / 20;
	sphere.CenterPoint.x = 200, sphere.CenterPoint.y = 200;
	Direction.x = 1, Direction.y = 1;

}

CTestSDIView::~CTestSDIView()
{
}

BOOL CTestSDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CTestSDIView 绘图

void CTestSDIView::OnDraw(CDC* pDC)
{
	CTestSDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	
	DoubleBuffer(pDC);
}


// CTestSDIView 打印


void CTestSDIView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CTestSDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CTestSDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CTestSDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CTestSDIView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTestSDIView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CTestSDIView 诊断

#ifdef _DEBUG
void CTestSDIView::AssertValid() const
{
	CView::AssertValid();
}

void CTestSDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestSDIDoc* CTestSDIView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestSDIDoc)));
	return (CTestSDIDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestSDIView 消息处理程序

void CTestSDIView::DoubleBuffer(CDC * pDC)
{
	CRect rect;
	GetClientRect(&rect);//client height,width
	nWidth = rect.Width(), nHeight = rect.Height();
	CDC memDC;//in memory DC
	memDC.CreateCompatibleDC(pDC);//创建与显示兼容的内存DC
	CBitmap NewBitmap, *pOldBitmap;
	NewBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());//创建兼容内存位图
	pOldBitmap = memDC.SelectObject(&NewBitmap);//兼容位图选入内存DC
	DrawObject(&memDC);//绘制小球
	//DrawObject(pDC);//绘制小球
	CollisionDetection();
	pDC->BitBlt(0, 0, nWidth, nHeight, &memDC, 0, 0, SRCCOPY);//显示内存位图
	memDC.SelectObject(pOldBitmap);
	NewBitmap.DeleteObject();
	memDC.DeleteDC();
}


void CTestSDIView::CollisionDetection(void)
{
	if (sphere.CenterPoint.x - sphere.R < 0) {
		Direction.x = 1;//左碰撞
	}
	if (sphere.CenterPoint.x + sphere.R > nWidth) {
		Direction.x = -1;//右碰撞
	}

	if (sphere.CenterPoint.y - sphere.R < 0) {
		Direction.y = 1;//上
	}

	if (sphere.CenterPoint.y + sphere.R > nHeight) {
		Direction.y = -1;//下
	}
}

void CTestSDIView::DrawObject(CDC * pDC)
{
	sphere.Draw(pDC);
}


void CTestSDIView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	P0 = point;
	CWnd::OnLButtonDown(nFlags, point);
}


void CTestSDIView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	P1 = point;
	CDC* pDC = GetDC();
	//画线
	/*pDC->MoveTo(P0);
	pDC->LineTo(P1);*/

	//pDC->Rectangle(CRect(P0, P1));

	pDC->Ellipse(CRect(P0, P1));

	ReleaseDC(pDC);
	CWnd::OnLButtonUp(nFlags, point);
}

void CTestSDIView::OnGraphAnimation() {
	bPlay = !bPlay;
	if (bPlay) {
		SetTimer(1, 1, NULL);
	}
	else {
		KillTimer(1);
	}
}



void CTestSDIView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	sphere.CenterPoint += Direction;
	Invalidate(FALSE);
	CView::OnTimer(nIDEvent);
}


void CTestSDIView::OnAnimateAnimate()
{
	// TODO: 在此添加命令处理程序代码
	OnGraphAnimation();
}
