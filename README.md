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
## 사용방법
```shell
Usage: ffmpegEnc srcfile outfile preset
preset : FHD (1920x1080, 4M)
         HD (1280x720, 2M)
         SD (720x480, 1M)
```
 process파일은 outfile.process에 작업상황 표시, 마지막 line 이 최종 progress
 ex) 
 0
2
4
7
9
12
14
15
18
20
23
25
28
30
32
34
36
39
41
43
47
51
52
54
57
58
60
64
67
69
71
75
76
79
81
84
86
87
90
91
93
95
97
100
100
