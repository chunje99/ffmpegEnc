#include <iostream>
#include <fstream>

#define BUFF_SIZE 128

void Usage(){
    std::cout << "Usage: ffmpegEnc srcfile outfile preset" << std::endl;
    std::cout << "preset : FHD (1920x1080, 4M)" << std::endl;
    std::cout << "         HD (1280x720, 2M)" << std::endl;
    std::cout << "         SD (720x480, 1M)" << std::endl;
    exit(0);
}

int main(int argc, char*argv[]){
    if(argc != 4)
        Usage();

    std::string srcFile = argv[1];
    std::string outFile = argv[2];
    std::string preset = argv[3];
    std::string options;
    std::string processFile = outFile + ".process";
    if(preset == "FHD")
        options = " -s 1920x1080 -b:v 4M -b:a 512k ";
    else if(preset == "HD")
        options = " -s 1280x720 -b:v 2M -b:a 256k ";
    else if(preset == "SD")
        options = " -s 720x480 -b:v 1M -b:a 128k ";
    else
        options = " -s 1280x720 -b:v 2M -b:a 256k ";

    std::string cmd = "ffmpeg -v verbose -y -i ";
    cmd += srcFile;
    cmd += options;
    cmd += " -strict -2 ";
    cmd += outFile;
    cmd += " 2>&1";
    FILE* fp = popen(cmd.c_str(), "r");
    if(fp == NULL){
        std::cerr << "popen Error" << std::endl;
        return -1;
    }
    //open process file
    std::ofstream of(processFile.c_str(), std::ios::trunc);
    if(!of.is_open()){
        std::cerr << "file open Error" << processFile << std::endl;
        return -2;
    }
    of << "0" << std::endl;
    std::string buffStr, lineStr;
    char buff[BUFF_SIZE+1];
    int c = 0;
    char t;
    int duration, process;
    size_t pos;
    int h,m,s,ms;
    while(1){
        t = fgetc(fp);
        if(t == EOF) break;
        if(t == '\n' || t == '\r') {
            if((pos = lineStr.find("Duration:")) != std::string::npos){
                h=m=s=ms=0;
                std::string du = lineStr.substr(pos+10,11);
                sscanf((char*)du.data(), "%02d:%02d:%02d.%02d", &h, &m, &s, &ms);
                duration = s + m*60 +  h*60*60;
            } else if((pos = lineStr.find("time=")) != std::string::npos){
                if(duration == 0) continue;
                std::string pro = lineStr.substr(pos+5,11);
                h=m=s=ms=0;
                sscanf((char*)pro.data(), "%02d:%02d:%02d.%02d", &h, &m, &s, &ms);
                process = s + m*60 +  h*60*60;
                of << process*100/duration << std::endl;
                std::cout << process*100/duration << std::endl;
           }
            lineStr = "";
        } else {
            lineStr.push_back(t);
        } 

    }
    of << 100 << std::endl;
    of.close();
    pclose(fp);
    return 0;
}
