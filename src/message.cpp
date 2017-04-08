#include <QDebug>
#include <stdexcept>
#include <ut/cast.hxx>

#include "message.h"

uint qHash(MessageLevel p_key, uint p_seed)
{
    return qHash(ut::enum_cast(p_key), p_seed);
}


Message::Message()
{

}

const QString& Message::message() const
{
    return m_Msg;
}

const QString& Message::source() const
{
    return m_Src;
}

const QDateTime& Message::timestamp() const
{
    return m_Timestamp;
}

bool Message::isBare() const
{
    return m_IsBare;
}

MessageLevel Message::level() const
{
    return m_Level;
}

bool Message::tryParse(QByteArray& p_data)
{
    // We need at least 2 bytes to determine lenght of both message
    // and source fields
    if(p_data.length() < 2)
        return false;

    // We can extract length information
    quint8 t_lenMsg; // Length of message
    quint8 t_lenSrc; // Length of source

    // Stream used to extract binary values
    QDataStream t_stream(&p_data, QIODevice::ReadWrite);
    t_stream >> t_lenMsg >> t_lenSrc;

    // Expected length of whole packet
    const quint32 t_pLen = t_lenMsg + t_lenSrc + fixed_length;

    // Decide if there is enough data available to read the whole packet
    if(p_data.length() >= t_pLen)
    {
        // Read remaining data
        quint8 t_level;
        quint8 t_isBare;
        quint64 t_timestamp;
        t_stream >> t_level >> t_isBare >> t_timestamp;

        m_Timestamp = QDateTime::fromTime_t(t_timestamp);
        m_IsBare = (t_isBare == 0x1u);

        // TODO use ut::enum_cast
        // Convert message level to enumeration, checking bounds
        if(t_level > ut::enum_cast(MessageLevel::Debug))
            throw ::std::runtime_error("Message: Received message level out of bounds!");
        else m_Level = ut::enum_cast<MessageLevel>(t_level);

        // Convert strings.
        m_Msg = QString::fromLocal8Bit(p_data.data() + fixed_length, t_lenMsg);
        m_Src = QString::fromLocal8Bit(p_data.data() + fixed_length + t_lenMsg, t_lenSrc);

        // Remove used-up data from buffer
        p_data.remove(0, t_pLen);

        return true;
    }
    else return false;  // There was not enough data to read the whole packet.
}

