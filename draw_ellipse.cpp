/*

 Drawing an Ellipse
void ellipse(Mat& img, Point center, Size axes, double angle, double startAngle, double endAngle, const Scalar& color, int thickness=1, int lineType=8, int shift=0)
Parameters:

    img – Image.
    center – Center of the ellipse.
    axes – Length of the ellipse axes.
    angle – Ellipse rotation angle in degrees.
    startAngle – Starting angle of the elliptic arc in degrees.
    endAngle – Ending angle of the elliptic arc in degrees.
    box – Alternative ellipse representation via RotatedRect or CvBox2D. This means that the function draws an ellipse inscribed in the rotated rectangle.
    color – Ellipse color.
    thickness – Thickness of the ellipse arc outline, if positive. Otherwise, this indicates that a filled ellipse sector is to be drawn.
     lineType – Type of the line:

    8 (or omitted) - 8-connected line.
    4 - 4-connected line.
    CV_AA - antialiased line.


    shift – Number of fractional bits in the coordinates of the center and values of axes.

The functions ellipse with less parameters draw an ellipse outline, a filled ellipse, an elliptic arc, or a filled ellipse sector. A piecewise-linear curve is used to approximate the elliptic arc boundary.

If you use the first variant of the function and want to draw the whole ellipse, not an arc, pass startAngle=0 and endAngle=360.
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
   
  // Draw a ellipse 
  ellipse( image, Point( 200, 200 ), Size( 100.0, 160.0 ), 45, 0, 360, Scalar( 255, 0, 0 ), 1, 8 );
  ellipse( image, Point( 200, 200 ), Size( 100.0, 160.0 ), 135, 0, 360, Scalar( 255, 0, 0 ), 10, 8 );
  ellipse( image, Point( 200, 200 ), Size( 150.0, 50.0 ), 135, 0, 360, Scalar( 0, 255, 0 ), 1, 8 );
  imshow("Image",image);
 
  waitKey( 0 );
  return(0);
}


