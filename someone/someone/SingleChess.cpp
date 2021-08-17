#include "SingleChess.h"
#include <cstdio>

void SingleChess::Init()
{
    InitGrids();
    InitPawns();
}

void SingleChess::Reset()
{
    
}

void SingleChess::Dump(Grid* theGrids[kRowCnt][kColCnt])
{
    printf("------- chess board ----- \n");
    for(int r = 0;r < kRowCnt;r++)
    {
        for(int c = 0;c < kColCnt;c++)
        {
            
        }
        printf("\n");
    }
}


void SingleChess::InitGrids()
{
    for(int row = 0;row < kRowCnt;row++)
    {
        for(int col = 0;col < kColCnt;col++)
        {
            grids[row][col].Init(row,col);
            
            
            bool bPlaceable = true;
            if((row == 0 && col == 0) ||
               (row == 0 && col == 1) ||
               (row == 0 && col == 5) ||
               (row == 0 && col == 6) ||
               (row == 1 && col == 0) ||
                  (row == 1 && col == 1) ||
                  (row == 1 && col == 5) ||
                  (row == 1 && col == 6) ||
               
               (row == 5 && col == 0) ||
                  (row == 5 && col == 1) ||
                  (row == 5 && col == 5) ||
                  (row == 5 && col == 6) ||

               (row == 6 && col == 0) ||
                  (row == 6 && col == 1) ||
                  (row == 6 && col == 5) ||
                  (row == 6 && col == 6)
               
               )
            {
                bPlaceable = false;
            }
            grids[row][col].SetAsPos(bPlaceable);
        }
    }
}

void SingleChess::InitPawns()
{
    
}

void SingleChess::PlacePawnToGrid(Pawn* pawn,int row,int col)
{
    
}

void SingleChess::MovePawnToGrid(Pawn* pawn,int row,int col)
{
    
}

void SingleChess::RemovePawnAtGrid(int row,int col)
{
    
}


void SingleChess::DoJob()
{
    Init();
    Reset();
    
//    Dump(&grids);
    
    Solve();
}

void SingleChess::Solve()
{
    
    
    // @todo
}
