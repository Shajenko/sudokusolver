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
		m_GameRows[row].SetCol();
        for(int col=0;col<9;col++)
        {
            // todo - set sector for each square
            m_GameRows[row].m_square[col].SetSector((row/3) * 3 + (col/3));
            m_GameRows[row].m_square[col].SetRow(row);
        }
    }
}

bool GameBoard::SetSquareTrue(unsigned int val, int row, int col)
{
	int sec;
	bool colFnd, rowFnd, secFnd;
	GameSquare * sq;
	sq = &m_GameRows[row].m_square[col];
	sec = sq->GetSector();

	rowFnd = (m_Rows[row].find(val) == m_Rows[row].end());
	colFnd = (m_Cols[col].find(val) == m_Cols[col].end());
	secFnd = (m_Sectors[sec].find(val) == m_Sectors[sec].end());
	//todo - check if value is impossible
	if (rowFnd &&
		colFnd &&
		secFnd &&
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

void GameBoard::RemovePossibles(GameSquare * sq)
{
	int row, col, sec;
	row = sq->GetRow();
	col = sq->GetCol();
	sec = sq->GetSector();
	for(int i=1;i<=9;i++)
	{
		if((m_Rows[row].find(i) != m_Rows[row].end()) ||
		   (m_Cols[col].find(i) != m_Cols[col].end()) ||
		   (m_Sectors[sec].find(i) != m_Sectors[sec].end()))
			sq->RemovePossibles(i);
	}


}

void GameBoard::GenBoard()
{
	unsigned int i, j, k, num;
	std::vector<unsigned int> selectList (9);
	wxString lst, error;
	bool setSucc;

	Binit();
	srand (time(NULL));

	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			RemovePossibles(&(m_GameRows[i].m_square[j]));
			selectList.clear();
			for(k=1;k<=9;k++)
				if(m_GameRows[i].m_square[j].GetPossibles(k))
					selectList.push_back(k);
			random_shuffle(selectList.begin(), selectList.end());
			lst.clear();
			for(k=0;k<selectList.size();k++)
			{
				lst << selectList[k] << _(" ");
			}
			lst << selectList.size();
			//wxMessageBox(lst);

			if(selectList.size() > 0)
			{
				num = *selectList.begin();
				selectList.erase(selectList.begin());

				setSucc = SetSquareTrue(num, i, j);
				while (!setSucc)
				{
					if(selectList.size() == 0)
						break;
					num = selectList.back();
					selectList.pop_back();
					SetSquareTrue(num, i, j);
				}
			}


			/*error.clear();
			error << _("Error -") << num;
			wxMessageBox(error);*/


		}
	}
}
