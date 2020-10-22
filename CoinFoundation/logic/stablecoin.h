#ifndef STABLECOIN_H
#define STABLECOIN_H

#include <string>
#include "crypto.h"

class StableCoin : public Crypto
{

public:
    StableCoin(const string& = "", const string& = "", const string& = "", double = 0.0,
           double = 0.0, const string& ="", unsigned int = 0);

    double returnOfInvestment(unsigned int amountCouldInvest) override;
    string print() const override;
    double pricePerCoin() const override;
    virtual string coinType() override { return "StableCoin"; }

};

#endif // STABLECOIN_H
