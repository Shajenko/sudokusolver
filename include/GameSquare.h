#ifndef GAMESQUARE_H
#define GAMESQUARE_H


class GameSquare
{
    public:
        GameSquare();
        virtual ~GameSquare();
        unsigned int GetTrueVal() { return m_TrueVal; }
        void SetTrueVal(unsigned int val) { m_TrueVal = val; }
        unsigned int GetGuessVal() { return m_GuessVal; }
        void SetGuessVal(unsigned int val) { m_GuessVal = val; }
        bool GetShown() { return m_Shown; }
        void SetShown(bool val) { m_Shown = val; }
        unsigned int GetPossibles(unsigned int pos) { return m_Possibles[pos]; }
        void SetPossibles(unsigned int val, unsigned int pos) { m_Possibles[pos] = val; }
    protected:
    private:
        unsigned int m_TrueVal;
        unsigned int m_GuessVal;
        bool m_Shown;
        unsigned int m_Possibles[9];
};

#endif // GAMESQUARE_H
