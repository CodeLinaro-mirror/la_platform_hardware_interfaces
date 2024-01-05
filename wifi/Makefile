# Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
# SPDX-License-Identifier: BSD-3-Clause-Clear

# WiFi Hal SomeIP Service Configuration
CONFIG_DEBUG:=y

BINARY=wifihal-someip-service

CUR_DIR = $(shell pwd)
WIFI_SERVICE_SRC_DIR = $(CUR_DIR)/aidl/default
WIFI_SERVICE_INC_AIDL_DIR = $(CUR_DIR)/aidl/include
SOMEIP_SERVER_SRC_DIR = $(CUR_DIR)/rpc/server/src
SOMEIP_SERVER_INC_DIR = $(CUR_DIR)/rpc/server/include

SOMEIP_SERVER_DIR = $(CUR_DIR)/rpc/server

SOMEIP_SERVER_SRCS = \
    $(SOMEIP_SERVER_SRC_DIR)/wifi_hal_message_handler.cpp \
    $(SOMEIP_SERVER_SRC_DIR)/wifi_hal_event_callback.cpp \
    $(SOMEIP_SERVER_SRC_DIR)/wifi_hal_someip_server.cpp

WIFI_SERVICE_SRCS = \
    $(WIFI_SERVICE_SRC_DIR)/aidl_sync_util.cpp \
    $(WIFI_SERVICE_SRC_DIR)/aidl_struct_util.cpp \
    $(WIFI_SERVICE_SRC_DIR)/ringbuffer.cpp \
    $(WIFI_SERVICE_SRC_DIR)/wifi_status_util.cpp \
    $(WIFI_SERVICE_SRC_DIR)/wifi_iface_util.cpp \
    $(WIFI_SERVICE_SRC_DIR)/wifi_feature_flags.cpp \
    $(WIFI_SERVICE_SRC_DIR)/wifi_legacy_hal.cpp \
    $(WIFI_SERVICE_SRC_DIR)/wifi_legacy_hal_stubs.cpp \
    $(WIFI_SERVICE_SRC_DIR)/wifi_legacy_hal_factory.cpp \
    $(WIFI_SERVICE_SRC_DIR)/wifi_mode_controller.cpp \
    $(WIFI_SERVICE_SRC_DIR)/wifi.cpp \
    $(WIFI_SERVICE_SRC_DIR)/wifi_chip.cpp \
    $(WIFI_SERVICE_SRC_DIR)/wifi_ap_iface.cpp \
    $(WIFI_SERVICE_SRC_DIR)/wifi_sta_iface.cpp \
    $(WIFI_SERVICE_SRC_DIR)/service.cpp
#   $(WIFI_SERVICE_SRC_DIR)/wifi_nan_iface.cpp
#   $(WIFI_SERVICE_SRC_DIR)/wifi_p2p_iface.cpp
#   $(WIFI_SERVICE_SRC_DIR)/wifi_rtt_controller.cpp

CXXSRCS = $(SOMEIP_SERVER_SRCS) $(WIFI_SERVICE_SRCS)
CXXOBJECTS := $(CXXSRCS:.cpp=.o)

CXXFLAGS += -c -std=c++17 -fPIC
CPPFLAGS += -Wno-unused-function -Wno-ignored-attributes
ifeq ($(CONFIG_DEBUG), y)
CPPFLAGS += -DENABLE_DEBUG
endif
CPPFLAGS += -I$(SOMEIP_SERVER_INC_DIR) -I$(WIFI_SERVICE_INC_AIDL_DIR) -I$(WIFI_SERVICE_SRC_DIR)
LDFLAGS += -lstdc++
LDFLAGS += -lbase -lutils -llog -lcutils
LDFLAGS += -lwifi-system -lwifi-system-iface -lwifi-hal-qcom -lwifi-hal
LDFLAGS += -lqti_someip_util -lqti_rpc_common_util
LDFLAGS += -lwifi-service-message

#-Wl,-Bstatic -lqti_rpc_common_util
#CPPFLAGS += -Wall -Werror

$(BINARY): $(CXXOBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf *.o *.so

$(CXXOBJECTS): %.o: %.cpp
	$(CXX) $< -o $@  $(CXXFLAGS) $(CPPFLAGS)

