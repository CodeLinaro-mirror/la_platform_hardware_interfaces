LIBRARY=libqti-wifi-server.so.0

CONFIG_AP := y

CUR_DIR = $(shell pwd)
SRC_DIR = $(CUR_DIR)/src
INC_DIR = $(CUR_DIR)/include

CXXFLAGS += -c -std=c++17 -fPIC
CPPFLAGS += -Wall -Werror -Wno-unused-function -Wno-ignored-attributes
CPPFLAGS += -I$(INC_DIR)
CPPFLAGS += -DENABLE_LOG
LDFLAGS += -lstdc++
LDFLAGS += -lwifi-ndk-header -lqti-wifi-message -lqti_someip_util -lqti_log_util
LDFLAGS += -shared -Wl,-soname,$(LIBRARY)

ifeq ($(CONFIG_AP), y)
CPPFLAGS += -DCONFIG_AP
endif
ifeq ($(CONFIG_DEBUG), y)
CPPFLAGS += -DCONFIG_DEBUG
endif

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
	$(CXX) $< -o $@ $(CXXFLAGS) $(CPPFLAGS)
