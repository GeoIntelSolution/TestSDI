#pragma once
#include"CRGB.h"
class Cpoint2
{
public:
	Cpoint2(void);
	Cpoint2(int x, int y);
	Cpoint2(int x, int y, CRGB c);
public:
	int x, y;
	CRGB c;
};

