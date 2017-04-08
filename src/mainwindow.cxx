#include <QTreeWidget>
#include <QTreeWidgetItem>

#include <ut/cast.hxx>

#include "filterdialog.hxx"
#include "mainwindow.hxx"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_Server(1337)
{
    ui->setupUi(this);

    connect(&m_Server, SIGNAL(messageReceived(Message)),
            this, SLOT(messageReceived(Message)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::messageReceived(Message p_msg)
{
    m_Messages.push_back(p_msg);

    if(m_Filter.isAllowed(p_msg.level()))
        displayMessage(p_msg);
}

void MainWindow::refreshDisplay()
{
    // Clear tree widget
    ui->treeWidget->clear();

    // Display all messages that are accepted by current filter settings
    for(const auto& t_msg: m_Messages)
    {
        if(m_Filter.isAllowed(t_msg.level()))
            displayMessage(t_msg);
    }
}

void MainWindow::clickedFilterSettings()
{
    FilterDialog t_dlg{m_Filter};
    t_dlg.exec();
    refreshDisplay();
}

void MainWindow::clickedClear()
{
    m_Messages.clear();
    refreshDisplay();
}

void MainWindow::displayMessage(const Message& p_msg)
{
    // Create new entry
    QTreeWidgetItem* t_item{};

    if(!p_msg.isBare())
    {
        t_item = new QTreeWidgetItem(QStringList
        {
            p_msg.source(),
            p_msg.timestamp().toString("hh:mm:ss"),
            levelString(p_msg.level()),
            p_msg.message()
        });
    }
    else
    {
        t_item = new QTreeWidgetItem(QStringList
        {
            "",
            "",
            "",
            p_msg.message()
        });
    }

    // Set colors
    for(int i = 0; i < 4; ++i)
    {
        t_item->setBackground(i, background(p_msg.level()));

        t_item->setForeground(i,
            (i == 3 ? foregroundMsg(p_msg.level()) : foreground(p_msg.level())));
    }



    // Add item
    ui->treeWidget->addTopLevelItem(t_item);
}

QString MainWindow::levelString(MessageLevel p_level) const
{
    static const QString t_Array[5] = {
        "Fatal",
        "Error",
        "Warning",
        "Info",
        "Debug"
    };

    const auto t_level = ut::enum_cast(p_level);

    if(t_level <= ut::enum_cast(MessageLevel::Debug))
        return t_Array[t_level];
    else throw ::std::runtime_error("levelString: MessageLevel out of bounds!");
}

QBrush MainWindow::foregroundMsg(MessageLevel p_level) const
{
    const QColor t_Array[5] = {
        QColor(255, 128, 128),
        QColor(255, 128, 128),
        QColor(255, 217, 128),
        QColor(195, 195, 201),
        QColor(195, 195, 201)
    };

    const auto t_level = ut::enum_cast(p_level);

    if(t_level <= ut::enum_cast(MessageLevel::Debug))
        return QBrush(t_Array[t_level]);
    else throw ::std::runtime_error("foregroundMsg: MessageLevel out of bounds!");
}

QBrush MainWindow::foreground(MessageLevel p_level) const
{
    const QColor t_Array[5] = {
        QColor(255, 72, 72),
        QColor(255, 72, 72),
        QColor(255, 198, 64),
        QColor(195, 195, 201),
        QColor(195, 195, 201)
    };

    const auto t_level = ut::enum_cast(p_level);

    if(t_level <= ut::enum_cast(MessageLevel::Debug))
        return QBrush(t_Array[t_level]);
    else throw ::std::runtime_error("foreground: MessageLevel out of bounds!");
}

QBrush MainWindow::background(MessageLevel p_level) const
{
    const QColor t_Array[5] = {
        QColor(77, 22, 22),
        QColor(77, 22, 22),
        QColor(102, 76, 14),
        QColor(30, 30, 28),
        QColor(30, 30, 28)
    };

    const auto t_level = ut::enum_cast(p_level);

    if(t_level <= ut::enum_cast(MessageLevel::Debug))
        return QBrush(t_Array[t_level]);
    else throw ::std::runtime_error("background: MessageLevel out of bounds!");
}
