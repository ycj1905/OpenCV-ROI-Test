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

     int i,i1=1;

     Mat frame[array_dim];

     int n_o_image = atoi(argv[1]);
  
     for (i=0;i<n_o_image;i++)
     frame[i] = imread(argv[i+2]);
 



//    write file

	stringstream ss;
	string str = ss.str();

//string filename = "golf_head.ymal";

        string filename;
        cout << "input file name (add an extension) to be saved: ";
        cin >> filename;

	FileStorage fs(filename, FileStorage::WRITE);
 	
	fs << "n_o_image" << n_o_image;  //save an integer

 	for (i=0;i<n_o_image;i++)
	{
          ss <<"img"<< i<<"_jpg";
          str = ss.str();
	  ss.str("");
		
     		fs<<str<<frame[i];   
	}

       fs.release();

	FileStorage fsr(filename, FileStorage::READ);


 	for (i=0;i<n_o_image;i++)
	{
          ss <<"img"<< i<<"_jpg";
          str = ss.str();
	  ss.str("");
		
     		fsr[str]>>frame[i];   
	}

       fsr.release();
 

    return 0;
}

