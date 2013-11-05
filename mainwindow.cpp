#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlTableModel>

#include <QSqlRecord>

#define STATUSBAR_TIMEOUT 3000

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
    QSqlTableModel* tableViewModel = new QSqlTableModel;
    tableViewModel->setTable("enterprise");
    tableViewModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    tableViewModel->select();

    ui->tableView->setModel(tableViewModel);
    ui->statusBar->showMessage("Connecting to DB successful",STATUSBAR_TIMEOUT);
    ui->comboBox->addItems(db.tables());
    ui->comboBox->setCurrentText("enterprise");
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
    QSqlTableModel* tableViewModel = new QSqlTableModel;

    tableViewModel->setTable(ui->comboBox->currentText());
    tableViewModel->setFilter(ui->scriptEdit->toPlainText());
    tableViewModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    tableViewModel->select(); //applying changes

    ui->tableView->setModel(tableViewModel);
    ui->statusBar->showMessage("Script executed",STATUSBAR_TIMEOUT);

    //QSqlRecord record = tableViewModel->col(table);

    //tableViewModel->insertRecord(-1,)
}
