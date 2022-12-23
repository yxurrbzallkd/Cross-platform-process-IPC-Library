#ifndef FIFO_HEADER
#define FIFO_HEADER

#include <stdio.h>
#include <iostream>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <string>
#include <pipc/errors_and_warnings.hpp>

#define BUF_SIZE 1024

namespace pipc {
	class fifo {
		private:
			const char* fname;
			bool fifo_create;
			int fifo_flag;
			int fifo_fd;
			int buf[BUF_SIZE];
			bool issetup = false;
		public:
			fifo(const char* name, bool create, int flag)
			: fname(name), fifo_create(create), fifo_flag(flag) { }
			int setup() {
				if (fifo_create) {
					if (mkfifo(fname, S_IRUSR|S_IWUSR) < 0)
						return FIFO_ERROR & FAILED_TO_MKFIFO;
				}
				fifo_fd = open(fname, fifo_flag);
				if (fifo_fd < 0)
					return FIFO_ERROR & FAILED_TO_OPEN;
				issetup = true;
				return SUCCESS;
			}

			int write_fifo(const char* buf, size_t size) {
				if (!issetup)
					return FIFO_ERROR & NOT_SETUP;
				if (write(fifo_fd, buf, size) <= 0)
					return FIFO_ERROR & BAD_WRITE;
				return SUCCESS;
			}

			int read_fifo(char* buf, size_t n) {
				if (!issetup)
					return FIFO_ERROR & NOT_SETUP;
				if (read(fifo_fd, buf, n) <= 0)
					return FIFO_ERROR & BAD_READ;
				return SUCCESS;
			}

			int clear_fifo() {
				// read everything from the pipe, clearing it
				while (read(fifo_fd, buf, BUF_SIZE) > 0) {}
				return SUCCESS;
			}

			int unlink_fifo() {
				if (unlink(fname) < 0)
					return FIFO_ERROR & FAILED_TO_UNLINK;
				issetup = false;
				return SUCCESS;
			}

			~fifo() {
				if (!(fifo_fd < 0))
					close(fifo_fd);
			}
	};
}

#endif