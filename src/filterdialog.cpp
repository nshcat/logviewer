#include <QRadioButton>
#include <QListWidget>
#include <QComboBox>
#include "filterdialog.h"
#include "ui_filterdialog.h"

FilterDialog::FilterDialog(FilterSettings& p_filter, QWidget *parent) :
    QDialog(parent),
    m_FilterRef(p_filter),
    ui(new Ui::FilterDialog)
{
    ui->setupUi(this);
    loadSettings();
}

FilterDialog::~FilterDialog()
{
    delete ui;
}

void FilterDialog::loadSettings()
{
    // Check the right radiobutton and disable controls
    ui->bttThreshold->setChecked(m_FilterRef.useThreshold());
    ui->bttSet->setChecked(!m_FilterRef.useThreshold());
    ui->boxThreshold->setEnabled(m_FilterRef.useThreshold());
    ui->lstSet->setEnabled(!m_FilterRef.useThreshold());

    // Load filter set
    for(int i = 0; i < 5; ++i)
    {
        const auto t_level = ut::enum_cast<MessageLevel>(i);
        updateSet(t_level, m_FilterRef.filterSet().contains(t_level));
    }

    // Select threshold item in combobox
    ui->boxThreshold->setCurrentIndex(ut::enum_cast(m_FilterRef.threshold()));
}

void FilterDialog::updateSet(MessageLevel p_level, bool p_isIn)
{
    // Modify underlying set accordingly
    if(p_isIn) m_Set.insert(p_level);
    else m_Set.remove(p_level);

    // Retrieve item in list widget and set color
    const auto t_color = p_isIn ? QColor(0, 255, 0) : QColor(255, 0, 0);
    ui->lstSet->item(ut::enum_cast(p_level))->setBackgroundColor(t_color);
}

void FilterDialog::itemClicked()
{
    // Retrieve clicked index
    const auto t_index = ui->lstSet->selectionModel()->currentIndex().row();

    // Convert it to message level
    const auto t_level = ut::enum_cast<MessageLevel>(t_index);

    // Toggle it
    updateSet(t_level, !m_Set.contains(t_level));
}

void FilterDialog::saveSettings()
{
    // Apply filter set
    m_FilterRef.filterSet() = m_Set;

    // Retrieve threshold settings
    m_FilterRef.useThreshold() = ui->bttThreshold->isChecked();
    m_FilterRef.threshold() = ut::enum_cast<MessageLevel>(ui->boxThreshold->currentIndex());
}

void FilterDialog::clickedOk()
{
    // Save current settings
    saveSettings();

    // Close dialog
    accept();
}

void FilterDialog::thresholdChosen(bool p_b)
{
    if(p_b)
    {
        ui->boxThreshold->setEnabled(true);
        ui->lstSet->setEnabled(false);
    }
}

void FilterDialog::setChosen(bool p_b)
{
    if(p_b)
    {
        ui->boxThreshold->setEnabled(false);
        ui->lstSet->setEnabled(true);
    }
}
