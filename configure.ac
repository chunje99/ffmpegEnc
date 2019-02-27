#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([ffmpegEnc], [1.0], [chunje99@gmail.com])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src])
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_MACRO_DIRS([m4])

# Checks for programs.
LT_INIT
AC_PROG_CC
AC_PROG_CXX
AC_PROG_RANLIB
AC_PROG_LIBTOOL

# AC_CANONICAL_HOST is needed to access the 'host_os' variable    
AC_CANONICAL_HOST

build_linux=no
build_windows=no
build_mac=no

# Detect the target system
case "${host_os}" in
    linux*)
        build_linux=yes
        ;;
    cygwin*|mingw*)
        build_windows=yes
        ;;
    darwin*)
        build_mac=yes
        ;;
    *)
        AC_MSG_ERROR(["OS $host_os is not supported"])
        ;;
esac
AC_MSG_NOTICE([${host_os}])
AC_MSG_NOTICE([${host}])

# Pass the conditionals to automake
AM_CONDITIONAL([LINUX], [test "$build_linux" = "yes"])
AM_CONDITIONAL([WINDOWS], [test "$build_windows" = "yes"])
AM_CONDITIONAL([OSX], [test "$build_mac" = "yes"])

# Checking for warning flags on the compiler
CXXFLAGS="$CXXFLAGS -std=c++11"
# Checks for libraries.
# check PHP-CPP
AC_CHECK_LIB([phpcpp], [main], [
              AC_MSG_NOTICE([libphpcpp OK])
              phpcpp=true
              ], [
              AC_MSG_NOTICE([unable to find libphpcpp])
              phpcpp=false
              ] )
AM_CONDITIONAL([LIB_PHPCPP], [test "x$phpcpp" = "xtrue"])
# Checks for header files.
# check jni.h
jni=false
#JAVAHOME="/usr/java/default"
##JAVAHOME="/usr/lib/jvm/default-java"
#AC_CHECK_FILE(["${JAVAHOME}/include/jni.h"], [
#               AC_MSG_NOTICE([jni.h OK])
#               jni=true
#               AC_SUBST(JNI_LOC, "${JAVAHOME}/include")
#               AC_SUBST(JNI_LOC_SUB, "${JAVAHOME}/include/linux")
#               ], [
#                   JAVAHOME="/Library/Java/JavaVirtualMachines/openjdk-11.0.2.jdk/Contents/Home"
#                   AC_CHECK_FILE(["${JAVAHOME}/include/jni.h"], [
#                                  AC_MSG_NOTICE([Mac jni.h OK])
#                                  jni=true
#                                  AC_SUBST(JNI_LOC, "${JAVAHOME}/include")
#                                  AC_SUBST(JNI_LOC_SUB, "${JAVAHOME}/include/darwin") ], [
#                                                                                          AC_MSG_NOTICE([unable to find jni.h])] ) ] )
JAVAHOME="/Library/Java/JavaVirtualMachines/openjdk-11.0.2.jdk/Contents/Home"
AC_CHECK_FILE(["${JAVAHOME}/include/jni.h"], [
               jni=true
               AC_SUBST(JNI_LOC, "${JAVAHOME}/include")
               AC_SUBST(JNI_LOC_SUB, "${JAVAHOME}/include/darwin") ], [ ])
JAVAHOME="/usr/lib/jvm/default-java"
AC_CHECK_FILE(["${JAVAHOME}/include/jni.h"], [
               jni=true
               AC_SUBST(JNI_LOC, "${JAVAHOME}/include")
               AC_SUBST(JNI_LOC_SUB, "${JAVAHOME}/include/linux") ], [ ])
JAVAHOME="/usr/java/default"
AC_CHECK_FILE(["${JAVAHOME}/include/jni.h"], [
               jni=true
               AC_SUBST(JNI_LOC, "${JAVAHOME}/include")
               AC_SUBST(JNI_LOC_SUB, "${JAVAHOME}/include/linux") ], [ ])

AS_IF([test "x$jni" = "xtrue"], [ AC_MSG_NOTICE([jni.h OK]) ], [ AC_MSG_NOTICE([unable to find jni.h]) ])
AM_CONDITIONAL([LIB_JNI], [test "x$jni" = "xtrue"])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
