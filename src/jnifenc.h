#ifndef JNIFENC_H
#define JNIFENC_H

#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include "fenc.h"
#include "JNITest.h"


class JNIFenc: public Fenc
{
    public:
        void Print();
};


#endif
