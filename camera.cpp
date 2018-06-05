#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    VideoCapture inputVideo(0);
    if (!inputVideo.isOpened())
    {
        cout << "Could not open the input video: " << endl;
        return -1;
    }
    Mat frame;
    Mat frameCalibration;

    inputVideo >> frame; // cannot be neglected!!!
    Mat cameraMatrix = Mat::eye(3, 3, CV_64F);
    cameraMatrix.at<double>(0, 0) = 4.745537506243416e+02;
    cameraMatrix.at<double>(0, 1) = 0.0;
    cameraMatrix.at<double>(0, 2) = 2.974489590204837e+02;
    cameraMatrix.at<double>(1, 1) = 4.745690628394497e+02;
    cameraMatrix.at<double>(1, 2) = 2.651734958206504e+02;

    Mat distCoeffs = Mat::zeros(5, 1, CV_64F);
    distCoeffs.at<double>(0, 0) = -0.416811439187776;
    distCoeffs.at<double>(1, 0) =  0.206770846440788;
    distCoeffs.at<double>(2, 0) =  0;
    distCoeffs.at<double>(3, 0) =  0;
    distCoeffs.at<double>(4, 0) =  0;

    Mat view, rview, map1, map2;
    Size imageSize;
    imageSize = frame.size();
    initUndistortRectifyMap(cameraMatrix, distCoeffs, Mat(),
        getOptimalNewCameraMatrix(cameraMatrix, distCoeffs, imageSize, 1, imageSize, 0),
        imageSize, CV_16SC2, map1, map2);


    while (1) //Show the image captured in the window and repeat
    {
        inputVideo >> frame;              // read
        if (frame.empty()) break;         // check if at end
        remap(frame, frameCalibration, map1, map2, INTER_LINEAR);
        imshow("Origianl", frame);
        imshow("Calibration", frameCalibration);
        char key = waitKey(1);
        if (key == 27 || key == 'q' || key == 'Q')break;
    }
    return 0;
}