#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "cardsingleton.h"
#include "httplibrary.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

public slots:
    void onKeyPressed(const QString &text);

private slots:
    void on_pushButtonCheckPin_clicked();

    void on_pushButtonExit_clicked();

private:
    Ui::Login *ui;
    CardSingleton *cs = CardSingleton::getInstance();
    QString pin;
};

#endif // LOGIN_H
