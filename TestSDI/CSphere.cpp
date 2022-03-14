#include "pch.h"
#include "CSphere.h"

CSphere::CSphere(void)
{
}

CSphere::~CSphere(void)
{
}

void CSphere::SetParameter(int R, CPoint CenterPoint)
{
	this->R = R;
	this->CenterPoint = CenterPoint;
}

void CSphere::Draw(CDC * pDC)
{
	CPoint TopLeft(CenterPoint.x - R, CenterPoint.y - R);
	CPoint BottomRight(CenterPoint.x + R, CenterPoint.y + R);
	CRect Square(TopLeft, BottomRight);
	pDC->Ellipse(Square);
}
