#pragma once
#include<opencv2\core.hpp>
#include"player.h"
#include<vector>
#include<opencv2\highgui.hpp>

class PlayerDetect {
private:

	cv::Mat binImage;
	cv::Mat backGroundImage;
	cv::Mat inputImage;
	cv::Mat element;
	int hight;
	int width;
	int thresholdVale = 60;
	std::vector<Player> playerArray;
	std::vector<Player> prevPlayerArray;
	int trackingDelta = 40;
	cv::Mat bin2ColorImage;
	float getDistance(const Player& prevPlayer, const Player& player);
	cv::Point averageArmPosition[5];
	void averageArmPositionSort();
	const int playerNum = 10;
	//const int armNum = 20;

public:
	PlayerDetect()
	{

	}
	PlayerDetect(int inputImageWidth, int inputImageHight)
	{
		hight = inputImageHight;
		width = inputImageWidth;
		playerArray = std::vector<Player>(10);
		prevPlayerArray = std::vector<Player>(10);
		element = cv::Mat::ones(3, 3, CV_8UC1);
		binImage = cv::Mat(hight, width, CV_8UC1);
		backGroundImage = cv::Mat(hight, width, CV_32FC1, cv::Scalar(0));
		inputImage = cv::Mat(hight, width, CV_32FC1);
		cv::namedWindow("binImage");
		for (int i = 0; i< 5; i++)
		{
			averageArmPosition[i].x = 0;
			averageArmPosition[i].y = 0;
		}
	}

	//コンストラクタで引数を取れなかったときは初期化関数を呼ばないといけない。
	void initialize(int inputImageWidth, int inputImageHight);

	void clacAverageArmPosition(const cv::Point point,cv::Point& outPut);

	void takeBackGroundImage();

	void calcBinImage();

	void upDateImage(const cv::Mat& mat);

	void debugDepth();
	
	void findPlayer();

	void setPlayerId();

	void draw();

	void armDetect(const cv::Mat& inputROIDepthImage,float depth, Player& player, cv::Point inputMinPosition,const cv::Rect& inputRoi);

	void getIsPlayer(bool input[]);

	void getPlayerPosition(float positionX[], float positionY[]);

	void getArmPosition(float positionX[], float positionY[]);

	void getArmNum(int input[]);

	void getPlayerId(unsigned long input[]);
};