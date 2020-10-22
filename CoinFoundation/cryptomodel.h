#ifndef CRYPTOMODEL_H
#define CRYPTOMODEL_H

#include <QAbstractTableModel>

#include <logic/crypto.h>
#include <cryptocontainer.h>


class CryptoModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit CryptoModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    //Funzionalità base:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    //Editare:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    //Aggiungere dati:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    //Rimuovere dati:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    void addCoinEntry(Crypto* coin);
    Crypto* getCoinEntry(int row);

private:
    ModelContainer<Crypto*> container;
    QStringList headers;

    QVariant getDataFromCrypto(Crypto* Crypto, int column) const;
    void setDataToCrypto(Crypto *crypto, QVariant value, int column) const;
};

#endif // CRYPTOMODEL_H
