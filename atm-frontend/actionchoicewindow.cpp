#include "actionchoicewindow.h"
#include "balancewindow.h"
#include "depositwindow.h"
#include "transactionswindow.h"
#include "transferwindow.h"
#include "ui_actionchoicewindow.h"
#include "withdrawalwindow.h"

#include <QJsonArray>

ActionChoiceWindow::ActionChoiceWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActionChoiceWindow)
{
    ui->setupUi(this);
    QPixmap pmbg(":/atm-frontend/bgwithkeypad.png");
    pmbg = pmbg.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, pmbg);
    this->setPalette(palette);
}

ActionChoiceWindow::~ActionChoiceWindow()
{
    delete ui;
    ui=nullptr;
}

void ActionChoiceWindow::on_pushButtonWithdrawal_clicked()
{
    hide();
    WithdrawalWindow *ww = new WithdrawalWindow();
    ww->show();
}

void ActionChoiceWindow::on_pushButtonBalance_clicked()
{
    hide();
    BalanceWindow *bw = new BalanceWindow();
    bw->show();
}

void ActionChoiceWindow::on_pushButtonTransactions_clicked()
{
    int acc = cs->getIsCreditSelected() ? cs->getCaId() : cs->getDaId();
    qDebug() << "\n cardsingleton ca id: " << cs->getCaId();
    HttpLibrary *hl = new HttpLibrary;
    cs->setTransactions(hl->getTransactions(acc));
    hide();
    TransactionsWindow *tw = new TransactionsWindow();
    tw->show();
}

void ActionChoiceWindow::on_pushButtonExit_clicked()
{
    this->close();
}

void ActionChoiceWindow::on_pushButtonTransfer_clicked()
{
    qDebug() << "on_pushButtonTransfer_clicked";
    hide();
    TransferWindow *tw = new TransferWindow();
    tw->show();
}

void ActionChoiceWindow::on_pushButtonDeposit_clicked()
{
    hide();
    DepositWindow *dw = new DepositWindow();
    dw->show();
}
