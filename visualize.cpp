#include<iostream>  
#include<string>  
#include<vector>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    vector<Mat> frames; //定义一个Matrix vector，用来存zhen
    string filename;  //定义一个字符串变量，用来存放文件的名称

    /*将png图片转换为Mat矩阵
    vector<Mat> images;
    for (string filename : filenames)
    {
        Mat im = imread(path + filename);
        images.push_back(im);
    }*/
    //后来发现好像不是很用转换， opencv的imread function 可以自动把png图片读成matrix
    //不停的接收filename
    while (cin >> filename) 
    {
        Mat frame = imread(filename); //将png文件读取到Mat类型的变量frame中
        frames.push_back(frame);      //将frame加入到vector中
    }

    //创建一个VideoWriter
    VideoWriter writer;
    writer.open("output.gif", VideoWriter::fourcc('G', 'I', 'F', '8'), 5.0, Size(frames[0].cols, frames[0].rows), true);

    //将vector中的每一帧都写入到输出文件
    for (int i=0; i<frames.size(); i++)
    {
        if (writer.isOpened())
        {
            writer.write(frames[i]);
        }
    }
    writer.release();
    return 0;
}