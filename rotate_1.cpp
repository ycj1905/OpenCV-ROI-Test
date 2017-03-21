
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

void rotate(Mat& src, double angle, Mat& dst);

 int main( int argc, char** argv )
 {
     // Load the image
     Mat src = imread( "lena.jpg", 1 );
	double angle;
        cout << "input rotation angle: ";
        cin >> angle;
Size size(256,256);//the dst image size,e.g.100x100
	Mat dst, dst_r;
	rotate(src, angle, dst);
	resize(dst,dst_r,size);//resize image
	imshow("original",src);
	imshow("rotated",dst_r);
	waitKey(0);

     return 0;
}


/**
 * Rotate an image
 */
void rotate(Mat& src, double angle, Mat& dst)
{
    int len = max(src.cols, src.rows);
    Point2f pt(len/2., len/2.);
    Mat r = getRotationMatrix2D(pt, angle, 2.0); //set rotatiion matrix for warpAffine()
//    warpAffine(src, dst, r, Size(len, len));
       warpAffine(src, dst, r, src.size());

}


