#include "cryptomodelstorage.h"

#include <QtXml>
#include <QFile>
#include <QDebug>
#include <QDomNodeList>
#include <QDomNode>
#include <QDomElement>
#include <QTextStream>

#include <cryptomodel.h>

#include <logic/cryptocurrency.h>
#include <logic/stablecoin.h>
#include <logic/nft.h>
#include <logic/erc20.h>

ModelStorage::ModelStorage()
{
    coinTypes << "Cryptocurrency" << "StableCoin" << "NFT" << "ERC20";
}

//LOAD
CryptoModel* ModelStorage::loadSavedModel(QString fileName)
{
    //Classe QDomDocument rappresenta un documento XML
    QDomDocument xmlBOM;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cerr << "Error while loading file" << std::endl;
        return nullptr;
    }
    //Settare i dati all'interno del documento
    xmlBOM.setContent(&file);
    file.close();

    CryptoModel* model = new CryptoModel();

    QDomElement root = xmlBOM.documentElement();
    QDomNodeList children = root.childNodes();

    for(int i=0; i < children.count(); i++)
    {
        QDomNode child = children.at(i);
        QString type = child.toElement().attribute("type");
        qDebug() << child.toElement().tagName() << type << endl;
        Crypto* crypto = createCryptoFromXMLNode(type, child);
        if ( crypto != nullptr )
            model->addCoinEntry(crypto);
    }

    return model;

}

//SAVE
bool ModelStorage::saveModel(QList<Crypto *> cryptos, QString fileName)
{
    QDomDocument xmlBOM("Cryptos");

    QDomElement root = xmlBOM.createElement("Cryptos");

    for(int i = 0; i < cryptos.size(); i++)
    {
        Crypto* crypto = cryptos.at(i);
        QDomElement elm = createXMLNodeFromCrypto(xmlBOM, crypto);
        root.appendChild(elm);
    }

    xmlBOM.appendChild(root);
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        std::cerr << "Error while writing file" << std::endl;
        return false;
    }
    QTextStream stream(&file);
    QString output = xmlBOM.toString(4).replace("&#xd;\n", "\n");
    stream << output;
    file.close();

    return true;
}

//XML -> Crypto
Crypto* ModelStorage::createCryptoFromXMLNode(QString type, QDomNode node)
{
    try
    {
        QDomElement baseInfo = node.firstChildElement("BaseInfo");

        string name = baseInfo.firstChildElement("name").toElement().text().toStdString();
        string symbol = baseInfo.firstChildElement("symbol").toElement().text().toStdString();
        string description = baseInfo.firstChildElement("description").toElement().text().toStdString();
        double marketCap = baseInfo.firstChildElement("marketCap").toElement().text().toDouble();
        double totalSupply = baseInfo.firstChildElement("totalSupply").toElement().text().toDouble();
        string createdOnTopOf = baseInfo.firstChildElement("createdOnTopOf").toElement().text().toStdString();
        int minAmountInvestment = baseInfo.firstChildElement("minAmountInvestment").toElement().text().toInt();

        if (coinTypes.indexOf(type) == 0)
        {
            QDomElement inflationRateNode = node.firstChildElement("inflationRate");
            double inflationRate = inflationRateNode.toElement().text().toDouble();

            QDomElement interestPerCoinNode = node.firstChildElement("interestPerCoin");
            double interestPerCoin = interestPerCoinNode.toElement().text().toDouble();

            return new CryptoCurrency(name, symbol, description, marketCap, totalSupply, createdOnTopOf, minAmountInvestment, inflationRate, interestPerCoin);
        }
        else if (coinTypes.indexOf(type) == 1)
        {
            return new StableCoin(name, symbol, description, marketCap, totalSupply, createdOnTopOf, minAmountInvestment);
        }
        else if (coinTypes.indexOf(type) == 2)
        {
            QDomElement feeOnTokenNode = node.firstChildElement("feeOnToken");
            double feeOnToken = feeOnTokenNode.toElement().text().toDouble();

            QDomElement volatilityPercentNode = node.firstChildElement("volatilityPercent");
            double volatilityPercent = volatilityPercentNode.toElement().text().toDouble();

            return new NFT(name, symbol, description, marketCap, totalSupply, createdOnTopOf, minAmountInvestment, feeOnToken, volatilityPercent);
        }
        else if (coinTypes.indexOf(type) == 3)
        {
            QDomElement feeOnTokenNode = node.firstChildElement("feeOnToken");
            double feeOnToken = feeOnTokenNode.toElement().text().toDouble();

            QDomElement volatilityPercentNode = node.firstChildElement("volatilityPercent");
            double volatilityPercent = volatilityPercentNode.toElement().text().toDouble();

            return new ERC20(name, symbol, description, marketCap, totalSupply, createdOnTopOf, minAmountInvestment, feeOnToken, volatilityPercent);
        }
        else
        {
            qDebug() << "Something is off: " << type << node.toDocument().toString() << endl;
            return nullptr;
        }
    }
    catch (exception e)
    {
        qDebug() << "Exception while creating a coin: " << e.what() << endl;
    }

    return nullptr;
}

