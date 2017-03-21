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

/// Function Headers
void MatchingMethod( int match_method, Point& lt_s, Mat& img ,Mat& templ, Point& matchLoc);

/**
 * @function main
 */
int main( int, char** argv )
{
        Point matchLoc;
	Mat img_m;
        Mat templ_m; 
	string filename, filename_t;
        cout << "source file name to be matched: ";cin >> filename;
        //cout<<endl;
        cout << "template file name: ";cin >> filename_t;

     /// Load image and template
     img_m = imread( filename, 1 );
     templ_m = imread( filename_t, 1 );
//      int rows = img.rows;
//      int cols = img.cols;
      
      cout << "img_cols_x: "<<img_m.cols<<endl; 
      cout << "img_rows_y: "<<img_m.rows<<endl;    

//      Size dim = img.size();

       imshow( filename, img_m );
       waitKey(0);

int x_col ;
int y_row ;
int rd_col;
int rd_row;

cout << "Set ROI reectangle "<<endl;
cout<<"* left-top's    x_col: "; cin>>x_col;
cout<<"* left-top's    y_row : "; cin>>y_row;
cout<<"* right-down's  x_col:"; cin>>rd_col;
cout<<"* right-down's  y_row : "; cin>>rd_row;

Point lt_roi;
      lt_roi.x=x_col;
      lt_roi.y=y_row;
int width=rd_col-x_col;
int height=rd_row-y_row;
		
Rect ROI = Rect(x_col, y_row, width, height);
Mat image_roi = img_m(ROI);

rectangle( img_m, Point( x_col ,y_row), Point( rd_col ,rd_row), Scalar::all(0), 2, 8, 0 );

//imshow(filename,img_m);
//imshow("image_roi",image_roi);
//waitKey(0);


  Point P1_matchLoc;
  Point P3_matchLoc;
  Point P4_matchLoc;
  Point P5_matchLoc;
  Point lt, rd;
  int rect_dim=20;
//  Point matchLoc;

  MatchingMethod(1,lt_roi,image_roi, templ_m, matchLoc);
  P1_matchLoc=matchLoc+lt_roi;
  cout << "P1_matchLoc:   "<<P1_matchLoc<<endl;
   lt=P1_matchLoc;
   rd.x=lt.x+rect_dim;
   rd.y=lt.y+rect_dim;
   rectangle( img_m, lt, rd, Scalar::all(0), 2, 8, 0 );

  MatchingMethod(3,lt_roi,image_roi, templ_m, matchLoc);
  P3_matchLoc=matchLoc+lt_roi;
  cout << "P3_matchLoc:   "<<P3_matchLoc<<endl;
   lt=P3_matchLoc;
   rd.x=lt.x+rect_dim;
   rd.y=lt.y+rect_dim;
   rectangle( img_m, lt, rd, Scalar::all(0), 2, 8, 0 );

  MatchingMethod(4,lt_roi,image_roi, templ_m, matchLoc);
  P4_matchLoc=matchLoc+lt_roi;
  cout << "P4_matchLoc:   "<<P4_matchLoc<<endl;
  lt=P4_matchLoc;
   rd.x=lt.x+rect_dim;
   rd.y=lt.y+rect_dim;
   rectangle( img_m, lt, rd, Scalar::all(0), 2, 8, 0 );   

  MatchingMethod(5,lt_roi,image_roi, templ_m, matchLoc);
  P5_matchLoc=matchLoc+lt_roi;
  cout << "P5_matchLoc:   "<<P5_matchLoc<<endl;
  lt=P5_matchLoc;
   rd.x=lt.x+rect_dim;
   rd.y=lt.y+rect_dim;
   rectangle( img_m, lt, rd, Scalar::all(0), 2, 8, 0 ); 


double threshold=1;
if (norm( P1_matchLoc- P3_matchLoc)<threshold)
    {//1=3
        //cout<<"bingo--1=3"<<endl;  
        if (norm( P1_matchLoc- P4_matchLoc)<threshold)
        {//1=3=4
               // cout<<"bingo--1=3=4"<<endl; 
               if (norm( P1_matchLoc- P5_matchLoc)<threshold)
               {//1=3=4=5
                   cout<<"bingo--1=3=4=5"<<endl; 

                }//1=3=4=5
                else
                {//1=3=4=!5
                   cout<<"bingo--1=3=4=!5"<<endl;
                }//1=3=4=!5
         }//1=3=4
         else
         {//1=3!=4  
               if (norm( P1_matchLoc- P5_matchLoc)<threshold)
               {//1=3!=4=5
                   cout<<"bingo--1=3!=4=5"<<endl; 

                }//1=3!=4=5
                else
                {//1=3!=4!=5
                   cout<<"bingo--1=3!=4!=5"<<endl;
                }//1=3!=4!=5
          }//1=3!=4 

   }//1=3

else
   {//1!=3

           if (norm( P1_matchLoc- P4_matchLoc)<threshold)
              {//1!=3=4
                //cout<<"bingo--1!=3=4"<<endl;  
                if (norm( P1_matchLoc- P5_matchLoc)<threshold)
                 {//1!=3=4=5
                   cout<<"bingo--1!=3=4=5"<<endl; 

                  }//1!=3=4=5
                else
                 {//1!=3=4!=5
                   cout<<"bingo--1!=3=4!=5"<<endl;
                 }//1!=3=4!=5
               }//1!=3=4
            else
              {//1!=3!=4
               if (norm( P1_matchLoc- P5_matchLoc)<threshold)
               {//1!=3!=4=5
                   cout<<"bingo--1!=3!=4=5"<<endl; 

                }//1!=3!=4=5
                else
                {//1!=3!=4!=5
                   cout<<" ---not bingo---1!=3!=4!=5"<<endl;
                }//1!=3!=4!=5
              }//1!=3!=4            
 
     }//1!=3


//   imshow(filename,img_m);
//   waitKey(0);
 
  return 0;
}

/**
 * @function MatchingMethod
 * @brief Trackbar callback
 */
void MatchingMethod( int match_method, Point& lt_s, Mat& img ,Mat& templ, Point& matchLoc)
{
  int img_row;
  int img_col;
  int templ_row;
  int templ_col;
  Mat result; Mat result_norm;

  /// Source image to display
      Mat img_display; 
//      Mat img_display=img;   //no good here, only set image header equivalent
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
  minMaxLoc( result_norm, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );

  /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
  if( match_method  == TM_SQDIFF || match_method == TM_SQDIFF_NORMED )
    { matchLoc = minLoc; }
  else
    { matchLoc = maxLoc; }

  return;
}


