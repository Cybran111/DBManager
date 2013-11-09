#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>
#include <QtSql>
#include <QtGui>

#define DEFAULT_TABLE "enterprise"
#define STATUSBAR_TIMEOUT 3000

//TODO LIST
/*
 * DONE. Make add/delete table item
 * DONE. dbBox for foreigh keys
 * 3. Test operator SOUNDEX for search nearest values
 * 4. User-friendly russian-style columns
 * 5. Set DB on cybran.ru //NOTE Do it when deploying
 */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   //Set up connection to DB
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
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
    ui->dbBox->setCurrentText(DEFAULT_TABLE);

    changeModel();
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));

    ui->statusBar->showMessage("Connecting to DB successful",STATUSBAR_TIMEOUT);
    }
    else
        ui->statusBar->showMessage("Something wrong with DB. MySQL is launched?");
}

MainWindow::~MainWindow()
{
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
        QModelIndex index = tableModel->index(tableModel->rowCount()-1, tableModel->fieldIndex("name"));
        ui->tableView->setCurrentIndex(index);
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
    //FIXME trouble with setFilter("name='Borland'")
//    tableModel->setFilter("name='Borland'");

    tableModel->setFilter(ui->scriptEdit->toPlainText());
    tableModel->select();

    ui->tableView->setModel(tableModel);
    ui->tableView->resizeColumnsToContents();
    qDebug() << tableModel->query().lastQuery();
}
//}

void MainWindow::findNearest()
{
//    QString query = "Borlewfwef";
//    query.length()
//    while (query.length() !=0)
//    {

//    }
}
