#include "GameBoard.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>

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
            setSqs.insert(row + col * 9);

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
	std::set<unsigned int> currSqs;
	std::set<unsigned int>::iterator sit;
	std::vector<unsigned int> vecsetSqs;
	std::vector<unsigned int>::iterator it;
	wxString debugStr;

	currSqs = setSqs;

	// randomizing the order
	for(sit=setSqs.begin(); sit!=setSqs.end(); ++sit)
        vecsetSqs.push_back(*sit);

    std::random_shuffle(vecsetSqs.begin(), vecsetSqs.end());

    // remove each square's value, check it, and then put it back if the puzzle isn't solvable
    for(it=vecsetSqs.begin(); it!=vecsetSqs.end(); ++it)
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
    unsigned int squares[81], i, temp, rn;

	setSqs.clear();
	remSqs.clear();

    // Randomize order of squares
    for(i = 0; i < 81; i++)
        squares[i] = i;

    for(i = 0; i < 81; i++)
    {
        // swap with a random index
        rn = rand() % 81;
        temp = squares[i];
        squares[i] = squares[rn];
        squares[rn] = temp;
    }

	// Initialize set of squares that have values
    for(i=0;i<81;i++)
        setSqs.insert(squares[i]);

	return RemoveLayerEasy(setSqs, remSqs);
}

bool GameBoard::RemoveLayerMedium(std::set<unsigned int> &setSqs, std::set<unsigned int> &remSqs)
{
    // Checks all squares and removes those that leave the board in a solvable state
    bool squareRemoved = false;
	unsigned int row, col, tempVal;
	GameSquare * sq;
	std::set<unsigned int> currSqs;
	std::set<unsigned int>::iterator sit;
	std::vector<unsigned int> vecsetSqs;
	std::vector<unsigned int>::iterator it;
	wxString debugStr;

	currSqs = setSqs;

    // randomizing the order
	for(sit=setSqs.begin(); sit!=setSqs.end(); ++sit)
        vecsetSqs.push_back(*sit);

    std::random_shuffle(vecsetSqs.begin(), vecsetSqs.end());

    // remove each square's value, check it, and then put it back if the puzzle isn't solvable
    for(it=vecsetSqs.begin(); it!=vecsetSqs.end(); ++it)
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
    unsigned int squares[81], i, temp, rn;

	setSqs.clear();
	remSqs.clear();

    // Randomize order of squares
    for(i = 0; i < 81; i++)
        squares[i] = i;

    for(i = 0; i < 81; i++)
    {
        // swap with a random index
        rn = rand() % 81;
        temp = squares[i];
        squares[i] = squares[rn];
        squares[rn] = temp;
    }

	// Initialize set of squares that have values
    for(i=0;i<81;i++)
        setSqs.insert(squares[i]);

	return RemoveLayerMedium(setSqs, remSqs);
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

void GameBoard::SwapCol(int col1, int col2)
{
    GameSquare tempSq;

    for(int i=0;i<9;i++)
    {
        tempSq.Copy(m_GameSquares[i][col1]);
        m_GameSquares[i][col1].Copy(m_GameSquares[i][col2]);
        m_GameSquares[i][col2].Copy(tempSq);
    }
}

void GameBoard::SwapRow(int row1, int row2)
{
    GameSquare tempSq;

    for(int j=0;j<9;j++)
    {
        tempSq.Copy(m_GameSquares[row1][j]);
        m_GameSquares[row1][j].Copy(m_GameSquares[row2][j]);
        m_GameSquares[row2][j].Copy(tempSq);
    }
}

void GameBoard::ScrambleBoard(GameBoard& trBd)
{
    // randomwly swap columns within each of the three sections
    int i;

    for(i = 0; i < 3; i++)  // each section of the board, with three columns
    {
        if(rand() % 2)
        {
            // swap first and second columns
            SwapCol(i*3 + 0, i*3 + 1);
            trBd.SwapCol(i*3 + 0, i*3 + 1);
        }
        if(rand() % 2)
        {
            // swap first and third columns
            SwapCol(i*3 + 0, i*3 + 2);
            trBd.SwapCol(i*3 + 0, i*3 + 2);
        }
    }
    for(i = 0; i < 3; i++)  // each section of the board, with three columns
    {
        if(rand() % 2)
        {
            // swap first and second rows
            SwapRow(i*3 + 0, i*3 + 1);
            trBd.SwapRow(i*3 + 0, i*3 + 1);

        }
        if(rand() % 2)
        {
            // swap first and third rows
            SwapRow(i*3 + 0, i*3 + 2);
            trBd.SwapRow(i*3 + 0, i*3 + 2);
        }
    }

    // swap the three-column sections


    // swap the three-row sections
}
