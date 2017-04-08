#ifndef FILTERSETTINGS_H
#define FILTERSETTINGS_H

#include <QSet>
#include <ut/cast.hxx>
#include "message.hxx"

class FilterSettings
{
    using FilterSet = QSet<MessageLevel>;

public:
    FilterSettings();
    ~FilterSettings() = default;
    FilterSettings(const FilterSettings&) = default;
    FilterSettings(FilterSettings&&) = default;

    FilterSettings& operator=(const FilterSettings&) = default;
    FilterSettings& operator=(FilterSettings&&) = default;

public:
    bool& useThreshold();
    MessageLevel& threshold();
    FilterSet& filterSet();

public:
    bool isAllowed(MessageLevel p_level) const;

private:
    bool m_UseThreshold{true};
    MessageLevel m_Threshold{MessageLevel::Debug};
    FilterSet m_FilterSet;
};

#endif // FILTERSETTINGS_H
