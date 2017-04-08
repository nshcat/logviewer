#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "filtersettings.h"
#include "message.h"
#include "messageserver.h"

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
    void displayMessage(const Message& p_msg);
    QString levelString(MessageLevel p_level) const;
    QBrush foregroundMsg(MessageLevel p_level) const;
    QBrush foreground(MessageLevel p_level) const;
    QBrush background(MessageLevel p_level) const;

    void refreshDisplay();

private slots:
    void messageReceived(Message p_msg);
    void clickedFilterSettings();
    void clickedClear();

private:
    Ui::MainWindow *ui;
    MessageServer m_Server;
    QVector<Message> m_Messages;
    FilterSettings m_Filter;
};

#endif // MAINWINDOW_H
