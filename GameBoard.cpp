#include "GameBoard.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>

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
	for(int row=0;row<9;row++)
    {
		m_GameRows[row].Rinit();

		m_Rows[row].clear();
		m_Sectors[row].clear();
		m_Cols[row].clear();
        for(int col=0;col<9;col++)
        {
            // todo - set sector for each square
            m_GameRows[row].m_square[col].SetSector((row/3) * 3 + (col/3));
        }
    }
}

bool GameBoard::SetSquareTrue(unsigned int val, int row, int col)
{
	int sec;
	GameSquare * sq;
	sq = &m_GameRows[row].m_square[col];
	sec = sq->GetSector();


	//todo - check if value is impossible
	if (m_Rows[row].find(val) != m_Rows[row].end() &&
		m_Cols[col].find(val) != m_Cols[col].end() &&
		m_Sectors[sec].find(val) != m_Sectors[sec].end() &&
		sq->GetTrueVal() == 0 &&
		val > 0 &&
		val < 10)
	{
		sq->SetTrueVal(val);
		m_GameRows[row].Settaken(val);
		m_Rows[row].insert(val);
		m_Cols[col].insert(val);
		m_Sectors[sec].insert(val);
		return true;
	}
	else
	{
		return false;
	}
}

void GameBoard::GenBoard()
{
	int i, j, k, num, sel;
	std::vector<unsigned int> selectList (9);
	unsigned int temp;
	wxString lst;

	Binit();
	srand (time(NULL));

	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
			selectList.push_back(j+1);
		random_shuffle(selectList.begin(), selectList.end());
		for(j=0;j<9;j++)
		{
			lst.clear();
			for(k=0;k<9;k++)
			{
				lst << selectList[k] << _(" ");
			}
			wxMessageBox(lst);
			sel = j;
			num = selectList[sel];
			selectList[sel] = 0;

			while (!SetSquareTrue(num, i, j))
			{
				sel = (sel + 1) % 9;
				while(selectList[sel] == 0)
					sel = (sel + 1) % 9;
				num = selectList[sel];
			}

		}
	}
}
