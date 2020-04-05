#include "API_detection.h"

/*
Function to detect ball and show the result
Input: Mat image
Output: 

*/
void API_detection::detect_ball(Mat image) {

    vector<Vec3f> circles;
    try
    {
        circles = position_ball(image);
    }
    catch (const std::exception&)
    {
        std::cout << "image not loaded" << std::endl;
    }
    

    for (size_t i = 0; i < circles.size(); i++)
    {
        char carac[50];
        Vec3i c = circles[i];
        Point center = Point(c[0], c[1]);
        sprintf(carac, "%d", i);


        Scalar mean = Color_detector(image, c);

        std::cout << "Boule_n:" << carac << mean << std::endl;

        //circle(image, center, 1, Scalar(255, 0, 0), 3, LINE_AA);

        int radius = c[2];
        circle(image, center, radius, Scalar(0, 0, 0), 3, LINE_AA);
        putText(image, carac, center, FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255));
        imshow("image with circle", image);

    }
}

API_detection::API_detection()
{
}
/*
Input: image matrice cv::Mat
Output: Vecteur 
*/
vector<Vec3f> API_detection::position_ball(Mat image)
{
    if (image.empty())
    {
        throw new Exception();
    }

    Mat gray;
    cvtColor(image, gray, COLOR_BGR2GRAY);
    medianBlur(gray, gray, 5);
    imshow("origin", image);
    vector<Vec3f> circles;
    HoughCircles(gray, circles,
        HOUGH_GRADIENT,
        1,
        gray.rows / 64,//matrix for minimum distance between circle
        30,
        13,
        12,//maximum radius of circle
        8 // minimum radius of circle
        );
    return circles;
}

/*
Function to return mean value of a cicle
Input: Mat original image , Circle point
Output: Scalar of mean color detected
*/
Scalar API_detection::Color_detector(Mat image, Vec3i c)
{
    //roi subMatrix of Matrix image
    Mat roi = image(Range(c[1] - c[2], c[1] + c[2]), Range(c[0] - c[2], c[0] + c[2]));

    Mat1b mask(roi.rows, roi.cols);

    Scalar mean = cv::mean(roi, mask);

    return mean;
}

void API_detection::experiment_detection_line(Mat image)
{
    Mat dst, cdst, cdstP;

    Mat src = image;
    // Check if image is loaded fine
    if (src.empty()) {
        throw new Exception();
    }
    // Edge detection
    Canny(src, dst, 30, 150, 3);
    // Copy edges to the images that will display the results in BGR
    cvtColor(dst, cdst, COLOR_GRAY2BGR);
    cdstP = cdst.clone();
    // Standard Hough Line Transform
    vector<Vec2f> lines; // will hold the results of the detection
    HoughLines(dst, lines, 1, CV_PI / 180, 150, 0, 0); // runs the actual detection
    // Draw the lines
    for (size_t i = 0; i < lines.size(); i++)
    {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        line(cdst, pt1, pt2, Scalar(0, 0, 255), 3, LINE_AA);
    }
    // Probabilistic Line Transform
    vector<Vec4i> linesP; // will hold the results of the detection
    HoughLinesP(dst, linesP, 1, CV_PI / 180, 50, 50, 10); // runs the actual detection
    // Draw the lines
    for (size_t i = 0; i < linesP.size(); i++)
    {
        Vec4i l = linesP[i];
        line(cdstP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);
    }
    // Show results
    imshow("Source", src);
    //imshow("Detected Lines (in red) - Standard Hough Line Transform", cdst);
    imshow("Detected Lines (in red) - Probabilistic Line Transform", cdstP);
}
