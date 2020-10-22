#include "erc20.h"

#include <sstream>

ERC20::ERC20(const string& name, const string& symbol, const string& descr, double mark,
    double tot, const string& create, unsigned int min, double fee, double volat)
    : Crypto(name, symbol, descr, mark, tot, create, min), Token(fee, volat)
{

}

double ERC20::returnOfInvestment(unsigned int amountCouldInvest)
{
    if (amountCouldInvest >= minAmountInvestment) {
        return (amountCouldInvest * (100 + volatilityPercent)) / 100;
    }
    else{
        return 0;
    }
}

string ERC20::print() const
{
    stringstream ss;
        ss << "Tokens are particular crypto assets build on top of a cryptocurrency using Smart Contract, "
              "particular ty pes of programs that runs alone and define autonously output receiving input from outside.\n";
        ss << "This type of token is fungible, it means that every token is the same to another, so basically it has a certain amount of "
              " tokens in circulation. This token is called "
           << name << " and its symbol it's " << symbol << " and it had been created on top of " << createdOnTopOf << ".\n";
        ss << "Tokens are really speculative crypto assets, so be safe when you decide to invest in them. The volatility on this assets it's really high, but at the same "
              "time is the return. The market capitalization of "
           << symbol << " is " << marketCap << "$, and the total supply in circulation is " << totalSupply << symbol << ".\n";
        ss << "If you want to have more informations about this particular token check out the description from the official site: " << description << ".\n";
    return ss.str();
}

double ERC20::pricePerCoin() const
{
    double norm = marketCap / totalSupply;
    return (norm * (100 - feeOnToken)) / 100;
}
