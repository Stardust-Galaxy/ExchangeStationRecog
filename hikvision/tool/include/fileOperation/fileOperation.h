#ifndef _FILEOPERATION_H_
#define _FILEOPERATION_H_

#include "../systemChoose.h"
#include "../CAMERA_LOG.h"

class FileOperation {
public:
    FileOperation() {}

    ~FileOperation() {}

    /**
     * ����·���µ������ļ���
     * @param folder �ļ��е�ַ
     * @return ����true
     */
    static bool createDirectory(const std::string &folder);

    /**
     * ���Ŀ¼������ͼƬ����ɵĶ�̬����
     * @param path ·��
     * @param number ͼƬ���
     * @param pictureFormat ͼƬ��ʽ
     * @param imgList ���ص�ͼƬ��̬����
     * @param readMode ��ȡģʽ
     */
    static void getImgFileInOrder(const std::string &path, uint32_t &number, const std::string &pictureFormat, std::vector<cv::Mat> &imgList, int readMode = 0);

    /**
     * ��ȡָ��Ŀ¼�µ��ļ���������0��ʼɨ��
     * @param path �ļ�·��
     * @param format �ļ���ʽ ��.avi .log .jpg .bmp
     * @return �ļ�����
     */
    static uint32_t getFileSizeInOrder(const std::string &path, const std::string &format);

    /**
     * ����ͼƬ
     * @param path ͼƬ·��
     * @param number ͼƬ���-�����ڲ�����
     * @param img Ҫ�����ͼƬ
     * @param pictureFormat ͼƬ��ʽ
     */
    static void saveImg(const std::string &path, uint32_t &number, const cv::Mat &img, const std::string &pictureFormat);

    /**
     * ��ȡָ��·���������ļ���
     * @param path �ļ��е�ַ
     * @param files �ļ�����̬����
     * @param mode ��ȡģʽ 0:�ļ����������ļ����� 1:�ļ������������ļ����� 2:�ļ����������ļ������ļ� Ĭ��: 1
     */
    static void getAllFilesName(std::string path, std::vector<std::string> &files, uint8_t mode = 1);
};

#endif
