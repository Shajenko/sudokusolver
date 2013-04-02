#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "GameSquare.h"
#include "GameRow.h"
#include <set>

enum Difficulty { EASY, MEDIUM, HARD };

class GameBoard
{
    public:
        GameBoard();
        virtual ~GameBoard();
		GameBoard operator= (const GameBoard& gb);
		void Copy(GameBoard& gb);
        void Binit();
        bool SetSquare(unsigned int val, int row, int col);
        unsigned int GetSquare(int row, int col) {return m_GameSquares[row][col].GetVal();}
        void RemoveAllPossibles();
        void RemovePossibles(GameSquare * sq);
        void RemovePossibles(int row, int col, int val) { m_GameSquares[row][col].RemovePossibles(val); }
        void ClearPossibles(int row, int col) {m_GameSquares[row][col].ClearPossibles();}
        bool GetPossibles(int row, int col, int val) { return m_GameSquares[row][col].GetPossibles(val);}
        void SetPossibles(int row, int col, int val) { m_GameSquares[row][col].SetPossibles(val);}
        bool GenBoard(int row, int col);
        bool Solvable();
        bool Solvable(std::set<unsigned int> &remSqs, Difficulty diff);
        void RemoveSquares(Difficulty diff);
        bool RemoveLayerEasy(std::set<unsigned int> &setSqs, std::set<unsigned int> &remSqs);
        bool RemoveLayerEasy();
        bool RemoveLayerMedium(std::set<unsigned int> &setSqs, std::set<unsigned int> &remSqs);
        bool RemoveLayerMedium();
        bool Solve();
        bool Solve(std::set<unsigned int> &remSqs, Difficulty diff);
        bool GetRows(int row, int val) { if(m_Rows[row].find(val) != m_Rows[row].end()) return true; else return false; }
        void SetRows(int row, unsigned int val) { m_Rows[row].insert(val); }
        unsigned int GetCols(int col, int val) { if(m_Cols[col].find(val) != m_Cols[col].end()) return true; else return false; }
        void SetCols(int col, unsigned int val) { m_Cols[col].insert(val); }
        unsigned int GetSectors(int sec, int val) { if(m_Sectors[sec].find(val) != m_Sectors[sec].end()) return true; else return false;}
        void SetSectors(int sec, unsigned int val) { m_Sectors[sec].insert(val); }
        void ResetRows();
        void ResetCols();
        void ResetSectors();
        unsigned int GetVal(int row, int col) { return m_GameSquares[row][col].GetVal();}
        void SetVal(int row, int col, int val);
        bool GetShown(int row, int col) { return m_GameSquares[row][col].GetShown();}
        void SetShown(int row, int col, bool val) { m_GameSquares[row][col].SetShown(val);}
    protected:
    private:

        GameSquare m_GameSquares[9][9];
        std::set<int> m_Rows[9];
        std::set<int> m_Cols[9];
        std::set<int> m_Sectors[9];

        bool NakedSingle(int row, int col);
        bool HiddenSingle(int row, int col);
        bool BlockLine(int row, int col);
        bool DoubleBlockLine(int row, int col);
        bool NakedSubset(int row, int col);
        bool HiddenSubset(int row, int col);
};

#endif // GAMEBOARD_H
