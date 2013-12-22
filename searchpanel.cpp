#include "searchpanel.h"
#include "ui_searchpanel.h"
#include "QSqlRelationalTableModel"
#include "QDebug"

searchPanel::searchPanel(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::searchPanel)
{
    ui->setupUi(this);
}

searchPanel::~searchPanel()
{
    delete ui;
}

void searchPanel::setComboBox(QSqlRelationalTableModel *tableModel)
{
    //trying to keep exist names of columns, another methods are not working
    for (int i =0;tableModel->headerData(i,Qt::Horizontal).toString().toInt()==0;i++){
        ui->columnBox->addItem(tableModel->headerData(i,Qt::Horizontal).toString());
    }
}

QString searchPanel::getParameters()
{
    QString par;
    par = ui->columnBox->currentText()+" ";
    if (ui->conditionBox->currentText()=="LIKE")
            par+=ui->conditionBox->currentText()+" '%"+
                ui->patternEdit->toPlainText()+"%'";

    else if (ui->conditionBox->currentText()=="=")
            par+=ui->conditionBox->currentText()+" '"+
                ui->patternEdit->toPlainText()+"'";
    return par;
}

void searchPanel::deletePanel()
{
delete this;
}
