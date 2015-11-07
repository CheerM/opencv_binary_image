#include <stdio.h>
#include<iostream>
#include <opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

string my_pic = "00.png";

void on_trackbar(int p, void*) {
	Mat dst = imread(my_pic, CV_LOAD_IMAGE_GRAYSCALE);
	int level = cvGetTrackbarPos("Level", "after change");
	int channels = dst.channels();
	int nrows = dst.rows;
	int ncols = dst.cols * channels;

	uchar table[256];

	for (int i = 0; i < 256; i ++) {
		if (i < level) table[i] = 0;
		else table[i] = 255;
	}

	if (dst.isContinuous()) {
		ncols *= nrows;
		nrows = 1;
	}

	if (channels == 1) {
		for (int i = 0; i < nrows; i ++) {
			uchar *p = dst.ptr<uchar>(i);
			for (int j = 0; j < ncols; j ++) {
				p[j] = table[p[j]];
			}
		}
	}
    	imshow("after change", dst);
}

int main( int argc, char** argv) {
	Mat image;  
    	image = imread(argv[1], 1); 
    	namedWindow("SHOW MY PICTURE", CV_WINDOW_AUTOSIZE);
	imshow("SHOW MY PICTURE", image);

	int level = 128;
	namedWindow("after change", CV_WINDOW_AUTOSIZE);
	createTrackbar( "Level", "after change", &level, 256, on_trackbar); //slider
	on_trackbar(0, 0);
	waitKey();
	return 0;
}
