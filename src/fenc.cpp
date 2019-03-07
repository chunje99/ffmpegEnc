#include "fenc.h"
#include <time.h>
#include <unistd.h>

Fenc::Fenc()
    : m_jobcnt(0)
      , m_normalize(0)
      , m_enc_start(0)
      , m_enc_end(0)
{}

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
    return m_thumbnailTime;
}
void Fenc::setThumbnailTime(int thumbnailTime){
    m_thumbnailTime = thumbnailTime;
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

void Fenc::setRatio(std::string ratio){
    m_ratio = ratio;
}
std::string Fenc::getRatio(){
    return m_ratio;
}
void Fenc::setBitRate(std::string bitRate){
    m_bitRate = bitRate;
}
std::string Fenc::getBitRate(){
    return m_bitRate;
}
void Fenc::setFileFormat(std::string fileFormat){
    m_fileFormat = fileFormat;
}
std::string Fenc::getFileFormat(){
    return m_fileFormat;
}
void Fenc::setSampleRate(int sampleRate){
    m_sampleRate = sampleRate;
}
int Fenc::getSampleRate(){
    return m_sampleRate;
}
void Fenc::setChannel(int channel){
    m_channel = channel;
}
int Fenc::getChannel(){
    return m_channel;
}
void Fenc::setMute(int mute){
    m_mute = mute;
}
int Fenc::getMute(){
    return m_mute;
}
void Fenc::setNormalize(int normalize){
    m_normalize = normalize;
}
int Fenc::getNormalize(){
    return m_normalize;
}
void Fenc::setFix(int fix){
    m_fix = fix;
}
int Fenc::getFix(){
    return m_fix;
}
void Fenc::setLogo(std::string logo){
    m_logo = logo;
}
std::string Fenc::getLogo(){
    return m_logo;
}
void Fenc::setLogoLocation(std::string logoLocation){
    m_logoLocation = logoLocation;
}
std::string Fenc::getLogoLocation(){
    return m_logoLocation;
}
void Fenc::setEncStart(int encStart){
    m_enc_start= encStart;
}
int Fenc::getEncStart(){
    return m_enc_start;
}
void Fenc::setEncEnd(int encEnd){
    m_enc_end = encEnd;
}
int Fenc::getEncEnd(){
    return m_enc_end;
}

void Fenc::StartEncode(){
    m_threadss.emplace_back(std::thread(&Fenc::Encode, this));
    m_jobcnt++;
}

void Fenc::StartThumbnail(){
    m_threadss.emplace_back(std::thread(&Fenc::Thumbnail, this));
    m_jobcnt++;
}

void Fenc::StartThumbnailAll(){
    m_threadss.emplace_back(std::thread(&Fenc::ThumbnailAll, this));
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
    /*
    if(m_preset == "FHD")
        m_options = " -s 1920x1080 -b:v 4M -b:a 512k ";
    else if(m_preset == "HD")
        m_options = " -s 1280x720 -b:v 2M -b:a 256k ";
    else if(m_preset == "SD")
        m_options = " -s 720x480 -b:v 1M -b:a 128k ";
    else
        m_options = " -s 1280x720 -b:v 2M -b:a 256k ";
    */
    m_options = " -s " + m_ratio;
    m_options += " -b:v " + m_bitRate;
    if(m_mute){
        m_options += " -an ";
    } else{
        m_options += " -ar " + std::to_string(m_sampleRate);
        m_options += " -ac " + std::to_string(m_channel);
    }
    if(m_normalize > 0 && m_normalize <= 100){
        m_options += " -af dynaudnorm=r=" + std::to_string(m_normalize / 100) + "." + std::to_string((m_normalize%100)/10);
    }

    if(m_enc_start > 0){
        char tbuf[100] = {0};
        sprintf(tbuf, "%02d:%02d:%02d", m_enc_start/3600, (m_enc_start/60)%60, m_enc_start%60);
        std::string tStr = tbuf;
        m_options += " -ss " + tStr;
    }
    if(m_enc_end > 0){
        char tbuf[100] = {0};
        sprintf(tbuf, "%02d:%02d:%02d", m_enc_end/3600, (m_enc_end/60)%60, m_enc_end%60);
        std::string tStr = tbuf;
        m_options += " -to " + tStr;
    }

    std::string cmd = "ffmpeg -v verbose -y -i ";
    cmd += m_srcFile + " ";
    if(m_logo != "") {
        if(m_logoLocation == "TR")
            cmd += " -i " + m_logo + " -filter_complex \"overlay=(main_w-overlay_w-5):5\" ";
        else ///center
            cmd += " -i " + m_logo + " -filter_complex \"overlay=(main_w-overlay_w)/2:(main_h-overlay_h)/2\" ";
    }
    cmd += m_options + " -strict -2 ";
    cmd += m_outFile;
    cmd += " 2>&1";
    std::cout << cmd << std::endl;
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
    int duration = 0, process = 0;
    m_progress = 0;
    size_t pos;
    int h,m,s,ms;
    while(1){
        t = fgetc(fp);
        if(t == EOF) break;
        if(t == '\n' || t == '\r') {
            if((pos = lineStr.find("Duration:")) != std::string::npos && duration == 0 ){
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

    if(m_thumbnailTime < 0)
        m_thumbnailTime = 0;
    int ttime = m_thumbnailTime * duration / 100 ;
    GetThumbnail(ttime);
}

void Fenc::ThumbnailAll(){
    std::string cmd = "ffmpeg -v verbose -y -i ";
    cmd += m_srcFile;
    cmd += " -an -vf fps=fps=1 -qscale:v 2 ";
    cmd += m_outFile + " ";
    cmd += " 2>&1";
    FILE* fp = popen(cmd.c_str(), "r");
    if(fp == NULL){
        std::cerr << "popen Error" << std::endl;
        return ;
    }
    char t;
    while(1){
        t = fgetc(fp);
        if(t == EOF) break;
    }
    pclose(fp);
    return ;
}
