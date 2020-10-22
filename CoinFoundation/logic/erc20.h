#ifndef ERC20_H
#define ERC20_H

#include "crypto.h"
#include "token.h"


class ERC20 : public Crypto, public Token {

public:
    ERC20(const string& = "", const string& = "", const string& = "", double = 0.0,
          double = 0.0, const string& ="", unsigned int = 0, double = 1.0, double = 1.0);

    double returnOfInvestment(unsigned int amountCouldInvest) override;
    string print() const override;
    double pricePerCoin() const override;
    virtual string coinType() override { return "ERC20"; }


};

#endif // ERC20_H
