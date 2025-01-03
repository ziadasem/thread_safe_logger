#ifndef __CONSOLE_LOGGING_STRATEGY__
#define __CONSOLE_LOGGING_STRATEGY__

#include <map>
#include <iostream>
#ifdef WINDOWS
    #include <windows.h>
#endif
#include "logging_strategy_base.hpp"


class ConsoleLoggingStrategy : public LogginStrategyBase{
    private:
        std::map<LogType, std::ostream*> m_LogAction_dict;
        std::map<LogType, std::string> m_LogColor_dict;
        
    public:
    
        ConsoleLoggingStrategy();
        void log(const LogModel& model) override;
    
    private:
       void enableANSIColors();
};

#endif // __CONSOLE_LOGGING_STRATEGY__