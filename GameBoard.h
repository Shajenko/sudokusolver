#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "GameSquare.h"
#include "GameRow.h"
#include <set>

class GameBoard
{
    public:
        GameBoard();
		GameBoard operator= (const GameBoard& gb);
        void Binit();
        bool SetSquare(unsigned int val, int row, int col);
        void RemovePossibles(GameSquare * sq);
        bool GenBoard(int row, int col);
        bool Solvable(unsigned int row, unsigned int col);
        void RemoveSquares();
        virtual ~GameBoard();
        bool GetRows(int row, int val) { if(m_Rows[row].find(val) != m_Rows[row].end()) return true; else return false; }
        void SetRows(int row, unsigned int val) { m_Rows[row].insert(val); }
        unsigned int GetCols(int col, int val) { if(m_Cols[col].find(val) != m_Cols[col].end()) return true; else return false; }
        void SetCols(int col, unsigned int val) { m_Cols[col].insert(val); }
        unsigned int GetSectors(int sec, int val) { if(m_Sectors[sec].find(val) != m_Sectors[sec].end()) return true; else return false;}
        void SetSectors(int sec, unsigned int val) { m_Sectors[sec].insert(val); }
        GameRow m_GameRows[9];
    protected:
    private:
        std::set<int> m_Rows[9];
        std::set<int> m_Cols[9];
        std::set<int> m_Sectors[9];
};

#endif // GAMEBOARD_H
