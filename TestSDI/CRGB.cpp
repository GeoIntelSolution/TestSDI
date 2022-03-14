#include "pch.h"
#include "CRGB.h"

CRGB::CRGB(void)
{
}

CRGB::CRGB(double red, double green, double blue, double alpha)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->alpha = alpha;
}

void CRGB::Normalize()
{
	red = (red < 0.0) ? 0.0 : ((red > 1.0) ? 1.0 : red);
	green = (green < 0.0) ? 0.0 : ((green > 1.0) ? 1.0 : green);
	blue = (blue < 0.0) ? 0.0 : ((blue > 1.0)?1.0: blue);
}
