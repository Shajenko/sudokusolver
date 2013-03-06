#include "GameBoard.h"

GameBoard::GameBoard()
{

	Binit();
}

GameBoard::~GameBoard()
{
    //dtor
}

void GameBoard::Binit()
{
	for(int i=0;i<9;i++)
    {
		m_GameRows[i].Rinit();

        for(int j=0;j<9;j++)
        {
            m_Rows[i][j] = 0;
            m_Cols[i][j] = 0;
            m_Sectors[i][j] = 0;
        }
    }
}
