#ifndef __Logging_Strategy__
#define __Logging_Strategy__

#include "logger_model.hpp"
//#include <fstream>
//#include <iostream>
#include <map>
//#include <memory>

class LogginStrategyBase {
    protected:
        std::map<LogType, std::string> m_LogType_dict ;
    public:
    
        LogginStrategyBase();
        virtual void log(const LogModel& model) = 0;
};

// class ConsoleLoggingStrategy : public LogginStrategyInterface{
//     private:
//         std::map<LogType, std::ostream*> m_LogAction_dict;
        
//     public:
    
//         ConsoleLoggingStrategy();
//         void log(const LogModel& model) override;
// };

// class FileLoggingStrategy : public LogginStrategyInterface{
//     private:
//         std::ofstream m_file;
//         bool m_printToConsole;
//         std::unique_ptr<ConsoleLoggingStrategy> m_logging_strategy;
        
//     public:    
//         FileLoggingStrategy(const std::string& filename, bool printToConsole= true);
//         void log(const LogModel& model) override;

//         ~FileLoggingStrategy();
// };




#endif // 