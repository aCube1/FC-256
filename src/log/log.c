#include "log/log.h"

#include <time.h>

typedef struct {
	va_list args;
	const char *fmt;
	const char *file;
	int line;
	int level;
	FILE *output;
	struct tm *time;
} LogData;

static const char *level_names[] = { "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL" };
static const char *level_color[] = { "\x1b[94m", "\x1b[32m", "\x1b[36m", "\x1b[33m", "\x1b[31m", "\x1b[35m" };

static void print_stdout(LogData *data) {
	char buf[16];
	buf[strftime(buf, sizeof(buf), "%H:%M:%S", data->time)] = '\0';

	/* NOLINTBEGIN(cert-err33-c) */
	fprintf(
		data->output, "%s %s[%s]\x1b[0m \x1b[90m%s:%d\x1b[0m - ", buf, level_color[data->level],
		level_names[data->level], data->file, data->line
	);
	vfprintf(data->output, data->fmt, data->args);
	fprintf(data->output, "%s", "\n");

	fflush(data->output);
	/* NOLINTEND(cert-err33-c) */
}

void log_message(int level, const char *file, int line, const char *fmt, ...) {
	LogData data = {
		.fmt = fmt,
		.file = file,
		.line = line,
		.level = level,
		.output = stderr,
	};

	if (!data.time) {
		time_t timer = time(NULL);
		data.time = localtime(&timer);
	}

	va_start(data.args, fmt);
	print_stdout(&data);
	va_end(data.args);
}
