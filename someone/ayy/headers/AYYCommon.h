#pragma once
#include <glad/glad.h>
#include <iostream>
#include <string>

#define AYY_SAFE_DEL(pt) { \
    if(pt != nullptr)\
    {\
        delete pt;\
        pt = nullptr;\
    }\
}\


namespace ayy {
extern GLenum glCheckError_(const char *file, int line);
extern void Log(const char* log);
extern void Log(const std::string& log);
extern void Log(const char* format,...);
}

#define glCheckError() ayy::glCheckError_(__FILE__, __LINE__)

