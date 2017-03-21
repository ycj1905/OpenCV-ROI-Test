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

Mat img; 
Mat templ; 
Mat result;
int array_dim= 20;
Mat frame[20];
int n_o_image=1;

const char* image_window = "Source Image";
const char* result_window = "Result window";

int match_method=1;

/// Function Headers

void MatchingMethod( int, void* );

void ReadFile();




/**
 * @function main
 */
int main( int, char** argv )
{
        string filename;
        cout << "input file name to be matched: ";
        cin >> filename;
        img = imread( filename, 1 );  //read in input file to be matched 

 	ReadFile();  //read in template array

        int i=0;
/*
stringstream ss;
string str = ss.str();

Size size(128,128);//the dst image size,e.g.100x100
Mat dst;//dst image 
       

	for (i=0;i<n_o_image;i++)
	{
          ss <<"img"<< i<<"_jpg";
          str = ss.str();
	  ss.str("");
		
	resize(frame[i],dst,size);//resize image
        imshow(str,dst); 
	}
  
	waitKey(0);
*/
  /// Create windows
  namedWindow( image_window, WINDOW_AUTOSIZE );
  namedWindow( result_window, WINDOW_AUTOSIZE );



for (i=0;i<n_o_image;i++)
	{

           templ = frame[i];
           MatchingMethod( 0, 0 ); 
	    waitKey(0); 
	}

 

  return 0;
}


/**
 * @function MatchingMethod
 * @brief Trackbar callback
 */
void MatchingMethod( int, void* )
{
  /// Source image to display
  Mat img_display;
  img.copyTo( img_display );

  /// Create the result matrix
  int result_cols =  img.cols - templ.cols + 1;
  int result_rows = img.rows - templ.rows + 1;

  result.create( result_rows, result_cols, CV_32FC1 );

  /// Do the Matching and Normalize
  matchTemplate( img, templ, result, match_method );//*****************************//
  normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );

  /// Localizing the best match with minMaxLoc
  double minVal; double maxVal; Point minLoc; Point maxLoc;
  Point matchLoc;

  minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );


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

  return;
}

/**
 * @function ReadFile
 * 
 */

void ReadFile()
{
    int array_dim= 20;
    int i;

 
//     Mat frame[array_dim];
 
//    read file

	stringstream ss;
	string str = ss.str();

//	string filename = "golf_head.ymal";

        string filename;
        cout << "input template file name (add an extension): ";
        cin >> filename;

	FileStorage fsr(filename, FileStorage::READ);

        fsr["n_o_image"]>>n_o_image;  //read an integer
	
 	for (i=0;i<n_o_image;i++)
	{
          ss <<"img"<< i<<"_jpg";
          str = ss.str();
	  ss.str("");
		
     		fsr[str]>>frame[i];   
	}

       fsr.release();
/*
Size size(128,128);//the dst image size,e.g.100x100
Mat dst;//dst image
	for (i=0;i<n_o_image;i++)
	{
          ss <<"img"<< i<<"_jpg";
          str = ss.str();
	  ss.str("");
		
	resize(frame[i],dst,size);//resize image
        imshow(str,dst); 
	}
  
	waitKey(0);
*/
    return;
}




