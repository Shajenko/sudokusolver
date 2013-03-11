#ifndef GAMEROW_H
#define GAMEROW_H

#include "GameSquare.h"
#include <set>

class GameRow
{
    public:
        GameRow();
        GameRow operator= (const GameRow& gr);
        void Rinit();
        void SetCol();
        virtual ~GameRow();
        bool Gettaken(unsigned int pos) { if(m_taken.find(pos) != m_taken.end()) return true; else return false;}
        void Settaken(unsigned int val) { m_taken.insert(val); }
        void Unsettaken(unsigned int val) { m_taken.erase(val); }
        GameSquare m_square[9];
    protected:
    private:
        std::set<int> m_taken;
};

#endif // GAMEROW_H
