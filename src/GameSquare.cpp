#include "GameSquare.h"

GameSquare::GameSquare()
{
	Sinit();
}

GameSquare GameSquare::operator= (const GameSquare& gs)
{
	GameSquare A;

	A.m_Val = gs.m_Val;
	A.m_Col = gs.m_Col;
	A.m_Row = gs.m_Row;
	A.m_Sector = gs.m_Sector;
	A.m_Shown = gs.m_Shown;
	A.m_Possibles = gs.m_Possibles;

	return A;
}

void GameSquare::Copy(const GameSquare& gs)
{
	this->m_Val = gs.m_Val;
	this->m_Col = gs.m_Col;
	this->m_Row = gs.m_Row;
	this->m_Sector = gs.m_Sector;
	this->m_Shown = gs.m_Shown;
	this->m_Possibles = gs.m_Possibles;
}

GameSquare::~GameSquare()
{
    //dtor
}

void GameSquare::Sinit()
{
	m_Val = 0;
    m_Shown = false;
    m_Sector = 0;
    for (int i = 0;i < 9;i++)
        m_Possibles.insert(i+1);
}

void GameSquare::ResetPossibles()
{
	for (int i = 0;i < 9;i++)
        m_Possibles.insert(i+1);
}
