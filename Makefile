
CC = gcc

CFLAGS = -Werror -Wextra
CFLAGS += -I./
CFLAGS += -I./include

LIBS = -lm -lraylib


LDFLAGS =


SRCS = $(wildcard src/*.c) $(wildcard src/tinyfiledialog/*.c)

OBJS = $(SRCS:%.c=%.o)

TARGET := RUNME

all: CFLAGS += -O2
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ $(LDFLAGS) $(LIBS) -o $@ 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


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

run: $(TARGET)
	./$<


CC_WIN = x86_64-w64-mingw32-gcc
CFLAGS_WIN = -Wextra -I./ -I./include
TARGET_WIN := RUNME.exe
LIBS_WIN = -lm -lraylib -lopengl32 -lgdi32 -lwinmm -luser32 -lkernel32 -lshell32 -lcomdlg32 -lole32
OBJS_WIN = $(SRCS:%.c=%.win.o)
LDFLAGS_WIN = -L ./libs/win/

win: $(TARGET_WIN)

$(TARGET_WIN): $(OBJS_WIN)
	$(CC_WIN) $^ $(LDFLAGS_WIN) $(LIBS_WIN) -o $@

%.win.o: %.c
	$(CC_WIN) $(CFLAGS_WIN) -c $< -o $@

clean: 
	rm -rf $(OBJS) $(OBJ_DEBUG) 
	rm -rf $(TARGET_DEBUG) $(TARGET)
