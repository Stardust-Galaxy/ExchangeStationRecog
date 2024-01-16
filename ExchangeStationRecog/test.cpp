#include "ExStationRecog.h"
#include "../hikvision/include/hikvision_camera.h"

int main() {
    bool from_camera = true;    //determine the sourceImg
    camera::HikCamera Camera;
    cv::VideoCapture capture;
    cv::Mat sourceImg;
    if(from_camera) {
        Camera.Init();
        Camera.CamInfoShow();
    }
    else {
        std::string fileName = "";
        capture.open(fileName);
        if (!capture.isOpened()) {
            std::cerr << "Error: Could not open capture file." << std::endl;
            return -1;
        }
    }

    //cv::namedWindow("Processed capture", cv::WINDOW_NORMAL);
    ExchangeStationRecog processor = ExchangeStationRecog();
    while (true) {
        if(from_camera) {
            Camera.ReadImg(sourceImg);
            if(sourceImg.empty())
                continue;
        }
        else {
            capture.read(sourceImg);
        }
        processor.getImage(sourceImg);
        processor.selectContours();
        processor.getCorners();
        processor.show();
        cv::imshow("Processed video", sourceImg);

        char key = cv::waitKey(1);
        if (key == 27) { 
            break;
        }
    }

    capture.release();
    cv::destroyAllWindows();

    return 0;
}

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
    std::cout << "������Ƶ��" << totalFrameNumber << "֡" << std::endl;



    long frameToStart = 1;
    capture.set(cv::CAP_PROP_POS_FRAMES, frameToStart);
    std::cout << "�ӵ�" << frameToStart << "֡��ʼ��" << std::endl;


    int frameToStop = 300;

    if (frameToStop < frameToStart)
    {
        std::cout << "����֡С�ڿ�ʼ֡��������󣬼����˳���" << std::endl;
        return -1;
    }
    else
    {
        std::cout << "����֡Ϊ����" << frameToStop << "֡" << std::endl;
    }


    double rate = capture.get(cv::CAP_PROP_FPS);
    std::cout << "֡��Ϊ:" << rate << std::endl;



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
            std::cout << "��ȡ��Ƶʧ��" << std::endl;
            return -1;
        }


        //cout << "���ڶ�ȡ��" << currentFrame << "֡" << endl;
        //imshow( "Extractedframe", frame );


        if (currentFrame % 10 == 0) 
        {
            std::cout << "����д��" << currentFrame << "֡" << std::endl;
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
/*
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
*/
