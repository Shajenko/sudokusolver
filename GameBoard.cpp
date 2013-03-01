#include "GameBoard.h"

GameBoard::GameBoard()
{
    m_Squares = new GameSquare [81];
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            m_Rows[i][j] = 0;
            m_Cols[i][j] = 0;
            m_Sectors[i][j] = 0;
        }
}

GameBoard::~GameBoard()
{
    //dtor
}
