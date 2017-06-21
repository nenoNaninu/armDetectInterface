#pragma once
#include"stream.h"
#ifdef _DLL_API_CALL_
#define _UNITY_API_ __declspec(dllexport)
#else 
#define _UNITY_API_ __declspec(dllimport)
#endif


extern "C" {

	_UNITY_API_ void* getStream();
	_UNITY_API_ void update(void* ptr);
	_UNITY_API_ void getIsPlayer(void* ptr, int input[]);
	_UNITY_API_ void getPlayerPosition(void* ptr, float positionX[],float positionY[]);
	_UNITY_API_ void getArmPosition(void* ptr, float positionX[],float positionY[]);
	_UNITY_API_ void getArmNum(void* ptr, int input[]);
	_UNITY_API_ void getPlayerId(void* ptr, unsigned long input[]);
	_UNITY_API_ void takeBackGround(void* ptr);
	_UNITY_API_ void releaseStream(void* ptr);

}