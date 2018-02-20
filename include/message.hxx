#ifndef MESSAGE_H
#define MESSAGE_H

#include <QByteArray>
#include <QDataStream>
#include <QString>
#include <QDateTime>

enum class MessageLevel
{
    Fatal = 0,
    Error,
    Warning,
    Info,
    Debug
};

uint qHash(MessageLevel p_key, uint p_seed);

class Message
{
public:
    Message();
    Message(const Message&) = default;
    Message(Message&&) = default;
    Message& operator=(const Message&) = default;
    Message& operator=(Message&&) = default;

public:
    bool tryParse(QByteArray& p_data);

public:
    const QString& message() const;
    const QString& source() const;
    const QString& tag() const;
    const QDateTime& timestamp() const;
    bool isBare() const;
    MessageLevel level() const;

private:
	QString m_Tag;
    QString m_Msg;
    QString m_Src;
    QDateTime m_Timestamp;
    bool m_IsBare{ };
    MessageLevel m_Level{ };

    // Length of the fixed part of a package, in bytes
    constexpr static quint32 fixed_length = 13;
};

#endif // MESSAGE_H
