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
	int sec, undoNum;
	bool colFnd, rowFnd, secFnd;
	GameSquare * sq;
	sq = &m_GameRows[row].m_square[col];
	sec = sq->GetSector();

	if(val == 0)
	{
		undoNum = sq->GetTrueVal();
		sq->SetTrueVal(val);
		m_GameRows[row].Unsettaken(undoNum);
		m_Rows[row].erase(undoNum);
		m_Cols[col].erase(undoNum);
		m_Sectors[sec].erase(undoNum);
		return true;
	}


	rowFnd = (m_Rows[row].find(val) == m_Rows[row].end());
	colFnd = (m_Cols[col].find(val) == m_Cols[col].end());
	secFnd = (m_Sectors[sec].find(val) == m_Sectors[sec].end());
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

bool GameBoard::GenBoard(int row, int col)
{
	unsigned int k, num;
	std::vector<unsigned int> selectList (9);
	wxString lst, error;
	bool setSucc, nextSucc;

	if(col == 9)
	{
		col = 0;
		row++;
	}
	if(row == 9)
		return true;



	//RemovePossibles(&(m_GameRows[row].m_square[col]));  // Possible problem
	selectList.clear();
	for(k=1;k<=9;k++)
		if(m_GameRows[row].m_square[col].GetPossibles(k))
			selectList.push_back(k);
	random_shuffle(selectList.begin(), selectList.end());
	lst.clear();
	for(k=0;k<selectList.size();k++)
	{
		lst << selectList[k] << _(" ");
	}
	lst << selectList.size();
	//wxMessageBox(lst);

	if(selectList.size() == 0)
		return false;
	else
	{
		setSucc = false;
		nextSucc = false;
		while (!nextSucc)
		{
			while (!setSucc)
			{
				if(selectList.size() == 0)
				{
					return false;
				}

				num = selectList.back();
				selectList.pop_back();
				setSucc = SetSquareTrue(num, row, col);
			}
			nextSucc = GenBoard(row, col + 1);
			if(!nextSucc)
			{
				SetSquareTrue(0, row, col);
				setSucc = false;
			}
		}
		return true;
	}




			/*error.clear();
			error << _("Error -") << num;
			wxMessageBox(error);*/



}
