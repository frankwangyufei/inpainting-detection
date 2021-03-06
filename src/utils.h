//
// Created by antoinewdg on 11/26/16.
//

#ifndef INPAINTING_DETECTION_UTIL_h
#define INPAINTING_DETECTION_UTIL_h

#include <cstdlib>
#include <iostream>
#include <chrono>
#include <array>

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs/imgcodecs_c.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "cv_utils/cv_utils.h"

using namespace cvu;

using std::vector;


template<class T>
Mat_<T> load_from_yaml(string filename) {
    cv::FileStorage fs(filename, cv::FileStorage::READ);
    Mat_<T> out;
    fs["matrix"] >> out;
    return out;
}

template<class T>
void write_to_yaml(string filename, const Mat_<T> &m) {
    cv::FileStorage fs(filename, cv::FileStorage::WRITE);
    fs << "matrix" << m;
    fs.release();
}

#endif //INPAINTING_DETECTION_UTIL_h
