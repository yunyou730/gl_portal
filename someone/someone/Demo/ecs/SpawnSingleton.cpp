#include "SpawnSingleton.h"

namespace crude
{
void SpawnSingleton::AddSpawnData(const SpawnParam& spawnParam)
{
    _toSpawn.push_back(spawnParam);
}

void SpawnSingleton::ClearData()
{
    _toSpawn.clear();
}

}
