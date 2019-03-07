#include <iostream>
#include <unistd.h>
#include "fenc.h"

std::string g_ratio = "1280x720";
std::string g_bitRate= "2000K";
std::string g_fileFormat = "mp4";
int g_sampleRate = 44100;
int g_channel = 2;
int g_mute = 0;
int g_normalize = 0;
int g_fix = 0;
std::string g_logo = "";
std::string g_logoLocation = "C";
int g_enc_start = 0;
int g_enc_end = 0;

void Usage(){
    std::cout << "Usage     :   ffmpegEnc [options] sourcefile outfile" << std::endl;
    std::cout << "options   : " << std::endl;
    std::cout << "  -r  : 화면 비율 [ 854x480 , 1280x720, 1920x1080 ] (" << g_ratio << ")" << std::endl;
    std::cout << "  -x  : 화면 비율 고정 (" << g_fix << ")" << std::endl;
    std::cout << "  -b  : 비트레이트 [ 1000K, 2000K, 4000K ] (" << g_bitRate << ")" << std::endl;
    std::cout << "  -f  : 파일포멧 [ mp4, mkv ] (" << g_fileFormat << ")" << std::endl;
    std::cout << "  -s  : 샘플레이트 [ 44100, 48000 ] (" << g_sampleRate << ")" << std::endl;
    std::cout << "  -c  : 모노/스테레오 [ 1, 2 ] (" << g_channel << ")" << std::endl;
    std::cout << "  -m  : 음소거 (" << g_mute << ")" << std::endl;
    std::cout << "  -n  : 노멀라이즈  [ 0~100 ] (" << g_normalize << ")" << std::endl;
    std::cout << "  -l  : 로고  [ path ] (" << g_logo << ")" << std::endl;
    std::cout << "  -L  : 로고 위치 [ C (center), TR (top right)] (" << g_logoLocation << ")" << std::endl;
    std::cout << "  -S  : 인코딩 시작초 (" << g_enc_start << ")" << std::endl;
    std::cout << "  -E  : 인코딩 종료초 (" << g_enc_end << ")" << std::endl;
    std::cout << "  -h  : help" << std::endl;
    exit(0);
}

int main(int argc, char*argv[]){

    int opt, remain_opt;
    while((opt = getopt(argc, argv, "r:b:f:s:c:mxn:l:L:hS:E:")) != -1){
        switch(opt){
            case 'r' : /// 화면 비율
                g_ratio = optarg;
                break; 
            case 'b' : /// bit_rate
                g_bitRate = optarg;
                break;
            case 'f' : /// file_format
                g_fileFormat = optarg;
                break;
            case 's' : /// sample_rate
                g_sampleRate = atoi(optarg);
                break;
            case 'c' : /// channel
                g_channel = atoi(optarg);
                break;
            case 'm' : /// mute
                g_mute = 1;
                break;
            case 'x' : /// 비율 고정 
                g_fix = 1;
                break;
            case 'n' : /// nomalrize
                g_normalize = atoi(optarg);
                break;
            case 'l' : /// logo path
                g_logo = optarg;
                break;
            case 'L' : /// logo location
                g_logoLocation = optarg;
                break;
            case 'S' : /// enc start
                g_enc_start = atoi(optarg);
            case 'E' : /// enc end
                g_enc_end = atoi(optarg);
                break;
            case 'h' :
            default :
                Usage();
                break;
        }
    }

    remain_opt = argc - optind;

    if(remain_opt != 2)
        Usage();

    std::string source = argv[argc-2];
    std::string target = argv[argc-1];

    std::cout << "source : " << source << std::endl;
    std::cout << "target : " << target << std::endl;

    Fenc fenc;
    fenc.setSource(source);
    fenc.setTarget(target);
    //fenc.setPreset(argv[3]);
    fenc.setRatio(g_ratio);
    fenc.setBitRate(g_bitRate);
    fenc.setFileFormat(g_fileFormat);
    fenc.setSampleRate(g_sampleRate);
    fenc.setChannel(g_channel);
    fenc.setMute(g_mute);
    fenc.setNormalize(g_normalize);
    fenc.setFix(g_fix);
    fenc.setLogo(g_logo);
    fenc.setLogoLocation(g_logoLocation);
    fenc.setEncStart(g_enc_start);
    fenc.setEncEnd(g_enc_end);

    fenc.StartEncode();
    return 0;
}
