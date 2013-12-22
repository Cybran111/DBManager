#ifndef CHOOSEDB_H
#define CHOOSEDB_H

#include <QDialog>

namespace Ui {
class chooseDB;
}

class chooseDB : public QDialog
{
    Q_OBJECT

public:
    explicit chooseDB(QWidget *parent = 0);
    ~chooseDB();
    QString hostname();
    QString schema();
    QString user();
    QString password();

private:
    Ui::chooseDB *ui;
};

#endif // CHOOSEDB_H
