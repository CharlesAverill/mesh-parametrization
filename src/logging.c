/**
 * @file logging.c
 * @author Charles Averill
 * @brief Warnings and fatal error handling
 * @date 08-Sep-2022
 */

#include <stdarg.h>
#include <stdlib.h>

#include "arguments.h"
#include "logging.h"

/**
 * @brief Raises a fatal error that will exit the program
 * 
 * @param rc Return code to exit with
 * @param fmt Format string for printed error
 * @param ... Varargs for printed error
 */
void fatal(ReturnCode rc, const char* fmt, ...)
{
    va_list func_args;

    va_start(func_args, fmt);
    fprintf(stderr, "%s%s%s", ERROR_RED "[", returnCodeStrings[rc], "] - " ANSI_RESET);
    vfprintf(stderr, fmt, func_args);
    va_end(func_args);

    // Print fence for error distinguishing
    fprintf(stderr, "\n----------------------------------------\n");

    exit(rc);
}

/**
 * @brief Raises a non-fatal logging statement
 * 
 * @param level Severity of statement
 * @param fmt Format string for printed statement
 * @param ... Varargs for printed statement
 */
void mp_log(LogLevel level, const char* fmt, ...)
{
    va_list func_args;
    FILE* output_stream = stdout;

    va_start(func_args, fmt);
    fprintf(output_stream, "LOG:%s%s%s", logInfoLevels[level].color, logInfoLevels[level].name,
            " - " ANSI_RESET);
    vfprintf(output_stream, fmt, func_args);
    fprintf(output_stream, "\n");
    va_end(func_args);
}
