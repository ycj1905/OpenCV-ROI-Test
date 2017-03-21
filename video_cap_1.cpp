#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

/// Global Variables for save to xml

Mat frame[50];
int n_o_image=12;
string filename;

void SaveFile();

/// Global variables for remapping
Mat src, dst;
Mat map_x, map_y;

void update_map( int index );


int main(int argc, char** argv)
{
 
        cout << "number of images [1<-->49]: ";
        cin >> n_o_image;
        cout << "filename to save images(e.g., xxx.xml): ";
        cin >> filename;

    VideoCapture cap;     //set VideoCapture
    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.

        stringstream ss;
	string str = ss.str();
	int camera_n;
        cout << "input camera number: ";
        cin >> camera_n;
        ss <<"camera number: "<< camera_n;
        str = ss.str();
 	if(cap.open(camera_n))
            cout <<str<< "  is open good"<<endl;
        else
            cout <<str<< "  is not open good"<<endl;
double t = (double)getTickCount();
double i1=0;

Mat frame2;
int i=0;

int delay=100;

cap >> frame[0];
waitKey(delay);
cap >> frame[1];
waitKey(delay);
cap >> frame[2];
waitKey(delay);
cap >> frame[3];
waitKey(delay);
cap >> frame[4];
waitKey(delay);
cap >> frame[5];
waitKey(delay);
cap >> frame[6];
waitKey(delay);
cap >> frame[7];
waitKey(delay);
cap >> frame[8];
waitKey(delay);
cap >> frame[9];
waitKey(delay);
cap >> frame[10];
waitKey(delay);
cap >> frame[11];
cap >> frame[12];
waitKey(delay);
cap >> frame[13];
waitKey(delay);
cap >> frame[4];
waitKey(delay);
cap >> frame[15];
waitKey(delay);
cap >> frame[16];
waitKey(delay);
cap >> frame[17];
waitKey(delay);
cap >> frame[18];
waitKey(delay);
cap >> frame[19];
waitKey(delay);
cap >> frame[20];





/*
	for(i=0;i<=n_o_image;i++)
    {
          
          cap >> frame[i];
//delay loop******* start  *****************************************************


//     waitKey(2000);

for(int i=1;i<delay;i++)
{
    for(int j=1;j<30000;j++)i1=10009.8/99.2;
}
	cap >> frame2;
    
t = ((double)getTickCount() - t)/getTickFrequency();
cout << "Times passed in seconds: " << t <<"    *************"<< endl;

//delay loop *****   End    ************************************************


     }

*/
//
//remapping  index=2 means x <--> -x
//
int ind=2;   //remapping  index=2 means x <--> -x
          src=frame[0] ;
          dst.create( src.size(), src.type() );
          map_x.create( src.size(), CV_32FC1 );
          map_y.create( src.size(), CV_32FC1 );

	for(i=0;i<=n_o_image;i++)
    {
         update_map(ind);
          src=frame[i];	
          remap( src, dst, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0) );
 	  frame[i]=dst;
     }

//
// show frame[i]
//
Size size(128,128);//the dst image size,e.g.100x100
Mat dst;//dst image

	for(i=0;i<=n_o_image;i++)
    {
          ss <<"img"<< i<<".jpg";
          str = ss.str();
	  ss.str("");

          resize(frame[i],dst,size);//resize image
	  imshow(str, dst);
	  imwrite(str, frame[i]);
     }
         
           waitKey(0);
//
//save file
//
	   SaveFile();
    
    // the camera will be closed automatically upon exit
    // cap.close();
    return 0;
}
/**
 * @function SaveFile
 * 
 */

void SaveFile()

{
 //    write file

	stringstream ss;
	string str = ss.str();

	FileStorage fs(filename, FileStorage::WRITE);
 	
	fs << "n_o_image" << n_o_image;  //save an integer

	int i;
 	for (i=0;i<=n_o_image;i++)
	{
          ss <<"img"<< i<<"_jpg";
          str = ss.str();
	  ss.str("");
		
     		fs<<str<<frame[i];   
	}

       fs.release();

    return;
}

/**
 * @function update_map
 * @brief Fill the map_x and map_y matrices with 4 types of mappings
 */
void update_map( int index )
{
//  ind = ind%4;

  for( int j = 0; j < src.rows; j++ )
    { for( int i = 0; i < src.cols; i++ )
     {
           switch( index )
         {
         case 0:
           if( i > src.cols*0.25 && i < src.cols*0.75 && j > src.rows*0.25 && j < src.rows*0.75 )
                 {
               map_x.at<float>(j,i) = 2*( i - src.cols*0.25f ) + 0.5f ;
               map_y.at<float>(j,i) = 2*( j - src.rows*0.25f ) + 0.5f ;
              }
           else
         { map_x.at<float>(j,i) = 0 ;
               map_y.at<float>(j,i) = 0 ;
                 }
                   break;
         case 1:
               map_x.at<float>(j,i) = (float)i ;
               map_y.at<float>(j,i) = (float)(src.rows - j) ;
           break;
             case 2:
               map_x.at<float>(j,i) = (float)(src.cols - i) ;
               map_y.at<float>(j,i) = (float)j ;
           break;
             case 3:
               map_x.at<float>(j,i) = (float)(src.cols - i) ;
               map_y.at<float>(j,i) = (float)(src.rows - j) ;
           break;
             } // end of switch
     }
    }
//  ind++;
}

