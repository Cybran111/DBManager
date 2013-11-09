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
      void changeModel();

public slots:
    void dbScriptExecute();
    void addItem();
    void deleteItem();
    void findNearest();
};

#endif // MAINWINDOW_H
