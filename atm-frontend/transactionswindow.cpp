#include "transactionswindow.h"
#include "ui_transactionswindow.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QStandardItemModel>

TransactionsWindow::TransactionsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransactionsWindow)
{
    ui->setupUi(this);

    QJsonArray arr = cs->getTransactions();
    QStandardItemModel *table_model = new QStandardItemModel(arr.size(),3);
    table_model->setHeaderData(0, Qt::Horizontal, QObject::tr("Summa"));
    table_model->setHeaderData(1, Qt::Horizontal, QObject::tr("Aika"));
    table_model->setHeaderData(2, Qt::Horizontal, QObject::tr("Tyyppi"));

    QJsonObject jsob;
    int row = arr.size() - 1;
    foreach(const QJsonValue &value, arr) {
        jsob = value.toObject();
        QStandardItem *amount = new QStandardItem(jsob["amount"].toString());
        table_model->setItem(row, 0, amount);
        amount->setTextAlignment(Qt::AlignCenter);
        QDateTime timestamp;
        timestamp.setTime_t(jsob["time"].toString().toInt());
        QStandardItem *time = new QStandardItem(timestamp.toString(Qt::SystemLocaleShortDate));
        table_model->setItem(row, 1, time);
        time->setTextAlignment(Qt::AlignCenter);
        QStandardItem *type = new QStandardItem(jsob["action"].toString());
        table_model->setItem(row, 2, type);
        type->setTextAlignment(Qt::AlignCenter);
        row -= 1;
    }

    if(cs->getIsCreditSelected()){
        ui->labelCardId->setText("Luottotili: " + QString::number(cs->getCaId()));
    } else {
        ui->labelCardId->setText("Pankkitili: " + QString::number(cs->getDaId()));
    }

    ui->tableViewTransactions->setModel(table_model);
    ui->tableViewTransactions->setColumnWidth(0, 100);
    ui->tableViewTransactions->setColumnWidth(1, 160);
    ui->tableViewTransactions->setColumnWidth(2, 100);

    QPixmap pmbg(":/atm-frontend/bg.png");
    pmbg = pmbg.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, pmbg);
    this->setPalette(palette);
}

TransactionsWindow::~TransactionsWindow()
{
    delete ui;
    ui=nullptr;
}

void TransactionsWindow::on_pushButtonExit_clicked()
{
    this->close();
}
