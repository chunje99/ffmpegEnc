#include <iostream>
#include "fenc.h"

void Usage(){
    std::cout << "Usage     :   ffmpegThumbAll srcfile outfile " << std::endl;
    std::cout << "outfile   :   name%d.jpeg ( name1.jpeg, name2.jpeg... )" << std::endl;
    exit(0);
}

int main(int argc, char*argv[]){
    if(argc != 3)
        Usage();
    Fenc fenc;
    fenc.setSource(argv[1]);
    fenc.setTarget(argv[2]);
    fenc.StartThumbnailAll();
    return 0;
}
