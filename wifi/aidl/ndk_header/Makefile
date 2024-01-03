
#Wifi Hal NDK headers configuration
CONFIG_P2P := n


# WiFi Hal NDK Headers library
LIBRARY=libwifi-ndk-header.so.0

CUR_DIR = $(shell pwd)
INC_DIR = $(CUR_DIR)/include

CXXFLAGS += -c -std=c++17 -fPIC
CPPFLAGS += -Wall -Werror -Wno-unused-function -Wno-ignored-attributes
CPPFLAGS += -I. -I$(INC_DIR)
LDFLAGS += -lstdc++ -lutils
LDFLAGS += -shared -Wl,-soname,$(LIBRARY)

SRCS := wifi_hal_delegator.cpp
CXXOBJECTS := $(SRCS:.cpp=.o)

$(LIBRARY): $(CXXOBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

$(CXXOBJECTS): %.o: %.cpp
	$(CXX) $< -o $@  $(CXXFLAGS) $(CPPFLAGS)

clean:
	rm -rf *.o *.so*
