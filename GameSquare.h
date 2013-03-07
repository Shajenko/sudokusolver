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
        unsigned int GetPossibles(unsigned int pos) { if(m_Possibles.find(pos) != m_Possibles.end()) return true; else return false;}
        void SetPossibles(unsigned int val, unsigned int pos) { m_Possibles.insert(val); }
        unsigned int GetSector() { return m_Sector; }
        void SetSector(unsigned int val) { m_Sector = val; }
    protected:
    private:
        unsigned int m_TrueVal;
        unsigned int m_GuessVal;
        bool m_Shown;
        std::set<int> m_Possibles;
        unsigned int m_Sector;
};

#endif // GAMESQUARE_H
