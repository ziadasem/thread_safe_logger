#include "../headers/console_logging_strategy.hpp" 


ConsoleLoggingStrategy::ConsoleLoggingStrategy()
: m_LogAction_dict{
        {LogType::ERROR_DEBUG, &std::cerr},
        {LogType::WARNING_DEBUG, &std::cout}, // Using std::cout as an example
        {LogType::INFO_DEBUG, &std::cout}, // Using std::cout as an example

        {LogType::INFO_RELEASE, &std::cout},  // Using std::cout as an example
        {LogType::WARNING_RELEASE, &std::cout},
        {LogType::ERROR_RELEASE, &std::cerr}
    },
 m_LogColor_dict{
        {LogType::ERROR_DEBUG, "\033[31m"},
        {LogType::WARNING_DEBUG, "\033[33m"}, // Using std::cout as an example
        {LogType::INFO_DEBUG, "\033[97m"}, // Using std::cout as an example

        {LogType::ERROR_RELEASE, "\033[31m"}, 
        {LogType::WARNING_RELEASE, "\033[33m"},
        {LogType::INFO_RELEASE, "\033[97m"},  // Using std::cout as an example
        
    } 
{
    enableANSIColors();
}

void ConsoleLoggingStrategy::enableANSIColors() { //enable ANSI Colors for windows
    #ifdef WINDOWS
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        if (GetConsoleMode(hConsole, &dwMode)) {
            SetConsoleMode(hConsole, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
        }
    #endif
}



void ConsoleLoggingStrategy::log(const LogModel &model)
{    
       
    std::string message =  m_LogType_dict[model.type] + ": " + model.message + " ; L# " + std::to_string(model.line_number)  + " ; "  + model.file_name  ;
    *m_LogAction_dict[model.type] << m_LogColor_dict[model.type]<< message  <<"\033[0m" << std::endl;
}

