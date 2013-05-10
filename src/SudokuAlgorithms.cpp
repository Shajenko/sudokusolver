#include "GameBoard.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>


bool GameBoard::NakedSingle(unsigned int row, unsigned int col)
{
    unsigned int numPos, poss;

    // todo: Naked Single Algorithm
    numPos = this->m_GameSquares[row][col].GetNumPossibles();
    if(numPos == 1)   // Only one possible value
    {
    	poss = this->m_GameSquares[row][col].GetOnlyPossible();
        this->m_GameSquares[row][col].SetVal(poss);// Set value to only possibility
        return true;
    }
    else
        return false;
}

bool GameBoard::HiddenSingle(unsigned int row, unsigned int col)
{
    std::set<unsigned int> possSet;
    unsigned int i, j, sec;
    unsigned int possibleVal, sqVal;
    bool hasPosVal;
    bool only;
    wxString dString, fdString;

	fdString.clear();


    possSet.clear();
    for(i=1;i<=9;i++)
        if(m_GameSquares[row][col].GetPossibles(i))
            possSet.insert(i);

    for(std::set<unsigned int>::iterator it=possSet.begin(); it!=possSet.end(); ++it)
    {
        possibleVal = *it;
        // Do for every possibility of this square
        //Check all squares in this row
        only = true;
        for(i=0;i<9;i++)
		{
			if(i != col)
			{
				sqVal = m_GameSquares[row][i].GetVal();
				hasPosVal = m_GameSquares[row][i].GetPossibles(possibleVal);
				dString.clear();
				dString << _("Error - possible contains value of set square ") << sqVal << _(" in row ") << row << _("\n");
				if(sqVal == possibleVal)  // Possibles == a value already taken
					fdString << dString;
				if(sqVal == 0 &&
					hasPosVal) //Square is blank and has this as a possibility
					only = false;
			}

		}

        if(only)
        {
            SetVal(row, col, possibleVal);
            return true;
        }

        //Check all squares in this column
        only = true;
        for(i=0;i<9;i++)
		{
			if(i != row)
			{
				sqVal = m_GameSquares[i][col].GetVal();
				hasPosVal = m_GameSquares[i][col].GetPossibles(possibleVal);
				dString.clear();
				dString << _("Error - possible contains value of set square ") << sqVal << _(" in col ") << col << _("\n");
				if(sqVal == possibleVal)  // Possibles == a value already taken
					fdString << dString;
				if(sqVal == 0 &&
					hasPosVal) //Square is blank and has this as a possibility
					only = false;
			}
		}

		if(only)
		{
			SetVal(row, col, possibleVal);
				return true;
		}

        //Check all squares in this sector
        sec = m_GameSquares[row][col].GetSector();
        only = true;
        for(i=0;i<9;i++)
            for(j=0;j<9;j++)
			{
				if(i != row || j != col)
				{
					sqVal = m_GameSquares[i][col].GetVal();
					hasPosVal = m_GameSquares[i][col].GetPossibles(possibleVal);
					dString.clear();
					dString << _("Error - possible contains value of set square ") << sqVal << _(" in sector ") << sec << _("\n");
					if(sqVal == possibleVal)  // Possibles == a value already taken
						fdString << dString;
					if(sqVal == 0 &&
						m_GameSquares[i][j].GetSector() == sec &&
						hasPosVal) //Square is blank and has this as a possibility
						only = false;
				}
			}
        if(only)
        {
            SetVal(row, col, possibleVal);
            return true;
        }
    }
    if(fdString.size() > 0)
		wxMessageBox(fdString);
    return false;
}

bool GameBoard::BlockLine(unsigned int row, unsigned int col)
{
    // todo: Block Line Algorithm
    return false;
}

bool GameBoard::DoubleBlockLine(unsigned int row, unsigned int col)
{
    // todo: Double Block Line Algorithm
    return false;
}

bool GameBoard::NakedPair(unsigned int row, unsigned int col)
{
	// Checks for a naked pair, clears possibilities from other squares
	std::set<unsigned int> possSet1, possSet2, possSet3, possSet4;
	std::set<unsigned int>::iterator it;
    unsigned int i, j, k, l, sec;
    bool pr;

	pr = false;
    possSet1.clear();
	for(i=1;i<=9;i++)
        if(m_GameSquares[row][col].GetPossibles(i))
            possSet1.insert(i);
    // todo: Naked Subset Algorithm


	switch(possSet1.size())
	{
		case 2:
		//Naked Pair
		//Check for another square that shares the exact same two possibilities in each:
			//Row
			for(i=0;i<9;i++)
			{
				if(i != col  && m_GameSquares[row][i].GetVal() == 0)
				{
					possSet2.clear();
					for(j=0;j<9;j++)
						if(m_GameSquares[row][i].GetPossibles(j))
							possSet2.insert(j);
					// Compare possSet2 & possSet1
					if(possSet1 == possSet2)  // They match, eliminate these possibilities from all other squares in row
					{
						pr = true;
						for(it=possSet1.begin();it!=possSet1.end();++it) // For both possibilities
						{
							for(j=0;j<9;j++)
								if(j!=i && j!=col) // Do not change the pair
									m_GameSquares[row][j].RemovePossibles(*it);
						}
					}
				}
			}

			//Column
			for(i=0;i<9;i++)
			{
				if(i != row  && m_GameSquares[row][i].GetVal() == 0)
				{
					possSet2.clear();
					for(j=0;j<9;j++)
						if(m_GameSquares[i][col].GetPossibles(j))
							possSet2.insert(j);
					// Compare possSet2 & possSet1
					if(possSet1 == possSet2)  // They match, eliminate these possibilities from all other squares in row
					{
						pr = true;
						for(it=possSet1.begin();it!=possSet1.end();++it) // For both possibilities
						{
							for(j=0;j<9;j++)
								if(j!=i && j!=row) // Do not change the pair
									m_GameSquares[j][col].RemovePossibles(*it);
						}
					}
				}
			}
		//Sector
			sec = m_GameSquares[row][col].GetSector();
			for(i=0;i<9;i++)
				for(j=0;j<9;j++)
					if(m_GameSquares[i][j].GetSector() == sec &&
					   (i != row || j != col))
						// Only care if the square is in this sector and not the original square
						{
							possSet2.clear();
							for(k=0;k<9;k++)
								if(m_GameSquares[i][j].GetPossibles(k))
									possSet2.insert(k);
							if(possSet1 == possSet2)  // They match, eliminate these possibilities from all other squares in sector
							{
								pr = true;
								for(it=possSet1.begin();it!=possSet1.end();++it) // For both possibilities
								{
									for(k=0;k<9;k++)
										for(l=0;l<9;l++)
											if((i != k || j != l) && (row != k || col != l)) // Do not change the pair
												m_GameSquares[k][l].RemovePossibles(*it);
								}
							}
						}
	}

    return pr;
}

bool GameBoard::HiddenPair(unsigned int row, unsigned int col)
{
    // todo: Hidden Pair Algorithm
    return false;
}
