#ifndef CRYPTOMODELSTORAGE_H
#define CRYPTOMODELSTORAGE_H

#include <QList>
#include <QString>
#include <QStringList>
#include <QDomNode>

class CryptoModel;
class Crypto;

class ModelStorage
{
public:
    ModelStorage();

    CryptoModel* loadSavedModel(QString fileName);
    bool saveModel(QList<Crypto*> cryptos, QString fileName);

private:
    QStringList coinTypes;

    Crypto* createCryptoFromXMLNode(QString type, QDomNode node);
    QDomElement createXMLNodeFromCrypto(QDomDocument &document, Crypto* crypto);
};

#endif // CRYPTOMODELSTORAGE_H
