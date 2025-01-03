#include "../headers/thread_safe_logger.hpp"

// Initialize static members
std::unique_ptr<ThreadSafeLogger> ThreadSafeLogger::m_instance = nullptr;
std::mutex ThreadSafeLogger::m_instanceMutex;

 ThreadSafeLogger ::ThreadSafeLogger(std::unique_ptr<LogginStrategyBase> loggingStrategy) 
    :loggLevel{63},m_stop_requested{false}, m_loggingStrategy{std::move(loggingStrategy)}{}

ThreadSafeLogger& ThreadSafeLogger::getInstance(std::unique_ptr<LogginStrategyBase> loggingStrategy) {
    std::lock_guard<std::mutex> lock(m_instanceMutex);
    if (!m_instance) {
        if (!loggingStrategy) {
            throw std::runtime_error("Logging strategy must be provided on the first call to getInstance.");
        }
        m_instance.reset(new ThreadSafeLogger(std::move(loggingStrategy)));
    }
    return *m_instance;
}

void ThreadSafeLogger::setLoggingOutput(bool show_INFO_DEBUG,
                                        bool show_WARNING_DEBUG,
                                        bool show_ERROR_DEBUG,
                                        bool show_INFO_RELEASE,
                                        bool show_WARNING_RELEASE,
                                        bool show_ERROR_RELEASE)
{
    if (show_INFO_DEBUG)
    {
        loggLevel |= static_cast<int>(LogType::INFO_DEBUG);
    }
    if (show_WARNING_DEBUG)
    {
        loggLevel |= static_cast<int>(LogType::WARNING_DEBUG);
    }
    if (show_ERROR_DEBUG)
    {
        loggLevel |= static_cast<int>(LogType::ERROR_DEBUG);
    }
    if (show_INFO_RELEASE)
    {
        loggLevel |= static_cast<int>(LogType::INFO_RELEASE);
    }
    if (show_WARNING_RELEASE)
    {
        loggLevel |= static_cast<int>(LogType::WARNING_RELEASE);
    }
    if (show_ERROR_RELEASE)
    {
        loggLevel |= static_cast<int>(LogType::ERROR_RELEASE);
    }
}

void ThreadSafeLogger::log(const std::string &message,
                            LogType logType,
                           const std::string &file_name,
                           const int lineNumber)
{
    if ((loggLevel & static_cast<int>(logType)) == 0)
    {
        return;
    }

    {
        std::unique_lock<std::mutex> lock(m_mtx);
        m_queue.push(std::move(LogModel(message, file_name, lineNumber, logType)));
    }

    m_cv.notify_all();
}

void ThreadSafeLogger::startLoggingThread() {
    m_loggingThread = std::thread(&ThreadSafeLogger::loggesHandlerThread, this);
}

void ThreadSafeLogger::loggesHandlerThread()
{

    std::queue<LogModel> localQueue;
    while (!m_stop_requested)
    {
        //critical section
        {
            std::unique_lock<std::mutex> lock{m_mtx};
            m_cv.wait(lock, [this]
                      { return !m_queue.empty() || m_stop_requested ;});
            localQueue.swap(m_queue); // avoid racing conditions
            if (m_stop_requested){
                lock.unlock();
                processLogs(localQueue); 
                break;
            }
        }

        processLogs(localQueue); // process logs in the local queue and print them
    }
}

void ThreadSafeLogger::processLogs(std::queue<LogModel> &tempQueue) {
    while (!tempQueue.empty()){
        LogModel log = std::move(tempQueue.front());
        tempQueue.pop();
        m_loggingStrategy->log(log);            
    }
}


 ThreadSafeLogger::~ThreadSafeLogger()
 {
    m_stop_requested = true;
    m_cv.notify_all();
    m_loggingThread.join();
 }

