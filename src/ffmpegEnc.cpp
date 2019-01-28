#include <iostream>

#define BUFF_SIZE 128

void Usage(){
    std::cout << "Usage: ffmpegEnc srcfile outfile preset" << std::endl;
    std::cout << "preset : FHD (1920x1080, 4M)" << std::endl;
    std::cout << "         HD (1280x720, 2M)" << std::endl;
    std::cout << "         SD (720x480, 1M)" << std::endl;
    exit(0);
}

int main(int argc, char*argv[]){
    std::cout << "Hello World!" << std::endl;
    if(argc != 4)
        Usage();

    std::string srcFile = argv[1];
    std::string outFile = argv[2];
    std::string preset = argv[3];
    std::string options;
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
    cmd += outFile;
    cmd += " 2>&1";
    FILE* fp = popen(cmd.c_str(), "r");
    if(fp == NULL){
        std::cerr << "popen Error" << std::endl;
        return -1;
    }
    std::string buffStr, lineStr;
    char buff[BUFF_SIZE+1];
    //while( fgets( buff, BUFF_SIZE, fp) ){
    //while( fgets( buff, BUFF_SIZE, fp) ){
    int c = 0;
    char h;
    while(1){
        //c = fread(buff, BUFF_SIZE,1, fp);
        h = fgetc(fp);
        if(h == EOF) break;
        //if(h == '\n' || h == 4 || h == 13){
        if(h == '\n' || h == '\r') {
            if(lineStr.find("Duration:") != std::string::npos)
                std::cout << lineStr << std::endl;
            else if(lineStr.find("time=") != std::string::npos){
                std::cout << lineStr << std::endl;
           }
            lineStr = "";
        } else {
            lineStr.push_back(h);
            //std::cout << lineStr << std::endl;
            //std::cout << (int)h << std::endl;
        } 

    }
    pclose(fp);
    return 0;
}
