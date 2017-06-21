#include<opencv2\core.hpp>
#include<opencv2\highgui.hpp>
#include<opencv2\imgproc.hpp>
#include<opencv2\imgcodecs.hpp>
#include"kinectAPI.h"
#include"playerDetect.h"
#include"mouseCtr.h"
#include"dllCallFunctions.h"

//using namespace cv;
//
//int main()
//{
//	KinectAPI kinect;
//	kinect.initialize();
//	int imageWidth = kinect.getWidth();
//	int imageHight = kinect.getHight();
//
//	Mat depthImage(imageHight, imageWidth, CV_32FC1);
//	namedWindow("KinectDepthImage");
//	PlayerDetect playerDetect = PlayerDetect(imageWidth,imageHight);
//
//	//以下デバッグ	
//	MouseParam mouseEvent;
//	setMouseCallback("KinectDepthImage", mFunc, &mouseEvent);
//	Point p0;
//	//ここまでデバッグ
//	while (1)
//	{
//		char key = waitKey(1);
//		kinect.upDateImage();
//		kinect.queryImage(depthImage);
//
//		//デバッグ用で
//		
//		if (mouseEvent.event == CV_EVENT_LBUTTONDOWN)
//		{
//			p0 = Point(mouseEvent.x, mouseEvent.y);
//		}
//
//		float* depthPtr = (float*)depthImage.data;
//		float depthVal = depthPtr[imageWidth*p0.y + p0.x];
//
//		char string[128];
//		sprintf_s(string, "depth::%lf", depthVal);
//		cv::putText(depthImage, string, p0, CV_FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0), 1, CV_AA);
//
//		//ここまでデバッグ用
//
//		imshow("KinectDepthImage", depthImage);
//		playerDetect.upDateImage(depthImage);
//		playerDetect.calcBinImage();
//		//playerDetect.debugDepth();
//		playerDetect.findPlayer();
//
//		if (key == 'q')
//		{
//			break;
//		}
//		if (key == 'b')
//		{
//			playerDetect.takeBackGroundImage();
//		}
//		if (key == 's')
//		{
//			waitKey(0);
//		}
//	}
//
//	destroyAllWindows();
//
//	return 0;
//}

int main()
{

	void*  streamPtr;
	streamPtr = getStream();
	
	int armNum[10];
	int isPlayer[10];
	float playerPositionX[10];
	float playerPositionY[10];
	float armPositionX[20];
	float armPositionY[20];
	unsigned long playerId[10];

	while (1)
	{
		char key = cv::waitKey(1);
		if (key == 'b')
		{
			takeBackGround(streamPtr);
		}
		if (key == 'q')
		{
			break;
		}

		if (key == 's')
		{
			cv::waitKey(0);
		}
		update(streamPtr);
		getIsPlayer(streamPtr, isPlayer);
		getPlayerId(streamPtr, playerId);
		getArmNum(streamPtr, armNum);
		getPlayerPosition(streamPtr, playerPositionX, playerPositionY);
		getArmPosition(streamPtr, armPositionX, armPositionY);

		std::cout << "isPlayer" << isPlayer[0] << std::endl;

		//if (1)
		//{
			std::cout << "playerId" << playerId[0] << std::endl;
		//	std::cout << "ArmNum" << armNum[0] << std::endl;

		//}

	}


	return 0;
}