#ifndef SEARCHPANEL_H
#define SEARCHPANEL_H

#include <QFrame>

namespace Ui {
class searchPanel;
}

class searchPanel : public QFrame
{
    Q_OBJECT

public:
    explicit searchPanel(QWidget *parent = 0);
    ~searchPanel();

private:
    Ui::searchPanel *ui;
};

#endif // SEARCHPANEL_H
