#include <iostream>
#include "fenc.h"

void Usage(){
    std::cout << "Usage             :   ffmpegThumb srcfile outfile thumbnail_time" << std::endl;
    std::cout << "thumbnail_time    :   전체 시간의 퍼센트 (0~100)" << std::endl;
    exit(0);
}

int main(int argc, char*argv[]){
    if(argc != 4)
        Usage();
    Fenc fenc;
    fenc.setSource(argv[1]);
    fenc.setTarget(argv[2]);
    fenc.setThumbnailTime(atoi(argv[3]));
    fenc.StartThumbnail();
    return 0;
}
