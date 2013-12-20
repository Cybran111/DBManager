#include "searchpanel.h"
#include "ui_searchpanel.h"

searchPanel::searchPanel(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::searchPanel)
{
    ui->setupUi(this);
}

searchPanel::~searchPanel()
{
    delete ui;
}
