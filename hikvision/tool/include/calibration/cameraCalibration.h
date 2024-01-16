#ifndef HIKVISION_CAMERA_TOOL_CAMERACALIBRATION_H
#define HIKVISION_CAMERA_TOOL_CAMERACALIBRATION_H

//#include "tool/Conf.h"
#include "../fileOperation/fileOperation.h"
#include "iostream"
#include "opencv2/opencv.hpp"


#define PATTERN_IMG_PATH            HIK_CALI_FILE_PATH"/caliPattern/"      //�궨ͼ�洢�ĵ�ַ
#define CALI_RESULTS_PATH           HIK_CALI_FILE_PATH"/caliResults/"      //�궨��������ļ��洢�ĵ�ַ
#define REPAIR_IMG_PATH             HIK_CALI_FILE_PATH"/caliRepairImg/"    //��У��ͼ�洢�ĵ�ַ


#define REPAIR_IMG_NAME               "0.jpg"
#define REPAIR_FINISH_IMG_NAME        "1.jpg"

#define CALI_CAMERA_DATA_NAME    "calibCameraData.yml"        //�궨��������ļ���
#define CALI_BIAS_DATA_NAME      "caliBiasData.txt"           //�궨ͼ����ƫ������ļ���


struct CameraCalibrationStruct {
    float fx, fy, u0, v0;                 //����ڲ���Ϣ
    float k_1, k_2, p_1, p_2, k_3;        //�������ϵ������
    CameraCalibrationStruct() {
        fx = 1741.0f;
        fy = 1742.74f;
        u0 = 997.25f;
        v0 = 531.544f;
        k_1 = -0.124502f;
        k_2 = 0.315098f;
        p_1 = -0.00353137f;
        p_2 = 0.0078087f;
        k_3 = -0.223415f;
    }
};

//����ͷ�궨��
class CCalibration {
public:
    CCalibration(std::string patternImgPath, std::string calibResultPath, std::string caliCameraDataName, std::string caliBiasDataName, const cv::Size &boardSize) {
        this->patternImgPath = patternImgPath;
        this->calibResultPath = calibResultPath;
        this->caliCameraDataName = caliCameraDataName;
        this->caliBiasDataName = caliBiasDataName;
        this->boardSize = boardSize;
    }

    ~CCalibration() {}

private:
    std::vector<cv::Point3f> singlePatternPoints;
    std::vector<cv::Mat> patternImgList;
    int imgHeight;
    int imgWidth;
    int imgNum;
    float scale = 0.25;
    float errThresh = 3000;
    std::string patternImgPath;
    std::string calibResultPath;
    std::string caliCameraDataName;
    std::string caliBiasDataName;
    cv::Size boardSize;
    cv::Mat camK;
    cv::Mat camDiscoeff;

    int evaluateCalibrationResult(std::vector<std::vector<cv::Point3f>> objectPoints, std::vector<std::vector<cv::Point2f>> cornerSquare, std::vector<cv::Vec3d> _rvec,
                                  std::vector<cv::Vec3d> _tvec, cv::Mat _K, cv::Mat _D, int count, std::vector<int> &outLierIndex, int errThresh);

    static bool testCorners(std::vector<cv::Point2f> &corners, int patternWidth, int patternHeight);

    static void init3DPoints(const cv::Size &boardSize, const cv::Size &squareSize, std::vector<cv::Point3f> &singlePatternPoint);

    //���ļ���д��궨����
    bool writeParams();

    bool readPatternImg();

    void calibProcess();

    void run();

public:

    /**
     * ����궨
     */
    static bool cameraCali();

    /**
     * ��������궨����
     * @param filename �ļ���
     * @return �궨�����ṹ��
     */
    static CameraCalibrationStruct readCalibrationData(const std::string &filename);

    /**
     * ��ӡ�궨����
     * @param calibrationData �궨�����ṹ��
     */
    static void printCalibrationData(CameraCalibrationStruct calibrationData);
};

//�޸�������
class CUndistort {
public:
    CUndistort(std::string srcImgPath, std::string dstImgPath, std::string calibResultPath, std::string caliCameraDataName) {
        this->srcImgPath = srcImgPath;
        this->dstImgPath = dstImgPath;
        this->calibResultPath = calibResultPath;
        this->caliCameraDataName = caliCameraDataName;
        this->K = cv::Mat::eye(cv::Size(3, 3), CV_32FC1);
        this->discoeff = cv::Mat::zeros(cv::Size(1, 4), CV_32FC1);
    }

    ~CUndistort() {}

private:
    std::string srcImgPath;
    std::string dstImgPath;
    std::string calibResultPath;
    std::string caliCameraDataName;
    std::vector<cv::Mat> srcImgList;
    std::vector<cv::Mat> dsrImgList;
    cv::Mat K;
    cv::Mat R;
    cv::Mat discoeff;

    bool readParams();

    bool undistProcess();

public:

    void run();

};

#endif //HIKVISION_CAMERA_TOOL_CAMERACALIBRATION_H

