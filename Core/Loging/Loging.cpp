//
// Created by 김준성 on 2016. 5. 11..
//

#include "Loging.h"

vector<ResultLines> resultLines_vector;

vector<int> roadline_right;
vector<int> roadline_left;
vector<int> cornerline_right;
vector<int> cornerline_left;
vector<int> vertical;

int frame_count=0;

void loging_initalizing() {
    Py_Initialize();
    PyRun_SimpleString("from matplotlib.pyplot import *");
    PyRun_SimpleString("ion()");
}
void plot() {
    string plot_roadright = "plot("+vector2String(roadline_right)+",color='r',label="+'\''+"Road_Right"+'\''+");";
    string plot_roadleft = "plot("+vector2String(roadline_left)+",color='g',label="+'\''+"Road_Left"+'\''+");";
    string plot_cornerright = "plot("+vector2String(cornerline_right)+",color='b',label="+'\''+"Corner_Right"+'\''+");";
    string plot_cornerleft = "plot("+vector2String(cornerline_left)+",color='y',label="+'\''+"Corner_Left"+'\''+");";
    string plot_vertical = "plot("+vector2String(vertical)+",color='k',label="+'\''+"Vertical"+'\''+");";
    PyRun_SimpleString(plot_roadright.c_str());
    PyRun_SimpleString(plot_roadleft.c_str());
    PyRun_SimpleString(plot_cornerright.c_str());
    PyRun_SimpleString(plot_cornerleft.c_str());
    PyRun_SimpleString(plot_vertical.c_str());
    PyRun_SimpleString("show(False)");
}
void plot_clear() {
    roadline_right.clear();
    roadline_left.clear();
    cornerline_right.clear();
    cornerline_left.clear();
    vertical.clear();
    frame_count=0;
    PyRun_SimpleString("close();");
}

void matplot_refreash(ResultLines lines) {

    resultLines_vector.push_back(lines);
    if (frame_count == 0) {
        roadline_right.push_back(0);
        roadline_left.push_back(0);
        cornerline_right.push_back(0);
        cornerline_left.push_back(0);
        vertical.push_back(0);
    }
    if (frame_count % 40 != 0)
    {
        roadline_right.push_back(roadline_right[frame_count] + lines.roadlines_right.size());
        roadline_left.push_back(roadline_left[frame_count] + lines.roadlines_left.size());
        cornerline_right.push_back(cornerline_right[frame_count] + lines.conerlines_right.size());
        cornerline_left.push_back(cornerline_left[frame_count] + lines.conerline_left.size());
        vertical.push_back(vertical[frame_count]+lines.horizenLines.size());
    }
    else{
        roadline_right.push_back(0);
        roadline_left.push_back(0);
        cornerline_right.push_back(0);
        cornerline_left.push_back(0);
        vertical.push_back(0);
    }

    plot();
    frame_count++;
}
string vector2String(vector<int> vec) {
    string result="[";
    for(int i : vec)
    {
        result += to_string(i);
        result += ",";
    }
    result = result.substr(0, result.size()-1);
    result +="]";
    return result;
}
void resultLineLoging(string fileurl, string filename) {
    vector<int> roadline_right;
    vector<int> roadline_left;
    vector<int> cornerline_right;
    vector<int> cornerline_left;

    for(ResultLines resultLines : resultLines_vector)
    {
        roadline_right.push_back(resultLines.roadlines_right.size());
        roadline_left.push_back(resultLines.roadlines_left.size());
        cornerline_right.push_back(resultLines.conerlines_right.size());
        cornerline_left.push_back(resultLines.conerline_left.size());
    }
    //Log 파일 write Initializing
    ofstream logfile;
    logfile.open (fileurl+"/result/"+filename+"_Resultline.txt");

    for(int l : roadline_right)
        logfile << l<<",";
    logfile << "\n";
    for(int l : roadline_left)
        logfile << l<<",";
    logfile << "\n";
    for(int l : cornerline_right)
        logfile << l<<",";
    logfile << "\n";
    for(int l : cornerline_left)
        logfile << l<<",";
    logfile << "\n";

    logfile.close();
    resultLines_vector.clear();
}
void direction_result_print(int code) {
    Mat result_mat = Mat::zeros(200,400,CV_8UC1);
    /// Font Face
    int myFontFace = 2;
    /// Font Scale
    double myFontScale = 1.2;
    string result;

    switch(code)
    {
        case RIGHT_VERTICAL:
            result = "Right_Vertical";
            break;

        case LEFT_VERTIVAL:
            result = "Left_Vertical";
            break;

        case UNKNWON_VERTICAL:
            result = "Unknown_Vertical";
            break;

        case RIGHT_ROUND:
            result = "Right_Round";
            break;

        case LEFT_ROUND:
            result = "Left_Round";
            break;

        case ROUND:
            result = "Round";
            break;

        case NOTHING:
            result = "Nothing";
            break;
    }
    cv::putText( result_mat , result, Point(50,50), myFontFace, myFontScale, Scalar::all(255) );
    cout << "Result : "+result+"\n";
    imshow("result_Text",result_mat);
}




