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
        i18nText i18n;
        if (i18n.setFont("simsun.ttc")) {
          cout << "Load fonts successfully." << endl;
          const wchar_t *msg = L"2018-04-20 16:25:25 抓拍图片";
          cout << "Put ";
          int num = i18n.putText(img_groud, msg, Point(25, 50), CV_RGB(0, 0, 0));
          cout << num << " chars." << endl;
          compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
          compression_params.push_back(80);
          Mat new_img;
          new_img.push_back(img);
          new_img.push_back(img_groud);
          imwrite("test.jpg", new_img, compression_params);
        }
        fclose(fp);
    } catch (Exception e) {
        cout << e.what() << endl;
    }
    return 0;
}
