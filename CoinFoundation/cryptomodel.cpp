#include "cryptomodel.h"
#include <logic/cryptocurrency.h>
#include <logic/stablecoin.h>
#include <logic/token.h>

#include <QDebug>

CryptoModel::CryptoModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    headers << "Coin Type" << "Name" << "Symbol" << "Description" << "Market Capitalization" << "Total Supply" << "Created on Top of"
            << "Min. Investment" << "Price";
}

QVariant CryptoModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        return QVariant(headers.at(section));
    }
    return QVariant();
}

bool CryptoModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (value != headerData(section, orientation, role)) {

        if (orientation == Qt::Horizontal)
        {
            headers[section] = value.toString();
            emit headerDataChanged(orientation, section, section);
            return true;
        }
    }
    return false;
}


int CryptoModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return container.size();
}

int CryptoModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return headers.size();
}

QVariant CryptoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= (int) container.size())
        return QVariant();

    if ( role == Qt::DisplayRole || role == Qt::EditRole )
    {
        Crypto* crypto = container.at(index.row());
        if (crypto == nullptr)
            return QVariant();
        return getDataFromCrypto(crypto, index.column());
    }
    else if (role == Qt::DisplayRole || role == Qt::ToolTipRole)
    {
        Crypto* crypto = container.at(index.row());
        return QVariant(crypto->print().c_str());
    }
    return QVariant();
}

bool CryptoModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value)
    {
        Crypto* crypto = container.at(index.row());

        if (crypto == nullptr)
            return false;

        setDataToCrypto(crypto, value, index.column());
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags CryptoModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    //Il tipo di moneta non può essere cambiata:
    if (index.column() == 0 || index.column() == headers.size() - 1)
        return Qt::ItemIsEnabled;
    return Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

bool CryptoModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    beginInsertRows(QModelIndex(), row, row + count - 1);
    endInsertRows();
    return true;
}


bool CryptoModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    beginRemoveRows(parent, row, row + count - 1);
    for ( int i = 0; i < count; i++ )
    {
        Crypto* crypto = container.at(row);
        container.remove(crypto);
    }
    endRemoveRows();
    return true;
}

void CryptoModel::addCoinEntry(Crypto *coin)
{
    int row = rowCount();
    insertRow(row);
    container.push(coin);
    emit dataChanged(index(0, 0), index(row, headers.count()));
    qDebug() << rowCount() << container.size() << endl;

}

Crypto *CryptoModel::getCoinEntry(int row)
{
    if (row >= rowCount() || row < 0 )
        return nullptr;

    return container.at(row);
}

QVariant CryptoModel::getDataFromCrypto(Crypto *crypto, int column) const
{
    if (column >= headers.size() || crypto == nullptr)
        return QVariant();

    switch (column)
    {
    case 0:
        return QVariant(crypto->coinType().c_str());
    case 1:
        return QVariant(crypto->getName().c_str());
    case 2:
        return QVariant(crypto->getSymbol().c_str());
    case 3:
        return QVariant(crypto->getDescription().c_str());
    case 4:
        return QVariant(crypto->getMarketCapitalization());
    case 5:
        return QVariant(crypto->getTotalSupply());
    case 6:
        return QVariant(crypto->getCreatedOnTopOf().c_str());
    case 7:
        return QVariant(crypto->getMinAmountInvestment());
    case 8:
        return QVariant(crypto->pricePerCoin());
    default:
        return QVariant();

    }
}

void CryptoModel::setDataToCrypto(Crypto *crypto, QVariant value, int column) const
{
    if (column >= headers.size() || crypto == nullptr)
        return;

    switch (column)
    {
    case 0:
        //Il tipo di moneta non può cambiare
        break;
    case 1:
        crypto->setName(value.toString().toStdString());
        break;
    case 2:
        crypto->setSymbol(value.toString().toStdString());
        break;
    case 3:
        crypto->setDescription(value.toString().toStdString());
        break;
    case 4:
        crypto->setMarketCapitalization(value.toDouble());
        break;
    case 5:
        crypto->setTotalSupply(value.toDouble());
        break;
    case 6:
        crypto->setCreatedOnTopOf(value.toString().toStdString());
        break;
    case 7:
        crypto->setMinAmountInvestment(value.toInt());
        break;
    default:
        return;
    }
}
