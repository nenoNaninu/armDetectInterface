#include"player.h"
#include<Windows.h>

bool Player::getIsArm()const
{
	return isArm;
}

int Player::getPositionX()const 
{
	return positionX;
}

int Player::getPositionY()const
{
	return positionY;
}

void Player::setId()
{
	id = (unsigned long)timeGetTime();
}

void Player::setIsArm(bool exist)
{
	isArm = exist;
}

void Player::setIsPlayer()
{
	isPlayer = true;
}

void Player::release()
{
	isArm = false;
	isPlayer = false;
	armNum = 0;
	headDepth = 0;
	id = 0;
	positionX = 0;
	positionY = 0;
	armPosition[0] = cv::Point(0, 0);
	armPosition[1] = cv::Point(0, 0);
}

bool Player::getIsPlayer ()const
{
	return isPlayer;
}

void Player::setId(unsigned long inputId)
{
	id = inputId;
}

void Player::setPosition(int x, int y)
{
	positionX = x;
	positionY = y;
}

unsigned long Player::getId()const 
{
	return id;
}

void Player::setHeadPosition(cv::Point inputPosition)
{
	headPosition = inputPosition;
}

void Player::setArmPosition(cv::Point inputPositin[],int inputArmNum)
{
	armNum = inputArmNum;
	for (int i = 0; i <inputArmNum ; i++)
	{
		armPosition[i] = inputPositin[i];
	}
}

void Player::setHeadDepth(float inputDepth)
{
	headDepth = inputDepth;
}

float Player::getHeadDepth()const
{
	return headDepth;
}

cv::Point Player::getHeadPosition()
{
	return headPosition;
}

int Player::getArmNum()const
{
	return armNum;
}

void Player::getArmPosition(cv::Point inputPosition[], int intputArmNum)const
{
	for (int i = 0; i < intputArmNum; i++)
	{
		inputPosition[i] = armPosition[i];
	}
}

