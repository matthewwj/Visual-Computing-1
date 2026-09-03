#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <opencv2/imgproc.hpp>
// Testing
using namespace cv;
using namespace std;

int main(int, char**)
{
    Mat frame;
    VideoCapture cap;
    Mat processedFrame;

    int deviceID = 0;             // 0 = open default camera
    int apiID = cv::CAP_ANY;      // 0 = autodetect default API
    // open selected camera using selected API
    cap.open(deviceID, apiID);
    // check if we succeeded
    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }

    cout << "Press:" << endl;
    cout << "0 - Original" << endl;
    cout << "1 - Gaussian Blur" << endl;
    cout << "2 - Grayscale" << endl;
    cout << "3 - Canny Edge Detection" << endl;
    cout << "q - Quit" << endl;

    //--- GRAB AND WRITE LOOP
    //cout << "Start grabbing" << endl
    //    << "Press any key to terminate" << endl;

    int filter = 0;

    for (;;)
    {
        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame);
        // check if we succeeded
        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }

        if (filter == 0) {
            // Original image
            processedFrame = frame;
        }
        else if (filter == 1) {
            // Gaussian Blur
            GaussianBlur(frame, processedFrame, Size(15, 15), 0);
        }   
        else if (filter == 2) {
            // Grayscale
            cvtColor(frame, processedFrame, COLOR_BGR2GRAY);
        }
        else if (filter == 3) {
            // Canny Edge Detection
            Mat gray, edges;
            cvtColor(frame, gray, COLOR_BGR2GRAY);
            Canny(gray, edges, 100, 200);
            processedFrame = edges;
        }

        // show live and wait for a key with timeout long enough to show images
        imshow("Live", processedFrame);
        
        // Check keyboard input
        char key = (char)waitKey(5);

        if (key == 'q')
            break;
        if (key == '0')
            filter = 0;
        else if (key == '1')
            filter = 1;
        else if (key == '2')
            filter = 2;
        else if (key == '3')
            filter = 3;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}