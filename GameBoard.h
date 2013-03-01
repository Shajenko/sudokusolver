#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "include\GameSquare.h"

class GameBoard
{
    public:
        GameBoard();
        virtual ~GameBoard();
        //unsigned int GetSquares(int x, int y) { return m_Squares(x + y*9); }
        //void SetSquares( val) { m_Squares[9][9] = val; }
        unsigned int GetRows(int row, int val) { return m_Rows[row][val]; }
        //void SetRows(unsigned int val) { m_Rows[9][9] = val; }
        unsigned int GetCols(int col, int val) { return m_Cols[col][val]; }
        //void SetCols[9][9](unsigned int val) { m_Cols[9][9] = val; }
        unsigned int GetSectors(int sec, int val) { return m_Sectors[sec][val]; }
        //void SetSectors[9][9](unsigned int val) { m_Sectors[9][9] = val; }
        GameSquare * m_Squares;
    protected:
    private:
        unsigned int m_Rows[9][9];
        unsigned int m_Cols[9][9];
        unsigned int m_Sectors[9][9];
};

#endif // GAMEBOARD_H
