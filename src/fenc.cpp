#include "fenc.h"

void Fenc::Print() {
    std::cout << "Print" << std::endl;
}

void Fenc::setSource(std::string src){
    m_srcFile = src;
}
void Fenc::setTarget(std::string target){ 
    m_outFile = target;
}
void Fenc::setPreset(std::string preset) {
    m_preset = preset;
}

int Fenc::getProgress(){
    return m_progress;
}

std::string Fenc::getSource(){
    return m_srcFile;
}
std::string Fenc::getTarget(){
    return m_outFile;
}
std::string Fenc::getPreset(){
    return m_preset;
}

void Fenc::StartEncode(){
    m_threads[m_jobcnt] = std::thread{&Fenc::Encode, this};
    m_jobcnt++;
}

void Fenc::Wait(){
    for(int i = 0 ; i < 10 ; ++i)
        if(m_threads[i].joinable())
            m_threads[i].join();
}

void Fenc::Encode(){
    std::string processFile = m_outFile + ".process";
    if(m_preset == "FHD")
        m_options = " -s 1920x1080 -b:v 4M -b:a 512k ";
    else if(m_preset == "HD")
        m_options = " -s 1280x720 -b:v 2M -b:a 256k ";
    else if(m_preset == "SD")
        m_options = " -s 720x480 -b:v 1M -b:a 128k ";
    else
        m_options = " -s 1280x720 -b:v 2M -b:a 256k ";

    std::string cmd = "ffmpeg -strict -2 -v verbose -y -i ";
    cmd += m_srcFile;
    cmd += m_options;
    cmd += m_outFile;
    cmd += " 2>&1";
    FILE* fp = popen(cmd.c_str(), "r");
    if(fp == NULL){
        std::cerr << "popen Error" << std::endl;
        return;
    }
    //open process file
    std::ofstream of(processFile.c_str(), std::ios::trunc);
    if(!of.is_open()){
        std::cerr << "file open Error" << processFile << std::endl;
        return;
    }
    of << "0" << std::endl;
    std::string buffStr, lineStr;
    int BUFF_SIZE = 128;
    char buff[BUFF_SIZE+1];
    int c = 0;
    char t;
    int duration, process;
    m_progress = 0;
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
                m_progress = process*100/duration;
                of << m_progress << std::endl;
            }
            lineStr = "";
        } else {
            lineStr.push_back(t);
        } 

    }
    m_progress = 100;
    of << m_progress << std::endl;
    of.close();
    pclose(fp);
}
