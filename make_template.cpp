/**
 * @file Make Template.cpp
 * @brief Sample code to use the function MatchTemplate
 * @author OpenCV team
 */

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/// Global Variables
Mat img,img_w; Mat templ; Mat result; Mat result_norm;
const char* image_window = "Source Image";
const char* result_window = "Result window";

int match_method=1;
int max_Trackbar = 5;

/// Function Headers
void MatchingMethod( int, void* );
void save_xml();

/**
 * @function main
 */
int main( int, char** argv )
{

        string filename;

       cout << "input file name to be read: ";
       cin >> filename;

  /// Load image and template
  img = imread( filename, 1 );
imshow("img",img);
waitKey(0);

int x_col ;
int y_row ;
int rd_col;
int rd_row;

string filename_t;
cout << "template's filename : "; cin >> filename_t;
cout<<"* left-top's    x_col: "; cin>>x_col;
cout<<"* left-top's    y_row : "; cin>>y_row;
cout<<"* right-down's  x_col:"; cin>>rd_col;
cout<<"* right-down's  y_row : "; cin>>rd_row;

int width=rd_col-x_col;
int height=rd_row-y_row;

		
Rect ROI = Rect(x_col, y_row, width, height);
Mat image_roi = img(ROI);

imshow(filename_t,image_roi);
imwrite(filename_t,image_roi);


rectangle( img, Point( x_col ,y_row), Point( rd_col ,rd_row), Scalar::all(0), 2, 8, 0 );

imshow(filename,img);
waitKey(0);


return 0;
}

