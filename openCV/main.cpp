#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main() {
  Mat image = imread("../images/1.png", 1);
  namedWindow("pic");
  imshow("pic", image);
  waitKey(0);

  return 0;
}