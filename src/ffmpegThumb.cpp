#include <iostream>
#include <fstream>

#define BUFF_SIZE 128

void Usage(){
    std::cout << "Usage             :   ffmpegThumb srcfile outfile thumbnail_time" << std::endl;
    std::cout << "thumbnail_time    :   전체 시간의 퍼센트 (0~100)" << std::endl;
    exit(0);
}

int GetThumbnail(std::string srcFile, std::string outFile, int ttime){
    char ss[16];
    sprintf(ss, "%02d:%02d:%02d", ttime/60/60, (ttime/60)%60, ttime%60);
    std::string option = " -ss ";
    option += ss;
    std::string cmd = "ffmpeg -v verbose -y -i ";
    cmd += srcFile;
    cmd += " -vframes 1 -strict -2 ";
    cmd += option + " ";
    cmd += outFile + " ";
    cmd += " 2>&1";
    FILE* fp = popen(cmd.c_str(), "r");
    if(fp == NULL){
        std::cerr << "popen Error" << std::endl;
        return -1;
    }
    char t;
    while(1){
        t = fgetc(fp);
        if(t == EOF) break;
    }
    pclose(fp);
    return 0;
}

int main(int argc, char*argv[]){
    if(argc != 4)
        Usage();

    std::string srcFile = argv[1];
    std::string outFile = argv[2];
    int thumbnail_time = atoi(argv[3]);
    if(thumbnail_time < 0)
        thumbnail_time = 0;

    std::string options;

    std::string cmd = "ffmpeg -v verbose -y -i ";
    cmd += srcFile;
    cmd += " -strict -2 ";
    cmd += " 2>&1";
    FILE* fp = popen(cmd.c_str(), "r");
    if(fp == NULL){
        std::cerr << "popen Error" << std::endl;
        return -1;
    }
    std::string buffStr, lineStr;
    char buff[BUFF_SIZE+1];
    int c = 0;
    char t;
    int duration, process;
    size_t pos;
    int h,m,s,ms;
//      Duration: 00:01:22.50, start: 0.000000, bitrate: 434 kb/s
//    Stream #0:0(und): Video: h264 (Constrained Baseline) (avc1 / 0x31637661), yuv420p, 640x358, 335 kb/s, 25 fps, 25 tbr, 50 tbn, 50 tbc (default)
//    Metadata:
//      handler_name    : VideoHandler
//    Stream #0:1(und): Audio: aac (LC) (mp4a / 0x6134706D), 44100 Hz, stereo, fltp, 95 kb/s (default)

    while(1){
        t = fgetc(fp);
        if(t == EOF) break;
        if(t == '\n' || t == '\r') {
            if((pos = lineStr.find("Duration:")) != std::string::npos){
                h=m=s=ms=0;
                std::string du = lineStr.substr(pos+10,11);
                sscanf((char*)du.data(), "%02d:%02d:%02d.%02d", &h, &m, &s, &ms);
                duration = s + m*60 +  h*60*60;
            }
            lineStr = "";
        } else {
            lineStr.push_back(t);
        } 

    }
    pclose(fp);
    //get Thumbnail
    //if(duration == 0 ){
    //    std::cerr << "duration Error " << duration << std::endl;
    //    return -1;
    //}
    int ttime = thumbnail_time * duration / 100 ;
    GetThumbnail(srcFile, outFile, ttime);
    return 0;
}
