#pragma once
#include <glad/glad.h>
#include <iostream>


#define AYY_SAFE_DEL(pt) { \
    if(pt != nullptr)\
    {\
        delete pt;\
        pt = nullptr;\
    }\
}\


namespace ayy {
extern GLenum glCheckError_(const char *file, int line);

}

#define glCheckError() ayy::glCheckError_(__FILE__, __LINE__)

