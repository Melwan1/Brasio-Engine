#include <io/logging/logger.hh>

#include <chrono>

#include <io/escapes/ansi-escapes.hh>

namespace brasio::io::logging
{

    std::map<std::string, io::logging::LogLevel> Logger::logLevelMap = {
            { "TRACE", io::logging::LogLevel::TRACE },
            { "DEBUG", io::logging::LogLevel::DEBUG },
            { "INFO", io::logging::LogLevel::INFO },
            { "WARNING", io::logging::LogLevel::WARNING },
            { "ERROR", io::logging::LogLevel::ERROR },
            { "CRITICAL", io::logging::LogLevel::CRITICAL }
    };

    LogLevel Logger::sLogLevel = LogLevel::DEBUG;
    std::map<std::string, LogLevel> Logger::specificLogLevelMap{};

    Logger::Logger(std::ostream &ostr, LogLevel logLevel)
        : _ostr(ostr)
        , _globalLogLevel(logLevel)
    {}

    bool Logger::_shouldLog(const LogLevel messageLevel, const std::vector<std::string> &additionalTags)
    {
        LogLevel minimalLogLevel = _globalLogLevel;
        for (unsigned i = 0; i < additionalTags.size(); i++)
        {
            std::string tagsAsString = tagsToString(std::vector<std::string>(additionalTags.begin(), additionalTags.begin() + i + 1));
            if (!specificLogLevelMap.contains(tagsAsString))
            {
                return minimalLogLevel <= messageLevel;
            }
            minimalLogLevel = specificLogLevelMap[tagsAsString];
        }
        return minimalLogLevel <= messageLevel;

    }

    std::string Logger::tagsToString(const std::vector<std::string> &tags)
    {
        std::ostringstream oss;
        for (const std::string &tag : tags)
        {
            oss << "[" << tag << "]";
        }
        return oss.str();
    }

    void Logger::setLogLevel(LogLevel logLevel, std::vector<std::string> specificTags)
    {
        if (specificTags.empty())
        {
            _globalLogLevel = logLevel;
            return;
        }

        specificLogLevelMap.insert_or_assign(tagsToString(specificTags), logLevel);
    }

    void Logger::_log(const std::string &message, const LogLevel messageLevel,
                      const std::vector<std::string> &additionalTags)
    {
        if (!_shouldLog(messageLevel, additionalTags))
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
        _ostr << tagsToString(additionalTags);

        _ostr << ESC_RESET << " " << message << "\n";
    }

    void Logger::log(std::ostream &ostr, const std::string &message,
                     LogLevel messageLevel,
                     std::vector<std::string> additionalTags)
    {
        Logger(ostr, Logger::sLogLevel)._log(message, messageLevel, additionalTags);
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

    void Logger::fromConfig(const YAML::Node &config)
    {
        Logger::sLogLevel =
            logLevelMap.at(config["global_level"].as<std::string>());
        Logger logger(std::cout, Logger::sLogLevel);
        logger.setLogLevel(Logger::sLogLevel, {});
        fromConfigRec(config["specific_levels"], {});
    }

    void Logger::fromConfigRec(const YAML::Node &config, const std::vector<std::string> &tags)
    {
        for (YAML::const_iterator it = config.begin(); it != config.end(); ++it)
        {
            std::string name = it->first.as<std::string>();
            if (it->second.IsMap())
            {
                std::vector<std::string> newTags(tags.begin(), tags.end());
                newTags.emplace_back(name);
                fromConfigRec(it->second, newTags);
            }
            else {

                if (!name.compare("global"))
                {
                    std::string key = tagsToString(tags);
                    std::string value = it->second.as<std::string>();
                    specificLogLevelMap.insert_or_assign(key, logLevelMap.at(value));
                }
                else {
                    std::vector<std::string> newTags(tags.begin(), tags.end());
                    newTags.emplace_back(name);
                    std::string key = tagsToString(newTags);
                    std::string value = it->second.as<std::string>();
                    specificLogLevelMap.insert_or_assign(key, logLevelMap.at(value));
                }
            }

        }
    }
} // namespace brasio::io::logging
