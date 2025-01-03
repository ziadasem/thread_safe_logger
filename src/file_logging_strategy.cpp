#include "../headers/file_logging_strategy.hpp"

FileLoggingStrategy::FileLoggingStrategy(const std::string& filename, bool printToConsole)
    : m_printToConsole{printToConsole}
{

    m_file.open(filename); // Open in append mode
    if (!m_file.is_open()) {
        throw std::ios_base::failure("Failed to open log file: " + filename);
    }
    if (m_printToConsole) {
        m_logging_strategy = std::make_unique<ConsoleLoggingStrategy>();
    } 

}

void FileLoggingStrategy::log(const LogModel &model)
{   
    
    std::string message =  m_LogType_dict[model.type] + ": " + model.message + " ; L# " + std::to_string(model.line_number)+ " ; " + model.file_name   ;

    if (m_logging_strategy){
        m_logging_strategy->log(model);
    }
    m_file << message << std::endl;
}

FileLoggingStrategy::~FileLoggingStrategy() {}