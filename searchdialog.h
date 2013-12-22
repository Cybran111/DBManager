#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include "searchpanel.h"
#include "QSqlRelationalTableModel"
namespace Ui {
class searchDialog;
}

class searchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit searchDialog(QWidget *parent = 0);
    ~searchDialog();
    QString getQuery(QSqlRelationalTableModel*);

    QString query;


private:
    Ui::searchDialog *ui;
    QSqlRelationalTableModel *searchTableModel;


private slots:
    void insertSearchPanel();

    void OK();

    void Cancel();
};

#endif // SEARCHDIALOG_H
