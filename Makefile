CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11

# Source files and object files for each executable
MYBASH_SRCS = mybash.c
MYBASH_OBJS = $(MYBASH_SRCS:.c=.o)
LS_SRCS = myls.c
LS_OBJS = $(LS_SRCS:.c=.o)
MYFIND_SRCS = myFind.c
MYFIND_OBJS = $(MYFIND_SRCS:.c=.o)
MYXARGS_SRCS = myXargs.c
MYXARGS_OBJS = $(MYXARGS_SRCS:.c=.o)


# Target executables
MYBASH_TARGET = mybash
LS_TARGET = myls
MYFIND_TARGET = myfind
MYXARGS_TARGET = myxargs

.PHONY: all clean

all: $(MYBASH_TARGET) $(LS_TARGET) $(MYFIND_TARGET) $(MYXARGS_TARGET)

$(MYBASH_TARGET): $(MYBASH_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(LS_TARGET): $(LS_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(MYFIND_TARGET): $(MYFIND_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(MYXARGS_TARGET): $(MYXARGS_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(MYBASH_OBJS) $(MYBASH_TARGET) $(LS_OBJS) $(LS_TARGET) $(MYFIND_OBJS) $(MYFIND_TARGET) $(MYXARGS_OBJS) $(MYXARGS_TARGET)
