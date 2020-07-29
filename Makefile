CFLAGS ?= -Wall -Wextra -Os -ggdb3
CFLAGS += -Ilibhistory

.c.opic:
	${CC} -fPIC ${CFLAGS} -o $@ -c $<

.c.o:
	${CC} ${CFLAGS} -o $@ -c $<

LIBHISTORY_SRC = \
	libhistory/history.c

LIBHISTORY_STATIC_OBJ = ${LIBHISTORY_SRC:.c=.o}
LIBHISTORY_SHARED_OBJ = ${LIBHISTORY_SRC:.c=.opic}
LIBHISTORY_SOMAJOR = 8
LIBHISTORY_SOMINOR = 0

TARGET_LIBS = libhistory.a libhistory.so

all: ${TARGET_LIBS}

libhistory.a: ${LIBHISTORY_STATIC_OBJ}
	${AR} -rcs $@ ${LIBHISTORY_STATIC_OBJ}

libhistory.so: ${LIBHISTORY_SHARED_OBJ}
	${CC} -shared -fPIC -Wl,-soname=libhistory.so.${LIBHISTORY_SOMAJOR} -o $@ ${LIBHISTORY_SHARED_OBJ}

clean:
	rm -f ${TARGET_LIBS} ${LIBHISTORY_SHARED_OBJ} ${LIBHISTORY_STATIC_OBJ}

.SUFFIXES: .c .o .opic
