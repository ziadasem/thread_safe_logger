#ifndef __File_Logging_Strategy__
#define __File_Logging_Strategy__

#include <memory>
#include <fstream>

#include "logger_model.hpp"
#include "logging_strategy_base.hpp"
#include "console_logging_strategy.hpp"


class FileLoggingStrategy : public LogginStrategyBase{
    private:
        std::ofstream m_file;
        bool m_printToConsole;
        std::unique_ptr<ConsoleLoggingStrategy> m_logging_strategy;
        
    public:    
        FileLoggingStrategy(const std::string& filename, bool printToConsole= true);
        void log(const LogModel& model) override;

        ~FileLoggingStrategy();
};




#endif // __File_Logging_Strategy__