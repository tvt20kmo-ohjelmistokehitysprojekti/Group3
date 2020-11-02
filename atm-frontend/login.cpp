#include "login.h"
#include "ui_login.h"
#include "httplibrary.h"

Login::Login(QString cardId, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->labelCardId->setText(cardId);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButtonCheckPin_clicked()
{
    HttpLibrary *hl = new HttpLibrary;
    hl->checkPin(this->ui->labelCardId->text(), this->ui->lineEditPin->text());
}
