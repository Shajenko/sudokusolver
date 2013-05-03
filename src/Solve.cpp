#include "GameBoard.h"

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
					tempSq = NakedPair(row, col);
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
