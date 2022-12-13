#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;

int main(){
    Mat srcImg;
    Mat channels[3],dstImg;
    Mat bImg,rImg,gImg;
    string srcImg_path = "D:/MS/111_1/ADIP/ADIP_Final_project_dataset/PUBG/Ground truth/001.png";
    srcImg = cv::imread(srcImg_path);

    if (srcImg.empty()){
        printf("oh oh oh"); 
        return -1; 
    }
    imshow("in", srcImg);

    split(srcImg,channels);

    medianBlur(channels[0], bImg, 3);
    medianBlur(channels[1], rImg, 3);
    medianBlur(channels[2], gImg, 3);

    imshow("bImg", bImg);
    imshow("rImg", rImg);
    imshow("gImg", gImg);
    
    vector<Mat> srcMerge = {bImg,rImg,gImg};
    merge(srcMerge,dstImg);

    imshow("merge", dstImg);



    waitKey();
    return 0;

}