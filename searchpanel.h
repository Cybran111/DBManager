#ifndef SEARCHPANEL_H
#define SEARCHPANEL_H

#include <QFrame>
#include "QSqlRelationalTableModel"

namespace Ui {
class searchPanel;
}

class searchPanel : public QFrame
{
    Q_OBJECT

public:
    explicit searchPanel(QWidget *parent = 0);
    ~searchPanel();
    QString getParameters();
    void setComboBox(QSqlRelationalTableModel *tableModel);
private slots:
    void deletePanel();

private:
    Ui::searchPanel *ui;
};

#endif // SEARCHPANEL_H
