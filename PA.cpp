#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <numeric>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;

int gNoise = 0;

int PA_out (vector<vector<int>> src,int window_size,int max_window_size,int increment){
    while(window_size <= max_window_size){
        vector<int> vec_Uncorrupted;
        int count_0 = 0;
        int count_255 = 0;

        int center = max_window_size/2;
        int scale = window_size/2;
        for (int y = (center-scale); y <= (center+scale); y++){
            for (int x = (center-scale); x <= (center+scale); x++){
                if (src[y][x] !=0 && src[y][x] != 255){
                    vec_Uncorrupted.push_back(src[y][x]); 
                }
                else if (src[y][x] == 0){
                    count_0++;
                }
                else if (src[y][x] == 255){
                    count_255++;
                }
            }
        }
        sort(vec_Uncorrupted.begin(),vec_Uncorrupted.end());
        // for (int cnt =0;cnt<vec_Uncorrupted.size();cnt++){
        //     printf("%d ",vec_Uncorrupted[cnt]);
        // }
        if (window_size < max_window_size && vec_Uncorrupted.size() < window_size) //1
            window_size += increment;
        else if (window_size <= max_window_size && vec_Uncorrupted.size() >= window_size){
            gNoise ++ ;
            return vec_Uncorrupted[vec_Uncorrupted.size()/2];
        } //2

        else if (window_size == max_window_size && vec_Uncorrupted.size() < window_size && vec_Uncorrupted.size() !=0){
            gNoise ++ ;
            return accumulate(vec_Uncorrupted.begin(),vec_Uncorrupted.end(),0) / vec_Uncorrupted.size();
        }//3
        else if (window_size == max_window_size && vec_Uncorrupted.size() ==0 && count_0 == pow(max_window_size,2)) //5
            return 255;
        else if (window_size == max_window_size && vec_Uncorrupted.size() ==0 && count_255 == pow(max_window_size,2)) //6
            return 0;
        else if (window_size == max_window_size && vec_Uncorrupted.size() ==0) //4
            return (255*count_255)/(count_0+count_255);
    }
}

void PA (Mat src,Mat dst,int src_width,int src_height,int max_window_size){
    int window_size = 3;
    int increment = 2;

    vector<int> v1(max_window_size,0);
    vector<vector<int>> window(max_window_size,v1);
    gNoise = 0;
    for (int row = 0; row < (src_height-max_window_size); row++){
        for (int col = 0; col < (src_width-max_window_size); col++){
            int center = static_cast<int>(src.at<uchar>(row+(max_window_size/2),col+(max_window_size/2)));
            if (center == 0 || center == 255){
                for (int y = 0; y < max_window_size; y++){
                    for (int x = 0; x < max_window_size; x++){  
                        int value = static_cast<int>(src.at<uchar>(row+y,col+x));
                        window[y][x] = value;
                    }
                }
                
            dst.at<uchar>(row,col) = PA_out (window,window_size,max_window_size,increment);
            // printf("%d,%d\n",dst.at<uchar>(row,col),center);
            }
            else
                dst.at<uchar>(row,col) = center;
                // printf("%d\n",dst.at<uchar>(row,col));
            
        }
    }
    cout << gNoise << endl;
}


int main(){
    Mat srcImg;
    Mat channels[3];
    int width = 382;
    int height = 568 ;
    string srcImg_path = "D:/MS/111_1/ADIP/pepper_salt.png";
    srcImg = cv::imread(srcImg_path,CV_8UC1);
    if (srcImg.empty()){
        printf("oh oh oh"); 
        return -1; 
    }
    imshow("in", srcImg);
    waitKey();
    Mat dstImg (height,width,CV_8UC1);
    PA(srcImg,dstImg,width,height,9);
    // Mat bImg (height,width,CV_8UC1);
    // Mat rImg (height,width,CV_8UC1);
    // Mat gImg (height,width,CV_8UC1);

    // split(srcImg,channels);
    // imshow("ori", channels[0]);
    // waitKey();

    // PA(channels[0],bImg,width,height,9);
    // PA(channels[1],rImg,width,height,9);
    // PA(channels[2],gImg,width,height,9);
    // // printf("%d",); 

    // medianBlur(channels[0], bImg, 3);
    // medianBlur(channels[1], rImg, 3);
    // medianBlur(channels[2], gImg, 3);

    // imshow("bImg", bImg);
    // imshow("rImg", rImg);
    // imshow("gImg", gImg);
    // imshow("rImg", rImg);
    // imshow("gImg", gImg);
    
    // vector<Mat> srcMerge = {bImg,rImg,gImg};
    // merge(srcMerge,dstImg);

    imshow("merge", dstImg);


    waitKey();
    return 0;

}