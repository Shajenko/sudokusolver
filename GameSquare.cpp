#include "GameSquare.h"

GameSquare::GameSquare()
{
	Sinit();
}

GameSquare::~GameSquare()
{
    //dtor
}

void GameSquare::Sinit()
{
	m_TrueVal = 0;
    m_Shown = false;
    m_GuessVal = 0;
    m_Sector = 0;
    for (int i = 0;i < 9;i++)
        m_Possibles.insert(i+1);
}
