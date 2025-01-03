#include "headers/thread_safe_logger.hpp"
#include "headers/file_logging_strategy.hpp"
#include <format>
#include <thread>
#include <vector>
#include <utility>

using namespace std;

void logSomeMessages(int id, ThreadSafeLogger& logger)
{
	for (int i{ 0 }; i < 10; ++i) {
        std::string message = "Hello from thread: " + std::to_string(id) + " and iteration # " + std::to_string(i) ;
        logger.log( message,  i%3 ==0 ?LogType::ERROR_DEBUG : i%2 ==0 ? LogType::WARNING_DEBUG :  LogType::INFO_DEBUG, __FILE__, __LINE__);
		this_thread::sleep_for(50ms);
	}
    
}

int main()
{
	std::unique_ptr<FileLoggingStrategy> strategy = std::make_unique<FileLoggingStrategy>("log_file.txt");
	auto& logger = ThreadSafeLogger::getInstance(std::move(strategy));

    logger.startLoggingThread() ;
	vector<thread> threads;
	// Create a few threads all working with the same Logger instance.
	for (int i{ 0 }; i < 10; ++i) {
		threads.emplace_back(logSomeMessages, i, ref(logger));
	}
    for (int i{ 0 }; i < 10; ++i) {
		threads[i].join();
	}
}