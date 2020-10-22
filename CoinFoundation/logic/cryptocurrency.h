#ifndef CRYPTOCURRENCY_H
#define CRYPTOCURRENCY_H

#include <string>
#include "crypto.h"

class CryptoCurrency: public Crypto
{

private:
    double inflationRate;
    double interestPerCoin;

public:
    CryptoCurrency(const string& = "", const string& = "", const string& = "", double = 0.0,
                   double = 0.0, const string& ="", unsigned int = 0, double = 1.0, double = 1.0);

    double returnOfInvestment(unsigned int amountCouldInvest) override;
    string print() const override;
    double pricePerCoin() const override;
    virtual string coinType() override { return "Cryptocurrency"; }

    double getInflationRate() { return inflationRate; }
    double getInterestPerCoin() { return interestPerCoin; }

};

#endif // CRYPTOCURRENCY_H
