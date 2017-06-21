#pragma once
#include<opencv2\core.hpp>
#include<vector>

class Player
{
private:
	bool isPlayer;
	bool isArm;
	unsigned long id;
	cv::Point headPosition;
	int positionX;
	int positionY;
	cv::Point armPosition[2]; //���E�̘r���Ԃ����ނ��Ƃ��l���ē�قǍ쐬�B
	int armNum;
	float headDepth;
    
	
public:
	Player()
	{
		armNum = 0;
		positionX = 0;//����d�S
		positionY = 0;//������d�S
		headDepth = 0;
		isPlayer = false;
		isArm = false;
		id = 0;
	};
	~Player()
	{
	};

	int getArmNum()const;

	void setHeadDepth(float inputDepth);
	float getHeadDepth()const;

	void setHeadPosition(cv::Point inputPosition);
	cv::Point getHeadPosition();

	void setArmPosition(cv::Point inputPosition[],int inputArmNum);
	void getArmPosition(cv::Point inputPosition[],int intputArmNum)const;

	bool getIsArm()const;
	void setIsArm(bool exist);

	void setId(unsigned long inputId);
	void setId();
	unsigned long getId() const;

	void setIsPlayer();
	bool getIsPlayer()const;

	void release();

	void setPosition(int x, int y);

	int getPositionX()const;
	int getPositionY()const;

	
};

