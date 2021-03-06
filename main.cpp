/** 
 * @file    main.cpp
 * @author  Jan Dufek
 * @date    03/05/2018
 * @version 1.0
 *  
 * This application can be used to label the ground truth in a video. The ground
 * truth can be labeled using a mouse cursor. The position of the cursor in each
 * video frame is recorded. The data can be used later for training or evaluation.
 *
 */

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <time.h>
#include <iostream>
#include "opencv2/opencv.hpp"
#include "Settings.hpp"
#include "Logger.hpp"
#include "UserInterface.hpp"

////////////////////////////////////////////////////////////////////////////////
// TODOs
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Name spaces
////////////////////////////////////////////////////////////////////////////////

using namespace cv;
using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Settings
////////////////////////////////////////////////////////////////////////////////

Settings * settings = new Settings();

////////////////////////////////////////////////////////////////////////////////
// Video Capture
////////////////////////////////////////////////////////////////////////////////

VideoCapture video_capture = VideoCapture(settings->video_capture_source);

////////////////////////////////////////////////////////////////////////////////
// Global variables
////////////////////////////////////////////////////////////////////////////////

// New resized size of video used in processing
Size resized_video_size;

// Indicates that resizing is necessary
bool resize_video = false;

// Original frame
Mat original_frame;

// EMILY location
Point emily_location;

// Cursor location
Point cursor_position;

// Status of the algorithm
int status = 0;

// Frame number
long frame_number = -1;

/**
 * Get the resolution of the input video feed.
 */
void get_input_video_size() {

    Size input_video_size(video_capture.get(CV_CAP_PROP_FRAME_WIDTH), video_capture.get(CV_CAP_PROP_FRAME_HEIGHT));

    // If the input video exceeds processing video size limits, we will have to resize it
    if (input_video_size.height > settings->PROCESSING_VIDEO_HEIGHT_LIMIT) {

        // Compute scale ratio
        double ratio = (double) settings->PROCESSING_VIDEO_HEIGHT_LIMIT / input_video_size.height;

        // Compute new width
        int new_video_width = input_video_size.width * ratio;

        // Set new size
        resized_video_size.height = settings->PROCESSING_VIDEO_HEIGHT_LIMIT;
        resized_video_size.width = new_video_width;

        // Indicate that resizing is necessary
        resize_video = true;

    } else {

        // Set video size to original size
        resized_video_size.height = input_video_size.height;
        resized_video_size.width = input_video_size.width;

        // Indicate that resizing is not necessary
        resize_video = false;

    }
}

/**
 * Create one log entry with current system status.
 * 
 * @param logger
 * @param current_commands
 */
void create_log_entry(Logger* logger) {

    // Get current time
    time_t raw_time;
    time(&raw_time);
    struct tm * local_time;
    local_time = localtime(&raw_time);
    char current_time[40];
    strftime(current_time, 40, "%Y%m%d%H%M%S", local_time);

    // Log time
    logger->log_general(current_time);
    logger->log_general(" ");

    // Log frame number
    logger->log_general(frame_number);
    logger->log_general(" ");

    // Log EMILY location
    logger->log_general(cursor_position.x);
    logger->log_general(" ");
    logger->log_general(cursor_position.y);
    logger->log_general(" ");

    // End of log entry
    logger->log_general("\n");
}

int main(int argc, char** argv) {

    ////////////////////////////////////////////////////////////////////////////
    // Output video initialization
    //////////////////////////////////////////////////////////////////////////// 

    // Get the size of input video
    get_input_video_size();

    // Output video name. It is in format year_month_day_hour_minute_second.avi.
    time_t raw_time;
    time(&raw_time);
    struct tm * local_time;
    local_time = localtime(&raw_time);
    char output_file_name[40];
    strftime(output_file_name, 40, "output/%Y_%m_%d_%H_%M_%S_ground_truth", local_time);
    string output_file_name_string(output_file_name);

    ////////////////////////////////////////////////////////////////////////////
    // Log
    ////////////////////////////////////////////////////////////////////////////

    Logger * logger = new Logger(output_file_name_string);

    ////////////////////////////////////////////////////////////////////////////
    // GUI
    ////////////////////////////////////////////////////////////////////////////

    UserInterface * user_interface = new UserInterface(* settings, resized_video_size);

    ////////////////////////////////////////////////////////////////////////////
    // Local variables
    ////////////////////////////////////////////////////////////////////////////

    // Was the first frame annotated?
    bool first_frame_annotated = false;
    
    ////////////////////////////////////////////////////////////////////////////
    // Labeling
    ////////////////////////////////////////////////////////////////////////////

    // Iterate over each frame from the video input and wait between iterations.
    while (true) {
        
        // If status is initialization or recording, load new frame     
        if (status == 2 || status == 0) {

            // If the first frame was not annotated yet, do not load the next frame and use the last one (frame 0)
            if (frame_number == 0 && !first_frame_annotated) {
                
                // First frame (frame 0) will be annotated now
                first_frame_annotated = true;
                
            } else {
                
                // Read one frame
                video_capture >> original_frame;
                
                // Increase frame number counter
                frame_number++;
                
            }

            // End if frame is empty
            if (original_frame.empty()) {
                break;
            }

            // If status was initialization, switch to ready
            if (status == 0) {
                status = 1;
            }

        }

        ////////////////////////////////////////////////////////////////////////
        // Preprocessing
        ////////////////////////////////////////////////////////////////////////

        // Make copy of current frame
        Mat output;
        original_frame.copyTo(output);


        if (resize_video) {

            // Resize the input
            //resize(original_frame, original_frame, resized_video_size, 0, 0, INTER_LANCZOS4);

        }

        ////////////////////////////////////////////////////////////////////////
        // Visualization
        ////////////////////////////////////////////////////////////////////////

        // Visualize cursor location
        user_interface->draw_position(cursor_position.x, cursor_position.y, 10, output);

        // Get status as a string message
        user_interface->print_status(output, status);

        ////////////////////////////////////////////////////////////////////////
        // Main Window
        ////////////////////////////////////////////////////////////////////////

        // Show output frame in the main window
        user_interface->show_main(output);

        ////////////////////////////////////////////////////////////////////////
        // Log output
        ////////////////////////////////////////////////////////////////////////

        // Wait some time before recording cursor position to allow the user
        // to move the cursor to the desired position.
        if (waitKey(settings->time_for_annotation) != 27) {
            
            // Only log if status is recording and the first frame was annotated
            if (status == 2 && first_frame_annotated) {

                // Log the data
                create_log_entry(logger);

            }
        
        } else {
            
            // User pressed ESC so we can exit
            break;
            
        }

    }

    // Close logs
    delete logger;

    // Announce that the processing was finished
    cout << "Processing finished!" << endl;

    // Clean return
    return 0;

}