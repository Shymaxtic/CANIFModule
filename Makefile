CC 			:= g++ 
CPPFLAGS 	:= -std=c++11 -pthread -fPIC -Wall -Wextra -O2 -g
LDFLAGS 	:= -shared  

BUILDDIR 	:= ./build
SRCDIR 		:= ./src
TARGET 		:= $(BUILDDIR)/libCANIFModule.so 

SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CPPFLAGS) -c -o $@ $<
