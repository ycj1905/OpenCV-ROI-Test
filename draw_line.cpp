/*

 Drawing a line
void line(Mat& img, Point pt1, Point pt2, const Scalar& color, int thickness=1, int lineType=8, int shift=0)
 Parameters:

    img – Image.
    pt1 – First point of the line segment.
    pt2 – Second point of the line segment.
    color – Line color.
    thickness – Line thickness.(Thickness of the circle outline, if positive. Negative thickness means that a filled circle is to be drawn.)
    lineType – Type of the line:
        8 (or omitted) - 8-connected line.
        4 - 4-connected line.
        CV_AA - antialiased line.
    shift – Number of fractional bits in the point coordinates.
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
   
  // Draw a line 
  line( image, Point( 15, 20 ), Point( 70, 50), Scalar( 110, 220, 0 ),  2, 8 );
  imshow("Image",image);
 
  waitKey( 0 );
  return(0);
}

