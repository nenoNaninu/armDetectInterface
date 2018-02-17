#include"playerDetect.h"
#include<opencv2\imgcodecs.hpp>
#include<opencv2\imgproc.hpp>
#include<opencv2\highgui.hpp>
#include<iostream>
#include<cmath>

void PlayerDetect::takeBackGroundImage()
{
	inputImage.copyTo(backGroundImage);
}

float PlayerDetect::getDistance(const Player& prevPlayer, const Player& player)
{
	return std::sqrt(std::pow(prevPlayer.getPositionX() - player.getPositionX(), 2) + std::pow(prevPlayer.getPositionY() - player.getPositionY(), 2));
}

void PlayerDetect::calcBinImage()
{
	cv::Mat diffTemp32F(hight, width, CV_32FC1);
	cv::absdiff(backGroundImage, inputImage, diffTemp32F);
	cv::Mat diffTemp8U(hight, width, CV_8UC1);
	diffTemp32F.convertTo(diffTemp8U, CV_8UC1);
	cv::threshold(diffTemp8U, binImage, thresholdVale, 255, CV_THRESH_BINARY);
	cv::erode(binImage, binImage, element, cv::Point(-1, -1), 1);
	//cv::imshow("binImage",binImage);
}

void PlayerDetect::upDateImage(const cv::Mat& mat)
{
	//hight, width, CV_32FC1;
	mat.copyTo(inputImage);
}

void PlayerDetect::debugDepth()
{
	float* temp = (float*)inputImage.data;
	//std::cout << temp[hight / 2 * inputImage.cols + width / 2] << std::endl;
	cv::circle(inputImage, cv::Point(width / 2, hight / 2), 10, cv::Scalar(0), 3, 4);
}

