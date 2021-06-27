#pragma once

#define AYY_SAFE_DEL(pt) { \
    if(pt != nullptr)\
    {\
        delete pt;\
        pt = nullptr;\
    }\
}\
