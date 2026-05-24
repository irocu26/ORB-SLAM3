/*#include <iostream>
#include <chrono>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "System.h"

using namespace std;

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        cerr << endl
             << "Usage: ./mono_webcam path_to_vocabulary path_to_settings"
             << endl;
        return 1;
    }

    ORB_SLAM3::System SLAM(
        argv[1],
        argv[2],
        ORB_SLAM3::System::MONOCULAR,
        false
    );

    cv::VideoCapture cap(0, cv::CAP_V4L2);

    if(!cap.isOpened())
    {
        cerr << "Failed to open camera" << endl;
        return -1;
    }

    cap.set(cv::CAP_PROP_FOURCC,
         cv::VideoWriter::fourcc(\'M\',\'J\',\'P\',\'G\')); #this line is there and not commented

    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    cap.set(cv::CAP_PROP_FPS, 15);

    cout << "Camera started..." << endl;

while(true)
{
    cv::Mat frame;
    cap >> frame;

    if(frame.empty())
    {
        std::cout << "EMPTY FRAME" << std::endl;
        continue;
    }

    std::cout << "FRAME RECEIVED: "
              << frame.cols
              << " x "
              << frame.rows
              << std::endl;

   // cv::imshow("DEBUG_CAMERA", frame);

    double timestamp =
        chrono::duration_cast<chrono::duration<double>>
        (
            chrono::steady_clock::now().time_since_epoch()
        ).count();

    std::cout << "TRACKING FRAME..." << std::endl;

    //SLAM.TrackMonocular(frame, timestamp);
    //Sophus::SE3f Tcw = SLAM.TrackMonocular(frame, timestamp);

auto Tcw = SLAM.TrackMonocular(frame, timestamp);

if(!Tcw.matrix().isZero())
{
    std::cout << "POSE ESTIMATED" << std::endl;
}
else
{
    std::cout << "NO POSE YET" << std::endl;
}

    std::cout << "TRACKING DONE" << std::endl;

    char key = cv::waitKey(1);

    if(key == 27)
        break;
}

    SLAM.Shutdown();

    SLAM.SaveKeyFrameTrajectoryTUM("KeyFrameTrajectory.txt");

    return 0;
} */

/*#include <iostream>
#include <chrono>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio.hpp>

#include "System.h"

using namespace std;

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        cerr << endl
             << "Usage: ./mono_webcam path_to_vocabulary path_to_settings"
             << endl;

        return 1;
    }

    ORB_SLAM3::System SLAM(
        argv[1],
        argv[2],
        ORB_SLAM3::System::MONOCULAR,
        false
    );

    cv::VideoCapture cap(0, cv::CAP_V4L2);

    if(!cap.isOpened())
    {
        cerr << "Failed to open camera" << endl;
        return -1;
    }

    cap.set(
        cv::CAP_PROP_FOURCC,
        cv::VideoWriter::fourcc('M','J','P','G')
    );

    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    cap.set(cv::CAP_PROP_FPS, 15);

    cout << "Camera started..." << endl;

    cv::namedWindow("DEBUG_CAMERA", cv::WINDOW_NORMAL);

    while(true)
    {
        cv::Mat frame;

        cap >> frame;

        if(frame.empty())
        {
            cout << "EMPTY FRAME" << endl;
            continue;
        }

        cout << "FRAME RECEIVED: "
             << frame.cols
             << " x "
             << frame.rows
             << endl;

        double timestamp =
            chrono::duration_cast<chrono::duration<double>>
            (
                chrono::steady_clock::now().time_since_epoch()
            ).count();

        cout << "TRACKING FRAME..." << endl;

        auto Tcw = SLAM.TrackMonocular(frame, timestamp);

        if(!Tcw.matrix().isZero())
        {
            cout << "POSE ESTIMATED" << endl;
        }
        else
        {
            cout << "NO POSE YET" << endl;
        }

        cout << "TRACKING DONE" << endl;

        cv::imshow("DEBUG_CAMERA", frame);

        char key = cv::waitKey(1);

        if(key == 27)
        {
            cout << "ESC PRESSED" << endl;
            break;
        }
    }

    cout << "Shutdown" << endl;

    SLAM.Shutdown();

    cout << endl;
    cout << "Saving trajectories..." << endl;

    SLAM.SaveKeyFrameTrajectoryTUM(
        "KeyFrameTrajectory.txt"
    );

    SLAM.SaveTrajectoryTUM(
        "FrameTrajectory.txt"
    );

    cout << "Trajectory files saved" << endl;

    return 0;
}*/

#include <iostream>
#include <chrono>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio.hpp>

#include "System.h"

using namespace std;

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        cerr << endl
             << "Usage: ./mono_webcam path_to_vocabulary path_to_settings"
             << endl;
        return 1;
    }

    // Initialize ORB-SLAM3
    ORB_SLAM3::System SLAM(
        argv[1],
        argv[2],
        ORB_SLAM3::System::MONOCULAR,
        false
    );

    // Open USB camera
    cv::VideoCapture cap(2, cv::CAP_V4L2);

    if(!cap.isOpened())
    {
        cerr << "Failed to open USB camera" << endl;
        return -1;
    }

    // Camera settings
    cap.set(cv::CAP_PROP_FOURCC,
             cv::VideoWriter::fourcc('M','J','P','G'));

    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    cap.set(cv::CAP_PROP_FPS, 15);

    cout << "USB Camera started..." << endl;

    while(true)
    {
        cv::Mat frame;
        cap >> frame;

        if(frame.empty())
        {
            cout << "EMPTY FRAME" << endl;
            continue;
        }

        cout << "FRAME RECEIVED: "
             << frame.cols
             << " x "
             << frame.rows
             << endl;

        // Current timestamp
        double timestamp =
            chrono::duration_cast<chrono::duration<double>>
            (
                chrono::steady_clock::now().time_since_epoch()
            ).count();

        cout << "TRACKING FRAME..." << endl;

        // Run ORB-SLAM3
        auto Tcw = SLAM.TrackMonocular(frame, timestamp);

        // Check pose estimation
        if(!Tcw.matrix().isZero())
        {
            cout << "POSE ESTIMATED" << endl;
        }
        else
        {
            cout << "NO POSE YET" << endl;
        }

        cout << "TRACKING DONE" << endl;

        // Show camera feed
        cv::imshow("USB Camera Feed", frame);

        // ESC key to exit
        char key = cv::waitKey(1);

        if(key == 27)
            break;
    }

    cout << "Shutting down SLAM..." << endl;

    // Shutdown SLAM properly
    SLAM.Shutdown();

    // Save trajectories
    SLAM.SaveKeyFrameTrajectoryTUM("KeyFrameTrajectory.txt");

    cout << "Trajectory saved to KeyFrameTrajectory.txt" << endl;

    return 0;
}