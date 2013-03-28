#include "GameBoard.h"
#include <cstdlib>

bool GameBoard::NakedSingle(int row, int col)
{
    unsigned int numPos;

    // todo: Naked Single Algorithm
    numPos = this->m_GameSquares[row][col].GetNumPossibles();
    if(numPos == 1)   // Only one possible value
    {
        this->m_GameSquares[row][col].SetVal(this->m_GameSquares[row][col].GetOnlyPossible());// Set value to only possibility
        return true;
    }
    else
        return false;
}

bool GameBoard::HiddenSingle(int row, int col)
{
    std::set<unsigned int> possSet;
    unsigned int i, j, sec;
    unsigned int possibleVal;
    bool only;

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
            if(m_GameSquares[row][i].GetVal() == 0 &&
               m_GameSquares[row][i].GetPossibles(possibleVal)) //Square is blank and has this as a possibility
                only = false;
        if(only)
        {
            SetVal(row, col, possibleVal);
            return true;
        }

        //Check all squares in this column
        only = true;
        for(i=0;i<9;i++)
            if(m_GameSquares[i][col].GetVal() == 0 &&
               m_GameSquares[i][col].GetPossibles(possibleVal)) //Square is blank and has this as a possibility
                only = false;
        if(only)
        {
            SetVal(row, col, possibleVal);
            return true;
        }

        //Check all squares in this sector
        sec = m_GameSquares[row][col].GetSector();
        for(i=0;i<9;i++)
            for(j=0;j<9;j++)
                if(m_GameSquares[i][j].GetVal() == 0 &&
                   m_GameSquares[i][j].GetSector() == sec &&
                    m_GameSquares[i][j].GetPossibles(possibleVal)) //Square is blank and has this as a possibility
                only = false;
        if(only)
        {
            SetVal(row, col, possibleVal);
            return true;
        }
    }
    return false;
}

bool GameBoard::BlockLine(int row, int col)
{
    // todo: Block Line Algorithm
    return false;
}

bool GameBoard::DoubleBlockLine(int row, int col)
{
    // todo: Double Block Line Algorithm
    return false;
}

bool GameBoard::NakedSubset(int row, int col)
{
	std::set<unsigned int> possSet1, possSet2, possSet3, possSet4;
	std::set<unsigned int>::iterator it;
    int i, j, k, sec;
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
		//Check for another square that share the exact same two possibilities in each:
			//Row
			for(i=0;i<9;i++)
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

			//Column
			for(i=0;i<9;i++)
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
		//Sector

	}

    return pr;
}

bool GameBoard::HiddenSubset(int row, int col)
{
    // todo: Hidden Subset Algorithm
    return false;
}
