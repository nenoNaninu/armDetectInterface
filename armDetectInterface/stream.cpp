#include"stream.h"
#include<iostream>

std::vector<std::string> Stream::split(const std::string& line, char delimiter)
{
	std::istringstream stream(line);
	std::string filed;
	std::vector<std::string> result;
	while (std::getline(stream, filed, delimiter))
	{
		result.push_back(filed);
	}

	return result;
}

void Stream::update()
{
	kinect.upDateImage();
	kinect.queryImage(depthImage);
	playerDetect.upDateImage(depthImage);
	playerDetect.calcBinImage();
	playerDetect.findPlayer();
}

void Stream::takeBackGround()
{
	playerDetect.takeBackGroundImage();
}

void Stream::release()
{
	cv::destroyAllWindows();
}

void Stream::getIsPlayer(bool input[])
{
	playerDetect.getIsPlayer(input);
}

void Stream::getPlayerPosition(float positionX[], float positionY[])
{
	//カメラ座標を取得、ホモグラフィをも用いてガリっと計算する。
	playerDetect.getPlayerPosition(positionX,positionY);//カメラ画像取得
	cv::Mat cameraMat = cv::Mat(3, 1, CV_32FC1);
	float* cameraMatPtr = (float*)cameraMat.data;
	cv::Mat unityPosiMat(3, 1, CV_32FC1);
	float* unityPosiMatPtr = (float*)unityPosiMat.data;

	for (int i = 0; i < 10 ; i++)
	{
		cameraMatPtr[0] = positionX[i];
		cameraMatPtr[1] = positionY[i];
		cameraMatPtr[2] = 1.0f;

		unityPosiMat = homographyMat*cameraMat;

		positionX[i] = unityPosiMatPtr[0];
		positionY[i] = unityPosiMatPtr[1];

		if (i == 0)
		{
			std::cout << "positionX::" << positionX[0] << "positionY::" << positionX[0] << std::endl;
		}
	}
}

void Stream::getArmPosition(float positionX[], float positionY[])
{

	playerDetect.getArmPosition(positionX,positionY);
	cv::Mat cameraMat = cv::Mat(3, 1, CV_32FC1);
	float* cameraMatPtr = (float*)cameraMat.data;
	cv::Mat unityPosiMat(3, 1, CV_32FC1);
	float* unityPosiMatPtr = (float*)unityPosiMat.data;

	for (int i = 0; i < 10; i++)
	{
		cameraMatPtr[0] = positionX[i];
		cameraMatPtr[1] = positionY[i];
		cameraMatPtr[2] = 1.0f;

		unityPosiMat = homographyMat*cameraMat;

		positionX[i] = unityPosiMatPtr[0];
		positionY[i] = unityPosiMatPtr[1];
	}
}

void Stream::getArmNum(int input[])
{
	playerDetect.getArmNum(input);
}

void Stream::getPlayerId(unsigned long input[])
{
	playerDetect.getPlayerId(input);
}
