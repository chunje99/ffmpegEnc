#ifndef PHPFENC_H
#define PHPFENC_H

#include <iostream>
#include <thread>
#include <phpcpp.h>
#include <vector>
#include <fstream>
#include "fenc.h"


/**
 *  Counter class that can be used for counting
 */
class PHPFenc: public Fenc, public Php::Base
{
    private:

    public:
        PHPFenc() = default;
        PHPFenc(PHPFenc const&) = delete;
        virtual ~PHPFenc() = default;

        virtual void setSource(Php::Parameters &params);
        Php::Value getSource();

        virtual void setTarget(Php::Parameters &params);
        Php::Value getTarget();

        virtual void setPreset(Php::Parameters &params);
        Php::Value getPreset();

        virtual void setThumbnailTime(Php::Parameters &params);
        Php::Value getThumbnailTime();

        Php::Value getProgress();

        virtual void StartEncode();
        virtual void StartThumbnail();
        //void Encode();
        virtual void Wait();
        //void Print();

};
/**
 *  Switch to C context to ensure that the get_module() function
 *  is callable by C programs (which the Zend engine is)
 */
extern "C" {
    /**
     *  Startup function that is called by the Zend engine 
     *  to retrieve all information about the extension
     *  @return void*
     */
    PHPCPP_EXPORT void *get_module() {
        // create static instance of the extension object
        static Php::Extension myExtension("my_extension", "1.0");

        // description of the class so that PHP knows which methods are accessible
        Php::Class<PHPFenc> fenc("PHPFenc");
        fenc.method<&PHPFenc::setSource>     ("setSource",{ Php::ByVal("src", Php::Type::String)});
        fenc.method<&PHPFenc::getSource>     ("getSource");
        fenc.method<&PHPFenc::setTarget>     ("setTarget",{ Php::ByVal("tar", Php::Type::String)});
        fenc.method<&PHPFenc::getTarget>     ("getTarget");
        fenc.method<&PHPFenc::setPreset>     ("setPreset",{ Php::ByVal("preset", Php::Type::String)});
        fenc.method<&PHPFenc::getPreset>     ("getPreset");
        fenc.method<&PHPFenc::setThumbnailTime>     ("setThumbnailTime",{ Php::ByVal("ttime", Php::Type::Numeric)});
        fenc.method<&PHPFenc::getThumbnailTime>     ("getThumbnailTime");
        fenc.method<&PHPFenc::getProgress>   ("getProgress");
        fenc.method<&PHPFenc::StartEncode>   ("StartEncode");
        fenc.method<&PHPFenc::StartThumbnail>   ("StartThumbnail");
        fenc.method<&PHPFenc::Wait>          ("Wait");

        // add the class to the extension
        myExtension.add(std::move(fenc));

        // return the extension
        return myExtension;
    }
}
#endif
