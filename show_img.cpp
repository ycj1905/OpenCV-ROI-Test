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
      Mat img;
      int rows;
      int cols;

       string filename;
       cout << "input file name to be read: ";
       cin >> filename;
      img = imread( filename, 1 );
      rows = img.rows;
      cols = img.cols;
      
      cout << "img_cols_x: "<<cols<<endl; 
      cout << "img_rows_y: "<<rows<<endl;    

//      Size dim = img.size();

      imshow( filename, img );
       waitKey(0);
    return 0;
}

