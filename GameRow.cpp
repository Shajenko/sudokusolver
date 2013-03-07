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
	m_taken.clear();
	for(int i=0;i<9;i++)
    {
        m_square[i].Sinit();
    }
}
