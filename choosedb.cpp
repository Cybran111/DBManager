#include "choosedb.h"
#include "ui_choosedb.h"

chooseDB::chooseDB(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chooseDB)
{
    ui->setupUi(this);
}

chooseDB::~chooseDB()
{
    delete ui;
}
QString chooseDB::hostname()
{
    return ui->hostnameEdit->toPlainText();
}

QString chooseDB::schema()
{
    return ui->schemaEdit->toPlainText();
}

QString chooseDB::user()
{
    return ui->userEdit->toPlainText();
}

QString chooseDB::password()
{
    return ui->passwordEdit->text();
}
