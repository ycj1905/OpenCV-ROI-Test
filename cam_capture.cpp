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

    CvCapture* capture = cvCaptureFromCAM(0);  //Capture using any camera connected
    IplImage* frame1 = cvQueryFrame(capture); //Create image frames from capture

double t = (double)getTickCount();
     waitKey(delay);
    IplImage* frame2 = cvQueryFrame(capture); //Create image frames from capture

t = ((double)getTickCount() - t)/getTickFrequency();
cout << "Times passed in seconds: " << t << endl;

    src1 = cvarrToMat(frame1);  //ipl to Mat
    src2 = cvarrToMat(frame2);  //ipl to Mat
    
  /// Create dst1, map_x and map_y with the same size as src:
  src=src1;
  dst2.create( src.size(), src.type() );
  map_x.create( src.size(), CV_32FC1 );
  map_y.create( src.size(), CV_32FC1 );
  
  /// Update map_x & map_y. Then apply remap
    update_map(ind);
    remap( src, dst1, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0) );

  /// Create dst2, map_x and map_y with the same size as src:
  src=src2;
  dst2.create( src.size(), src.type() );
  map_x.create( src.size(), CV_32FC1 );
  map_y.create( src.size(), CV_32FC1 );
  
 
/// Update map_x & map_y. Then apply remap
    update_map(ind);
    remap( src, dst2, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0) ); 
///  write image
     imwrite( "capture_1.jpg", dst1 );
     imwrite( "capture_2.jpg", dst2 );


    // Display results
    //imshow( remap_window, dst );
    IplImage ipl1=dst1;             //Mat to ipl
    IplImage ipl2=dst2;             //Mat to ipl
    cvShowImage("capture_1", &ipl1);   //Show captured image
    cvShowImage("capture_2", &ipl2);   //Show captured image
    waitKey(0);


cvReleaseCapture(&capture); //Release capture.
cvDestroyWindow("capture_1"); //Destroy Window
cvDestroyWindow("capture_2"); //Destroy Window
return 0;
}
/**
 * @function update_map
 * @brief Fill the map_x and map_y matrices with 4 types of mappings
 */
void update_map( int ind )
{
//  ind = ind%4;

  for( int j = 0; j < src.rows; j++ )
    { for( int i = 0; i < src.cols; i++ )
     {
           switch( ind )
         {
         case 0:
           if( i > src.cols*0.25 && i < src.cols*0.75 && j > src.rows*0.25 && j < src.rows*0.75 )
                 {
               map_x.at<float>(j,i) = 2*( i - src.cols*0.25f ) + 0.5f ;
               map_y.at<float>(j,i) = 2*( j - src.rows*0.25f ) + 0.5f ;
              }
           else
         { map_x.at<float>(j,i) = 0 ;
               map_y.at<float>(j,i) = 0 ;
                 }
                   break;
         case 1:
               map_x.at<float>(j,i) = (float)i ;
               map_y.at<float>(j,i) = (float)(src.rows - j) ;
           break;
             case 2:
               map_x.at<float>(j,i) = (float)(src.cols - i) ;
               map_y.at<float>(j,i) = (float)j ;
           break;
             case 3:
               map_x.at<float>(j,i) = (float)(src.cols - i) ;
               map_y.at<float>(j,i) = (float)(src.rows - j) ;
           break;
             } // end of switch
     }
    }
//  ind++;
}

