/* 
 * File:   UserInterface.cpp
 * Author: Jan Dufek
 */

#include "UserInterface.hpp"

// Program settings
Settings * UserInterface::settings;

Size UserInterface::video_size;

UserInterface::UserInterface(Settings& s, Size sz) {

    UserInterface::settings = &s;

    UserInterface::video_size = sz;

    // Show main window including slide bars
    create_main_window();

    // Set mouse handler on main window to choose object of interest
    setMouseCallback(UserInterface::settings->MAIN_WINDOW, onMouse, 0);

    // Set main window to full screen
    setWindowProperty(settings->MAIN_WINDOW, CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
}

UserInterface::UserInterface(const UserInterface& orig) {
}

UserInterface::~UserInterface() {
}

/**
 * Shows the main window and creates track bars.
 * 
 */
void UserInterface::create_main_window() {

    // Show new window
    namedWindow(UserInterface::settings->MAIN_WINDOW, CV_GUI_NORMAL);

}

/**
 * Mouse handler.
 * 
 */
void UserInterface::onMouse(int event, int x, int y, int flags, void*) {

    // Check mouse button
    switch (event) {

        // Right drag is reserved for moving over the image
        // Left click context menu is disabled
        // Scrool is reserved for zoom

        // Left double click to start/stop recording
        case EVENT_LBUTTONDBLCLK:

            //            // Print to console
            //            cout << "Right button double click event!" << endl;

            // Toggle status between recording/stop
            if (status == 1) {
                status = 2;
            } else {
                status = 1;
            }

            break;

        // Change of cursor
        case EVENT_MOUSEMOVE:

            // Get mouse location
            cursor_position = Point(x, y);

            // Print mouse location
            //cout << int_to_string(mouse_location.x) + " " + int_to_string(mouse_location.y) << endl;

            break;
    }
}

/**
 * Draws position of the object as crosshairs with the center in the object's
 * centroid.
 * 
 * @param x x coordinate
 * @param y y coordinate
 * @param radius radius of crosshairs
 * @param frame frame to which draw into
 */
void UserInterface::draw_position(int x, int y, double radius, Mat &frame) {

    // Lines
    if (y - radius > 0) {
        line(frame, Point(x, y), Point(x, y - radius), UserInterface::settings->LOCATION_COLOR, UserInterface::settings->LOCATION_THICKNESS);
    } else {
        line(frame, Point(x, y), Point(x, 0), UserInterface::settings->LOCATION_COLOR, UserInterface::settings->LOCATION_THICKNESS);
    }

    if (y + radius < UserInterface::video_size.height) {
        line(frame, Point(x, y), Point(x, y + radius), UserInterface::settings->LOCATION_COLOR, UserInterface::settings->LOCATION_THICKNESS);
    } else {
        line(frame, Point(x, y), Point(x, UserInterface::video_size.height), UserInterface::settings->LOCATION_COLOR, UserInterface::settings->LOCATION_THICKNESS);
    }

    if (x - radius > 0) {
        line(frame, Point(x, y), Point(x - radius, y), UserInterface::settings->LOCATION_COLOR, UserInterface::settings->LOCATION_THICKNESS);
    } else {
        line(frame, Point(x, y), Point(0, y), UserInterface::settings->LOCATION_COLOR, UserInterface::settings->LOCATION_THICKNESS);
    }

    if (x + radius < UserInterface::video_size.width) {
        line(frame, Point(x, y), Point(x + radius, y), UserInterface::settings->LOCATION_COLOR, UserInterface::settings->LOCATION_THICKNESS);
    } else {
        line(frame, Point(x, y), Point(UserInterface::video_size.width, y), UserInterface::settings->LOCATION_COLOR, UserInterface::settings->LOCATION_THICKNESS);
    }

    // Text coordinates
    putText(frame, "[" + int_to_string(x) + "," + int_to_string(y) + "]", Point(x, y + radius + 20), 1, 1, UserInterface::settings->LOCATION_COLOR, 1, 8);

}

/**
 * Prints current status to the GUI.
 * 
 * @param frame
 * @param status
 * @param time_to_target
 */
void UserInterface::print_status(Mat& frame, int status) {

    String stringStatus;

    switch (status) {
        case 0:
            stringStatus = "Initialization! Please wait!";
            break;
        case 1:
            stringStatus = "Ready! Set cursor over the centroid of the object of interest and left double click to start recording.";
            break;
        case 2:
            stringStatus = "Recording! Left double click to stop recording.";
            break;
    }

    // Print status
    putText(frame, stringStatus, Point(50, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2);

}

/**
 * Convert integer to string.
 * 
 * @param number integer to be converted to string
 * 
 */
string UserInterface::int_to_string(int number) {
    stringstream stringStream;
    stringStream << number;
    return stringStream.str();
}

/**
 * Show main window.
 * 
 * @param mat
 */
void UserInterface::show_main(Mat& mat) {
    imshow(UserInterface::settings->MAIN_WINDOW, mat);
}