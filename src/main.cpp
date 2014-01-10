#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

#include "pwm.h"

cv::vector<cv::Rect> faces;

int main(int argc, char **argv) {
    if(argc != 2) {
        std::cout << "usage: eye [cascade xml]" << std::endl;
        return -1;
    }

    cv::VideoCapture cap(0);
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 160);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 120);
    cap.set(CV_CAP_PROP_FPS, 7);

    if(!cap.isOpened())
        return -1;

    int xservopwm = 1500;
    int yservopwm = 1500;
    int xpos = 80;
    int ypos = 60;
    int xposold;
    int yposold;
    float p = 1;
    float d = 1;

    setup(1, DELAY_VIA_PWM);
    init_channel(0, 20000);
    print_channel(0);
    add_channel_pulse(0, 17, 0, 1500);
    add_channel_pulse(0, 27, 0, 1500);

    cv::CascadeClassifier cascade;
    cascade.load(argv[1]);

    cv::namedWindow("eye", 1);

    for(;;) {
        cv::Mat frame;
        cap >> frame;
        cascade.detectMultiScale(frame, faces, 1.1, 1, CV_HAAR_SCALE_IMAGE, cv::Size(25, 25), cv::Size(100, 100));

        if(faces.size()) {
            cv::rectangle(frame, cv::Point(faces[0].x, faces[0].y), cv::Point(faces[0].x + faces[0].width, faces[0].y + faces[0].height), cv::Scalar(0, 0, 255));

            xposold = xpos;
            yposold = ypos;
            xpos = faces[0].x + faces[0].width / 2;
            ypos = faces[0].y + faces[0].height / 2;

            xservopwm += (xpos - 80) * p + (xpos / xposold) * d;
            yservopwm += (ypos - 60) * p + (ypos / yposold) * d;

            if(xservopwm > 2400)
                xservopwm = 2400;

            if(xservopwm < 600)
                xservopwm = 600;

            if(yservopwm > 2400)
                yservopwm = 2400;

            if(yservopwm < 600)
                yservopwm = 600;

            add_channel_pulse(0, 17, 0, xservopwm);
            add_channel_pulse(0, 27, 0, yservopwm);
        }

        cv::imshow("eye", frame);
        cv::waitKey(5);
    }

    shutdown();
    return 0;
}
