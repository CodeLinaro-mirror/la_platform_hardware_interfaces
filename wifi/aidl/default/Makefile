# WiFi Hal SomeIP Service Configuration
CONFIG_DEBUG := y
CONFIG_AP := n
CONFIG_P2P := n
CONFIG_NAN := n
CONFIG_RTT := n

BINARY=wifihal-someip-service

CXXSRCS := \
    aidl_sync_util.cpp \
    aidl_struct_util.cpp \
    ringbuffer.cpp \
    wifi_status_util.cpp \
    wifi_iface_util.cpp \
    wifi_feature_flags.cpp \
    wifi_legacy_hal.cpp \
    wifi_legacy_hal_stubs.cpp \
    wifi_legacy_hal_factory.cpp \
    wifi_mode_controller.cpp \
    wifi.cpp \
    wifi_chip.cpp \
    wifi_ap_iface.cpp \
    wifi_sta_iface.cpp \
    service.cpp

ifeq ($(CONFIG_P2P), y)
CXXSRCS += wifi_p2p_iface.cpp
endif

ifeq ($(CONFIG_NAN), y)
CXXSRCS += wifi_nan_iface.cpp
endif

ifeq ($(CONFIG_RTT), y)
CXXSRCS += wifi_rtt_controller.cpp
endif

CXXOBJECTS := $(CXXSRCS:.cpp=.o)

CXXFLAGS += -c -std=c++17 -fPIC
CPPFLAGS += -Wno-unused-function -Wno-ignored-attributes
ifeq ($(CONFIG_DEBUG), y)
CPPFLAGS += -DCONFIG_DEBUG -DCONFIG_DEBUG_DUMP
endif
ifeq ($(CONFIG_AP), y)
CPPFLAGS += -DCONFIG_AP
endif
ifeq ($(CONFIG_P2P), y)
CPPFLAGS += -DCONFIG_P2P
endif
ifeq ($(CONFIG_NAN), y)
CPPFLAGS += -DCONFIG_NAN
endif
ifeq ($(CONFIG_RTT), y)
CPPFLAGS += -DCONFIG_RTT
endif
CPPFLAGS += -I.
#CPPFLAGS += -Wall -Werror
LDFLAGS += -lstdc++
LDFLAGS += -lbase -lutils -llog -lcutils
LDFLAGS += -lwifi-ndk-header
LDFLAGS += -lwifi-system -lwifi-system-iface -lwifi-hal-qcom -lwifi-hal
LDFLAGS += -lqti_someip_util -lqti_rpc_common_util
LDFLAGS += -lwifi-rpc-server

$(BINARY): $(CXXOBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf *.o *.so

$(CXXOBJECTS): %.o: %.cpp
	$(CXX) $< -o $@ $(CXXFLAGS) $(CPPFLAGS)
