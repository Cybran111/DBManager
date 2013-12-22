#include "searchdialog.h"
#include "ui_searchdialog.h"

#include "QDebug"

searchDialog::searchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::searchDialog)
{
    ui->setupUi(this);
}
searchDialog::~searchDialog()
{

    //qDebug() << ui->verticalLayout->itemAt(0)->widget();
    delete ui;
}

void searchDialog::insertSearchPanel()
{
     searchPanel *panel = new searchPanel;
     panel->setComboBox(searchTableModel);
     ui->verticalLayout->addWidget(panel);
}

QString searchDialog::getQuery(QSqlRelationalTableModel *tableModel)
{
    searchTableModel = tableModel;
    exec();
    return query;
}

void searchDialog::OK()
{
    query+= ((searchPanel*)ui->verticalLayout->itemAt(0)->widget())->getParameters();
    delete ui->verticalLayout->itemAt(0)->widget();
    while (ui->verticalLayout->itemAt(0)!=0)
    {
        query+= " AND "+((searchPanel*)ui->verticalLayout->itemAt(0)->widget())->getParameters();
        delete ui->verticalLayout->itemAt(0)->widget();
    }
    searchDialog::accept();
}

void searchDialog::Cancel()
{
//query="";
searchDialog::reject();
}
