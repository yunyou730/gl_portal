#pragma once
#include "Ayy.h"
#include "Define.h"
#include "SingletonComponent.h"
#include <vector>

namespace crude {
struct SpawnParam;
class SpawnSingleton : public SingletonComponent
{
public:
    void AddSpawnData(const SpawnParam& spawnParam);
    void ClearData();
public:
    std::vector<SpawnParam> _toSpawn;
};

struct SpawnParam
{
    EActorType  actorType;
    int     atRow = 0;
    int     atCol = 0;
    
    SpawnParam(EActorType actorType,int row,int col)
        :atRow(row),atCol(col),actorType(actorType)
    {}
    
    void operator=(const SpawnParam& other)
    {
        atRow = other.atRow;
        atCol = other.atCol;
        actorType = other.actorType;
    }
};


}

