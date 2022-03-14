#include "pch.h"
#include "Cpoint2.h"

Cpoint2::Cpoint2(void)
{
}

Cpoint2::Cpoint2(int x, int y)
{
	this->x = x;
	this->y = y;
}

Cpoint2::Cpoint2(int x, int y, CRGB c)
{
	this->x = x;
	this->y = y;
	this->c = c;
}
