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
AC_CHECK_FILE(["/usr/lib/jvm/default-java/include/jni.h"], [
              AC_MSG_NOTICE([jni.h OK])
              jni=true
              AC_SUBST(JNI_LOC, "/usr/lib/jvm/default-java/include")
              AC_SUBST(JNI_LOC_SUB, "/usr/lib/jvm/default-java/include/linux")
              ], [
                  AC_CHECK_FILE(["/Library/Java/JavaVirtualMachines/openjdk-11.0.2.jdk/Contents/Home/include/jni.h"], [
              AC_MSG_NOTICE([Mac jni.h OK])
             jni=true
             AC_SUBST(JNI_LOC, "/Library/Java/JavaVirtualMachines/openjdk-11.0.2.jdk/Contents/Home/include")
             AC_SUBST(JNI_LOC_SUB, "/Library/Java/JavaVirtualMachines/openjdk-11.0.2.jdk/Contents/Home/include/darwin") ], [
             AC_MSG_NOTICE([unable to find jni.h])] ) ] )

AM_CONDITIONAL([LIB_JNI], [test "x$jni" = "xtrue"])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
