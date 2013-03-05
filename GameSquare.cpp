#include "GameSquare.h"

GameSquare::GameSquare()
{
    m_TrueVal = 0;
    m_Shown = false;
    m_GuessVal = 0;
    m_Sector = 0;
    for (int i = 0;i < 9;i++)
        m_Possibles[i] = 0;
}

GameSquare::~GameSquare()
{
    //dtor
}
