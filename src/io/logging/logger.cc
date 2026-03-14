#include <io/logging/logger.hh>

#include <chrono>

#include <io/escapes/ansi-escapes.hh>

namespace brasio::io::logging
{
    LogLevel Logger::sLogLevel = LogLevel::TRACE;

    Logger::Logger(std::ostream &ostr, LogLevel logLevel)
        : _ostr(ostr)
        , _logLevel(logLevel)
    {}

    void Logger::_log(const std::string &message, const LogLevel messageLevel,
                      const std::vector<std::string> &additionalTags)
    {
        if (_logLevel > messageLevel)
        {
            return;
        }
        // print the message
        std::chrono::system_clock::time_point now =
            std::chrono::system_clock::now();
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
        std::tm local_time = *std::localtime(&currentTime);
        auto microseconds =
            std::chrono::duration_cast<std::chrono::microseconds>(
                now.time_since_epoch())
            % 1'000'000;
        std::ostringstream oss;
        oss << std::put_time(&local_time, "%Y-%m-%d %H:%M:%S");

        _ostr << FG_ESC(244) << oss.str() << "."
              << std::format("{:06}", microseconds.count()) << "   ";

        _ostr << toColor(messageLevel) << "[" << toString(messageLevel) << "]";

        for (const auto &tag : additionalTags)
        {
            _ostr << "[" << tag << "]";
        }
        _ostr << ESC_RESET << " " << message << "\n";
    }

    void Logger::log(std::ostream &ostr, const std::string &message,
                     LogLevel messageLevel,
                     std::vector<std::string> additionalTags)
    {
        Logger(ostr, Logger::sLogLevel)
            ._log(message, messageLevel, std::move(additionalTags));
    }

    void Logger::trace(const std::string &message,
                       std::vector<std::string> additionalTags)
    {
        _log(message, LogLevel::TRACE, additionalTags);
    }

    void Logger::trace(std::ostream &ostr, const std::string &message,
                       std::vector<std::string> additionalTags)
    {
        log(ostr, message, LogLevel::TRACE, additionalTags);
    }

    void Logger::debug(const std::string &message,
                       std::vector<std::string> additionalTags)
    {
        _log(message, LogLevel::DEBUG, additionalTags);
    }

    void Logger::debug(std::ostream &ostr, const std::string &message,
                       std::vector<std::string> additionalTags)
    {
        log(ostr, message, LogLevel::DEBUG, additionalTags);
    }

    void Logger::info(const std::string &message,
                      std::vector<std::string> additionalTags)
    {
        _log(message, LogLevel::INFO, additionalTags);
    }

    void Logger::info(std::ostream &ostr, const std::string &message,
                      std::vector<std::string> additionalTags)
    {
        log(ostr, message, LogLevel::INFO, additionalTags);
    }

    void Logger::warning(const std::string &message,
                         std::vector<std::string> additionalTags)
    {
        _log(message, LogLevel::WARNING, additionalTags);
    }

    void Logger::warning(std::ostream &ostr, const std::string &message,
                         std::vector<std::string> additionalTags)
    {
        log(ostr, message, LogLevel::WARNING, additionalTags);
    }

    void Logger::error(const std::string &message,
                       std::vector<std::string> additionalTags)
    {
        _log(message, LogLevel::ERROR, additionalTags);
    }

    void Logger::error(std::ostream &ostr, const std::string &message,
                       std::vector<std::string> additionalTags)
    {
        log(ostr, message, LogLevel::ERROR, additionalTags);
    }

    void Logger::critical(const std::string &message,
                          std::vector<std::string> additionalTags)
    {
        _log(message, LogLevel::CRITICAL, additionalTags);
        _ostr << std::flush;
        throw std::runtime_error("RECEIVED A CRITICAL MESSAGE: " + message);
    }

    void Logger::critical(std::ostream &ostr, const std::string &message,
                          std::vector<std::string> additionalTags)
    {
        log(ostr, message, LogLevel::CRITICAL, additionalTags);
        ostr << std::flush;
        throw std::runtime_error("RECEIVED A CRITICAL MESSAGE: " + message);
    }
} // namespace brasio::io::logging
