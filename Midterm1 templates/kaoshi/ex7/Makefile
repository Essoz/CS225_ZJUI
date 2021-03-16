CC = g++
LD = g++
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %cpp, %o, $(SRCS))
TARGET = hashtest
all: $(TARGET)
$(TARGET): $(OBJS)
	$(LD) -o $@ $^
%.o: %.cpp
	$(CC) -c $^
# make clean删除所有.o和目标文件
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY:all clean