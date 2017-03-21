#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;



//int main(int argc, char** argv)
int main(void)
{
      Mat img;
      int rows;
      int cols;

       string filename="lena.jpg";
 
      img = imread( filename, 1 );


	Mat dst;

		int smooth_v; 
		cout<<"* Enter [1<-->30] odd number: "; cin>>smooth_v;
		//GaussianBlur( img, dst, Size( smooth_v, smooth_v ), 0, 0 );
                //bilateralFilter ( img, dst,smooth_v,smooth_v*2, smooth_v/2 );
                medianBlur ( img, dst, smooth_v );
 
       imshow(filename, img ); 
       imshow( "bluring", dst );
 
      waitKey(0);
       return 0;
}


