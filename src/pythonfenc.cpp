#include "pythonfenc.h"

void PYTHONFenc::setSource(const char* src){
    std::cout << src << std::endl;
    Fenc::setSource(src);
}

std::string PYTHONFenc::getSource(){
    std::string s = Fenc::getSource();
    std::cout << s << std::endl;
    return s;
}
