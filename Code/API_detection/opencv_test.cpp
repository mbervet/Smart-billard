// opencv_test.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>

#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>
#include "API_detection.h"

using namespace cv;
using namespace std;



Mat src_gray;

int thresh = 100;
RNG rng(12345);


void thresh_callback(int, void*);


int main()
{
    // Read the image file
    //Mat image = imread("Z:/image/P3130438_01.jpg");
    //Mat image = imread("Z:/image/P3130439.jpg");
    //Mat image = imread("Z:/image/P3130440.jpg");
    Mat image = imread("Z:/image/P3130441.jpg");
    Mat image2 = imread("Z:/image/P3130442.jpg");

    
    API_detection api;

    api.detect_ball(image);

    waitKey();

    

    VideoCapture cap;
    /*
    if (!cap.open(0))
        return EXIT_SUCCESS;
    for (;;)
    {
        try
        {
            Mat frame;
            cap >> frame;
            if (frame.empty()) break;
            if (waitKey(10) == 27) break;
            api.detect_ball(frame);
        }
        catch (const std::exception&)
        {

        }

    }

    */
    
    system("pause");
    api.experiment_detection_line(image);
    
    /*
    waitKey();

    cvtColor(image2, src_gray, COLOR_BGR2GRAY);
    blur(src_gray, src_gray, Size(3, 3));
    const char* source_window = "Source";
    namedWindow(source_window);
    imshow(source_window, image2);
    const int max_thresh = 255;
    createTrackbar("Canny thresh:", source_window, &thresh, max_thresh, thresh_callback);
    thresh_callback(0, 0);


    waitKey();
    */
    system("pause");
    
    return EXIT_SUCCESS;
}

void thresh_callback(int, void*)
{
    Mat canny_output;
    Canny(src_gray, canny_output, thresh, thresh * 2);
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
    Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
    for (size_t i = 0; i < contours.size(); i++)
    {
        Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
        drawContours(drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
    }
    imshow("Contours", drawing);
}
