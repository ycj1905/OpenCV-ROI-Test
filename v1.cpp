#include "cameralibrary.h"
#include "supportcode.h"  

#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;
using namespace CameraLibrary;

int main(int argc, char** argv){ 

    CameraManager::X().WaitForInitialization();
    Camera *camera = CameraManager::X().GetCamera();
    camera->SetVideoType(Core::GrayscaleMode);  

    int cameraWidth  = camera->Width();
    int cameraHeight = camera->Height();

    Mat imageCV(cv::Size(cameraWidth, cameraHeight), CV_8UC1);
    const int BITSPERPIXEL = 8;

    Frame *frame;

    namedWindow("frame", WINDOW_AUTOSIZE);

    camera->Start();

    while(1){

        //maximum of 2 micro seconds:
        frame = camera->GetLatestFrame();   

        //maximum of 60 micro seconds:
        if(frame){                      
            frame->Rasterize(cameraWidth, cameraHeight, imageCV.step, BITSPERPIXEL, imageCV.data);
        }

        //maximum of 0.75 ms
        imshow("frame", imageCV); 

        // **PROBLEM HERE**  12 ms on average
        waitKey(1);                     

        //maximum of 2 micro seconds:
        frame->Release();                   

    }

    camera->Release();
    CameraManager::X().Shutdown();
    return 0;
}

