#include "GameRow.h"

GameRow::GameRow()
{
	Rinit();
}

GameRow GameRow::operator= (const GameRow& gr)
{
	unsigned int i;
	GameRow A;

	A.m_taken.clear();
	for(i=1;i<=9;i++)
	{
		if(gr.m_taken.find(i) != gr.m_taken.end())
			this->m_taken.insert(i);
		A.m_square[i] = gr.m_square[i];
	}

	return A;
}

void GameRow::Copy(const GameRow& gr)
{
    unsigned int i;

	this->m_taken.clear();
	for(i=1;i<=9;i++)
	{
		if(gr.m_taken.find(i) != gr.m_taken.end())
			this->m_taken.insert(i);
		this->m_square[i].Copy(gr.m_square[i]);
	}
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

void GameRow::SetCol()
{
	for(int i=0;i<9;i++)
	{
		m_square[i].SetCol(i);
	}

}
