#ifndef WIZARDPAGE_H
#define WIZARDPAGE_H

#include <QWizardPage>

namespace Ui {
class WizardPage;
}

class WizardPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit WizardPage(QWidget *parent = 0);
    ~WizardPage();

private:
    Ui::WizardPage *ui;
};

#endif // WIZARDPAGE_H
