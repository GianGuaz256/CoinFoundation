#ifndef CRYPTO_H
#define CRYPTO_H

#include <string>
#include <iostream>

using namespace std;


class Crypto
{
protected:
    string name;
    string symbol;
    string description;
    double marketCap;
    double totalSupply;
    string createdOnTopOf;
    unsigned int minAmountInvestment;

public:
    Crypto(const string& = "", const string& = "", const string& = "", double = 0.0,
           double = 0.0, const string& ="", unsigned int = 0);
    virtual ~Crypto() = default;

    //GETTERS
    const string& getName() const;
    const string& getSymbol() const;
    const string& getDescription() const;
    double getMarketCapitalization();
    double getTotalSupply();
    const string& getCreatedOnTopOf() const;
    unsigned int getMinAmountInvestment();

    // SETTERS
    void setName(const string &value);
    void setSymbol(const string &value);
    void setDescription(const string &value);
    void setMarketCapitalization(double value);
    void setTotalSupply(double value);
    void setCreatedOnTopOf(const string &value);
    void setMinAmountInvestment(unsigned int value);

    //OSTREAM ON
    friend ostream& operator<<(ostream&, const Crypto&);

    //METODI VIRTUALI PURI
    virtual string coinType() = 0;
    virtual double returnOfInvestment(unsigned int amountCouldInvest) = 0;
    virtual string print() const = 0;
    virtual double pricePerCoin() const = 0;

};

#endif // CRYPTO_H
