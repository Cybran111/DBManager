#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QtSql>
#include <QtGui>
//#include <QSqlRelationalDelegate>
//#include <QMessageBox>

#define DEFAULT_TABLE "enterprise"
#define STATUSBAR_TIMEOUT 3000

//TODO LIST
/*
 * 1. Make add/delete table item
 * DONE. Combobox for foreigh keys
 * 3. Test operator SOUNDEX for search nearest values
 * 4. User-friendly columns
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
    QSqlRelationalTableModel* tableModel = new QSqlRelationalTableModel;
    tableModel->setTable(DEFAULT_TABLE);
    tableModel->setEditStrategy(QSqlTableModel::OnFieldChange);

    tableModel->setRelation(tableModel->fieldIndex("country"),QSqlRelation("country","id_country","name"));
    tableModel->setRelation(tableModel->fieldIndex("city"),QSqlRelation("cities","id_cities","name"));
    tableModel->setRelation(tableModel->fieldIndex("business_form"),QSqlRelation("business_form","id_business_form","name"));
    tableModel->setRelation(tableModel->fieldIndex("industry"),QSqlRelation("industry","id_industry","name"));


    tableModel->select();


    ui->tableView->setModel(tableModel);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));

    ui->statusBar->showMessage("Connecting to DB successful",STATUSBAR_TIMEOUT);

    ui->comboBox->addItems(db.tables());
    ui->comboBox->setCurrentText(DEFAULT_TABLE);


    }
    else
    {
        ui->statusBar->showMessage("Something wrong with DB. MySQL is launched?");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dbScriptExecute()

{
    QSqlRelationalTableModel* tableModel = new QSqlRelationalTableModel;

    tableModel->setTable(ui->comboBox->currentText());
    if (tableModel->tableName()=="enterprise"){

        tableModel->setRelation(tableModel->fieldIndex("country"),QSqlRelation("country","id_country","name"));
        tableModel->setRelation(tableModel->fieldIndex("city"),QSqlRelation("cities","id_cities","name"));
        tableModel->setRelation(tableModel->fieldIndex("business_form"),QSqlRelation("business_form","id_business_form","name"));
        tableModel->setRelation(tableModel->fieldIndex("industry"),QSqlRelation("industry","id_industry","name"));

    }

    tableModel->setFilter(ui->scriptEdit->toPlainText());
    tableModel->select(); //applying changes
    ui->tableView->setModel(tableModel);
    ui->statusBar->showMessage("Script executed",STATUSBAR_TIMEOUT);

    //QSqlRecord record = tableModel->col(table);

    //tableModel->insertRecord(-1,)
}
