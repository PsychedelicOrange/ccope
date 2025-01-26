#ifndef LOG_H
#define LOG_H

#include <stdarg.h>
void logp(const char *fmt, ...);
void logd(const char *fmt, ...);
void logi(const char *fmt, ...);
void logw(const char *fmt, ...);
void loge(const char *fmt, ...);

// Settings
/*#define MUTE_LOG_P*/
// #define MUTE_LOG_D
/*#define MUTE_LOG_I*/
/*#define MUTE_LOG_W*/
/*#define MUTE_LOG_E*/

#endif
#ifdef LOG_IMPLENTATION_PSYCH_H

#include <stdio.h>

void logp(const char *fmt, ...) {
#if !defined(MUTE_LOG_P)
  va_list args;
  va_start(args, fmt);
  vfprintf(stdout, fmt, args);
  va_end(args);
#endif
}
void logd(const char *fmt, ...) {
#if !defined(MUTE_LOG_D)
  fprintf(stdout, "\033[0;34m[DEBUG] \033[0m");
  va_list args;
  va_start(args, fmt);
  vfprintf(stdout, fmt, args);
  va_end(args);
  fprintf(stdout, "\n");
#endif
}
void logi(const char *fmt, ...) {
#if !defined(MUTE_LOG_I)
  fprintf(stdout, "\033[0;33m[INFO] \033[0m");
  va_list args;
  va_start(args, fmt);
  vfprintf(stdout, fmt, args);
  va_end(args);
  fprintf(stdout, "\n");
#endif
}
void logw(const char *fmt, ...) {
#if !defined(MUTE_LOG_W)
  fprintf(stderr, "\033[31m[WARN] \033[0m");
  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);
  fprintf(stderr, "\n");
#endif
}
void loge(const char *fmt, ...) {
#if !defined(MUTE_LOG_E)
  fprintf(stderr, "\033[41m[ERROR]\033[0m ");
  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);
  fprintf(stderr, "\n");
#endif
}
#endif
