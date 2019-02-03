#include "phpfenc.h"

void PHPFenc::setSource(Php::Parameters &params){
    for(auto t : params)
        Fenc::setSource(t.stringValue());
}
void PHPFenc::setTarget(Php::Parameters &params){
    for(auto t : params)
        Fenc::setTarget(t.stringValue());
}
void PHPFenc::setPreset(Php::Parameters &params){
    for(auto t : params)
        Fenc::setPreset(t.stringValue());
}
void PHPFenc::setThumbnailTime(Php::Parameters &params){
    for(auto t : params)
        Fenc::setThumbnailTime(t.numericValue());
}

Php::Value PHPFenc::getProgress(){
    return Fenc::getProgress();
}

Php::Value PHPFenc::getSource(){
    return Fenc::getSource();
}
Php::Value PHPFenc::getTarget(){
    return Fenc::getTarget();
}
Php::Value PHPFenc::getPreset(){
    return Fenc::getPreset();
}
Php::Value PHPFenc::getThumbnailTime(){
    return Fenc::getThumbnailTime();
}

void PHPFenc::StartEncode(){
    Fenc::StartEncode();
}
void PHPFenc::StartThumbnail(){
    Fenc::StartThumbnail();
}
void PHPFenc::Wait(){
    Fenc::Wait();
}
