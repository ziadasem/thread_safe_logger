#include "../headers/logging_strategy_base.hpp"

LogginStrategyBase::LogginStrategyBase() : 
    m_LogType_dict
        {
            {LogType::INFO_DEBUG, "INFO_DEBUG"},
            {LogType::WARNING_DEBUG, "WARNING_DEBUG"},
            {LogType::ERROR_DEBUG, "ERROR_DEBUG"},

            {LogType::INFO_RELEASE, "INFO_RELEASE"},
            {LogType::WARNING_RELEASE, "WARNING_RELEASE"},
            {LogType::ERROR_RELEASE, "ERROR_RELEASE"}
        } 
    {}
