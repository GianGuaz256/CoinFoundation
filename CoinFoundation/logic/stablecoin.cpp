#include "stablecoin.h"

#include <sstream>

StableCoin::StableCoin(const string& name, const string& symbol, const string& descr, double mark,
    double tot, const string& create, unsigned int min)
    : Crypto(name, symbol, descr, mark, tot, create, min)
{
}

string StableCoin::print() const
{
    stringstream ss;
    ss << "Stable Coins are crypto assets anchored to the value of a fiat currency. "
          "All the Stable that we have in store are anchored to the value of the USD.\n";
    ss << "This particular coin is called " << name << " and its symbol is " << symbol << ". \n";
    ss << "Stable Coins are not used for speculative investment but they're assets used for "
          "safe investment. You won't have a return on Stable Coins but your money will stay "
          "here until you'll move it. It's easier to move money from stable to crypto rather that"
          "fiat to Cryptocurrency.\n";
    ss << "If you want to understand better what this Stable is used for, here there's the description"
          "from the official site: "
       << description << "\n";
    ss << "This crypto has been created on top of " << createdOnTopOf << ", it has a market capitalization of " << marketCap << "$"
                                                                                                                                " and the supply in circulation is"
       << totalSupply << symbol << ".\n";
    return ss.str();
}

double StableCoin::returnOfInvestment(unsigned int amountCouldInvest)
{
    return 0;
}

double StableCoin::pricePerCoin() const
{
    return 1;
}
