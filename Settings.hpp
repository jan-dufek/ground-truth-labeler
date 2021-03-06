#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

class Settings {
public:
    
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    // Input
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////
    // Video streams
    ////////////////////////////////////////////////////////////////////////////

    // Logitech USB Camera
    ////////////////////////////////////////////////////////////////////////////////

    // Camera index (sometimes the external USB camera is on 0 and sometimes on 1)
    // The index of the camera have to be checked manually
//    int video_capture_source = 0;

    // Calibration Data
    Mat camera_intrinsic_matrix = (Mat_<double>(3, 3) <<
            1.4006590516106746e+03, 0., 7.9950000000000000e+02,
            0., 1.4006590516106746e+03, 5.9950000000000000e+02,
            0., 0., 1.);

    Mat camera_distortion_vector = (Mat_<double>(1, 5) <<
            5.4296267484343998e-02, -5.9413030935709088e-01, 0., 0., 1.9565543630464968e+00);

    // Inogeni
    ////////////////////////////////////////////////////////////////////////////////

    // If USB device is Inogeni, uncomment this to set correct FPS
    //#define INOGENI

    // Screen mirroring application from DJI tablet
    ////////////////////////////////////////////////////////////////////////////////

    //string video_capture_source = "rtsp://10.201.147.238:5000/screen";
    //string video_capture_source = "http://195.67.26.73/mjpg/video.mjpg";

    // HDMI stream from Teradek VidiU from Fotokite or 3DR Solo
    ////////////////////////////////////////////////////////////////////////////////

    //string video_capture_source = "rtmp://127.0.0.1/EMILY_Tracker/fotokite";

    ////////////////////////////////////////////////////////////////////////////////
    // Video files
    ////////////////////////////////////////////////////////////////////////////
  
    // Trial 1: Lake Bryan AI Robotic class field test 2016 03 28
    string video_capture_source = "input/2016_03_28_lake_bryan.mp4"; // Source video file to annotate
    int time_for_annotation = 1000; // Time for annotation specifies how many milliseconds to wait before loading the next frame. This has to be hight enough so that the annotator has enough time to move the cursor to the position to be annotated before the next frame is loaded.

    // Trial 2: Fort Bend floods 2016 04 23
//    string video_capture_source = "input/2016_04_23_fort_bend.mp4";
//    int time_for_annotation = 250;
    
    // Trial 3: Lake Bryan AI Robotics class final 2016 05 10
//    string video_capture_source = "input/2016_05_10_lake_bryan.mov";
//    int time_for_annotation = 250;

    // Trial 4: Lab 2016 07 05
//    string video_capture_source = "input/2016_07_05_lab.mp4";
//    int time_for_annotation = 500;

    ////////////////////////////////////////////////////////////////////////////////
    // GUI Parameters
    ////////////////////////////////////////////////////////////////////////////////

    // Main window name
    const string MAIN_WINDOW = "EMILY Tracker";

    // Object position crosshairs color
    const Scalar LOCATION_COLOR = Scalar(0, 255, 0);

    // Object position crosshairs thickness
    const int LOCATION_THICKNESS = 1;

    ////////////////////////////////////////////////////////////////////////////////
    // Algorithm Static Parameters
    ////////////////////////////////////////////////////////////////////////////////

    // Input will be resized to this number of lines to speed up the processing
    //const int PROCESSING_VIDEO_HEIGHT_LIMIT = 640; // MOD webcam resolution
    // Higher resolution will be better if EMILY is in the distance
    //const int PROCESSING_VIDEO_HEIGHT_LIMIT = 1200;
    const int PROCESSING_VIDEO_HEIGHT_LIMIT = 2160;

};

#endif /* SETTINGS_HPP */