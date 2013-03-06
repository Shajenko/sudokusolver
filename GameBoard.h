#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "GameSquare.h"
#include "GameRow.h"

class GameBoard
{
    public:
        GameBoard();
        void Binit();
        virtual ~GameBoard();
        unsigned int GetRows(int row, int val) { return m_Rows[row][val]; }
        //void SetRows(unsigned int val) { m_Rows[9][9] = val; }
        unsigned int GetCols(int col, int val) { return m_Cols[col][val]; }
        //void SetCols[9][9](unsigned int val) { m_Cols[9][9] = val; }
        unsigned int GetSectors(int sec, int val) { return m_Sectors[sec][val]; }
        //void SetSectors[9][9](unsigned int val) { m_Sectors[9][9] = val; }
        GameRow m_GameRows[9];
    protected:
    private:
        unsigned int m_Rows[9][9];
        unsigned int m_Cols[9][9];
        unsigned int m_Sectors[9][9];
};

#endif // GAMEBOARD_H
