ffmpegEnc
==============
# 사전 작업
## ffmpeg 설치

```shell
sudo yum install epel-release -y

sudo rpm --import http://li.nux.ro/download/nux/RPM-GPG-KEY-nux.ro

sudo rpm -Uvh http://li.nux.ro/download/nux/dextop/el7/x86_64/nux-dextop-release-0-5.el7.nux.noarch.rpm

sudo yum install ffmpeg ffmpeg-devel -y
```
## ffmpegEnc 설치
```shell
git clone https://github.com/chunje99/ffmpegEnc
cd ffmpegEnc
autoreconf -i
./configure
make
sudo make install
```
