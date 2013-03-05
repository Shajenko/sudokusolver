#include "GameRow.h"

GameRow::GameRow()
{
    for(int i=0;i<9;i++)
    {
        m_taken[i] = 0;
    }
}

GameRow::~GameRow()
{

    //dtor
}
