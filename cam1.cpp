/*    cam1.cpp :Code to display an image using OpenCV

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
Mat src, dst;
Mat map_x, map_y;



/// Function Headers
void update_map( int ind );

/**
 * @function main
 */
int main( int argc, char** argv )
{
    int ind = 0;
    stringstream s;
    s << argv[1];
    s >> ind;
 
    cvNamedWindow("capture", CV_WINDOW_AUTOSIZE );    //Create capture window

    CvCapture* capture = cvCaptureFromCAM(0);  //Capture using any camera connected
    IplImage* frame = cvQueryFrame(capture); //Create image frames from capture
    src = cvarrToMat(frame);  //ipl to Mat
    
  /// Create dst, map_x and map_y with the same size as src:
  dst.create( src.size(), src.type() );
  map_x.create( src.size(), CV_32FC1 );
  map_y.create( src.size(), CV_32FC1 );
  
  
    /// Update map_x & map_y. Then apply remap
    update_map(ind);
    remap( src, dst, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0) );

    // Display results
    //imshow( remap_window, dst );
    IplImage ipl=dst;             //Mat to ipl
    cvShowImage("capture", &ipl);   //Show captured image
    waitKey(0);


cvReleaseCapture(&capture); //Release capture.
//cvDestroyWindow(argv[1]); //Destroy Window
cvDestroyWindow("capture"); //Destroy Window
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

