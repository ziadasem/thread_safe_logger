 #include "../headers/logger_model.hpp"

 LogModel::LogModel(const std::string& message, const std::string& file_name, int line_number, LogType type)
         : message{message}, file_name{file_name}  ,line_number{line_number}, type{type} 
    {
            
    }