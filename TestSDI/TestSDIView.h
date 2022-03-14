
// TestSDIView.h: CTestSDIView 类的接口
//

#pragma once
#include"CSphere.h"


class CTestSDIView : public CView
{
protected: // 仅从序列化创建
	CTestSDIView() noexcept;
	DECLARE_DYNCREATE(CTestSDIView)

// 特性
public:
	CTestSDIDoc* GetDocument() const;

// 操作
public:
	CPoint P0, P1;
	void DoubleBuffer(CDC* pDC);//双缓冲函数
	void CollisionDetection(void);//碰撞检测函数
	void DrawObject(CDC* pDC);//绘图函数
	CButton m_cBtn;

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void OnGraphAnimation();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);


// 实现
public:
	virtual ~CTestSDIView();
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
	int nWidth, nHeight;//客户端宽高
	CSphere sphere; //小球对象
	CPoint Direction;
	BOOL bPlay=true;//动画开关
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnAnimateAnimate();
};

#ifndef _DEBUG  // TestSDIView.cpp 中的调试版本
inline CTestSDIDoc* CTestSDIView::GetDocument() const
   { return reinterpret_cast<CTestSDIDoc*>(m_pDocument); }
#endif

