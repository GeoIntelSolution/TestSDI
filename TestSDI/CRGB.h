#pragma once
class CRGB
{
public:
	CRGB(void);
	CRGB(double red, double green, double blue, double alpha = 0.0);
	virtual ~CRGB();
	void Normalize();
public:
	double red;
	double green;
	double blue;
	double alpha;
};

