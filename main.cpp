#include "include/i18nText.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>

using namespace cv;
using namespace std;

int main(int argc, char **argv) {
    FILE *fp;
    char img_buf[200*1024+1];
    vector<int> compression_params;

    try {
        fp = fopen("0B17E0002018032717164200000001_SB.jpg", "r");
        if (fp == NULL)
        {
            printf("read image file failed!\n");
            return -1;
        }

#if 1
        memset(img_buf, 0, sizeof(img_buf));
        fread(img_buf, 200, 1024, fp);
        Mat img_jpeg = Mat(1080, 1920, CV_8UC3, img_buf);
        Mat img = imdecode(img_jpeg, CV_LOAD_IMAGE_COLOR);
        Mat img_groud = Mat(150, 1920, CV_8UC3, Scalar(200, 215, 230));
#else
        Mat img = imread(argv[1], -1);   // Read the file
#endif
        i18nText i18n1;
        if (i18n1.setFont("simkai.ttf")) {
            cout << "Load fonts successfully." << endl;
            const wchar_t *msg1 = L"云停车一体机出口(识别抓拍)";
            const wchar_t *msg2 = L"2018-04-25 17:18:25";
            cout << "Put 1";
            int num = i18n1.putText(img_groud, msg1, Point(25, 50), CV_RGB(0, 0, 0));
            cout << num << " chars." << endl;
            cout << "Put 2";
            num = i18n1.putText(img_groud, msg2, Point(25, 120), CV_RGB(0, 0, 0));
            cout << num << " chars." << endl;
        }
        i18nText i18n2;
        if (i18n2.setFont("simkai.ttf")) {
            cout << "Load fonts successfully." << endl;
            SizeDesc size;
            size.pixelSize = 80;
            size.space = 0.8;
            size.gap = 0.1;
            i18n2.setSize(&size);
            const wchar_t *msg3 = L"粤BMW888";
            cout << "Put 3";
            int num = i18n2.putText(img_groud, msg3, Point(1280, 100), CV_RGB(0, 0, 0));
            cout << num << " chars." << endl;
        }

        compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
        compression_params.push_back(80);
        Mat new_img;
        new_img.push_back(img);
        new_img.push_back(img_groud);
        imwrite("test.jpg", new_img, compression_params);
        fclose(fp);
    } catch (Exception e) {
        cout << e.what() << endl;
    }
    return 0;
}
