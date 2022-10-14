/*
    Part of the Real-Time Embedded Systems course at Halmstad University
    Copyright (c) 2016, Sebastian Kunze <sebastian.kunze@hh.se>
    All rights reserved.
*/

/* Newlib Syscalls */
#include <sys/types.h>
#include <sys/times.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

/* ================================================================== */
/* misc things */
#include <errno.h>
#undef errno
extern int errno;

char *__env[1] = { 0 };
char **environ = __env;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

/* ================================================================== */
/* dummy output routine */
void __attribute__((weak)) piface_putc(char c) { }
char __attribute__((weak)) piface_getc(void)   { return 0; }

/* ================================================================== */
/* memory management */
caddr_t _sbrk(int incr)
{
	extern const void _end, _heap_end;
	static caddr_t heap_ptr = NULL;
	       caddr_t base;

	if(heap_ptr == NULL)
		heap_ptr = (caddr_t)&_end;

	if(((caddr_t)&_heap_end - heap_ptr) >= 0) {
		/* allocate heap */
		base = heap_ptr;
		heap_ptr += incr;
		return base;
	} else {
		/* OOM */
		errno = ENOMEM;
		return ((caddr_t)-1);
	}
}

/* ================================================================== */
/* file handling */
int _open(const char *name, int flags, int mode) { return -1; }
int _close(int fd)                     { return -1; }
int _lseek(int fd, int ptr, int dir)   { return 0; }
int _isatty(int fd)                    { return 1; }
int _stat(char *file, struct stat *st) { st->st_mode = S_IFCHR; return 0; }
int _fstat(int fd, struct stat *st)    { st->st_mode = S_IFCHR; return 0; }
int _link(char *old, char *new)        { errno = EMLINK; return -1; }
int _unlink(char *name)                { errno = ENOENT; return -1; }

ssize_t _read(int fd, char *buf, size_t len)
{
	switch(fd) {
	case STDIN_FILENO:
#if 0
		for(size_t i = 0; i < len; ++i) {
			buf[i] = uart_rx();

			uart_tx(buf[i]);	/* echo */
			if(buf[i] == '\r' || buf[i] == '\n') {
				uart_tx('\n');
				buf[i] = '\n';
				return i+1;
			}
		}
		return len;
#else
		buf[0] = piface_getc();
		return 1;
#endif

	default:
		errno = EBADF;
		return -1;
	}
}

ssize_t _write(int fd, char *buf, size_t len)
{
	switch(fd) {
	case STDOUT_FILENO:
		for(size_t i = 0; i < len; i++)
			piface_putc(*buf++);
		break;

	case STDERR_FILENO:
		for(size_t i = 0; i < len; i++)
			piface_putc(*buf++);
		break;

	default:
		errno = EBADF;
		return -1;
	}

	return len;
}

/* ================================================================== */
/* process management */
int _getpid(void)                                { return 1; }
int _fork(void)                                  { errno = EAGAIN; return -1; }
int _execve(char* name, char** argv, char** env) { errno = ENOMEM; return -1; }
int _kill(int pid, int sig)                      { errno = EINVAL; return -1; }
int _wait(int *status)                           { errno = ECHILD; return -1; }
int _times(struct tms *buf)                      { return -1; }
void _exit(int status)                           { while(1); }

#pragma GCC diagnostic pop
