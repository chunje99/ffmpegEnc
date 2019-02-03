#ifndef FENC_H
#define FENC_H

#include <iostream>
#include <thread>
#include <vector>
#include <fstream>

#define BUFF_SIZE 128

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
        int m_ttime;
        int m_thumbnail_time;
        std::vector<std::thread> m_threadss;
        //std::thread m_threads[10];
        //std::thread m_threads;

    public:
        /**
         *  C++ constructor and destructor
         */
        Fenc();
        ~Fenc();

        virtual void setSource(std::string src);
        std::string getSource();
        virtual void setTarget(std::string target);
        std::string getTarget();
        virtual void setPreset(std::string preset);
        std::string getPreset();
        int getProgress();
        virtual void setThumbnailTime(int thumbnail_time);
        int getThumbnailTime();

        virtual void StartEncode();
        virtual void StartThumbnail();
        virtual void Wait();

    private:
        void Encode();
        void Thumbnail();
        int GetThumbnail(int ttime);
};
#endif
