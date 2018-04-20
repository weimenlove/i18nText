#include "include/i18nText.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char **argv) {
    try {
        vector<int> compression_params;

        Mat image = imread(argv[1], -1);   // Read the file
        //namedWindow("test", CV_WINDOW_NORMAL);
        i18nText i18n;
        if (i18n.setFont("simsun.ttc")) {
          cout << "Load fonts successfully." << endl;
          const wchar_t *msg = L"2018-04-20 16:25:25 抓拍图片";
          cout << "Put ";
          int num = i18n.putText(image, msg, Point(25, 50), CV_RGB(255, 0, 0));
          cout << num << " chars." << endl;

          //imshow("text", image);
          //cvWaitKey(0);
          compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
          compression_params.push_back(37);
          imwrite("test.jpg", image, compression_params);
        }
    } catch (Exception e) {
        cout << e.what() << endl;
    }
    return 0;
}
