#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>

#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;

class API_detection
{
	public:
		void detect_ball(Mat image);
		API_detection();
		vector<Vec3f> position_ball(Mat image);
		Scalar Color_detector(Mat image, Vec3i c);

		void experiment_detection_line(Mat image);
};

