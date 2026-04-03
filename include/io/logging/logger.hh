#pragma once

#include <iostream>
#include <ostream>
#include <sstream>
#include <vector>

#include <io/logging/log-level.hh>

namespace brasio::io::logging
{
    /*
     * The Logger class.
     * A logger can write formatted messages to any output stream with a certain
     * level.
     *
     * Messages can be printed from a logger object or without an object using
     * class methods.
     */
    class Logger
    {
    public:
        /*
         * The Logger constructor.
         *
         * @param ostr the output stream
         * @param logLevel the initial log level of the logger, INFO by default.
         *
         */
        Logger(std::ostream &ostr, LogLevel logLevel = LogLevel::INFO);

        /**
         * ===============
         * Object methods.
         * ===============
         */

        /**
         * Set the log level of the logger.
         *
         * @param   logLevel  the new log level of the logger.
         * @return  void
         */
        void setLogLevel(LogLevel logLevel);

        /**
         * Log a trace message using the logger object.
         *
         * Writes a message to the output stream if the logger level is lower or
         * equal (as integers) to LogLevel::TRACE.
         *
         * @param   message         the message to write
         * @param   additionalTags  a list of additional tags, defaults to empty
         *
         * @return  void
         * @see     LogLevel
         */
        void trace(const std::string &message,
                   std::vector<std::string> additionalTags = {});

        /**
         * Log a debug message using the logger object.
         *
         * Writes a message to the output stream if the logger level is lower or
         * equal (as integers) to LogLevel::DEBUG.
         *
         * @param   message         the message to write
         * @param   additionalTags  a list of additional tags, defaults to empty
         * @return  void
         * @see     LogLevel
         */
        void debug(const std::string &message,
                   std::vector<std::string> additionalTags = {});

        /**
         * Log an info message using the logger object.
         *
         * Writes a message to the output stream if the logger level is lower or
         * equal (as integers) to LogLevel::INFO.
         *
         * @param   message         the message to write
         * @param   additionalTags  a list of additional tags, defaults to empty
         * @return  void
         * @see     LogLevel
         */
        void info(const std::string &message,
                  std::vector<std::string> additionalTags = {});

        /**
         * Log a warning message using the logger object.
         *
         * Writes a message to the output stream if the logger level is lower or
         * equal (as integers) to LogLevel::WARNING.
         *
         * @param   message         the message to write
         * @param   additionalTags  a list of additional tags, defaults to empty
         * @return  void
         * @see     LogLevel
         */
        void warning(const std::string &message,
                     std::vector<std::string> additionalTags = {});

        /**
         * Log an error message using the logger object.
         *
         * Writes a message to the output stream if the logger level is lower or
         * equal (as integers) to LogLevel::ERROR.
         *
         * @param   message         the message to write
         * @param   additionalTags  a list of additional tags, defaults to empty
         * @return  void
         * @see     LogLevel
         */
        void error(const std::string &message,
                   std::vector<std::string> additionalTags = {});

        /**
         * Log a critical message using the logger object.
         *
         * Writes a message to the output stream if the logger level is lower or
         * equal (as integers) to LogLevel::CRITICAL, which should always be the
         * case.
         *
         * @param   message         the message to write
         * @param   additionalTags  a list of additional tags, defaults to empty
         * @return  void
         * @see     LogLevel
         */
        void critical(const std::string &message,
                      std::vector<std::string> additionalTags = {});

        /**
         * The static logging level. Used in the static methods only.
         */
        static LogLevel sLogLevel;

        /**
         * ====================================================
         * Static methods imitating the logging object methods.
         * ====================================================
         */

        /**
         * Log a message using a static logger.
         *
         * Writes a message to the output stream if the static logger level is
         * lower or equal (as integers) to the message level.
         *
         * @param   ostr            the output stream on which to write the
         * message
         * @param   message         the message to write
         * @param   messageLevel    the level of the message
         * @param   additionalTags  a list of additional tags, defaults to empty
         * @return  void
         * @see     LogLevel
         */
        static void log(std::ostream &ostr, const std::string &message,
                        LogLevel messageLevel,
                        std::vector<std::string> additionalTags = {});

        /**
         * Log a trace message using a static logger.
         *
         * Writes a message to the output stream if the static logger level is
         * lower or equal (as integers) to LogLevel::TRACE.
         *
         * @param   ostr            the output stream on which to write the
         * message
         * @param   message         the message to write
         * @param   additionalTags  a list of additional tags, defaults to empty
         * @return  void
         * @see     LogLevel
         */
        static void trace(std::ostream &ostr, const std::string &message,
                          std::vector<std::string> additionalTags = {});

