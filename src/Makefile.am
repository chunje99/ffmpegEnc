bin_PROGRAMS = ffmpegEnc ffmpegThumb
lib_LIBRARIES =
lib_LTLIBRARIES =

fencSOURCE = fenc.cpp
fencSOURCE += fenc.h

ffmpegEnc_SOURCES = ffmpegEnc.cpp
ffmpegEnc_SOURCES += ${fencSOURCE}
ffmpegEnc_LDADD = -lpthread

ffmpegThumb_SOURCES = ffmpegThumb.cpp
ffmpegThumb_SOURCES += ${fencSOURCE}
ffmpegThumb_LDADD = -lpthread

if LIB_PHPCPP
lib_LIBRARIES += libphpfenc.a
lib_LTLIBRARIES += libphpfenc.la

libphpfenc_a_SOURCES = ${fencSOURCE}
libphpfenc_a_SOURCES += phpfenc.cpp
libphpfenc_a_SOURCES += phpfenc.h

libphpfenc_a_CFLAGS = ${AM_CFLAGS}
libphpfenc_a_CXXFLAGS = ${AM_CXXFLAGS}
libphpfenc_a_CXXFLAGS += -IPHP-CPP
libphpfenc_a_CXXFLAGS += -static
libphpfenc_a_CXXFLAGS += -lphpcpp -lpthread
#libphpfenc_a_LIBADD = -lphpcpp -lpthread
#libphpfenc_a_LIBADD = $(LIBOBJS) $(ALLOCA)

libphpfenc_la_SOURCES = ${fencSOURCE}
libphpfenc_la_SOURCES += phpfenc.cpp
libphpfenc_la_SOURCES += phpfenc.h

libphpfenc_la_CFLAGS = ${AM_CFLAGS}
libphpfenc_la_CXXFLAGS = ${AM_CXXFLAGS}
libphpfenc_la_CXXFLAGS += -IPHP-CPP
libphpfenc_la_LIBADD = -lphpcpp -lpthread
endif

#lib_python
lib_LIBRARIES += libpythonfenc.a
lib_LTLIBRARIES += libpythonfenc.la

libpythonfenc_a_SOURCES = ${fencSOURCE}
libpythonfenc_a_SOURCES += pythonfenc.cpp
libpythonfenc_a_SOURCES += pythonfenc.h

libpythonfenc_a_CFLAGS = ${AM_CFLAGS}
libpythonfenc_a_CXXFLAGS = ${AM_CXXFLAGS}
libpythonfenc_a_CXXFLAGS += -lpthread

libpythonfenc_la_SOURCES = ${fencSOURCE}
libpythonfenc_la_SOURCES += pythonfenc.cpp
libpythonfenc_la_SOURCES += pythonfenc.h

libpythonfenc_la_CFLAGS = ${AM_CFLAGS}
libpythonfenc_la_CXXFLAGS = ${AM_CXXFLAGS}
libpythonfenc_la_CXXFLAGS += -shared
libpythonfenc_la_CXXFLAGS += -fPIC
libpythonfenc_la_LIBADD = -lpthread

#lib_jni
lib_LIBRARIES += libjnifenc.a
lib_LTLIBRARIES += libjnifenc.la

JAVA_HOME = /usr/lib/jvm/java-8-openjdk-amd64


libjnifenc_a_SOURCES = ${fencSOURCE}
libjnifenc_a_SOURCES += jnifenc.cpp
libjnifenc_a_SOURCES += jnifenc.h
libjnifenc_a_SOURCES += JNITest.h

libjnifenc_a_CFLAGS = ${AM_CFLAGS}
libjnifenc_a_CXXFLAGS = ${AM_CXXFLAGS}
libjnifenc_a_CXXFLAGS += -lpthread
libjnifenc_a_CXXFLAGS += -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux

libjnifenc_la_SOURCES = ${fencSOURCE}
libjnifenc_la_SOURCES += jnifenc.cpp
libjnifenc_la_SOURCES += jnifenc.h
libjnifenc_la_SOURCES += JNITest.h

libjnifenc_la_CFLAGS = ${AM_CFLAGS}
libjnifenc_la_CXXFLAGS = ${AM_CXXFLAGS}
libjnifenc_la_CXXFLAGS += -shared
libjnifenc_la_CXXFLAGS += -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux
libjnifenc_la_CXXFLAGS += -fPIC
libjnifenc_la_LIBADD = -lpthread
