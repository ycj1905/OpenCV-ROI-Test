//
//mk_template.cpp
//
// ./mk_template <image> <x> <y> <width> <height>

#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;


int main(int argc, char** argv)
{
	IplImage* src;
	if( argc == 7 && ((src=cvLoadImage(argv[1],1)) != 0 ))
	{
		int x = atoi(argv[2]);
		int y = atoi(argv[3]);
		int width = atoi(argv[4]);
		int height = atoi(argv[5]);
		int add = atoi(argv[6]);
		cvSetImageROI(src, cvRect(x,y,width,height));
		cvAddS(src, cvScalar(add),src);
		cvNamedWindow( "template", 1 );
		cvShowImage( "template", src );
        CvSize dim = cvGetSize(src);
        cout <<" ROI dimensions:: height:" <<  dim.height<<" width:"<< dim.width<< endl;
	Mat mat_src = cvarrToMat(src);  //ipl to Mat
	imwrite( "template.jpg", mat_src );

		cvResetImageROI(src);
        dim = cvGetSize(src);
        cout <<" src dimensions:: height:" <<  dim.height<<" width:"<< dim.width<< endl;


		cvNamedWindow( argv[1], 1 );
		cvShowImage( argv[1], src );
		cvWaitKey();
	}
	return 0;
}

