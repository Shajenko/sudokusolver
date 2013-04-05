#include "GameBoard.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>

bool GameBoard::Solvable()
{
	// Determines whether the puzzle is currently solvable

    bool solved;
    GameBoard * trying = new GameBoard();

    trying->Binit();
    trying->Copy(*this);
    solved = trying->Solve();
    delete trying;


	return solved;
}

bool GameBoard::Solvable(std::set<unsigned int> &remSqs, Difficulty diff)
{
	// Determines whether the puzzle is currently solvable

    bool solved;
    GameBoard * trying = new GameBoard();

    trying->Binit();
    trying->Copy(*this);
    solved = trying->Solve(remSqs, diff);
    delete trying;

	return solved;
}

void GameBoard::RemoveSquares(Difficulty diff)
{
    // Removes squares from the visible list until the minimum number of squares remains
	//   for the puzzle to remain solvable - in theory

    unsigned int row, col;
    std::set<unsigned int> setSqs;
    std::set<unsigned int> remSqs;;
	std::set<unsigned int>::iterator it;

	bool squareRemoved = true;

    setSqs.clear();
    remSqs.clear();

    ResetCols();
    ResetRows();
    ResetSectors();

	// Initialize set of squares that have values
    for(row=0;row<9;row++)
        for(col=0;col<9;col++)
        {
            setSqs.insert(row + col * 9);
        }

    while(squareRemoved)
    {
        squareRemoved = RemoveLayerEasy(setSqs, remSqs); // Pass the sets of squares with and without values
    }
    if(diff == MEDIUM || diff == HARD)
    {
    	squareRemoved = true;
		while(squareRemoved)
		{
			squareRemoved = RemoveLayerMedium(setSqs, remSqs);
		}
    }
    for(it=remSqs.begin(); it!=remSqs.end(); ++it)
	{
        RemoveAllPossibles();
	}
}

bool GameBoard::RemoveLayerEasy(std::set<unsigned int> &setSqs, std::set<unsigned int> &remSqs)
{
    // Checks all squares and removes those that leave the board in a solvable state
    bool squareRemoved = false;
	unsigned int row, col, tempVal;
	GameSquare * sq;
	std::set<unsigned int>::iterator it;
	std::set<unsigned int> currSqs;
	wxString debugStr;

	currSqs = setSqs;

    for(it=setSqs.begin(); it!=setSqs.end(); ++it)
    {
        row = *it % 9;
        col = *it / 9;
        sq = &m_GameSquares[row][col];
        if (sq->GetVal() != 0)
        {
            tempVal = sq->GetVal();
            SetSquare(0, row, col);
            remSqs.insert(row + col * 9);
            if(Solvable(remSqs, EASY))
            {
                squareRemoved = true;
                sq->SetShown(false);
                currSqs.erase(*it);

            }
            else
            {
                SetSquare(tempVal, row, col);
                remSqs.erase(row + col * 9);
            }
        }
    }
    setSqs = currSqs;
    return squareRemoved;
}

bool GameBoard::RemoveLayerEasy()
{
	std::set<unsigned int> setSqs;
    std::set<unsigned int> remSqs;
    unsigned int row, col;

	setSqs.clear();
	remSqs.clear();

	for(row=0;row<9;row++)
		for(col=0;col<9;col++)
        {
            setSqs.insert(row + col * 9);
        }

	return RemoveLayerEasy(setSqs, remSqs);
}

bool GameBoard::RemoveLayerMedium(std::set<unsigned int> &setSqs, std::set<unsigned int> &remSqs)
{
    // Checks all squares and removes those that leave the board in a solvable state
    bool squareRemoved = false;
	unsigned int row, col, tempVal;
	GameSquare * sq;
	std::set<unsigned int>::iterator it;
	std::set<unsigned int> currSqs;
	wxString debugStr;

	currSqs = setSqs;

    for(it=setSqs.begin(); it!=setSqs.end(); ++it)
    {
    	debugStr.clear();
    	debugStr << *it;
 //   	wxMessageBox(debugStr);

        row = *it % 9;
        col = *it / 9;
        sq = &m_GameSquares[row][col];
        if (sq->GetVal() != 0)
        {
            tempVal = sq->GetVal();
            SetSquare(0, row, col);
            remSqs.insert(row + col * 9);
            if(Solvable(remSqs, MEDIUM))
            {
                squareRemoved = true;
                sq->SetShown(false);
                currSqs.erase(*it);
            }
            else
            {
                SetSquare(tempVal, row, col);
                remSqs.erase(row + col * 9);
            }
        }
    }
    setSqs = currSqs;
    return squareRemoved;
}

