#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

/// Global Variables for save to xml

Mat frame[20];
int n_o_image=1;
string filename;

void SaveFile();

/// Global variables for remapping
Mat src, dst;
Mat map_x, map_y;

void update_map( int index );


int main(int argc, char** argv)
{
 
        cout << "number of images [1<-->19]: ";
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


int i=0;
	for(i=0;i<=n_o_image;i++)
    {
          
          cap >> frame[i];
//      waitKey(1000);
     }


//
//remapping  index=2 means x <--> -x
//
int ind=2;   //remapping  index=2 means x <--> -x
          

	for(i=0;i<=n_o_image;i++)
    {
          //src=frame[i] ;
          frame[i].copyTo(src);
          dst.create( src.size(), src.type() );
          map_x.create( src.size(), CV_32FC1 );
          map_y.create( src.size(), CV_32FC1 );

          update_map(ind);
          remap( src, dst, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0) );
 	  //frame[i]=dst;
          dst.copyTo(frame[i]);

     }


//
// show frame[i]
//
Size size(256,256);//the dst image size,e.g.100x100

          str = ss.str();
	  ss.str("");

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

