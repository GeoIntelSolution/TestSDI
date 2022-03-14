#pragma once
class CSphere
{
public:
	CSphere(void);
	virtual ~CSphere(void);
	void SetParameter(int R, CPoint CenterPoint);
	void Draw(CDC* pDC);
public:
	int R;
	CPoint CenterPoint;
};

