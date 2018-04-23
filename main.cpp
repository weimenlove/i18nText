#include "include/i18nText.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>

using namespace cv;
using namespace std;

int main(int argc, char **argv) {
    FILE *fp;
    char img_buf[200*1024];
    vector<int> compression_params;
    vector<char *> v;

    try {
        fp = fopen("0B17E0002018032717164200000001_SB.jpg", "r");
        if (fp == NULL)
        {
            printf("read image file failed!\n");
            return -1;
        }

        memset(img_buf, 0, sizeof(img_buf));
        fread(img_buf, 199, 1024, fp);
        v.push_back(img_buf);

        Mat img2 = imdecode(v, -1);

        cout << "img2.flags: " << img2.flags << endl;
        cout << "img2.dims: " << img2.dims << endl;
        cout << "img2.rows: " << img2.rows << endl;
        cout << "img2.cols: " << img2.cols << endl;
        cout << "img2.depth(): " << img2.depth() << endl;

        //Mat image = imread(argv[1], -1);   // Read the file
        i18nText i18n;
        if (i18n.setFont("simsun.ttc")) {
          cout << "Load fonts successfully." << endl;
          const wchar_t *msg = L"2018-04-20 16:25:25 抓拍图片";
          cout << "Put ";
          int num = i18n.putText(img2, msg, Point(25, 50), CV_RGB(255, 0, 0));
          cout << num << " chars." << endl;
          compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
          compression_params.push_back(37);
          imwrite("test.jpg", img2, compression_params);
        }
        fclose(fp);
    } catch (Exception e) {
        cout << e.what() << endl;
    }
    return 0;
}
