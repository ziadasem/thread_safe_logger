#ifndef __LOGGER_MODEL_H__
#define __LOGGER_MODEL_H__

#include <string>

enum class LogType {
    INFO_DEBUG = 1,
    WARNING_DEBUG = 2,
    ERROR_DEBUG = 4,
    INFO_RELEASE = 8,
    WARNING_RELEASE = 16,
    ERROR_RELEASE = 32,
};

class LogModel {
    public:
        std::string message ;
        int line_number;
        std::string file_name;
        LogType type ;
        LogModel(const std::string& message, const std::string& file_name, int line_number, LogType type);
};

#endif // !__LOGGER_MODEL_H__


