#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H

#include <QDialog>
#include <QSet>

#include "filtersettings.hxx"

namespace Ui {
class FilterDialog;
}

class FilterDialog : public QDialog
{
    Q_OBJECT

    using FilterSet = QSet<MessageLevel>;

public:
    explicit FilterDialog(FilterSettings& p_filter, QWidget *parent = 0);
    ~FilterDialog();

private:
    void loadSettings();
    void saveSettings();
    void updateSet(MessageLevel p_level, bool p_isIn);

private slots:
    void clickedOk();
    void itemClicked();
    void thresholdChosen(bool);
    void setChosen(bool);

private:
    Ui::FilterDialog *ui;
    FilterSettings& m_FilterRef;
    FilterSet m_Set;
};

#endif // FILTERDIALOG_H
