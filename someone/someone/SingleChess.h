#pragma once


const int kInvalId = -1;
const int kInvalidRow = -1;
const int kInvalidCol = -1;
const int kRowCnt = 7;
const int kColCnt = 7;

typedef int PawnId;
//typedef int GridId;

class Grid
{
public:
    void Init(int atRow,int atCol)
    {
        row = atRow;
        col = atCol;
        SetFree();
    }
    
    void SetOccupy(PawnId pawnId)
    {
        occupyPawnId = pawnId;
    }
    
    void SetFree()
    {
        occupyPawnId = kInvalId;
    }
    
    void SetAsPos(bool bPlaceable)
    {
        bPos = bPlaceable;
    }
    
    bool IsBeOccupy()
    {
        return occupyPawnId != kInvalId;
    }
    
    int row;
    int col;
    bool bPos = true;
    PawnId occupyPawnId = kInvalId;
};

class Pawn
{
public:
    void Init(PawnId pawnId)
    {
        uuid = pawnId;
    }
    
    void SetCoord(int toRow,int toCol)
    {
        row = toRow;
        col = toCol;
    }
    
    void SetDead()
    {
        row = kInvalidRow;
        col = kInvalidCol;
    }
    
    int row = kInvalidRow;
    int col = kInvalidCol;
    
    PawnId uuid = kInvalId;
};

class SingleChess
{
public:
    void DoJob();

protected:
    void Init();
    void Reset();
    
    void InitGrids();
    void InitPawns();
    
    void PlacePawnToGrid(Pawn* pawn,int row,int col);
    void MovePawnToGrid(Pawn* pawn,int row,int col);
    void RemovePawnAtGrid(int row,int col);
    
    
    void Solve();
    void Dump(Grid* theGrids[kRowCnt][kColCnt]);
    
protected:
    Grid grids[kRowCnt][kColCnt];
    Pawn pawns[32];
};
