#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;
int main(int argc, char** argv)
{
    int delay = 1;
    int i1 = 1;
if( argc == 2) 
	{
		delay = atoi(argv[1]);
        } 
    VideoCapture cap;
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
   
          Mat frame1,frame2;
          cap >> frame1;
double t = (double)getTickCount();
//     waitKey(2000);
int i,j;
for(i=1;i<delay;i++)
{
    for(j=1;j<30000;j++)i1=10009.8/99.2;
}
	cap >> frame2;
    
t = ((double)getTickCount() - t)/getTickFrequency();
cout << "Times passed in seconds: " << t <<"    *************"<< endl;

	imwrite( "cap_1.jpg", frame1 );
        imwrite( "cap_2.jpg", frame2 );

          imshow("capture_1", frame1);
	 imshow("capture_2", frame2);
           waitKey(0);
    
    // the camera will be closed automatically upon exit
    // cap.close();
    return 0;
}

