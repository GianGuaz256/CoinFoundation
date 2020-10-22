#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QList>
#include <QInputDialog>
#include <QMessageBox>
#include <QTimer>
#include <QFileDialog>
#include <QDir>
#include <QCoreApplication>

#include <QDebug>

#include <logic/cryptocurrency.h>
#include <logic/stablecoin.h>
#include <logic/nft.h>
#include <logic/erc20.h>

#include <cryptomodelstorage.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->sidebar->hide();

    fileName = QDir(QCoreApplication::applicationDirPath()).filePath("data.xml");
    model = nullptr;
    modelStorage = new ModelStorage();

    coinTypes << "Cryptocurrency" << "StableCoin" << "NFT" << "ERC20";

    connect(ui->add, SIGNAL(clicked()), this, SLOT(onAddEntryClicked()));
    connect(ui->remove, SIGNAL(clicked()), this, SLOT(onRemoveEntryClicked()));

    connect(ui->amount, SIGNAL(valueChanged(int)), this, SLOT(onAmountChanged(int)));

    QTimer::singleShot(0, this, SLOT(initModel()));

    icons.insert(coinTypes[0], QPixmap(":/icons/cryptocurrency.png"));
    icons.insert(coinTypes[1], QPixmap(":/icons/stablecoin.png"));
    icons.insert(coinTypes[2], QPixmap(":/icons/nft.png"));
    icons.insert(coinTypes[3], QPixmap(":/icons/erc20.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
    delete modelStorage;
}

void MainWindow::updateSideBar()
{
    QModelIndex index = ui->tableView->currentIndex();
    if ( !index.isValid() )
    {
        ui->sidebar->hide();
        return;
    }

    index = filterModel->mapToSource(index);

    Crypto* coinEntry = model->getCoinEntry(index.row());

    ui->lbl_type->setText(QString(coinEntry->coinType().c_str()));
    ui->lbl_name->setText(QString(coinEntry->getName().c_str()));
    ui->lbl_symbol->setText(QString(coinEntry->getSymbol().c_str()));
    ui->lbl_summary->setText(QString(coinEntry->getDescription().c_str()));
    ui->lbl_description->setText(QString(coinEntry->print().c_str()));
    ui->lbl_marketCap->setText(QString::number(coinEntry->getMarketCapitalization(), 'f'));
    ui->lbl_total->setText(QString::number(coinEntry->getTotalSupply(), 'f'));
    ui->lbl_createdOn->setText(QString(coinEntry->getCreatedOnTopOf().c_str()));
    ui->lbl_min->setText(QString::number(coinEntry->getMinAmountInvestment()));
    ui->lbl_price->setText(QString::number(coinEntry->pricePerCoin(), 'f'));

    QString type = coinEntry->coinType().c_str();
    QString additional = "";

    if (icons.contains(type))
    {
        ui->logo->setPixmap(icons[type]);
        ui->logo->show();
    }
    else
    {
        ui->logo->hide();
    }


    if (coinTypes.indexOf(type) == 0)
    {
        CryptoCurrency* c = dynamic_cast<CryptoCurrency*>(coinEntry);

        additional = QString("%1: %2 \n%3: %4").arg("Inflation Rate").arg(c->getInflationRate()).arg("Interest per Coin").arg(c->getInterestPerCoin());
        ui->lbl_additional_vals->setText(additional);
        ui->lbl_additional_vals->show();
        ui->lbl_additional->show();

    }
    else if (coinTypes.indexOf(type) == 1)
    {
        ui->lbl_additional_vals->setText("");
        ui->lbl_additional_vals->hide();
        ui->lbl_additional->hide();
    }
    else if (coinTypes.indexOf(type) == 2)
    {
        NFT* c = dynamic_cast<NFT*>(coinEntry);
        additional = QString("%1: %2 \n%3: %4").arg("Fee on Token").arg(c->getFeeOnToken()).arg("Volatility Percentage").arg(c->getVolatilityPercent());
        ui->lbl_additional_vals->setText(additional);
        ui->lbl_additional_vals->show();
        ui->lbl_additional->show();
    }
    else if (coinTypes.indexOf(type) == 3)
    {
        ERC20* c = dynamic_cast<ERC20*>(coinEntry);
        additional = QString("%1: %2 \n%3: %4").arg("Fee on Token").arg(c->getFeeOnToken()).arg("Volatility Percentage").arg(c->getVolatilityPercent());
        ui->lbl_additional_vals->setText(additional);
        ui->lbl_additional_vals->show();
        ui->lbl_additional->show();
    }
    else
    {
        ui->lbl_additional_vals->hide();
        ui->lbl_additional->hide();
    }

    ui->sidebar->show();
    ui->sidebar->repaint();
}

void MainWindow::closeEvent(QCloseEvent* event)
{

    if ( QMessageBox::Yes != QMessageBox::question(this, "Save data file?", "Do you want to save the data file?") )
    {
        event->accept();
        return;
    }

    QList<Crypto*> list;

    for ( int i = 0; i < model->rowCount(); i++ )
    {
        list.append(model->getCoinEntry(i));
    }

    modelStorage->saveModel(list, fileName);

    QMessageBox::information(this, "Data file saved.", QString("Data file was saved to %1.\nIt will be used next time to load data.").arg(fileName));

    event->accept();
}

void MainWindow::initModel()
{
    if ( model == nullptr )
    {
        model = modelStorage->loadSavedModel(fileName);

        if ( model == nullptr )
        {
            model = new CryptoModel();
        }
    }

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

    connect(ui->tableView,  SIGNAL(clicked(const QModelIndex &)), this, SLOT(selectionChanged(const QModelIndex &)));
    connect(ui->tableView->selectionModel(), SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(currentChanged(const QModelIndex &, const QModelIndex &)));
    connect(model, &CryptoModel::dataChanged, this, &MainWindow::modelDataChanged);

    filterModel = new QSortFilterProxyModel(this);
    filterModel->setDynamicSortFilter(true);
    filterModel->setSourceModel(model);
    ui->tableView->setModel(filterModel);
    ui->tableView->setSortingEnabled(true);

}

void MainWindow::onAddEntryClicked()
{
    bool ok;
    QString item = QInputDialog::getItem(this,"Select the Coin Type", "Type:", coinTypes, 0, false, &ok);
    if (ok && !item.isEmpty())
    {
        if (coinTypes.indexOf(item) == 0)
        {
            model->addCoinEntry(
                        new CryptoCurrency("", "", "", 0, 0, "", 0)
                        );
        }
        else if (coinTypes.indexOf(item) == 1)
        {
            model->addCoinEntry(
                        new StableCoin("", "", "", 0, 0, "", 0)
                        );
        }
        else if (coinTypes.indexOf(item) == 2)
        {
            model->addCoinEntry(
                        new NFT("", "", "", 0, 0, "", 0)
                        );
        }
        else if (coinTypes.indexOf(item) == 3)
        {
            model->addCoinEntry(
                        new ERC20("", "", "", 0, 0, "", 0)
                        );
        }
    }
}

void MainWindow::onRemoveEntryClicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    index = filterModel->mapToSource(index);

    if (index.isValid())
        model->removeRows(index.row(), 1);
}

void MainWindow::selectionChanged(const QModelIndex &current)
{

    if (!current.isValid())
    {
        qDebug() << "No selected row." << endl;
        return;
    }

    int amount = ui->amount->value();
    QModelIndex index = filterModel->mapToSource(current);

    Crypto* coinEntry = model->getCoinEntry(index.row());

    if ( coinEntry == nullptr )
    {
        qDebug() << "Coin is NULL" << endl;
        return;
    }

    int roi = coinEntry->returnOfInvestment(amount);
    ui->roi->setText(QString::number(roi));

    updateSideBar();

}

void MainWindow::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);
    selectionChanged(current);
}

void MainWindow::onAmountChanged(int amount)
{
    Q_UNUSED(amount);
    QModelIndex index = ui->tableView->currentIndex();
    if (index.isValid())
        updateSideBar();
}

void MainWindow::modelDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    Q_UNUSED(topLeft);
    Q_UNUSED(bottomRight);
    Q_UNUSED(roles);

    QModelIndex index = ui->tableView->currentIndex();
    if (index.isValid())
        updateSideBar();
}
