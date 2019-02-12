#ifndef PYTHONFENC_H
#define PYTHONFENC_H

#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include "fenc.h"


/**
 *  Counter class that can be used for counting
 */
class PYTHONFenc: public Fenc
{
    public:
        void setSource(const char* src);
        std::string getSource();
};
/**
 *  Switch to C context to ensure that the get_module() function
 *  is callable by C programs (which the Zend engine is)
 */
extern "C" {
    PYTHONFenc* Fenc_new() { PYTHONFenc* p = new PYTHONFenc(); return p;}
    void Fenc_delete(PYTHONFenc* fenc) { delete fenc;}

    void Fenc_setSource(PYTHONFenc* fenc, const char* source)
    {fenc->setSource(source);}
    const char* Fenc_getSource(PYTHONFenc* fenc)
    { return fenc->getSource().c_str();}

    void Fenc_setTarget(PYTHONFenc* fenc, const char* target)
    {fenc->setTarget(target);}
    const char* Fenc_getTarget(PYTHONFenc* fenc)
    { return fenc->getTarget().c_str();}

    void Fenc_setPreset(PYTHONFenc* fenc, const char* preset)
    {fenc->setPreset(preset);}
    const char* Fenc_getPreset(PYTHONFenc* fenc)
    { return fenc->getPreset().c_str();}

    void Fenc_setThumbnailTime(PYTHONFenc* fenc, int thumbnail_time)
    {fenc->setThumbnailTime(thumbnail_time);}
    int Fenc_getThumbnailTime(PYTHONFenc* fenc)
    { return fenc->getThumbnailTime();}

    int Fenc_getProgress(PYTHONFenc* fenc)
    { return fenc->getProgress();}

    void Fenc_StartEncode(PYTHONFenc* fenc)
    { fenc->StartEncode();}

    void Fenc_StartThumbnail(PYTHONFenc* fenc)
    { fenc->StartThumbnail();}
}
#endif
