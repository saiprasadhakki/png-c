
CC = gcc

CFLAGS = -Werror -Wextra
CFLAGS += -I./
CFLAGS += -I./include

LIBS = -lraylib -lm


SRCS = $(wildcard src/*.c) $(wildcard src/tinyfiledialog/*.c)

OBJS = $(SRCS:%.c=%.o)

TARGET := RUNME

run: $(TARGET)
	./$<

all: CFLAGS += -O2
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ $(LDFLAGS) $(LIBS) -o $@ 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: $(TARGET) $(OBJS)
	rm -f $^

.PHONY: all clean

TARGET_DEBUG := DEBUG
OBJ_DEBUG = $(SRCS:%.c=%.d.o)

debug: CFLAGS += -g -fsanitize=address
debug: LDFLAGS += -g -fsanitize=address
debug: $(TARGET_DEBUG)

%.d.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(TARGET_DEBUG): $(OBJ_DEBUG)
	$(CC) $^ $(LDFLAGS) $(LIBS) -o $@
