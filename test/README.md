# test lib php
```shell
➜  test git:(master) ✗ cat t.ini
;extension=/home/ho80/devel/git/ffmpegEnc/lib/libphpfenc.so
extension=../lib/libphpfenc.so

➜  test git:(master) ✗ php -c t.ini t.php
```
# test lib python
```shell
➜  test git:(master) ✗ python test.py
```
# test lib java
```shell
➜  test git:(master) ✗ javac JNITest.java
➜  test git:(master) ✗ java -Djava.library.path=../lib JNITest
```
