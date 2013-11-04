#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QSqlDatabase"
#include "QSqlQuery"
#include "QDebug"
#include "QtSql"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("enterprises");
    db.setUserName("root");
    db.setPassword("VT.YnT;uY@+lb83|yrSL]s<N!");
    db.open();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dbScriptExecute()

{
    QSqlQuery query;
    query.exec(ui->scriptEdit->toPlainText());

   ui->tableWidget->setColumnCount(query.record().count());
   ui->tableWidget->setRowCount(query.size());

    int index =0;
    while (query.next()) {

        for (int i=0; i < query.record().count(); i++)
         {
             ui->tableWidget->setItem(index,i, new QTableWidgetItem(query.value(i).toString()));
         }
        index++;
     }

}
