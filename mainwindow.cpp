#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "choosedb.h"
#include "ui_choosedb.h"
#include "searchdialog.h"
#include <QSqlRelationalTableModel>
#include <QtSql>
#include <QtGui>

#define DEFAULT_TABLE "enterprise"
#define STATUSBAR_TIMEOUT 3000

//TODO LIST
/*
 * DONE. Make add/delete table item
 * DONE. dbBox for foreigh keys
 * DONE. Test operator SOUNDEX for search nearest values
 * 4. User-friendly russian-style columns without bugs with relations
 * UNFIXED. Set DB on cybran.ru //NOTE Do it when deploying
 * DONE. Make DB Chooser.
 */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   //Set up connection to DB
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("enterprises");
    db.setUserName("root");
    db.setPassword("VT.YnT;uY@+lb83|yrSL]s<N!");

    //Connecting...
    if (db.open()){
    //Initialize default model

        tableModel = new QSqlRelationalTableModel;
    tableModel->setEditStrategy(QSqlTableModel::OnFieldChange);

    ui->dbBox->addItems(db.tables());
    //ui->dbBox->setCurrentText(DEFAULT_TABLE);

    changeModel();
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));

    ui->statusBar->showMessage("Connecting to DB successful",STATUSBAR_TIMEOUT);

    }
    else
    {
        ui->statusBar->showMessage("Something wrong with DB. MySQL is launched?");
    }
}
MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}

void MainWindow::dbScriptExecute()
{
    changeModel();
    ui->statusBar->showMessage("Script executed",STATUSBAR_TIMEOUT);
}

void MainWindow::addItem()
{
        tableModel->insertRow(tableModel->rowCount());
        QModelIndex index = tableModel->index(tableModel->rowCount()-1, tableModel->fieldIndex("name")); // set index to new row and edit
        ui->tableView->setCurrentIndex(index);                                                           //field 'name'
        ui->tableView->edit(index);
}

void MainWindow::deleteItem()
{
    tableModel->removeRow(ui->tableView->currentIndex().row());
}

void MainWindow::changeModel()
{
    tableModel->setTable(ui->dbBox->currentText());
    //set foreigh keys
    if (tableModel->tableName() == "enterprise"){
    tableModel->setRelation(tableModel->fieldIndex("country"),QSqlRelation("country","id_country","name"));
    tableModel->setRelation(tableModel->fieldIndex("city"),QSqlRelation("cities","id_cities","name"));
    tableModel->setRelation(tableModel->fieldIndex("business_form"),QSqlRelation("business_form","id_business_form","name"));
    tableModel->setRelation(tableModel->fieldIndex("industry"),QSqlRelation("industry","id_industry","name"));
    }
    if (tableModel->tableName() == "cities")
    {
        tableModel->setRelation(tableModel->fieldIndex("country"),QSqlRelation("country","id_country","name"));
    }

    tableModel->setFilter(ui->scriptEdit->text());

    tableModel->select();

    ui->tableView->setModel(tableModel);
    ui->tableView->resizeColumnsToContents();
}

void MainWindow::findNearest()
{
   QString query = ui->scriptEdit->text();

   while (!query.isEmpty())
   {
        tableModel->setFilter(tableModel->tableName()+".name LIKE '"+query+"%'");
        tableModel->select();
        if (tableModel->rowCount()!=0){ //if tableModel have something...
            ui->tableView->setModel(tableModel);
            ui->tableView->resizeColumnsToContents();
            break;
            }
        else
        {
            query.remove(query.length()-1,1); //remove last symbol
        }
   }
}

void MainWindow::showSettings()
{
    chooseDB *Dialog=new chooseDB();
    Dialog->exec();
    if(Dialog->result()==1)
    {
        db.setHostName(Dialog->hostname());
        db.setDatabaseName(Dialog->schema());
        db.setUserName(Dialog->user());
        db.setPassword(Dialog->password());
        db.open();

    }

}


void MainWindow::extendedSearch()
{
    searchDialog *form = new searchDialog;

    QSqlQueryModel *queryModel = new QSqlQueryModel;

    queryModel->setQuery("SELECT * FROM "+
                         tableModel->tableName()
                         +" WHERE "+
                         form->getQuery(tableModel),db);
    if(queryModel->query().isActive())
    {
        ui->tableView->setModel(queryModel);
        ui->tableView->resizeColumnsToContents();
    }
}
