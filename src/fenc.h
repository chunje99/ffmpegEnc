#ifndef FENC_H
#define FENC_H

#include <iostream>
#include <thread>
#include <vector>
#include <fstream>


/**
 *  Counter class that can be used for counting
 */
class Fenc
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

        void setSource(std::string src);
        std::string getSource();
        void setTarget(std::string target);
        std::string getTarget();
        void setPreset(std::string preset);
        std::string getPreset();
        int getProgress();
        void StartEncode();
        void Encode();
        void Wait();
        void Print();
};
#endif
