#ifndef NFT_H
#define NFT_H

#include "crypto.h"
#include "token.h"

class NFT : public Crypto, public Token {

public:
    NFT(const string& = "", const string& = "", const string& = "", double = 0.0,
        double = 0.0, const string& ="", unsigned int = 0, double = 1.0, double = 1.0);

    double returnOfInvestment(unsigned int amountCouldInvest) override;
    string print() const override;
    double pricePerCoin() const override;
    virtual string coinType() override { return "NFT"; }

};

#endif // NFT_H
