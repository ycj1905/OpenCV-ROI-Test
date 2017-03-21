/*    cam0.cpp :One maping of a picture

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
const char* remap_window = "Remap demo";
int ind = 0;


/// Function Headers
void update_map( void );

/**
 * @function main
 */
int main( int argc, char** argv )
{
 
    cvNamedWindow("capture", CV_WINDOW_AUTOSIZE );    //Create capture window

    CvCapture* capture = cvCaptureFromCAM(0);  //Capture using any camera conne$
    IplImage* frame = cvQueryFrame(capture); //Create image frames from capture
    src = cvarrToMat(frame);  //ipl to Mat
    
  /// Create dst, map_x and map_y with the same size as src:
  dst.create( src.size(), src.type() );
  map_x.create( src.size(), CV_32FC1 );
  map_y.create( src.size(), CV_32FC1 );
  
  /// Loop

  for(;;)
  {
    /// Each 1 sec. Press ESC to exit the program
    int c = waitKey( 5000 );

    if( (char)c == 27 )
      { break; }

    /// Update map_x & map_y. Then apply remap
    update_map();
    remap( src, dst, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0) );

    // Display results
    //imshow( remap_window, dst );
    IplImage ipl=dst;             //Mat to ipl
    cvShowImage("capture", &ipl);   //Show captured image
  }

cvReleaseCapture(&capture); //Release capture.
//cvDestroyWindow(argv[1]); //Destroy Window
cvDestroyWindow("capture"); //Destroy Window
return 0;
}
/**
 * @function update_map
 * @brief Fill the map_x and map_y matrices with 4 types of mappings
 */
void update_map( void )
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

