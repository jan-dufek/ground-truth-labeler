# Ground Truth Labeler
This application can be used to label the ground truth in a video. The ground truth can be labeled using a mouse cursor. The position of the cursor in each video frame is recorded. The data can be used later for training or evaluation.

## Installation on macOS

1. Install Homebrew:

    /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"

2. Install OpenCV with FFmpeg support:

    brew tap homebrew/science

    brew install opencv3 --with-contrib --with-ffmpeg --with-tbb --with-qt5

3. Link OpenCV:

    brew link --force --override opencv3

4. Install CMake:

    https://cmake.org

5. In terminal, change directory into the root directory of the project and run the following command to generate makefile:

    cmake .

6. Compile the project:

    make

## Manual

The graphical user interface has the following functionality:

* Left double click to start or stop recording. When the recording is stopped, the video will pause.

* Zoom with mouse wheel or touchpad scroll.

* Drag with left mouse button.

* Press escape key to exit.

After the recording is started, hold the cursor over the position you want to record. The position of the cursor in each frame is saved to the log file.