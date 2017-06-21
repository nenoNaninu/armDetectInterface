#include"dllCallFunctions.h"
#include<iostream>
//‚±‚¢‚Â‚ç‚Íc#‚©‚çŒÄ‚Î‚ê‚éŠÖ”ŒQ

void* getStream()
{
	Stream* streamPtr = new Stream();
	return (void*)streamPtr;
}

void releaseStream(void* ptr)
{
	Stream* streamptr = (Stream*)ptr;
	streamptr->release();
	delete streamptr;
}

void takeBackGround(void* ptr)
{
	Stream* streamptr = (Stream*)ptr;
	streamptr->takeBackGround();
}

void getIsPlayer(void* ptr, int input[])
{
	bool isPlayer[10];
	Stream* streamPtr = (Stream*)ptr;
	streamPtr->getIsPlayer(isPlayer);
	for (int i = 0; i < 10; i++)
	{
		if (isPlayer[i] == true)
		{
			input[i] = 1;
		}
		else
		{
			input[i] = 0;
		}
	}
	//std::cout << "isPlayer[0]" << input[0] << std::endl;
}

void update(void* ptr)
{
	Stream* streamPtr = (Stream*)ptr;
	streamPtr->update();
}

void getPlayerPosition(void* ptr, float positionX[], float positionY[])
{
	Stream* streamPtr = (Stream*)ptr;
	streamPtr->getPlayerPosition(positionX,positionY);	
}

void getArmPosition(void* ptr, float positionX[], float positionY[])
{
	Stream* streamPtr = (Stream*)ptr;
	streamPtr->getArmPosition(positionX, positionY);
}

void getArmNum(void* ptr,int input[])
{
	Stream* streamPtr = (Stream*)ptr;
	streamPtr->getArmNum(input);
}

void getPlayerId(void* ptr, unsigned long input[])
{
	Stream* streamPtr = (Stream*)ptr;
	streamPtr->getPlayerId(input);
}