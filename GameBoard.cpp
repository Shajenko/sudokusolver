#include "GameBoard.h"
#include <cstdlib>
#include <ctime>

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

        for(int col=0;col<9;col++)
        {
            m_Rows[row][col] = 0;
            m_Cols[col][row] = 0;
            m_Sectors[row][col] = 0;

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
	if (m_Rows[row][val-1] == 0 &&
		m_Cols[col][val-1] == 0 &&
		m_Sectors[sec][val-1] == 0 &&
		sq->GetTrueVal() == 0 &&
		val > 0 &&
		val < 10)
	{
		sq->SetTrueVal(val);
		m_GameRows[row].Settaken(val, row);
		m_Rows[row][val-1] = 1;
		m_Cols[col][val-1] = 1;
		m_Sectors[sec][val-1] = 1;
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
	unsigned int selectList[9], temp;
	wxString lst;

	Binit();
	srand (time(NULL));

	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
			selectList[j] = j+1;
		for(j=0;j<9;j++)
		{
			num = (rand() % 9);
			temp = selectList[j];
			selectList[j] = selectList[num];
			selectList[num] = temp;

		}
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
