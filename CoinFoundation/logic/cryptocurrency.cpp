#include "cryptocurrency.h"

#include <sstream>

CryptoCurrency::CryptoCurrency(const string& name, const string& symbol, const string& descr, double mark,
    double tot, const string& create, unsigned int min, double infla, double interest)
    : Crypto(name, symbol, descr, mark, tot, create, min), inflationRate(infla), interestPerCoin(interest){}

string CryptoCurrency::print() const
{
    stringstream ss;
    ss << "Cryptocurrencies are crypto assets that works on top of a Blockchain: "
          "they have different consensus algorithm, "
          "different time on creating a Block and different community behind them.\n";
    ss << "This cryptocurrency is called " << name << " and its symvol is " << symbol << ".\n";
    ss << "Cryptocurrencies are used for speculative investment and each of them has "
          "different inflation rate and interest per coin."
          " With these assets you could have a really good return in terms of percentage "
          "of investment. The price for every "
       << symbol << "is " << pricePerCoin() << "$.\n";
    ss << "The price is based on the market capitalization, that's " << marketCap << "$, on the"
                                                                                     " total supply circulating, that's "
       << totalSupply << symbol << ", and"
                                   " on the inflation rate based on new currency 'created'.\n";
    ss << "The description, that you can find in the official site is: " << description << "\n";
    return ss.str();
}

double CryptoCurrency::returnOfInvestment(unsigned int amountCouldInvest)
{
    if (amountCouldInvest >= minAmountInvestment) {
        double nOfCoin = amountCouldInvest / pricePerCoin();
        double ret = nOfCoin * interestPerCoin;
        return (amountCouldInvest * (100 + ret)) / 100;
    }
    else {
        return 0;
    }
}

double CryptoCurrency::pricePerCoin() const
{
    double normalPrice = marketCap / totalSupply;
    normalPrice = (normalPrice * (100 - inflationRate)) / 100;
    return normalPrice;
}
