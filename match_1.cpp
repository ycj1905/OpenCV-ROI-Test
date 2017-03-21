/**
 * @file MatchTemplate_Demo.cpp
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
Mat img; Mat templ; Mat result; Mat result_norm;
const char* image_window = "Source Image";
const char* result_window = "Result window";

int match_method;
int max_Trackbar = 5;

/// Function Headers
void MatchingMethod( int, void* );
void save_xml();

/**
 * @function main
 */
int main( int, char** argv )
{
  /// Load image and template
  img = imread( argv[1], 1 );
  templ = imread( argv[2], 1 );

int x ;
int y ;
int width;
int height;
int add=200;
cout<<"* Enter ROI's   x : "; cin>>x;
cout<<"* Enter ROI's   y : "; cin>>y;
cout<<"* Enter ROI's   width : "; cin>>width;
cout<<"* Enter ROI's   height : "; cin>>height;

/*
Color image: Mat3b

Gray scale image: Mat1b

Matrix of floating point values: Mat1f

Matrix of double precision values: Mat1d

Matrix of integer values: Mat1i
*/
		
Rect ROI = Rect(x, y, width, height);
Mat image_roi = img(ROI);


  /// Create windows
  namedWindow( image_window, WINDOW_AUTOSIZE );
  namedWindow( result_window, WINDOW_AUTOSIZE );
//  namedWindow( result_norm_window, WINDOW_AUTOSIZE );

  /// Create Trackbar
  const char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
  createTrackbar( trackbar_label, image_window, &match_method, max_Trackbar, MatchingMethod );

  MatchingMethod( 0, 0 );

  waitKey(0);
  return 0;
}

/**
 * @function MatchingMethod
 * @brief Trackbar callback
 */
void MatchingMethod( int, void* )
{
  int img_row;
  int img_col;
  int templ_row;
  int templ_col;

  /// Source image to display
  Mat img_display;
  img.copyTo( img_display );

  /// Create the result matrix
  int result_cols =  img.cols - templ.cols + 1;
  int result_rows = img.rows - templ.rows + 1;

  result.create( result_rows, result_cols, CV_32FC1 );
  result_norm.create( result_rows, result_cols, CV_32FC1 );

  /// Do the Matching and Normalize
  matchTemplate( img, templ, result, match_method );
  normalize( result, result_norm, 0, 1, NORM_MINMAX, -1, Mat() );

  /// Localizing the best match with minMaxLoc
  double minVal; double maxVal; Point minLoc; Point maxLoc;
  Point matchLoc;

  minMaxLoc( result_norm, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
        cout << "img_row:  "<<img.rows<<endl;
        cout << "img_col:  "<<img.cols<<endl;
	cout << "templ_row:  "<<templ.rows<<endl;
        cout << "templ_col:  "<<templ.cols<<endl;
	cout << "minVal:  "<<minVal<<endl;
	cout << "maxVal:  "<<maxVal<<endl;
	cout << "minLoc:  "<<minLoc<<endl;
	cout << "maxLoc:  "<<maxLoc<<endl;

  /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
  if( match_method  == TM_SQDIFF || match_method == TM_SQDIFF_NORMED )
    { matchLoc = minLoc; }
  else
    { matchLoc = maxLoc; }

  /// Show me what you got
  rectangle( img_display, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );
  rectangle( result, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );

  imshow( image_window, img_display );
  imshow( result_window, result );
  imshow( "result_norm_window", result_norm );
  save_xml();

  return;
}

/**
 * Save imgage to .xml
 * 
 *
*/
void save_xml()
{
//    write file

	stringstream ss;
	string str = ss.str();

//string filename = "golf_head.ymal";

//        string filename;
//        cout << "input file name (add an extension) to be saved: ";
//        cin >> filename;
	string filename="t1.xml";

	FileStorage fs(filename, FileStorage::WRITE);
/* 	
	fs << "n_o_image" << n_o_image;  //save an integer

	for (i=0;i<n_o_image;i++)
	{
          ss <<"img"<< i<<"_jpg";
          str = ss.str();
	  ss.str("");
*/		
   		fs<<"result"<<result; 
                fs<<"result_norm"<<result_norm;  
	

       fs.release();
/*
	FileStorage fsr(filename, FileStorage::READ);


 	for (i=0;i<n_o_image;i++)
	{
          ss <<"img"<< i<<"_jpg";
          str = ss.str();
	  ss.str("");
		
     		fsr[str]>>frame[i];   
	}

       fsr.release();
 */

    return;
}

