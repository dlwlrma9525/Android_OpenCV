#include <jni.h>
#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

extern "C"
JNIEXPORT void JNICALL
Java_com_iudeveloment_opencv_MainActivity_CannyEdgeDetect(JNIEnv *env, jobject instance,
                                                           jlong matAddrInput,
                                                           jlong matAddrResult) {
    // TODO
    cv::Mat &matInput = *(cv::Mat*) matAddrInput;
    cv::Mat &matResult = *(cv::Mat*) matAddrResult;

    cv::cvtColor(matInput, matInput, COLOR_RGBA2GRAY);

    cv::Mat edge;
    cv::Canny(matInput, edge, 50, 150);

    matResult = edge;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_iudeveloment_opencv_MainActivity_FindContours(JNIEnv *env, jobject instance,
                                                       jlong matAddrInput, jlong matAddrResult) {

    // TODO
    cv::RNG rng(12345);

    cv::Mat &matInput = *(cv::Mat*) matAddrInput;
    cv::Mat &matResult = *(cv::Mat*) matAddrResult;

    cv::cvtColor(matInput, matInput, COLOR_RGBA2GRAY);

    // Canny Edge..
    cv::Mat edge;
    cv::Canny(matInput, edge, 50, 150);

    // Noise Suppress..
    cv::dilate(edge, edge, 1);
    cv::erode(edge, edge, 1);

    // Edge Copy
    cv::Mat copyEdge;
    edge.copyTo(copyEdge);

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    Scalar color = Scalar(255, 255, 255);

    cv:: findContours(copyEdge, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

    cv::Mat drawing = Mat::zeros(edge.size(), CV_8UC3);
    for( int i = 0; i< contours.size(); i++ )
        cv::drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());

    matResult = drawing;
}