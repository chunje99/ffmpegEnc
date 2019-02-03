bin_PROGRAMS = ffmpegEnc ffmpegThumb

fencSOURCE = fenc.cpp
fencSOURCE += fenc.h

ffmpegEnc_SOURCES = ffmpegEnc.cpp
ffmpegEnc_SOURCES += ${fencSOURCE}
ffmpegEnc_LDADD = -lpthread

ffmpegThumb_SOURCES = ffmpegThumb.cpp
ffmpegThumb_SOURCES += ${fencSOURCE}
ffmpegThumb_LDADD = -lpthread

if LIB_PHPCPP
lib_LIBRARIES = libphpfenc.a
lib_LTLIBRARIES = libphpfenc.la

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
