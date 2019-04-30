//
//  main.cpp
//  NumberRecognition
//
//  Created by Jeremy Lee on 2019-04-03.
//  Copyright © 2019 Jeremy Lee. All rights reserved.
//

#include <string>
#include <math.h>
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/plot.hpp>

using namespace std;
using namespace cv;

#define template_width 24
#define template_height 38
#define left 63234
#define right 63235
#define up 63232
#define down 63233
#define enter 13
#define xkey 120
#define zkey 122

int main()
{
    Mat input;
    Mat output;
    
    int count=0;
    int posx,posy;
    posx=posy=0;
    
    input=imread("./1.png");
    cvtColor(input, input, COLOR_RGB2GRAY);
    threshold(input, input, 0, 255, THRESH_BINARY | THRESH_OTSU);
    
    while (1)
    {
        output=input.clone();
        Rect window(posx,posy,template_width,template_height);
        Rect show=window;
        show.x-=1;
        show.y-=1;
        rectangle(output, show.tl(), show.br(), Scalar(255), 1);
        imshow("output",output);
        int key=waitKeyEx();
        switch (key)
        {
            case left:
                if(posx>0)
                    posx--;
                break;
            case right:
                if(posx<input.cols)
                    posx++;
                break;
            case up:
                if(posy>0)
                    posy--;
                break;
            case down:
                if(posy<input.rows)
                    posy++;
                break;
            case xkey:
                resize(input, input,cv::Size(), 1.1,1.1);
                threshold(input, input, 0, 255, THRESH_BINARY | THRESH_OTSU);
                break;
            case zkey:
                resize(input, input,cv::Size(), 0.9,0.9);
                threshold(input, input, 0, 255, THRESH_BINARY | THRESH_OTSU);
                break;
            case enter:
                imwrite(to_string(count++)+".png", input(window));
        }
    }
    return 0;
}
