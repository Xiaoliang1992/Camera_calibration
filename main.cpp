#include <opencv2/opencv.hpp>  
#include <iostream>  
#include <stdio.h>
using namespace std;  
using namespace cv;  
int main( )
{
    Mat frame;
    VideoCapture capture;
    capture.open(0);
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    char imgName[40]; 
    int num_frame = 0;

    while(true)
    {
        capture >> frame;
        imshow("Display Image", frame);
        char c = waitKey(50);
        if (c == 's')
        {
            sprintf(imgName, "../saved _pics/image%d.jpg",num_frame++);  
            cout << "Frame [" << num_frame << "] has been saved" << endl;
            imwrite( imgName,frame);  
        }
        if (c == 'q')
        return 0;
    }
    
    return 0;
}