        /**
         * Log a debug message using a static logger.
         *
         * Writes a message to the output stream if the static logger level is
         * lower or equal (as integers) to LogLevel::DEBUG.
         *
         * @param   ostr            the output stream on which to write the
         * message
         * @param   message         the message to write
         * @param   additionalTags  a list of additional tags, defaults to empty
         * @return  void
         * @see     LogLevel
         */
        static void debug(std::ostream &ostr, const std::string &message,
                          std::vector<std::string> additionalTags = {});

        /**
         * Log an info message using a static logger.
         *
         * writes a message to the output stream if the static logger level is
         * lower or equal (as integers) to LogLevel::INFO.
         *
         * @param   ostr            the output stream on which to write the
         * message
         * @param   message         the message to write
         * @param   additionalTags  a list of additional tags, defaults to empty
         * @return  void
         * @see     LogLevel
         */
        static void info(std::ostream &ostr, const std::string &message,
                         std::vector<std::string> additionalTags = {});

        /**
         * Log a warning message using a static logger.
         *
         * writes a message to the output stream if the static logger level is
         * lower or equal (as integers) to LogLevel::WARNING.
         *
         * @param   ostr            the output stream on which to write the
         * message
         * @param   message         the message to write
         * @param   additionalTags  a list of additional tags, defaults to empty
         * @return  void
         * @see     LogLevel
         */
        static void warning(std::ostream &ostr, const std::string &message,
                            std::vector<std::string> additionalTags = {});

        /**
         * Log an error message using a static logger.
         *
         * writes a message to the output stream if the static logger level is
         * lower or equal (as integers) to LogLevel::ERROR.
         *
         * @param   ostr            the output stream on which to write the
         * message
         * @param   message         the message to write
         * @param   additionalTags  a list of additional tags, defaults to empty
         * @return  void
         * @see     LogLevel
         */
        static void error(std::ostream &ostr, const std::string &message,
                          std::vector<std::string> additionalTags = {});

        /**
         * Log a critical message using a static logger.
         *
         * writes a message to the output stream if the static logger level is
         * lower or equal (as integers) to LogLevel::CRITICAL, which should
         * always be the case.
         *
         * @param   ostr            the output stream on which to write the
         * message
         * @param   message         the message to write
         * @param   additionalTags  a list of additional tags, defaults to empty
         * @return  void
         * @see     LogLevel
         */
        static void critical(std::ostream &ostr, const std::string &message,
                             std::vector<std::string> additionalTags = {});

    private:
        std::ostream &_ostr;
        LogLevel _logLevel;

        /**
         * Log a message.
         *
         * @param   message         the message to write
         * @param   messageLevel    the message level
         * @param   additionalTags  a list of additional tags, defaults to empty
         * @return  void
         */
        void _log(const std::string &message, const LogLevel messageLevel,
                  const std::vector<std::string> &additionalTags);
    };
} // namespace brasio::io::logging

#define BRASIO_LOG_TRACE(ostr, ...)                                             \
    do                                                                          \
    {                                                                           \
        if (::brasio::io::logging::Logger::sLogLevel                            \
            <= ::brasio::io::logging::LogLevel::TRACE)                          \
            ::brasio::io::logging::Logger::trace(ostr, __VA_ARGS__);            \
    } while (0)

#define BRASIO_LOG_DEBUG(ostr, ...)                                             \
    do                                                                          \
    {                                                                           \
        if (::brasio::io::logging::Logger::sLogLevel                            \
            <= ::brasio::io::logging::LogLevel::DEBUG)                          \
            ::brasio::io::logging::Logger::debug(ostr, __VA_ARGS__);            \
    } while (0)

#define BRASIO_LOG_INFO(ostr, ...)                                              \
    do                                                                          \
    {                                                                           \
        if (::brasio::io::logging::Logger::sLogLevel                            \
            <= ::brasio::io::logging::LogLevel::INFO)                           \
            ::brasio::io::logging::Logger::info(ostr, __VA_ARGS__);             \
    } while (0)

#define BRASIO_LOG_WARNING(ostr, ...)                                           \
    do                                                                          \
    {                                                                           \
        if (::brasio::io::logging::Logger::sLogLevel                            \
            <= ::brasio::io::logging::LogLevel::WARNING)                        \
            ::brasio::io::logging::Logger::warning(ostr, __VA_ARGS__);          \
    } while (0)

#define BRASIO_LOG_ERROR(ostr, ...)                                             \
    do                                                                          \
    {                                                                           \
        if (::brasio::io::logging::Logger::sLogLevel                            \
            <= ::brasio::io::logging::LogLevel::ERROR)                          \
            ::brasio::io::logging::Logger::error(ostr, __VA_ARGS__);            \
    } while (0)

#define BRASIO_LOG_CRITICAL(ostr, ...)                                          \
    do                                                                          \
    {                                                                           \
        if (::brasio::io::logging::Logger::sLogLevel                            \
            <= ::brasio::io::logging::LogLevel::CRITICAL)                       \
            ::brasio::io::logging::Logger::critical(ostr, __VA_ARGS__);         \
    } while (0)