bool GameBoard::RemoveLayerMedium()
{
	std::set<unsigned int> setSqs;
    std::set<unsigned int> remSqs;
    unsigned int row, col;

	setSqs.clear();
	remSqs.clear();

	for(row=0;row<9;row++)
		for(col=0;col<9;col++)
        {
            setSqs.insert(row + col * 9);
        }

	return RemoveLayerMedium(setSqs, remSqs);
}

bool GameBoard::Solve()
{
    unsigned int row, col;
    std::set<unsigned int> remSqs;


	ResetRows();
	ResetCols();
	ResetSectors();
	RemoveAllPossibles();

    remSqs.clear();

    for(row=0;row<9;row++)
        for(col=0;col<9;col++)
            if(m_GameSquares[row][col].GetVal() == 0)
                remSqs.insert(row + col * 9);

    return Solve(remSqs, EASY);
}

bool GameBoard::Solve(std::set<unsigned int> &remSqs, Difficulty diff)
{
    bool solSq, unknSq, tempSq;
    unsigned int row, col, sec, val;
    GameSquare * sq;


    solSq = true;
    unknSq = true;


    while(solSq && unknSq)  // We solved a square and there are still squares to solve
    {
        solSq = false;
        unknSq = false;

        for(std::set<unsigned int>::iterator it=remSqs.begin(); it!=remSqs.end(); ++it)
        {
            row = *it % 9;
            col = *it / 9;
            sq = &m_GameSquares[row][col];
            sec = sq->GetSector();
            if(sq->GetVal() == 0)  //Square is unknown
            {
                unknSq = true;
                RemovePossibles(sq);  // Figure out what is possible
                tempSq = NakedSingle(row, col);
                if(!tempSq)
                    unknSq = true;
                if(tempSq)
				{
					solSq = true;
					val = sq->GetVal();
					m_Rows[row].insert(val);
					m_Cols[col].insert(val);
					m_Sectors[sec].insert(val);
				}

            }
        }

        if(solSq)
			continue;

        for(std::set<unsigned int>::iterator it=remSqs.begin(); it!=remSqs.end(); ++it)
        {
            row = *it % 9;
            col = *it / 9;
            sq = &m_GameSquares[row][col];
			sec = sq->GetSector();
            if(sq->GetVal() == 0)  //Square is unknown
            {
                unknSq = true;
                RemovePossibles(sq);  // Figure out what is possible
                tempSq = HiddenSingle(row, col);
                if(!tempSq)
                    unknSq = true;
                if(tempSq)
				{
					solSq = true;
					val = sq->GetVal();
					m_Rows[row].insert(val);
					m_Cols[col].insert(val);
					m_Sectors[sec].insert(val);
				}
            }
        }

		if(solSq)
			continue;

		if(diff == MEDIUM || diff == HARD)
		{
			for(std::set<unsigned int>::iterator it=remSqs.begin(); it!=remSqs.end(); ++it)
			{
				row = *it % 9;
				col = *it / 9;
				sq = &m_GameSquares[row][col];
				if(sq->GetVal() == 0)  //Square is unknown
				{
					unknSq = true;
					RemovePossibles(sq);  // Figure out what is possible
					tempSq = NakedSubset(row, col);
				}
			}
			if(solSq)
				continue;
		}
    }

    if(unknSq)
        return false;
    else
        return true;
}


bool GameBoard::NakedSingle(unsigned int row, unsigned int col)
{
    unsigned int numPos, poss;

    // todo: Naked Single Algorithm
    numPos = this->m_GameSquares[row][col].GetNumPossibles();
    if(numPos == 1)   // Only one possible value
    {
    	poss = this->m_GameSquares[row][col].GetOnlyPossible();
        SetVal(row, col, poss);  //Set value to only possibility
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

bool GameBoard::NakedSubset(unsigned int row, unsigned int col)
{
	std::set<unsigned int> possSet1, possSet2, possSet3, possSet4;
	std::set<unsigned int>::iterator it;
    unsigned int i, j, k, sec;
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
				if(i != col)
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
								if(j!=i && j!=col && j==0) // Do not change the pair
									m_GameSquares[row][j].RemovePossibles(*it);
						}
					}
				}
			}

			//Column
			for(i=0;i<9;i++)
			{
				if(i != row)
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

	}

    return pr;
}

bool GameBoard::HiddenSubset(unsigned int row, unsigned int col)
{
    // todo: Hidden Subset Algorithm
    return false;
}
