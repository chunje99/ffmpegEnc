ffmpegEnc
==============
# 사전 작업
## ffmpeg 설치

```shell
$ sudo yum install epel-release -y
$ sudo rpm --import http://li.nux.ro/download/nux/RPM-GPG-KEY-nux.ro
$ sudo rpm -Uvh http://li.nux.ro/download/nux/dextop/el7/x86_64/nux-dextop-release-0-5.el7.nux.noarch.rpm
$ sudo yum install ffmpeg ffmpeg-devel -y
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
$ git clone https://github.com/chunje99/ffmpegEnc
$ cd ffmpegEnc
$ autoreconf -i
$ ./configure
$ make
$ sudo make install
```
## 사용방법
### 인코딩
```shell
Usage     :   ffmpegEnc [options] sourcefile outfile
options   :
  -r  : 화면 비율 [ 854x480 , 1280x720, 1920x1080 ] (1280x720)
  -b  : 비트레이트 [ 1000K, 2000K, 4000K ] (2000K)
  -s  : 샘플레이트 [ 44100, 48000 ] (44100)
  -c  : 모노/스테레오 [ 1, 2 ] (2)
  -m  : 음소거 (0)
  -n  : 노멀라이즈  [ 0~100 ] (0)
  -l  : 로고  [ path ] ()
  -L  : 로고 위치 [ C (center), TR (top right)] (C)
  -S  : 인코딩 시작초 (0)
  -E  : 인코딩 종료초 (0)

  -h  : help
```
 process파일은 outfile.process에 작업상황 표시, 마지막 line 이 최종 progress
 ```
 ex) ./ffmpegEnc -r 1280x720 -b 1000K -l ~/다운로드/temp_1551245232624.-959209158.png -L C -S 10 -E 20 ~/다운로드/SampleVideo_1280x720_20mb.mp4 out.mp4
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
###  초당 썸네일 추출
```shell
Usage     :   ffmpegThumbAll srcfile outfile
outfile   :   path/name%d.jpeg ( name1.jpeg, name2.jpeg... )
```
outfile이름이 중요.. %d가 있어야 초값이 들어감

###  특정 썸네일 추출
```shell
Usage             :   ffmpegThumb srcfile outfile thumbnail_time
thumbnail_time    :   전체 시간의 퍼센트 (0~100)
```
