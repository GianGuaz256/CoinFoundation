#include "nft.h"

#include <sstream>

NFT::NFT(const string& name, const string& symbol, const string& descr, double mark,
         double tot, const string& create, unsigned int min, double fee, double volat)
         : Crypto(name, symbol, descr, mark, tot, create, min), Token(fee, volat)
{

}

double NFT::returnOfInvestment(unsigned int amountCouldInvest)
{
    return 0;
}

string NFT::print() const
{
    stringstream ss;
        ss << "Tokens are particular crypto assets build on top of a cryptocurrency using Smart Contract, "
              "particular ty pes of programs that runs alone and define autonously output receiving input from outside.\n";
        ss << "This type of token has a limited supply to just 1 token and it's not usable for investment. These token are"
              " called NFT (Non Fungible Token) and they represent a digital assets that's unique in its own.\n";
        ss << "The name of this NFT is " << name << ", it's symbol it's " << symbol << " and it had been created on top of" << createdOnTopOf << ".\n";
        ss << "You can buy for " << pricePerCoin() << "$ but you can't receive interest until the intrinsic value of this token "
              " increase alone. Here there's the description for this NFT: "<< description << "\n";

    return ss.str();
}

double NFT::pricePerCoin() const
{
    return marketCap;
}
