LIBRARY=libwifi-rpc-server.so.0

CUR_DIR = $(shell pwd)
SRC_DIR = $(CUR_DIR)/src
INC_DIR = $(CUR_DIR)/include

CXXFLAGS += -c -std=c++17 -fPIC
CPPFLAGS += -Wall -Werror -Wno-unused-function -Wno-ignored-attributes
CPPFLAGS += -I$(INC_DIR)
LDFLAGS += -lstdc++ -lutils
#-lbase
LDFLAGS += -lwifi-ndk-header -lwifi-rpc-message -lqti_someip_util
LDFLAGS += -shared -Wl,-soname,$(LIBRARY)

SRCS := \
    $(SRC_DIR)/wifi_rpc_event.cpp \
    $(SRC_DIR)/wifi_rpc_message.cpp \
    $(SRC_DIR)/wifi_rpc_server.cpp

CXXOBJECTS := $(SRCS:.cpp=.o)

$(LIBRARY): $(CXXOBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf *.o *.so*

$(CXXOBJECTS): %.o: %.cpp
	$(CXX) $< -o $@  $(CXXFLAGS) $(CPPFLAGS)