void PlayerDetect::findPlayer()
{
	std::vector<std::vector<cv::Point>> conters;
	cv::findContours(binImage, conters, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	prevPlayerArray = playerArray;
	for (Player& player : playerArray)
	{
		player.release();
	}

	int i = 0;
	if (!conters.empty())
	{
		for (const std::vector<cv::Point>& conter : conters)
		{
			double size = cv::contourArea(conter);

			if (size < 200)
			{
				continue;
			}

			cv::Mat copyImage = inputImage.clone();
			cv::Rect roi = cv::boundingRect(conter);
			cv::Mat roiImage = copyImage(roi);
			//cv::Mat mask = binCopyImage(roi);
			cv::Mat mask;
			cv::inRange(roiImage, 400, 2200, mask);
			cv::Point minPosition;
			cv::Point maxPosition;

			double minVal;
			double maxVal;
			//double minVal,maxVal;

			cv::Moments moment = cv::moments(conter);
			int centerX = (int)(moment.m10 / moment.m00);
			int centerY = (int)(moment.m01 / moment.m00);

			playerArray[i].setIsPlayer();
			playerArray[i].setPosition(centerX, centerY);

			cv::erode(mask, mask, element);
			cv::erode(mask, mask, element);
			//cv::imshow("roiImage", roiImage);
			//cv::imshow("mask", mask);
			cv::minMaxLoc(roiImage, &minVal, &maxVal, &minPosition, &maxPosition, mask);

			playerArray[i].setHeadPosition(cv::Point(minPosition.x + roi.x, minPosition.y + roi.y));

			//std::cout << "minVal" << minVal << "maxVal" << maxVal << std::endl;


			armDetect(roiImage, minVal, playerArray[i], minPosition, roi);

			//cv::imshow("roi", roiImage);
			i++;
			if (i == 10)
			{
				break;
			}
		}
		setPlayerId();
		draw();
		cv::imshow("binImage", binImage);
		cv::imshow("inputImage", inputImage);
	}
}

void PlayerDetect::setPlayerId()
{
	for (Player& player : playerArray)
	{
		if (!player.getIsPlayer())
		{
			continue;
		}

		for (const Player& prevPlayer : prevPlayerArray)
		{
			if (prevPlayer.getIsPlayer())
			{
				if (trackingDelta > getDistance(prevPlayer, player))
				{
					player.setId(prevPlayer.getId());
					break;
				}
			}
		}

		if (player.getId() == 0 && player.getIsPlayer())
		{
			player.setId();
		}

	}
}

void PlayerDetect::draw()
{
	for (const Player& player : playerArray)
	{
		//重心描画
		cv::circle(binImage, cv::Point(player.getPositionX(), player.getPositionY()), 5, cv::Scalar(0), -1);
		//id描画
		char string[128];
		sprintf_s(string, "id::%lu", player.getId());
		cv::putText(binImage, string, cv::Point(player.getPositionX(), player.getPositionY()), CV_FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(40), 1, CV_AA);
		//手の重心位置の描画
		if (player.getIsArm())
		{
			int armNum = player.getArmNum();
			cv::Point armPosition[2];
			player.getArmPosition(armPosition, armNum);
			for (int i = 0; i < armNum; i++)
			{
				cv::circle(binImage, armPosition[i], 5, cv::Scalar(0), -1);
			}
		}
	}
}


//腕を探索してplayerのオブジェクトにかたかたとデータを打ち込む
void PlayerDetect::armDetect(const cv::Mat& inputROIDepthImage, float depth, Player& player, cv::Point inputMinPosition, const cv::Rect& inputRoi)
{
	cv::Mat inputImageCopy;
	cv::Mat armBinImage;
	int radius;
	int inRangeParamHight, inRangeParamLow;

	if (1400 <= depth)
	{
		radius = 40;
		inRangeParamHight = 200;
		inRangeParamLow = 600;
	}
	else
	{
		radius = 180;
		inRangeParamHight = 150;
		inRangeParamLow = 600;
	}
	inputROIDepthImage.copyTo(inputImageCopy);

	cv::circle(inputImageCopy, inputMinPosition, radius, cv::Scalar(0), -1);

	cv::inRange(inputImageCopy, depth + inRangeParamHight, depth + inRangeParamLow, armBinImage);
	//cv::imshow("inputImageCopy", inputImageCopy);
	//cv::imshow("armBimImage", armBinImage);

	std::vector<std::vector<cv::Point>> armConters;

	cv::findContours(armBinImage, armConters, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	cv::Point armPosition[2];

	if (!armConters.empty())
	{
		int i = 0;
		for (const std::vector<cv::Point>& armConter : armConters)
		{
			double size = cv::contourArea(armConter);

			if (size < 200)
			{
				continue;
			}

			player.setIsArm(true);

			cv::Moments moment = cv::moments(armConter);

			int centerX = (int)(moment.m10 / moment.m00);
			int centerY = (int)(moment.m01 / moment.m00);

			cv::Point tempPosition(centerX + inputRoi.x, centerY + inputRoi.y);

			clacAverageArmPosition(tempPosition, tempPosition);

			armPosition[i] = tempPosition;

			i++;
			if (i == 2)
			{
				break;
			}

		}
		player.setArmPosition(armPosition, i);
	}

	if (!player.getIsArm())
	{
		for (int i = 0; i < 5; i++)
		{
			averageArmPosition[i].x = 0;
			averageArmPosition[i].y = 0;
		}
	}
}


void PlayerDetect::averageArmPositionSort()
{
	for (int i = 0; i < 4; i++)
	{
		averageArmPosition[i] = averageArmPosition[i + 1];
	}
}

void PlayerDetect::clacAverageArmPosition(const cv::Point point, cv::Point& outPut)
{
	averageArmPositionSort();
	averageArmPosition[5] = point;

	cv::Point sumPoint(0, 0);

	int sumNum = 0;

	for (int i = 0; i < 5; i++)
	{
		if (averageArmPosition[i].x == 0 && averageArmPosition[i].y == 0)
		{
			continue;
		}
		sumPoint += averageArmPosition[i];
		sumNum++;
	}
	if (sumNum != 0)
	{
		sumPoint = (sumPoint / sumNum);

		outPut = sumPoint;

		return;
	}
}


void PlayerDetect::getIsPlayer(bool input[])
{
	//for (int i = 0; i < 10; i++)
	//{
	//	input[i] = playerArray[i].getIsPlayer();
	//}
	int i = 0;
	for (const Player& player : playerArray)
	{
		input[i] = player.getIsPlayer();
		i++;
	}
}


void PlayerDetect::getPlayerPosition(float positionX[], float positionY[])
{
	for (int i = 0; i < playerArray.size(); i++)
	{
		positionX[i] = playerArray[i].getPositionX();
		positionY[i] = playerArray[i].getPositionY();
	}
}

void PlayerDetect::getArmNum(int input[])
{
	for (int i = 0; i < playerArray.size(); i++)
	{
		input[i] = playerArray[i].getArmNum();
	}
}

void PlayerDetect::getArmPosition(float positionX[], float positionY[])
{
	int j = 0;
	for (int i = 0; i < 10; i++)
	{
		cv::Point point[2];
		playerArray[i].getArmPosition(point,2);
		positionX[j] = point[0].x;
		positionY[j] = point[0].y;
		positionX[j + 1] = point[1].x;
		positionY[j + 1] = point[1].y;
		j += 2;
	}
}

void PlayerDetect::initialize(int inputImageWidth, int inputImageHight)
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

void PlayerDetect::getPlayerId(unsigned long input[])
{
	for (int i = 0; i < playerArray.size();i++)
	{
		input[i] = playerArray[i].getId();
	}
}