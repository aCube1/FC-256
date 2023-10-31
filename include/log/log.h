#ifndef _LOG_LOG_H_
#define _LOG_LOG_H_

#include <stdarg.h>
#include <stdio.h>

#define log_trace(...) logMessage(LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define log_debug(...) logMessage(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define log_info(...)  logMessage(LOG_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define log_warn(...)  logMessage(LOG_WARN, __FILE__, __LINE__, __VA_ARGS__)
#define log_error(...) logMessage(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define log_fatal(...) logMessage(LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)

enum {
	LOG_TRACE,
	LOG_DEBUG,
	LOG_INFO,
	LOG_WARN,
	LOG_ERROR,
	LOG_FATAL,
};

/*!
 * Print formatted string to the STDERR.
 *
 * @param level Message debugging level.
 * @param file  File which the function has been called.
 * @param line  File line which the function has been called.
 * @param fmt   Formatted string to be displayed.
 */
void logMessage(int level, const char *file, int line, const char *fmt, ...);

#endif /* _LOG_LOG_H_ */
