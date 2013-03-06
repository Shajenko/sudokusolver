#include "GameRow.h"

GameRow::GameRow()
{
	Rinit();
}

GameRow::~GameRow()
{

    //dtor
}

void GameRow::Rinit()
{
	for(int i=0;i<9;i++)
    {
        m_taken[i] = 0;
        m_square[i].Sinit();
    }
}
