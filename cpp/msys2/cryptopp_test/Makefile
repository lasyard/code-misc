# Application name
TARGET := app.exe

DEV_ROOT := /z/workspace/devel

CRYPTOPP_VERSION := 840
CRYPTOPP_PATH := $(DEV_ROOT)/cryptopp$(CRYPTOPP_VERSION)-x86_64-msw-static

# Source files
SRCS := $(wildcard *.cpp)

CFLAGS += -O2
CXXFLAGS := $(CFLAGS)
CXXFLAGS += -pipe -Wall -std=c++11

CXXFLAGS += -I$(CRYPTOPP_PATH)
LDFLAGS += -L$(CRYPTOPP_PATH) -lcryptopp

OBJS := $(SRCS:.cpp=.o)

DEPFILE := .depend

.PHONY: all clean dep clean-dep

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

dep:
	$(CXX) -MM $(CXXFLAGS) $(CPP_SRCS) > $(DEPFILE)
	$(CC) -MM $(CFLAGS) $(C_SRCS) >> $(DEPFILE)

clean:
	-rm -f $(OBJS)
	-rm -f $(TARGET)

clean-dep:
	-rm -f $(DEPFILE)

ifeq ($(DEPFILE), $(wildcard $(DEPFILE)))
  include $(DEPFILE)
endif
