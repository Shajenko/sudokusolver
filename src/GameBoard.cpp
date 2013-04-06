#include "GameBoard.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>

GameBoard::GameBoard()
{

	Binit();
}

GameBoard GameBoard::operator= (const GameBoard& gb)
{
	GameBoard A;
	unsigned int i, j;

	for(i = 0;i < 9;i++)
        for(j = 0;j < 9;j++)
        {
            A.m_GameSquares[i][j] = gb.m_GameSquares[i][j];
            A.m_Cols[i] = gb.m_Cols[i];
            A.m_Rows[i] = gb.m_Rows[i];
            A.m_Sectors[i] = gb.m_Sectors[i];
        }

	return A;
}

void GameBoard::Copy(GameBoard& gb)
{
	unsigned int i,j,k;

	for(i = 0;i < 9;i++)
	{
	    for(j=0;j<9;j++)
        {
            this->m_GameSquares[i][j].SetVal(gb.m_GameSquares[i][j].GetVal());
            this->m_GameSquares[i][j].SetShown(gb.m_GameSquares[i][j].GetShown());
            this->m_GameSquares[i][j].SetCol(gb.m_GameSquares[i][j].GetCol());
            this->m_GameSquares[i][j].SetRow(gb.m_GameSquares[i][j].GetRow());
            this->m_GameSquares[i][j].SetSector(gb.m_GameSquares[i][j].GetSector());
            this->m_GameSquares[i][j].ClearPossibles();
            for(k=1;k<=9;k++)
                if(gb.m_GameSquares[i][j].GetPossibles(k))
                    this->m_GameSquares[i][j].SetPossibles(k);
        }


		this->m_Cols[i] = gb.m_Cols[i];
		this->m_Rows[i] = gb.m_Rows[i];
		this->m_Sectors[i] = gb.m_Sectors[i];
	}

}

GameBoard::~GameBoard()
{
    //dtor
}

void GameBoard::Binit()
{
	for(int row=0;row<9;row++)
    {


		m_Rows[row].clear();
		m_Sectors[row].clear();
		m_Cols[row].clear();
        for(int col=0;col<9;col++)
        {
            m_GameSquares[row][col].Sinit();
            // todo - set sector for each square
            m_GameSquares[row][col].SetSector((row/3) * 3 + (col/3));
            m_GameSquares[row][col].SetRow(row);
            m_GameSquares[row][col].SetCol(col);
        }
    }
}

bool GameBoard::SetSquare(unsigned int val, int row, int col)
{
	int sec, undoNum;
	bool colFnd, rowFnd, secFnd;
	GameSquare * sq;
	sq = &m_GameSquares[row][col];
	sec = sq->GetSector();

	if(val == 0)
	{
		undoNum = sq->GetVal();
		sq->SetVal(val);
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
		sq->GetVal() == 0 &&
		val > 0 &&
		val < 10)
	{
		sq->SetVal(val);
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

void GameBoard::RemoveAllPossibles()
{
    GameSquare * sq;

    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            sq = &m_GameSquares[i][j];
            RemovePossibles(sq);
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
		sq->SetPossibles(i);
		if(m_Rows[row].find(i) != m_Rows[row].end())
            sq->RemovePossibles(i);
        if(m_Cols[col].find(i) != m_Cols[col].end())
            sq->RemovePossibles(i);
		if((m_Sectors[sec].find(i) != m_Sectors[sec].end()))
			sq->RemovePossibles(i);
	}


}

bool GameBoard::GenBoard(int row, int col)
{
	unsigned int k, num, random;
	std::vector<unsigned int> selectList (9);
	wxString lst, error;
	bool setSucc, nextSucc;

	srand(time(NULL));

	if(col == 9)
	{
		col = 0;
		row++;
	}
	if(row == 9)
		return true;



	RemovePossibles(&(m_GameSquares[row][col]));  // Possible problem
	selectList.clear();
	for(k=1;k<=9;k++)
		if(m_GameSquares[row][col].GetPossibles(k))
			selectList.push_back(k);
	random_shuffle(selectList.begin(), selectList.end());

	// Shuffle things around more
	if(selectList.size() > 2)
		random = rand() % selectList.size();

	for(k=0;k<random && selectList.size() > 2;k++)
	{
		num = selectList.back();
		selectList.pop_back();
		selectList.insert(selectList.begin(), num);
	}

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
				setSucc = SetSquare(num, row, col);
			}
			nextSucc = GenBoard(row, col + 1);
			if(!nextSucc)
			{
				SetSquare(0, row, col);
				setSucc = false;
			}
		}
		return true;
	}


}

void GameBoard::ResetRows()
{
    unsigned int row, col, val;
    GameSquare * sq;


    // Add all elements back
    for(row=0;row<9;row++)
		m_Rows[row].clear();

    // Remove the values that are in each of the rows
    for(row=0;row<9;row++)
        for(col=0;col<9;col++)
        {
            sq = &m_GameSquares[row][col];
            val = sq->GetVal();
            if(val > 0)
                m_Rows[row].insert(val);
        }
}

void GameBoard::ResetCols()
{
    unsigned int row, col, val;
    GameSquare * sq;

    // Add all elements back
    for(col=0;col<9;col++)
	{
		m_Cols[col].clear();
	}


    // Remove the values that are in each of the columns
    for(row=0;row<9;row++)
        for(col=0;col<9;col++)
        {
            sq = &m_GameSquares[row][col];
            val = sq->GetVal();
            if(val > 0)
                m_Cols[col].insert(val);
        }
}

void GameBoard::ResetSectors()
{
    unsigned int row, col, sec, val;
    GameSquare * sq;

    // Add all elements back
    for(sec=0;sec<9;sec++)
	{
		m_Sectors[sec].clear();
	}

    // Remove the values that are in each of the sectors
    for(row=0;row<9;row++)
        for(col=0;col<9;col++)
        {
            sq = &m_GameSquares[row][col];
            sec = sq->GetSector();
            val = sq->GetVal();
            if(val > 0)
                m_Sectors[sec].insert(val);
        }
}

void GameBoard::SetVal(int row, int col, int val)
{
    unsigned int sec;
    unsigned int i,j;

    sec = m_GameSquares[row][col].GetSector();
    m_GameSquares[row][col].SetVal(val);
    m_GameSquares[row][col].ClearPossibles();

    m_Rows[row].insert(val);
    m_Cols[col].insert(val);
    m_Sectors[sec].insert(val);

    for(i=0;i<9;i++)
    {
        m_GameSquares[row][i].RemovePossibles(val);
        m_GameSquares[i][col].RemovePossibles(val);
        for(j=0;j<9;j++)
            if(m_GameSquares[i][j].GetSector() == sec)
                m_GameSquares[i][j].RemovePossibles(val);
    }
}
