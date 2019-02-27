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
        std::vector<std::thread> m_threadss;
        std::string m_srcFile;
        std::string m_outFile;
        std::string m_preset;
        std::string m_options;
        int m_progress;
        int m_jobcnt;
        int m_ttime;
        int m_thumbnailTime;

        std::string m_ratio;
        std::string m_bitRate;
        std::string m_fileFormat;
        int m_sampleRate;
        int m_channel;
        int m_mute;
        int m_normalize;
        int m_fix;
        std::string m_logo;
        std::string m_logoLocation;

    public:
        /**
         *  C++ constructor and destructor
         */
        Fenc();
        virtual ~Fenc();

        virtual void setSource(std::string src);
        std::string getSource();
        virtual void setTarget(std::string target);
        std::string getTarget();
        virtual void setPreset(std::string preset);
        std::string getPreset();
        int getProgress();
        virtual void setThumbnailTime(int thumbnailTime);
        int getThumbnailTime();
        virtual void setRatio(std::string ratio);
        std::string getRatio();
        virtual void setBitRate(std::string bitRate);
        std::string getBitRate();
        virtual void setFileFormat(std::string fileFormat);
        std::string getFileFormat();
        virtual void setSampleRate(int sampleRate);
        int getSampleRate();
        virtual void setChannel(int channel);
        int getChannel();
        virtual void setMute(int mute);
        int getMute();
        virtual void setNormalize(int normalize);
        int getNormalize();
        virtual void setFix(int fix);
        int getFix();
        virtual void setLogo(std::string logo);
        std::string getLogo();
        virtual void setLogoLocation(std::string logoLocation);
        std::string getLogoLocation();


        virtual void StartEncode();
        virtual void StartThumbnail();
        virtual void StartThumbnailAll(); ///초당 이미지
        virtual void Wait();

    private:
        void Encode();
        void Thumbnail();
        void ThumbnailAll();
        int GetThumbnail(int ttime);
};
#endif
