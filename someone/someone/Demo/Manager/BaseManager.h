#pragma once
#include "Ayy.h"

namespace crude
{
class BaseManager
{
public:
    virtual ~BaseManager() {}    
    virtual void Initialize() = 0;
    
    template<typename ManagerClass>
    static ManagerClass* GetInstance()
    {
        static ManagerClass instance;
        return &instance;
    }
protected:
    BaseManager() {}
};


}
