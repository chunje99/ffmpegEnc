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
## PHP-CPP 설치  (php extention 라이브러리로 사용할때 필요)
참조 : http://www.php-cpp.com/documentation/install
```shell
$ git clone https://github.com/CopernicaMarketingSoftware/PHP-CPP.git
$ cd PHP-CPP
$ make
$ sudo make install
```

# ffmpegEnc 설치
```shell
git clone https://github.com/chunje99/ffmpegEnc
cd ffmpegEnc
autoreconf -i
./configure
make
sudo make install
```
## 사용방법
### 인코딩
```shell
Usage: ffmpegEnc srcfile outfile preset
preset : FHD (1920x1080, 4M)
         HD (1280x720, 2M)
         SD (720x480, 1M)
```
 process파일은 outfile.process에 작업상황 표시, 마지막 line 이 최종 progress
 ```
 ex) 
{"Duration": 82}
0
2
4
9
14
15
18
20
23
25
28
30
32
91
93
95
97
100
100
```
###  썸네일 추출
```shell
Usage             :   ffmpegThumb srcfile outfile thumbnail_time
thumbnail_time    :   전체 시간의 퍼센트 (0~100)
```
