# Application name
TARGET := app.exe

DEV_ROOT := /z/workspace/devel

WX_VERSION := 3.1.4
WX_DYLIBS_VERSION := 3.1.4.0.0
WX_PATH := $(DEV_ROOT)/wxWidgets-$(WX_VERSION)

# Source files
SRCS := $(wildcard *.cpp)

STUB := $(MSYSTEM_CARCH)-msw-static

WX_BUILD_PATH := $(WX_PATH)/build-$(STUB)-release
WX_CONFIG := $(WX_BUILD_PATH)/wx-config

CFLAGS += -O2
CXXFLAGS := $(CFLAGS)
CXXFLAGS += -pipe -Wall -std=c++11

CXXFLAGS += $(shell $(WX_CONFIG) --cxxflags)
LDFLAGS += $(shell $(WX_CONFIG) --libs)

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
