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
    int array_dim= 20;
    int i;
    int n_o_image=1;
 
     Mat frame[array_dim];
 
//    read file

	stringstream ss;
	string str = ss.str();

//	string filename = "golf_head.ymal";

        string filename;
        cout << "input file name (add an extension)to be read: ";
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
//Size size(128,128);//the dst image size,e.g.100x100
Mat dst;//dst image
	for (i=0;i<n_o_image;i++)
	{
          ss <<"img"<< i<<"_jpg";
          str = ss.str();
	  ss.str("");
		
//	resize(frame[i],dst,size);//resize image
        imshow(str,frame[i]); 
	}
  
	waitKey(0);

    return 0;
}

