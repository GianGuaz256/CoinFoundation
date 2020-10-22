#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token
{

protected:
    double feeOnToken;
    double volatilityPercent;

public:
    Token(double fee = 1.0, double volatility = 1.0);

    virtual double getFeeOnToken() {return feeOnToken; }
    virtual double getVolatilityPercent() { return volatilityPercent; }
};

#endif // TOKEN_H
