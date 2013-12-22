#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlRelationalTableModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private:
    Ui::MainWindow *ui;
      QSqlRelationalTableModel* tableModel;
      QSqlDatabase db;
      void changeModel();
      //void extendedSearch();

public slots:
    void dbScriptExecute();
    void addItem();
    void deleteItem();
    void findNearest();
    void showSettings();
    void extendedSearch();

//private slots:
//    void on_tableView_clicked(const QModelIndex &index);
};

#endif // MAINWINDOW_H
