#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void rotate(Mat& src, double angle, Mat& dst);

int main(int argc, char** argv)
{
      Mat img;
      int rows;
      int cols;

       string filename;
       cout << "input file name to be read: ";
       cin >> filename;
 
      img = imread( filename, 1 );
      rows = img.rows;
      cols = img.cols;
      cout << "img_rows: "<<rows<<endl;
      cout << "img_cols: "<<cols<<endl;
      cout << "1. press right key of the mouse inside the picture, then"<<endl;
      cout << "2. press [space bar] in the keyboard to proceed next:"<<endl;
      imshow( filename, img );
waitKey(0);
	cout << endl;
	cout << "1 Rotation "<<endl; 
	cout << "2 smoothing (bluring)"<<endl;
	cout << "3 Increase contrast "<<endl;
	cout << "4 Change sizee "<<endl;
	cout << endl;
	cout << "press right key of the mouse inside the terminal"<<endl;
        cout << "then, enter the number choosen: ";
	int index;
	cin >> index;

	Mat dst;

         switch( index )
         {
           case 1:        // "1 Rotation "
		double angle;
		cout << "input rotation angle: ";
		cin >> angle;
		rotate(img, angle, dst);
                 break;
           case 2:        // "2 Smoothing"

		int smooth_v; 

		cout<<"---------------------- "<<endl;
		cout<<"* Enter [1<-->30], odd number: "; cin>>smooth_v;

		//GaussianBlur( img, dst, Size( smooth_v, smooth_v ), 0, 0 );
                //bilateralFilter ( img, dst,smooth_v,smooth_v*2, smooth_v/2 );
                medianBlur ( img, dst, smooth_v );
                  
                 break;
           case 3:        //"3 Increase contrast "
dst = Mat::zeros( img.size(), img.type() );

		double alpha; /**< Simple contrast control */
		int beta;  /**< Simple brightness control */

		cout<<"---------------------- "<<endl;
		cout<<"dst(i,j) = alpha * 3(i,j) + beta"<<endl;
		cout<<"---------------------- "<<endl;
		cout<<"* Enter the alpha value [1.0<-->3.0]: "; cin>>alpha;
		cout<<"* Enter the beta value [-100<-->100]: "; cin>>beta;

		 /// Do the operation new_image(i,j) = alpha*image(i,j) + beta
		 for( int y = 0; y < img.rows; y++ )
		    { for( int x = 0; x < img.cols; x++ )
			 { for( int c = 0; c < 3; c++ )
			      {
		      dst.at<Vec3b>(y,x)[c] =
			 saturate_cast<uchar>( alpha*( img.at<Vec3b>(y,x)[c] ) + beta);
			     }
			 }
		    }

                 
                 break;
           case 4:        //"4 Change sizee "
	       cout << "Enter number of rows: ";
	       cin >> rows;
	       cout << "Enter number of cols: ";
	       cin >> cols;

               Size size(rows,cols);//the dst image size,e.g.100x100
	       resize(img,dst,size);//resize image
                break;
         } // end of switch


       imshow( "dst", dst );

waitKey(0);

       cout << "input the proccessed file name : ";
       cin >> filename;
 
       imwrite( filename, dst );
//waitKey(0); 

       
       return 0;
}


/**
 * Rotate an image
 */
void rotate(Mat& src, double angle, Mat& dst)
{
    int len = max(src.cols, src.rows);
    Point2f pt(len/2., len/2.);
    Mat r = getRotationMatrix2D(pt, angle, 1); //set rotatiion matrix for warpAffine()
//    warpAffine(src, dst, r, Size(len, len));
       warpAffine(src, dst, r, src.size());

}



