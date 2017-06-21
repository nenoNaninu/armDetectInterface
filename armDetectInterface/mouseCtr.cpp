#include"mouseCtr.h"

void mFunc(int event, int x, int y, int flags, void *param)
{
	MouseParam* mouseParamPtr = static_cast<MouseParam*>(param);
	(*mouseParamPtr).x = x;
	(*mouseParamPtr).y = y;
	(*mouseParamPtr).event = event;
	(*mouseParamPtr).flags = flags;
}