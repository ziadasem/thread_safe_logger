#ifndef __THREAD_SAFE_LOGGER__
#define __THREAD_SAFE_LOGGER__

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>
#include <map>

#include "logger_model.hpp"
#include "logging_strategy_base.hpp"


#define print(X) {std::cout << X ;}
#define println(X) {std::cout << X << std::endl;}
 
class ThreadSafeLogger {
    private:
        std::mutex m_mtx ;
        std::condition_variable  m_cv ;
        std::queue<LogModel> m_queue ;
        std::thread m_loggingThread;
        int loggLevel ;
        std::atomic<bool> m_stop_requested;
        std::unique_ptr<LogginStrategyBase> m_loggingStrategy ;

        // Private static instance and mutex for the Singleton
        static std::unique_ptr<ThreadSafeLogger> m_instance;
        static std::mutex m_instanceMutex;
    public:
        static ThreadSafeLogger& getInstance(std::unique_ptr<LogginStrategyBase> loggingStrategy = nullptr);

        // ThreadSafeLogger(std::unique_ptr<LogginStrategyBase> loggingStrategy);
        ~ThreadSafeLogger();
        void setLoggingOutput(
                            bool show_INFO_DEBUG =true, 
                            bool show_WARNING_DEBUG =true, 
                            bool show_ERROR_DEBUG =true, 
                            bool show_INFO_RELEASE =true, 
                            bool show_WARNING_RELEASE=true, 
                            bool show_ERROR_RELEASE=true);
        void log(const std::string& message, LogType logType, const std::string &file_name,
                           const int lineNumbe) ;
        void startLoggingThread();
    
    private:
        explicit ThreadSafeLogger(std::unique_ptr<LogginStrategyBase> loggingStrategy);
        ThreadSafeLogger(const ThreadSafeLogger&) = delete;
        ThreadSafeLogger& operator=(const ThreadSafeLogger&) = delete;

        void loggesHandlerThread();
        void processLogs(std::queue<LogModel> &tempQueue);
};

#endif