#ifndef FENC_H
#define FENC_H

#include <iostream>
#include <thread>
#include <phpcpp.h>
#include <vector>
#include <fstream>


//namespace marco
//{
    /**
     *  Counter class that can be used for counting
     */
class Fenc: public Php::Base
{
    private:
        /**
         *  The initial value
         *  @var    int
         */
        std::string m_srcFile;
        std::string m_outFile;
        std::string m_preset;
        std::string m_options;
        int m_progress;
        int m_jobcnt;
        std::thread m_threads[10];

    public:
        /**
         *  C++ constructor and destructor
         */
        Fenc() = default;
        virtual ~Fenc() = default;

        void setSource(Php::Parameters &params);
        void setSource(std::string src);
        Php::Value getSource();
        void setTarget(Php::Parameters &params);
        void setTarget(std::string target);
        Php::Value getTarget();
        void setPreset(Php::Parameters &params);
        void setPreset(std::string preset);
        Php::Value getPreset();
        Php::Value getProgress();
        void StartEncode();
        void Encode();
        void Wait();
        void Print();

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
        Php::Class<Fenc> fenc("Fenc");
        fenc.method<&Fenc::setSource>     ("setSource",{ Php::ByVal("src", Php::Type::String)});
        fenc.method<&Fenc::getSource>     ("getSource");
        fenc.method<&Fenc::setTarget>     ("setTarget",{ Php::ByVal("tar", Php::Type::String)});
        fenc.method<&Fenc::getTarget>     ("getTarget");
        fenc.method<&Fenc::setPreset>     ("setPreset",{ Php::ByVal("preset", Php::Type::String)});
        fenc.method<&Fenc::getPreset>     ("getPreset");
        fenc.method<&Fenc::getProgress>   ("getProgress");
        fenc.method<&Fenc::Encode>        ("Encode");
        fenc.method<&Fenc::StartEncode>   ("StartEncode");
        fenc.method<&Fenc::Wait>          ("Wait");

        // add the class to the extension
        myExtension.add(std::move(fenc));

        // return the extension
        return myExtension;
    }
}
//}
#endif
