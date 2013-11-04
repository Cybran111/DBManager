#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QSqlDatabase"
#include "QSqlQuery"
#include "QDebug"
#include "QtSql"
#include <QSqlQueryModel>
#include <QSqlTableModel>

 #include <QPlainTextEdit>

#define STATUSBAR_TIMEOUT 3000

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


   //Open connection to DB
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("enterprises");
    db.setUserName("root");
    db.setPassword("VT.YnT;uY@+lb83|yrSL]s<N!");
    db.open();

    if (db.open()){
    //Initialize basic model
    QSqlTableModel* tableViewModel = new QSqlTableModel;
    tableViewModel->setTable("enterprise");
    tableViewModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    tableViewModel->select();
    ui->tableView->setModel(tableViewModel);
    ui->statusBar->showMessage("Connecting to DB successful",STATUSBAR_TIMEOUT);
    }
    else
        ui->statusBar->showMessage("Something wrong with DB. MySQL is launched?");

    ui->comboBox->addItems(db.tables());
    ui->comboBox->setCurrentIndex(3); //set index to enterprises
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dbScriptExecute()

{
    QSqlTableModel* tableViewModel = new QSqlTableModel;

    tableViewModel->setTable(ui->comboBox->currentText());
    tableViewModel->setFilter(ui->scriptEdit->toPlainText());
    tableViewModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    tableViewModel->select(); //applying changes

    ui->tableView->setModel(tableViewModel);
    ui->statusBar->showMessage("Script executed",STATUSBAR_TIMEOUT);


}
