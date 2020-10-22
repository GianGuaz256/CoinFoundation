#include "crypto.h"

Crypto::Crypto(const string& name, const string& symbol, const string& descr, double mark,
    double tot, const string& create, unsigned int min): name(name), symbol(symbol), description(descr),
    marketCap(mark), totalSupply(tot), createdOnTopOf(create), minAmountInvestment(min){}

//GETTERS

const string& Crypto::getName() const
{
    return name;
}

const string& Crypto::getSymbol() const
{
    return symbol;
}

const string& Crypto::getDescription() const
{
    return description;
}

double Crypto::getMarketCapitalization()
{
    return marketCap;
}

double Crypto::getTotalSupply()
{
    return totalSupply;
}

const string& Crypto::getCreatedOnTopOf() const
{
    return createdOnTopOf;
}

unsigned int Crypto::getMinAmountInvestment()
{
    return minAmountInvestment;
}

ostream& operator<<(ostream& os, const Crypto& c)
{
    os << c.print();
    return os;
}

void Crypto::setName(const string& value)
{
    name = value;
}

void Crypto::setSymbol(const string& value)
{
    symbol = value;
}

void Crypto::setDescription(const string& value)
{
    description = value;
}

void Crypto::setMarketCapitalization(double value)
{
    marketCap = value;
}

void Crypto::setTotalSupply(double value)
{
    totalSupply = value;
}

void Crypto::setCreatedOnTopOf(const string& value)
{
    createdOnTopOf = value;
}

void Crypto::setMinAmountInvestment(unsigned int value)
{
    minAmountInvestment = value;
}
