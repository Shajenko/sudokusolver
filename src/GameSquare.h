#ifndef GAMESQUARE_H
#define GAMESQUARE_H

#include "GameSquare.h"
#include <set>

class GameSquare
{
    public:
        GameSquare();
        GameSquare operator= (const GameSquare& gs);
        void Copy(const GameSquare& gs);
        void Sinit();
        virtual ~GameSquare();
        unsigned int GetVal() { return m_Val; }
        void SetVal(unsigned int val) { m_Val = val;}
        bool GetShown() { return m_Shown; }
        void SetShown(bool val) { m_Shown = val; }
        bool GetPossibles(unsigned int val) { if(m_Possibles.find(val) != m_Possibles.end()) return true; else return false;}
        unsigned int GetNumPossibles() {return m_Possibles.size(); }
        unsigned int GetOnlyPossible() {if(m_Possibles.size() > 1) return 0; else return *m_Possibles.begin(); }
        void RemovePossibles(unsigned int val) {m_Possibles.erase(val); }
        void ClearPossibles() {m_Possibles.clear(); }
        void SetPossibles(unsigned int val) { m_Possibles.insert(val); }
        void ResetPossibles();
        unsigned int GetSector() { return m_Sector; }
        void SetSector(unsigned int val) { m_Sector = val; }
		unsigned int GetRow() { return m_Row; }
        void SetRow(unsigned int val) { m_Row = val; }
        unsigned int GetCol() { return m_Col; }
        void SetCol(unsigned int val) { m_Col = val; }
    protected:
    private:
        unsigned int m_Val;
        bool m_Shown;
        std::set<int> m_Possibles;
        unsigned int m_Sector, m_Row, m_Col;
};

#endif // GAMESQUARE_H
