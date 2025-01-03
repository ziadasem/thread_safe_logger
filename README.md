# ThreadSafeLogger


A thread-safe logging system with support for different logging strategies, including logging to console and file. The logger ensures that log entries are handled asynchronously and safely in a multi-threaded environment.

## Features

- **Thread-Safety**: Ensures that log messages are processed safely across multiple threads.
- **Logging Strategies**: Supports multiple logging strategies including:
  - **Console Logging**: Logs messages to the console with customizable colors.
  - **File Logging**: Logs messages to a specified file, with an optional console output.
- **Log Levels**: Supports different log types, including:
  - `INFO_DEBUG`, `WARNING_DEBUG`, `ERROR_DEBUG`
  - `INFO_RELEASE`, `WARNING_RELEASE`, `ERROR_RELEASE`
- **Singleton Pattern**: Ensures only one instance of the logger is created and shared across the application.

## Files

### `ThreadSafeLogger.hpp`

Defines the main `ThreadSafeLogger` class responsible for managing log messages. It includes methods for logging messages, setting the log output, and managing the logging thread. It follows the singleton pattern to ensure only one instance exists.

- `log`: Logs a message with a specific log type.
- `startLoggingThread`: Starts the logging thread to process log messages.
- `setLoggingOutput`: Configures which types of logs to display.

### `LoggingStrategyBase.hpp`

Defines the interface for logging strategies. Any logging strategy (such as console or file logging) must implement this interface and define the `log` method to handle logging.

### `LogModel.hpp`

Defines the `LogModel` class, which contains the structure of a log message, including the message content, file name, line number, and log type.

### `FileLoggingStrategy.hpp`

Implements the `LogginStrategyBase` interface for logging to a file. The log messages are written to a specified file, with an optional console output.

- Constructor: Initializes the file logging strategy with a file name and optional console output flag.
- Destructor: Ensures the file is properly closed when the logging strategy is no longer needed.

### `ConsoleLoggingStrategy.hpp`

Implements the `LogginStrategyBase` interface for logging to the console. Supports ANSI color codes to colorize log messages based on log type.

- `enableANSIColors`: Enables ANSI color codes for console output (works on systems that support it).

## Installation

1. Clone or download the repository.
2. Include the header files in your project.
3. Link to any necessary libraries (if needed for console or file logging).

## Usage

### 1. Setting up the Logger

To use the logger, you need to create an instance of `ThreadSafeLogger`. You can specify the logging strategy (e.g., `ConsoleLoggingStrategy`, `FileLoggingStrategy`) during initialization.

```cpp
#include "thread_safe_logger.hpp"
#include "console_logging_strategy.hpp"
#include "file_logging_strategy.hpp"

int main() {
    // Example: Using Console Logging
    auto consoleStrategy = std::make_unique<ConsoleLoggingStrategy>();
    ThreadSafeLogger& logger = ThreadSafeLogger::getInstance(std::move(consoleStrategy));

    // Log messages
    logger.log("This is an info message", LogType::INFO_DEBUG, __FILE__, __LINE__);

    // Example: Using File Logging
    auto fileStrategy = std::make_unique<FileLoggingStrategy>("log.txt", true);
    ThreadSafeLogger& loggerFile = ThreadSafeLogger::getInstance(std::move(fileStrategy));

    // Log messages
    loggerFile.log("This is an error message", LogType::ERROR_DEBUG, __FILE__, __LINE__);

    return 0;
}
```

### 2. Log Types
The logger supports different log types, defined in LogType:

* INFO_DEBUG
* WARNING_DEBUG
* ERROR_DEBUG
* INFO_RELEASE
* WARNING_RELEASE
* ERROR_RELEASE

Each log type can be configured to display in the desired logging output (console or file).

### 3. Customizing the Logger
You can customize which types of logs are displayed in both debug and release modes.

```cpp
logger.setLoggingOutput(true, true, true, true, true, true);
```

### 4. Multi-threaded Logging

The logger is thread-safe, meaning it can be used in multi-threaded applications where different threads log messages concurrently.

```cpp
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
        std::string message = "Hello from thread: " + std::to_string(id) + " and iteration # " + std::to_string(i);
        logger.log(message, 
                   i % 3 == 0 ? LogType::ERROR_DEBUG :
                   i % 2 == 0 ? LogType::WARNING_DEBUG : 
                   LogType::INFO_DEBUG, 
                   __FILE__, __LINE__);
        this_thread::sleep_for(50ms);
    }
}

int main()
{
    // Create the FileLoggingStrategy and pass it to the logger
    std::unique_ptr<FileLoggingStrategy> strategy = std::make_unique<FileLoggingStrategy>("log_file.txt");
    auto& logger = ThreadSafeLogger::getInstance(std::move(strategy));

    // Start the logging thread to process the logs
    logger.startLoggingThread();

    vector<thread> threads;
    // Create a few threads all working with the same Logger instance.
    for (int i{ 0 }; i < 10; ++i) {
        threads.emplace_back(logSomeMessages, i, ref(logger));
    }

    // Wait for all threads to finish logging
    for (int i{ 0 }; i < 10; ++i) {
        threads[i].join();
    }

    return 0;
}
```


## Acknowledgements
This project uses the Singleton design pattern to ensure a single logger instance.
Color support for the console is achieved using ANSI escape sequences.


DISCLAIMER: The README was generated by AI. It is temporary until I can write a complete documentation.