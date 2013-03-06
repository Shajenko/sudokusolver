#ifndef GAMEROW_H
#define GAMEROW_H

#include "GameSquare.h"

class GameRow
{
    public:
        GameRow();
        void Rinit();
        virtual ~GameRow();
        unsigned int Gettaken(unsigned int pos) { return m_taken[pos]; }
        void Settaken(unsigned int val, unsigned int pos) { m_taken[pos] = val; }
        GameSquare m_square[9];
    protected:
    private:
        unsigned int m_taken[9];
};

#endif // GAMEROW_H
