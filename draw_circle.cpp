/*

 Drawing a Circle
void circle(Mat& img, Point center, int radius, const Scalar& color, int thickness=1, int lineType=8, int shift=0)
Parameters:

    img – Image where the circle is drawn.
    center – Center of the circle.
    radius – Radius of the circle.
    color – Circle color.
    thickness – Thickness of the circle outline, if positive. Negative thickness means that a filled circle is to be drawn.
    lineType – Type of the line:
    8 (or omitted) - 8-connected line.
    4 - 4-connected line.
    CV_AA - antialiased line.
    shift – Number of fractional bits in the coordinates of the center and in the radius value.

The function circle draws a simple or filled circle with a given center and radius.

*/


#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

int main( )
{    
  // Create black empty images
  Mat image = Mat::zeros( 400, 400, CV_8UC3 );
   
  // Draw a circle 
  circle( image, Point( 200, 200 ), 32.0, Scalar( 0, 0, 255 ), 1, 8 );
  imshow("Image",image);
 
  waitKey( 0 );
  return(0);
}

