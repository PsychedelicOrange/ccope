@include("stdarg.h");
@include("stdio.h");

void logp(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vfprintf(stdout, fmt, args);
    va_end(args);
}
void logd(const char *fmt, ...)
{
    fprintf(stdout, "\033[0;34m[DEBUG] \033[0m");
    va_list args;
    va_start(args, fmt);
    vfprintf(stdout, fmt, args);
    va_end(args);
    fprintf(stdout, "\n");
}
void logi(const char *fmt, ...)
{
    fprintf(stdout, "\033[0;33m[INFO] \033[0m");
    va_list args;
    va_start(args, fmt);
    vfprintf(stdout, fmt, args);
    va_end(args);
    fprintf(stdout, "\n");
}
void logw(const char *fmt, ...)
{
    fprintf(stderr, "\033[31m[WARN] \033[0m");
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
}
void loge(const char *fmt, ...)
{
    fprintf(stderr, "\033[41m[ERROR]\033[0m ");
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
}
