#include "Globals.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void log(const char file[], int line, const char* format, ...)
{
	static char tmp_string[4096];
	static char tmp_string2[4096];
	static va_list  ap;

	// Construct the string from variable arguments
	va_start(ap, format);
	vsnprintf(tmp_string, 4095, format, ap);
	va_end(ap);
	snprintf(tmp_string2, 4095, "\n%s(%d) : %s", file, line, tmp_string);

	fputs(tmp_string2, stderr);
}
