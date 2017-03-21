/*    cam_capture.cpp :Code to display an image using OpenCV

     g++ -o test_3 test_3.cpp `pkg-config opencv --cflags --libs`
     ./test_3 lena.jpg
 
*/

#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;
char key;

/// Global variables
Mat src;
Mat src1, src2;
Mat dst1, dst2;
Mat map_x, map_y;

/// Function Headers
void update_map( int ind );

/**
 * @function main
 */
int main( int argc, char** argv )
{
    int ind = 2;
    int delay = 1;
    stringstream s;
    s << argv[1];
    s >> ind;
	if( argc == 2) 
	{
		delay = atoi(argv[2]);
        } 
    cvNamedWindow("capture_1", CV_WINDOW_AUTOSIZE );    //Create capture window
    cvNamedWindow("capture_2", CV_WINDOW_AUTOSIZE );    //Create capture window

    CvCapture* capture1 = cvCaptureFromCAM(0);  //Capture using any camera connected
    IplImage* frame1 = cvQueryFrame(capture1); //Create image frames from capture

double t = (double)getTickCount();
     waitKey(2000);
 
    IplImage* frame2 = cvQueryFrame(capture1); //Create image frames from capture
    
t = ((double)getTickCount() - t)/getTickFrequency();
cout << "Times passed in seconds: " << t <<"    *************"<< endl;


///  write image
//    src1 = cvarrToMat(frame1);  //ipl to Mat
//    src2 = cvarrToMat(frame2);  //ipl to Mat
//     imwrite( "capture_1.jpg", src1 );
//     imwrite( "capture_2.jpg", src2 );


    // Display results
    
    cvShowImage("capture_1", frame1);   //Show captured image
    cvShowImage("capture_2", frame2);   //Show captured image
    waitKey(0);


cvReleaseCapture(&capture1); //Release capture.
//cvReleaseCapture(&capture2); //Release capture.
cvDestroyWindow("capture_1"); //Destroy Window
cvDestroyWindow("capture_2"); //Destroy Window
return 0;
}

