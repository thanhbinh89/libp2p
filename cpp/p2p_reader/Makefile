# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -g -O2

# Binary
BIN := p2p_reader

# Sources inside this test folder
SRCS := p2p_reader.cpp
OBJS := $(SRCS:.cpp=.o)

# Include paths (top-level include and libdatachannel headers)
INCLUDES := -I./ -I../include -I../libdatachannel/include

# Prebuilt shared library (one level up)
LIBP2P := ../libp2p.so

# Linker flags: set rpath so the executable finds ../libp2p.so at runtime
LDFLAGS := -Wl,-rpath,'$$ORIGIN/..'

all: $(BIN)

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^ $(LIBP2P) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(BIN)

.PHONY: all clean
