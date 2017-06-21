#pragma once
#include"playerDetect.h"
#include"kinectAPI.h"
#include<vector>
#include<fstream>
#include<string>

class Stream
{
private:
	
	PlayerDetect playerDetect;
	KinectAPI kinect;
	cv::Mat depthImage;
	int imageWidth;
	int imageHight;
	cv::Mat homographyMat;
	std::vector<Player> player;
	const int playerNum = 10;
	const int armNum = 20;
	//homographyのファイルを読みこんでスプリットするための関数・・・c#便利なんやなぁ(ため息)
	std::vector<std::string> split(const std::string& line,char delimiter);

public:

	//ストリームの初期化内部でhomograpy行列を取得して保存
	Stream()
	{
		player = std::vector<Player>(10);
		kinect.initialize();
		imageWidth = kinect.getWidth();
		imageHight = kinect.getHight();
		playerDetect.initialize(imageWidth, imageHight);
		depthImage = cv::Mat(imageHight, imageWidth, CV_32FC1);
		homographyMat = cv::Mat(3, 3, CV_32FC1);

		std::ifstream ifs("homography.csv");

		std::string line;

		int i = 0;
		float* matPtr = (float*)homographyMat.data;
		while (std::getline(ifs,line))
		{
			std::vector<std::string> temp = split(line, ',');
			matPtr[i] = std::stod(temp[0]);
			matPtr[i + 1] = std::stod(temp[1]);
			matPtr[i + 2] = std::stod(temp[2]);
			i += 3;
			if (i == 9)
			{
				break;
			}
		}




	}

	void update();

	void takeBackGround();

	void getPlayerPosition(float positionX[], float positionY[]);

	void getArmPosition(float positionX[], float positionY[]);

	void getArmNum(int input[]);

	void getIsPlayer(bool input[]);

	void release();

	void getPlayerId(unsigned long input[]);
};