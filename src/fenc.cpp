#include "fenc.h"
#include <time.h>
#include <unistd.h>

Fenc::Fenc()
    : m_jobcnt(0){
}

Fenc::~Fenc(){
    Wait();
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

int Fenc::getThumbnailTime(){
    return m_thumbnail_time;
}
void Fenc::setThumbnailTime(int thumbnail_time){
    m_thumbnail_time = thumbnail_time;
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
    //m_threads[m_jobcnt] = std::thread(&Fenc::Encode, this);
    //m_threads.push_back(std::thread(&Fenc::Encode, this));
    m_threadss.emplace_back(std::thread(&Fenc::Encode, this));
    m_jobcnt++;
}

void Fenc::StartThumbnail(){
    //m_threads[m_jobcnt] = std::thread(&Fenc::Thumbnail, this);
    m_threadss.emplace_back(std::thread(&Fenc::Thumbnail, this));
    //m_threads.push_back(std::thread(&Fenc::Thumbnail, this));
    //m_threads.push_back(std::move(std::thread(&Fenc::Thumbnail, this)));
    m_jobcnt++;
}

void Fenc::Wait(){
    //for(int i = 0 ; i < m_jobcnt ; ++i)
    //    if(m_threads[i].joinable())
    //        m_threads[i].join();
    //for(auto t : m_threads)
    //for(int i = 0 ; i < m_threads.size() ; i++){
    //    if(m_threads[i].joinable())
    //        m_threads[i].join();
    //}
    for(auto& t : m_threadss)
        if(t.joinable())
            t.join();
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
                of << "{\"Duration\": " << duration << "}" << std::endl;
                std::cout << "{\"Duration\": " << duration << "}" << std::endl;
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
    m_progress = 100;
    of << m_progress << std::endl;
    std::cout << 100 << std::endl;
    of.close();
    pclose(fp);
}

int Fenc::GetThumbnail(int ttime){
    char ss[16];
    sprintf(ss, "%02d:%02d:%02d", ttime/60/60, (ttime/60)%60, ttime%60);
    std::string option = " -ss ";
    option += ss;
    std::string cmd = "ffmpeg -v verbose -y -i ";
    cmd += m_srcFile;
    cmd += " -vframes 1 -strict -2 ";
    cmd += option + " ";
    cmd += m_outFile + " ";
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

void Fenc::Thumbnail(){

    std::string options;

    std::string cmd = "ffmpeg -v verbose -y -i ";
    cmd += m_srcFile;
    cmd += " -strict -2 ";
    cmd += " 2>&1";
    FILE* fp = popen(cmd.c_str(), "r");
    if(fp == NULL){
        std::cerr << "popen Error" << std::endl;
        return;
    }
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
            }
            lineStr = "";
        } else {
            lineStr.push_back(t);
        } 

    }
    pclose(fp);

    if(m_thumbnail_time < 0)
        m_thumbnail_time = 0;
    int ttime = m_thumbnail_time * duration / 100 ;
    GetThumbnail(ttime);
}

