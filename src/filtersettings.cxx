#include "filtersettings.hxx"

FilterSettings::FilterSettings()
{
    // Initial state is that all message levels are included in the
    // filter set
    for(int i = 0; i < 5; ++i)
        m_FilterSet.insert(ut::enum_cast<MessageLevel>(i));
}


bool& FilterSettings::useThreshold()
{
    return m_UseThreshold;
}

MessageLevel& FilterSettings::threshold()
{
    return m_Threshold;
}

FilterSettings::FilterSet& FilterSettings::filterSet()
{
    return m_FilterSet;
}

bool FilterSettings::isAllowed(MessageLevel p_level) const
{
    if(m_UseThreshold)
        return ut::enum_cast(p_level) <= ut::enum_cast(m_Threshold);
    else
        return m_FilterSet.contains(p_level);
}



