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

    // todo: Hidden Single Algorithm
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
    // todo: Naked Subset Algorithm
    return false;
}

bool GameBoard::HiddenSubset(int row, int col)
{
    // todo: Hidden Subset Algorithm
    return false;
}
