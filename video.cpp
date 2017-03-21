/*

remapping video stream
remapping  index=2 means x <--> -x

*/
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

/// Global variables
Mat src, dst;
Mat map_x, map_y;

void update_map( int index );

int main(int argc, char** argv)
{
    VideoCapture cap;
    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.

        stringstream ss;
	string str = ss.str();
	int camera_n;
        cout << "input camera number: ";
        cin >> camera_n;
        ss <<"camera number: "<< camera_n;
        str = ss.str();
 	if(cap.open(camera_n))
            cout <<str<< "  is open good"<<endl;
        else
            cout <<str<< "  is not open good"<<endl;

          cap >> src;
          dst.create( src.size(), src.type() );
          map_x.create( src.size(), CV_32FC1 );
          map_y.create( src.size(), CV_32FC1 );
int ind=2;   //remapping  index=2 means x <--> -x

    for(;;)
    {

          cap >> src;
          if( src.empty() ) break; // end of video stream

///remapping start here  index=2
 /// Create dst, map_x and map_y with the same size as src:
          
	  update_map(ind);
          remap( src, dst, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0) );
///remapping end here  index=2

          imshow(str, dst);
         if( waitKey(1) == 27 ) break; // stop capturing by pressing ESC 
    }
    // the camera will be closed automatically upon exit
    // cap.close();
    return 0;
}

/**
 * @function update_map
 * @brief Fill the map_x and map_y matrices with 4 types of mappings
 */
void update_map( int index )
{
//  ind = ind%4;

  for( int j = 0; j < src.rows; j++ )
    { for( int i = 0; i < src.cols; i++ )
     {
           switch( index )
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


