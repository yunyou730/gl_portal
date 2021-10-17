#include "MapSingleton.h"
#include "Util.h"

namespace crude
{

MapSingleton::~MapSingleton()
{
    ClearPreset();
}

void MapSingleton::InitDefaultValue()
{
    _rows = 20;
    _cols = 22;
    
    for(int i = 0;i < 100;i++)
    {
        int row = Util::random(0,_rows - 1);
        int col = Util::random(0,_cols - 1);
        
        AddPreset(EActorType::AT_Block,row,col);
    }
}

void MapSingleton::AddPreset(EActorType actorType,int row,int col)
{
    _presetRecords.push_back(new PresetRecord(actorType,row,col));
}

void MapSingleton::ClearPreset()
{
    for(auto it : _presetRecords)
    {
        delete it;
    }
    _presetRecords.clear();
}


}
