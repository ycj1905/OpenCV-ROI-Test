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
Mat img,img_w; Mat templ; Mat result; Mat result_norm;
const char* image_window = "Source Image";
const char* result_window = "Result window";

int n_o_method;
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
 

IplImage* ipl1=cvLoadImage(argv[1],1);

  /// Load image and template
  img = imread( argv[1], 1 );
//  img.copyTo( img_w );
  templ = imread( argv[2], 1 );

int img_rows,img_cols,templ_rows,templ_cols;

      img_rows = img.rows;
      img_cols = img.cols;
      cout << "img_cols_x: "<<img_cols<<endl; 
      cout << "img_rows_y: "<<img_rows<<endl;
      
      templ_rows = templ.rows;
      templ_cols = templ.cols;
      cout << "templ_cols_x: "<<templ_cols<<endl;
      cout << "templ_rows_y: "<<templ_rows<<endl;

//      imshow( argv[1],img);
//      imshow( argv[2],templ);
 //     waitKey(0);    

int x_col ;
int y_row ;
int rd_col;
int rd_row;
/*
cout<<" number of method  : "; cin>>n_o_method;

 cout << "Check number of method: "<<n_o_method<<endl;
 cout << "Check match_mehod:      "<<match_method<<endl;  
*/

cout<<" left-top's    x_col: "; cin>>x_col;
cout<<" left-top's    y_row: "; cin>>y_row;
cout<<" right-down's  x_col: "; cin>>rd_col;
cout<<" right-down's  y_row: "; cin>>rd_row;

int width=rd_col-x_col;
int height=rd_row-y_row;

/*
Color image: Mat3b

Gray scale image: Mat1b

Matrix of floating point values: Mat1f

Matrix of double precision values: Mat1d

Matrix of integer values: Mat1i
*/
		
Rect ROI = Rect(x_col, y_row, width, height);
Mat image_roi = img(ROI);
img=image_roi;



int add=200;
cvSetImageROI(ipl1, cvRect(x_col,y_row,width,height));  //set ROI for ipl1

//img = cvarrToMat(ipl1);  //change img into ROI

cvAddS(ipl1, cvScalar(add),ipl1);
cvResetImageROI(ipl1);           //reset ROI for ipl1
cvNamedWindow( "img+roi", 1 );   //widow for ipl image
cvShowImage( "img+roi", ipl1 );  //cvShowImage for ipl image
//waitKey(0);

//cout<<"* number of method  : "; cin>>n_o_method;   

  /// Create windows
  namedWindow( image_window, WINDOW_AUTOSIZE );
  namedWindow( result_window, WINDOW_AUTOSIZE );
//  namedWindow( result_norm_window, WINDOW_AUTOSIZE );

  /// Create Trackbar
  const char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF_N \n 2: TM CCORR \n 3: TM CCORR_N \n 4: TM COEFF \n 5: TM COEFF_N";
//  createTrackbar( trackbar_label, image_window, &match_method, max_Trackbar, MatchingMethod );

  MatchingMethod( 0, 0 );

//  waitKey(0);
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
  Mat img_display;                                      //************//
  img.copyTo( img_display );

  /// Create the result matrix
  int result_cols =  img.cols - templ.cols + 1;
  int result_rows = img.rows - templ.rows + 1;

  result.create( result_rows, result_cols, CV_32FC1 );
  result_norm.create( result_rows, result_cols, CV_32FC1 );

  /// Do the Matching and Normalize

  double minVal; double maxVal; Point minLoc; Point maxLoc;
  Point matchLoc;

Point P1_matchLoc;
Point P3_matchLoc;
 int i;     
for( i = 1; i < 4; i=i+2 )
{
  match_method=i;

  matchTemplate( img, templ, result, match_method );
  normalize( result, result_norm, 0, 1, NORM_MINMAX, -1, Mat() );

  /// Localizing the best match with minMaxLoc

  minMaxLoc( result_norm, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
/*
	cout << "minVal:  "<<minVal<<endl;
	cout << "maxVal:  "<<maxVal<<endl;
	cout << "minLoc:  "<<minLoc<<endl;
	cout << "maxLoc:  "<<maxLoc<<endl;
*/
//  jason


if( match_method  == TM_SQDIFF || match_method == TM_SQDIFF_NORMED )
   { 
     
    matchLoc = minLoc;
  
      cout << "matchLoc:    "<<minLoc<<endl;
      
      //cout << "matchLoc_x:  "<<minLoc.x<<endl;
      //cout << "matchLoc_y:  "<<minLoc.y<<endl;
   }
  else
    {  
     matchLoc = maxLoc;
     
     cout << "matchLoc:    "<<maxLoc<<endl;
     
     //cout << "matchLoc_x:  "<<minLoc.x<<endl;
     //cout << "matchLoc_y:  "<<minLoc.y<<endl;
    }

i=i;
int j=0;

//if (i=1) j=1;
//}
//else
//{
//j=3;
//}

//      if (i=1)
//        { 
//          P1_matchLoc=matchLoc;
//	  cout << "P1_matchLoc:   "<<P1_matchLoc<<endl;
//        }
//      else
//        {
 //         P3_matchLoc=matchLoc;
//	  cout << "P3_matchLoc:   "<<P3_matchLoc<<endl;
//	}

}// for

// jason


  /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better

//cout << "TM_SQDIFF: "<<TM_SQDIFF<<endl; 
//if( match_method  == TM_SQDIFF || match_method == TM_SQDIFF_NORMED ) 
//    { matchLoc = minLoc; }
//  else
//    { matchLoc = maxLoc; }




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

