#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMap>
#include <QString>
#include <QPixmap>

#include <QMainWindow>
#include <QCloseEvent>
#include <QItemSelection>
#include <QSortFilterProxyModel>

#include <cryptomodel.h>
#include <cryptomodelstorage.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    CryptoModel* model;
    QStringList coinTypes;
    ModelStorage* modelStorage;

    QString fileName = "data.xml";
    QSortFilterProxyModel* filterModel;

    QMap<QString, QPixmap> icons;

    void updateSideBar();
    void closeEvent(QCloseEvent* event);

private slots:
    void initModel();
    void onAddEntryClicked();
    void onRemoveEntryClicked();
    void selectionChanged(const QModelIndex &current);
    void currentChanged(const QModelIndex &current, const QModelIndex &previous);
    void onAmountChanged(int amount);
    void modelDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int>());

};
#endif // MAINWINDOW_H
