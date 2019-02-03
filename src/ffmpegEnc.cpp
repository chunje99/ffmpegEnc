#include <iostream>
#include "fenc.h"

void Usage(){
    std::cout << "Usage             :   ffmpegEnc srcfile outfile preset" << std::endl;
    std::cout << "preset            :   FHD (1920x1080, 4M)" << std::endl;
    std::cout << "                      HD (1280x720, 2M)" << std::endl;
    std::cout << "                      SD (720x480, 1M)" << std::endl;
    exit(0);
}

int main(int argc, char*argv[]){
    if(argc != 4)
        Usage();

    Fenc fenc;
    fenc.setSource(argv[1]);
    fenc.setTarget(argv[2]);
    fenc.setPreset(argv[3]);

    fenc.StartEncode();
    return 0;
}