//Crypto -> XML
QDomElement ModelStorage::createXMLNodeFromCrypto(QDomDocument& document, Crypto *crypto)
{
    QString type = crypto->coinType().c_str();
    QDomElement elm = document.createElement("Crypto");
    elm.setAttribute("type", type);

    QDomElement baseInfo = document.createElement("BaseInfo");

    QString name = crypto->getName().c_str();
    QString symbol = crypto->getSymbol().c_str();
    QString desc = crypto->getDescription().c_str();
    double marketCap = crypto->getMarketCapitalization();
    double totalSup = crypto->getTotalSupply();
    QString createdOn = crypto->getCreatedOnTopOf().c_str();
    int minInvestment = crypto->getMinAmountInvestment();

    QDomElement e = document.createElement("name");
    e.appendChild(document.createTextNode(name));
    baseInfo.appendChild(e);

    e = document.createElement("symbol");
    e.appendChild(document.createTextNode(symbol));
    baseInfo.appendChild(e);

    e = document.createElement("description");
    e.appendChild(document.createTextNode(desc));
    baseInfo.appendChild(e);

    e = document.createElement("marketCap");
    e.appendChild(document.createTextNode(QString::number(marketCap, 'f')));
    baseInfo.appendChild(e);

    e = document.createElement("totalSupply");
    e.appendChild(document.createTextNode(QString::number(totalSup, 'f')));
    baseInfo.appendChild(e);

    e = document.createElement("createdOnTopOf");
    e.appendChild(document.createTextNode(createdOn));
    baseInfo.appendChild(e);

    e = document.createElement("minAmountInvestment");
    e.appendChild(document.createTextNode(QString::number(minInvestment)));
    baseInfo.appendChild(e);

    if (coinTypes.indexOf(type) == 0)
    {
        CryptoCurrency* c = dynamic_cast<CryptoCurrency*>(crypto);

        e = document.createElement("inflationRate");
        e.appendChild(document.createTextNode(QString::number(c->getInflationRate(), 'f')));
        elm.appendChild(e);

        e = document.createElement("interestPerCoin");
        e.appendChild(document.createTextNode(QString::number(c->getInterestPerCoin(), 'f')));
        elm.appendChild(e);
    }
    else if (coinTypes.indexOf(type) == 1)
    {
        //Niente perchè stable coin
    }
    else if (coinTypes.indexOf(type) == 2)
    {
        NFT* c = dynamic_cast<NFT*>(crypto);

        e = document.createElement("feeOnToken");
        e.appendChild(document.createTextNode(QString::number(c->getFeeOnToken(), 'f')));
        elm.appendChild(e);

        e = document.createElement("volatilityPercent");
        e.appendChild(document.createTextNode(QString::number(c->getVolatilityPercent(), 'f')));
        elm.appendChild(e);
    }
    else if (coinTypes.indexOf(type) == 3)
    {
        ERC20* c = dynamic_cast<ERC20*>(crypto);

        e = document.createElement("feeOnToken");
        e.appendChild(document.createTextNode(QString::number(c->getFeeOnToken(), 'f')));
        elm.appendChild(e);

        e = document.createElement("volatilityPercent");
        e.appendChild(document.createTextNode(QString::number(c->getVolatilityPercent(), 'f')));
        elm.appendChild(e);
    }

    elm.appendChild(baseInfo);

    return elm;

}
