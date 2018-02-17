#pragma once
#include<opencv2\highgui.hpp>
#include<opencv2\imgcodecs.hpp>

struct MouseParam
{
	unsigned int x;
	unsigned int y;
	int event;
	int flags;
};

void mFunc(int event, int x, int y, int flags, void *param);