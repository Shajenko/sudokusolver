#ifndef GAMESQUARE_H
#define GAMESQUARE_H

#include "GameSquare.h"
#include <set>

class GameSquare
{
    public:
        GameSquare();
        void Sinit();
        virtual ~GameSquare();
        unsigned int GetTrueVal() { return m_TrueVal; }
        void SetTrueVal(unsigned int val) { m_TrueVal = val;}
        unsigned int GetGuessVal() { return m_GuessVal; }
        void SetGuessVal(unsigned int val) { m_GuessVal = val; }
        bool GetShown() { return m_Shown; }
        void SetShown(bool val) { m_Shown = val; }
        unsigned int GetPossibles(unsigned int val) { if(m_Possibles.find(val) != m_Possibles.end()) return true; else return false;}
        void RemovePossibles(unsigned int val) {m_Possibles.erase(val); }
        void SetPossibles(unsigned int val) { m_Possibles.insert(val); }
        unsigned int GetSector() { return m_Sector; }
        void SetSector(unsigned int val) { m_Sector = val; }
		unsigned int GetRow() { return m_Row; }
        void SetRow(unsigned int val) { m_Row = val; }
        unsigned int GetCol() { return m_Col; }
        void SetCol(unsigned int val) { m_Col = val; }
    protected:
    private:
        unsigned int m_TrueVal;
        unsigned int m_GuessVal;
        bool m_Shown;
        std::set<int> m_Possibles;
        unsigned int m_Sector, m_Row, m_Col;
};

#endif // GAMESQUARE_H
