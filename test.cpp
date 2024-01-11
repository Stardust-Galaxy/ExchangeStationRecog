#include "ExStationRecog.h"

/*
int main() {
    cv::VideoCapture video("test18.mp4");
    if (!video.isOpened()) {
        std::cerr << "Error: Could not open video file." << std::endl;
        return -1;
    }

    int totalFrames = static_cast<int>(video.get(cv::CAP_PROP_FRAME_COUNT));
    double frameRate = video.get(cv::CAP_PROP_FPS);

    cv::namedWindow("Processed Video", cv::WINDOW_NORMAL);
    ExStationRecog processor = ExStationRecog();
    cv::Mat frame;
    while (true) {
        if (!video.read(frame)) {
            break;
        }
        processor.getImage(frame);
        processor.selectContours();
        processor.calCornerPoints();
        processor.show();
        cv::imshow("Processed Video", frame);

        char key = cv::waitKey(1);
        if (key == 27) { 
            break;
        }
    }

    video.release();
    cv::destroyAllWindows();

    return 0;
}
*/
/*
int main() {
    cv::Mat image = cv::imread("test18.png");
    ExStationRecog processor = ExStationRecog();
    processor.getImage(image);
    processor.selectContours();
    processor.calCornerPoints();
    processor.show();
    int windowWidth = 800;
    int windowHeight = 600;
    cv::namedWindow("Image Window", cv::WINDOW_NORMAL);
    cv::resizeWindow("Image Window", windowWidth, windowHeight);
    cv::imshow("Image Window", image);
    cv::waitKey(0);
}
*/
/*
int main()
{

    cv::VideoCapture capture("test13.mp4");
 
    if (!capture.isOpened())
        std::cout << "fail toopen!" << std::endl;


    long totalFrameNumber = capture.get(cv::CAP_PROP_FRAME_COUNT);
    std::cout << "整个视频共" << totalFrameNumber << "帧" << std::endl;



    long frameToStart = 1;
    capture.set(cv::CAP_PROP_POS_FRAMES, frameToStart);
    std::cout << "从第" << frameToStart << "帧开始读" << std::endl;


    int frameToStop = 300;

    if (frameToStop < frameToStart)
    {
        std::cout << "结束帧小于开始帧，程序错误，即将退出！" << std::endl;
        return -1;
    }
    else
    {
        std::cout << "结束帧为：第" << frameToStop << "帧" << std::endl;
    }


    double rate = capture.get(cv::CAP_PROP_FPS);
    std::cout << "帧率为:" << rate << std::endl;



    bool stop = false;


    cv::Mat frame;


    //namedWindow( "Extractedframe" );


    //int delay = 1000/rate;
    double delay = 1000 / rate;



    long currentFrame = frameToStart;


    while (!stop)
    {

        if (!capture.read(frame))
        {
            std::cout << "读取视频失败" << std::endl;
            return -1;
        }


        //cout << "正在读取第" << currentFrame << "帧" << endl;
        //imshow( "Extractedframe", frame );


        if (currentFrame % 10 == 0) 
        {
            std::cout << "正在写第" << currentFrame << "帧" << std::endl;
            std::stringstream str;
            str << "D:/Visual Studio Projects/ExchangeStation/test8pic/" << currentFrame << ".png";

            std::cout << str.str() << std::endl;
            imwrite(str.str(), frame);
        }


        int c = cv::waitKey(delay);

        if ((char)c == 27 || currentFrame > frameToStop)
        {
            stop = true;
        }

        if (c >= 0)
        {
            cv::waitKey(0);
        }
        currentFrame++;

    }

}
*/

int main() {

    cv::VideoCapture inputVideo("test18.mp4");

    if (!inputVideo.isOpened()) {
        std::cerr << "Could not open the input video file!" << std::endl;
        return -1;
    }


    int frameWidth = static_cast<int>(inputVideo.get(cv::CAP_PROP_FRAME_WIDTH));
    int frameHeight = static_cast<int>(inputVideo.get(cv::CAP_PROP_FRAME_HEIGHT));
    double fps = inputVideo.get(cv::CAP_PROP_FPS);


    cv::VideoWriter outputVideo("result18.mp4", cv::VideoWriter::fourcc('X', '2', '6', '4'), fps, cv::Size(frameWidth, frameHeight));

    if (!outputVideo.isOpened()) {
        std::cerr << "Could not open the output video file!" << std::endl;
        return -1;
    }
    ExchangeStationRecog processor = ExchangeStationRecog();
    cv::Mat frame;
    while (inputVideo.read(frame)) {
        processor.getImage(frame);
        processor.selectContours();
        processor.getCorners();
        processor.show();
        outputVideo.write(frame);
    }

    inputVideo.release();
    outputVideo.release();

    return 0;
}

