#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QSqlDatabase"
#include "QSqlQuery"
#include "QDebug"
#include "QtSql"
#include <QSqlQueryModel>

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
    if (db.open())
    {
        ui->statusBar->showMessage("Connecting to DB successful",STATUSBAR_TIMEOUT);
    }
    else
    {
        ui->statusBar->showMessage("Something wrong with DB, DB is enabled?");
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dbScriptExecute()

{

    QSqlQueryModel *tableViewModel = new QSqlQueryModel;
    tableViewModel->setQuery(ui->scriptEdit->toPlainText());

    ui->tableView->setModel(tableViewModel);

    ui->statusBar->showMessage("Script executed",STATUSBAR_TIMEOUT);


}
