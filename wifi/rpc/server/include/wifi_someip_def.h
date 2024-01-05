/*
 * Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

/* This is an auto-generated base file. */

#pragma once

#include <stdio.h>
#include <unistd.h>

#define WIFI_HAL_INSTANCE_ID                                                        ((uint16_t) 0x1110)

#define WIFI_HAL_EVENTGROUP_ID                                                      ((uint16_t) 0xAAA0)

typedef uint16_t WifiMsg;

#define IWIFI_REQ_BASE                                                              ((WifiMsg)(0x0000))

#define IWIFI_GET_CHIP_REQ                                                          (WifiMsg)(IWIFI_REQ_BASE + 0x0000)
#define IWIFI_GET_CHIP_IDS_REQ                                                      (WifiMsg)(IWIFI_REQ_BASE + 0x0001)
#define IWIFI_IS_STARTED_REQ                                                        (WifiMsg)(IWIFI_REQ_BASE + 0x0002)
#define IWIFI_REGISTER_EVENT_CALLBACK_REQ                                           (WifiMsg)(IWIFI_REQ_BASE + 0x0003)
#define IWIFI_START_REQ                                                             (WifiMsg)(IWIFI_REQ_BASE + 0x0004)
#define IWIFI_STOP_REQ                                                              (WifiMsg)(IWIFI_REQ_BASE + 0x0005)

#define IWIFI_REQ_COUNT                                                             6

#define IWIFIAPIFACE_REQ_BASE                                                       ((WifiMsg)(0x0100))

#define IWIFIAPIFACE_GET_NAME_REQ                                                   (WifiMsg)(IWIFIAPIFACE_REQ_BASE + 0x0000)
#define IWIFIAPIFACE_GET_BRIDGED_INSTANCES_REQ                                      (WifiMsg)(IWIFIAPIFACE_REQ_BASE + 0x0001)
#define IWIFIAPIFACE_GET_FACTORY_MAC_ADDRESS_REQ                                    (WifiMsg)(IWIFIAPIFACE_REQ_BASE + 0x0002)
#define IWIFIAPIFACE_SET_COUNTRY_CODE_REQ                                           (WifiMsg)(IWIFIAPIFACE_REQ_BASE + 0x0003)
#define IWIFIAPIFACE_RESET_TO_FACTORY_MAC_ADDRESS_REQ                               (WifiMsg)(IWIFIAPIFACE_REQ_BASE + 0x0004)
#define IWIFIAPIFACE_SET_MAC_ADDRESS_REQ                                            (WifiMsg)(IWIFIAPIFACE_REQ_BASE + 0x0005)

#define IWIFIAPIFACE_REQ_COUNT                                                      6

#define IWIFICHIP_REQ_BASE                                                          ((WifiMsg)(0x0200))

#define IWIFICHIP_CONFIGURE_CHIP_REQ                                                (WifiMsg)(IWIFICHIP_REQ_BASE + 0x0000)
#define IWIFICHIP_CREATE_AP_IFACE_REQ                                               (WifiMsg)(IWIFICHIP_REQ_BASE + 0x0001)
#define IWIFICHIP_CREATE_BRIDGED_AP_IFACE_REQ                                       (WifiMsg)(IWIFICHIP_REQ_BASE + 0x0002)
#define IWIFICHIP_CREATE_NAN_IFACE_REQ                                              (WifiMsg)(IWIFICHIP_REQ_BASE + 0x0003)
#define IWIFICHIP_CREATE_P2P_IFACE_REQ                                              (WifiMsg)(IWIFICHIP_REQ_BASE + 0x0004)
#define IWIFICHIP_CREATE_RTT_CONTROLLER_REQ                                         (WifiMsg)(IWIFICHIP_REQ_BASE + 0x0005)
#define IWIFICHIP_CREATE_STA_IFACE_REQ                                              (WifiMsg)(IWIFICHIP_REQ_BASE + 0x0006)
#define IWIFICHIP_ENABLE_DEBUG_ERROR_ALERTS_REQ                                     (WifiMsg)(IWIFICHIP_REQ_BASE + 0x0007)
#define IWIFICHIP_FLUSH_RING_BUFFER_TO_FILE_REQ                                     (WifiMsg)(IWIFICHIP_REQ_BASE + 0x0008)
#define IWIFICHIP_FORCE_DUMP_TO_DEBUG_RING_BUFFER_REQ                               (WifiMsg)(IWIFICHIP_REQ_BASE + 0x0009)
#define IWIFICHIP_GET_AP_IFACE_REQ                                                  (WifiMsg)(IWIFICHIP_REQ_BASE + 0x000A)
#define IWIFICHIP_GET_AP_IFACE_NAMES_REQ                                            (WifiMsg)(IWIFICHIP_REQ_BASE + 0x000B)
#define IWIFICHIP_GET_AVAILABLE_MODES_REQ                                           (WifiMsg)(IWIFICHIP_REQ_BASE + 0x000C)
#define IWIFICHIP_GET_FEATURE_SET_REQ                                               (WifiMsg)(IWIFICHIP_REQ_BASE + 0x000D)
#define IWIFICHIP_GET_DEBUG_HOST_WAKE_REASON_STATS_REQ                              (WifiMsg)(IWIFICHIP_REQ_BASE + 0x000E)
#define IWIFICHIP_GET_DEBUG_RING_BUFFERS_STATUS_REQ                                 (WifiMsg)(IWIFICHIP_REQ_BASE + 0x000F)
#define IWIFICHIP_GET_ID_REQ                                                        (WifiMsg)(IWIFICHIP_REQ_BASE + 0x0010)
#define IWIFICHIP_GET_MODE_REQ                                                      (WifiMsg)(IWIFICHIP_REQ_BASE + 0x0011)
#define IWIFICHIP_GET_NAN_IFACE_REQ                                                 (WifiMsg)(IWIFICHIP_REQ_BASE + 0x0012)
#define IWIFICHIP_GET_NAN_IFACE_NAMES_REQ                                           (WifiMsg)(IWIFICHIP_REQ_BASE + 0x0013)
#define IWIFICHIP_GET_P2P_IFACE_REQ                                                 (WifiMsg)(IWIFICHIP_REQ_BASE + 0x0014)
#define IWIFICHIP_GET_P2P_IFACE_NAMES_REQ                                           (WifiMsg)(IWIFICHIP_REQ_BASE + 0x0015)
#define IWIFICHIP_GET_STA_IFACE_REQ                                                 (WifiMsg)(IWIFICHIP_REQ_BASE + 0x0016)
#define IWIFICHIP_GET_STA_IFACE_NAMES_REQ                                           (WifiMsg)(IWIFICHIP_REQ_BASE + 0x0017)
#define IWIFICHIP_GET_SUPPORTED_RADIO_COMBINATIONS_REQ                              (WifiMsg)(IWIFICHIP_REQ_BASE + 0x0018)
#define IWIFICHIP_GET_WIFI_CHIP_CAPABILITIES_REQ                                    (WifiMsg)(IWIFICHIP_REQ_BASE + 0x0019)
#define IWIFICHIP_GET_USABLE_CHANNELS_REQ                                           (WifiMsg)(IWIFICHIP_REQ_BASE + 0x001A)
#define IWIFICHIP_SET_AFC_CHANNEL_ALLOWANCE_REQ                                     (WifiMsg)(IWIFICHIP_REQ_BASE + 0x001B)
#define IWIFICHIP_REGISTER_EVENT_CALLBACK_REQ                                       (WifiMsg)(IWIFICHIP_REQ_BASE + 0x001C)
#define IWIFICHIP_REMOVE_AP_IFACE_REQ                                               (WifiMsg)(IWIFICHIP_REQ_BASE + 0x001D)
#define IWIFICHIP_REMOVE_IFACE_INSTANCE_FROM_BRIDGED_AP_IFACE_REQ                   (WifiMsg)(IWIFICHIP_REQ_BASE + 0x001E)
#define IWIFICHIP_REMOVE_NAN_IFACE_REQ                                              (WifiMsg)(IWIFICHIP_REQ_BASE + 0x001F)
#define IWIFICHIP_REMOVE_P2P_IFACE_REQ                                              (WifiMsg)(IWIFICHIP_REQ_BASE + 0x0020)
#define IWIFICHIP_REMOVE_STA_IFACE_REQ                                              (WifiMsg)(IWIFICHIP_REQ_BASE + 0x0021)
#define IWIFICHIP_REQUEST_CHIP_DEBUG_INFO_REQ                                       (WifiMsg)(IWIFICHIP_REQ_BASE + 0x0022)
#define IWIFICHIP_REQUEST_DRIVER_DEBUG_DUMP_REQ                                     (WifiMsg)(IWIFICHIP_REQ_BASE + 0x0023)
#define IWIFICHIP_REQUEST_FIRMWARE_DEBUG_DUMP_REQ                                   (WifiMsg)(IWIFICHIP_REQ_BASE + 0x0024)
#define IWIFICHIP_RESET_TX_POWER_SCENARIO_REQ                                       (WifiMsg)(IWIFICHIP_REQ_BASE + 0x0025)
#define IWIFICHIP_SELECT_TX_POWER_SCENARIO_REQ                                      (WifiMsg)(IWIFICHIP_REQ_BASE + 0x0026)
#define IWIFICHIP_SET_COEX_UNSAFE_CHANNELS_REQ                                      (WifiMsg)(IWIFICHIP_REQ_BASE + 0x0027)
#define IWIFICHIP_SET_COUNTRY_CODE_REQ                                              (WifiMsg)(IWIFICHIP_REQ_BASE + 0x0028)
#define IWIFICHIP_SET_LATENCY_MODE_REQ                                              (WifiMsg)(IWIFICHIP_REQ_BASE + 0x0029)
#define IWIFICHIP_SET_MULTI_STA_PRIMARY_CONNECTION_REQ                              (WifiMsg)(IWIFICHIP_REQ_BASE + 0x002A)
#define IWIFICHIP_SET_MULTI_STA_USE_CASE_REQ                                        (WifiMsg)(IWIFICHIP_REQ_BASE + 0x002B)
#define IWIFICHIP_START_LOGGING_TO_DEBUG_RING_BUFFER_REQ                            (WifiMsg)(IWIFICHIP_REQ_BASE + 0x002C)
#define IWIFICHIP_STOP_LOGGING_TO_DEBUG_RING_BUFFER_REQ                             (WifiMsg)(IWIFICHIP_REQ_BASE + 0x002D)
#define IWIFICHIP_TRIGGER_SUBSYSTEM_RESTART_REQ                                     (WifiMsg)(IWIFICHIP_REQ_BASE + 0x002E)
#define IWIFICHIP_ENABLE_STA_CHANNEL_FOR_PEER_NETWORK_REQ                           (WifiMsg)(IWIFICHIP_REQ_BASE + 0x002F)
#define IWIFICHIP_SET_MLO_MODE_REQ                                                  (WifiMsg)(IWIFICHIP_REQ_BASE + 0x0030)

#define IWIFICHIP_REQ_COUNT                                                         49

#define IWIFICHIP_IND_BASE                                                          ((WifiMsg)(0x0300))

#define IWIFICHIP_ON_CHIP_RECONFIGURE_FAILURE_IND                                   (WifiMsg)(IWIFICHIP_IND_BASE + 0x0000)
#define IWIFICHIP_ON_CHIP_RECONFIGURED_IND                                          (WifiMsg)(IWIFICHIP_IND_BASE + 0x0001)
#define IWIFICHIP_ON_DEBUG_ERROR_ALERT_IND                                          (WifiMsg)(IWIFICHIP_IND_BASE + 0x0002)
#define IWIFICHIP_ON_DEBUG_RING_BUFFER_DATA_AVAILABLE_IND                           (WifiMsg)(IWIFICHIP_IND_BASE + 0x0003)
#define IWIFICHIP_ON_IFACE_ADDED_IND                                                (WifiMsg)(IWIFICHIP_IND_BASE + 0x0004)
#define IWIFICHIP_ON_IFACE_REMOVED_IND                                              (WifiMsg)(IWIFICHIP_IND_BASE + 0x0005)
#define IWIFICHIP_ON_RADIO_MODE_CHANGE_IND                                          (WifiMsg)(IWIFICHIP_IND_BASE + 0x0006)

#define IWIFICHIP_IND_COUNT                                                         7

#define IWIFI_IND_BASE                                                              ((WifiMsg)(0x0400))

#define IWIFI_ON_FAILURE_IND                                                        (WifiMsg)(IWIFI_IND_BASE + 0x0000)
#define IWIFI_ON_START_IND                                                          (WifiMsg)(IWIFI_IND_BASE + 0x0001)
#define IWIFI_ON_STOP_IND                                                           (WifiMsg)(IWIFI_IND_BASE + 0x0002)
#define IWIFI_ON_SUBSYSTEM_RESTART_IND                                              (WifiMsg)(IWIFI_IND_BASE + 0x0003)

#define IWIFI_IND_COUNT                                                             4

#define IWIFINANIFACE_REQ_BASE                                                      ((WifiMsg)(0x0500))

#define IWIFINANIFACE_GET_NAME_REQ                                                  (WifiMsg)(IWIFINANIFACE_REQ_BASE + 0x0000)
#define IWIFINANIFACE_CONFIG_REQUEST_REQ                                            (WifiMsg)(IWIFINANIFACE_REQ_BASE + 0x0001)
#define IWIFINANIFACE_CREATE_DATA_INTERFACE_REQUEST_REQ                             (WifiMsg)(IWIFINANIFACE_REQ_BASE + 0x0002)
#define IWIFINANIFACE_DELETE_DATA_INTERFACE_REQUEST_REQ                             (WifiMsg)(IWIFINANIFACE_REQ_BASE + 0x0003)
#define IWIFINANIFACE_DISABLE_REQUEST_REQ                                           (WifiMsg)(IWIFINANIFACE_REQ_BASE + 0x0004)
#define IWIFINANIFACE_ENABLE_REQUEST_REQ                                            (WifiMsg)(IWIFINANIFACE_REQ_BASE + 0x0005)
#define IWIFINANIFACE_GET_CAPABILITIES_REQUEST_REQ                                  (WifiMsg)(IWIFINANIFACE_REQ_BASE + 0x0006)
#define IWIFINANIFACE_INITIATE_DATA_PATH_REQUEST_REQ                                (WifiMsg)(IWIFINANIFACE_REQ_BASE + 0x0007)
#define IWIFINANIFACE_REGISTER_EVENT_CALLBACK_REQ                                   (WifiMsg)(IWIFINANIFACE_REQ_BASE + 0x0008)
#define IWIFINANIFACE_RESPOND_TO_DATA_PATH_INDICATION_REQUEST_REQ                   (WifiMsg)(IWIFINANIFACE_REQ_BASE + 0x0009)
#define IWIFINANIFACE_START_PUBLISH_REQUEST_REQ                                     (WifiMsg)(IWIFINANIFACE_REQ_BASE + 0x000A)
#define IWIFINANIFACE_START_SUBSCRIBE_REQUEST_REQ                                   (WifiMsg)(IWIFINANIFACE_REQ_BASE + 0x000B)
#define IWIFINANIFACE_STOP_PUBLISH_REQUEST_REQ                                      (WifiMsg)(IWIFINANIFACE_REQ_BASE + 0x000C)
#define IWIFINANIFACE_STOP_SUBSCRIBE_REQUEST_REQ                                    (WifiMsg)(IWIFINANIFACE_REQ_BASE + 0x000D)
#define IWIFINANIFACE_TERMINATE_DATA_PATH_REQUEST_REQ                               (WifiMsg)(IWIFINANIFACE_REQ_BASE + 0x000E)
#define IWIFINANIFACE_SUSPEND_REQUEST_REQ                                           (WifiMsg)(IWIFINANIFACE_REQ_BASE + 0x000F)
#define IWIFINANIFACE_RESUME_REQUEST_REQ                                            (WifiMsg)(IWIFINANIFACE_REQ_BASE + 0x0010)
#define IWIFINANIFACE_TRANSMIT_FOLLOWUP_REQUEST_REQ                                 (WifiMsg)(IWIFINANIFACE_REQ_BASE + 0x0011)
#define IWIFINANIFACE_INITIATE_PAIRING_REQUEST_REQ                                  (WifiMsg)(IWIFINANIFACE_REQ_BASE + 0x0012)
#define IWIFINANIFACE_RESPOND_TO_PAIRING_INDICATION_REQUEST_REQ                     (WifiMsg)(IWIFINANIFACE_REQ_BASE + 0x0013)
#define IWIFINANIFACE_INITIATE_BOOTSTRAPPING_REQUEST_REQ                            (WifiMsg)(IWIFINANIFACE_REQ_BASE + 0x0014)
#define IWIFINANIFACE_RESPOND_TO_BOOTSTRAPPING_INDICATION_REQUEST_REQ               (WifiMsg)(IWIFINANIFACE_REQ_BASE + 0x0015)
#define IWIFINANIFACE_TERMINATE_PAIRING_REQUEST_REQ                                 (WifiMsg)(IWIFINANIFACE_REQ_BASE + 0x0016)

#define IWIFINANIFACE_REQ_COUNT                                                     23

#define IWIFINANIFACE_IND_BASE                                                      ((WifiMsg)(0x0600))

#define IWIFINANIFACE_EVENT_CLUSTER_EVENT_IND                                       (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x0000)
#define IWIFINANIFACE_EVENT_DATA_PATH_CONFIRM_IND                                   (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x0001)
#define IWIFINANIFACE_EVENT_DATA_PATH_REQUEST_IND                                   (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x0002)
#define IWIFINANIFACE_EVENT_DATA_PATH_SCHEDULE_UPDATE_IND                           (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x0003)
#define IWIFINANIFACE_EVENT_DATA_PATH_TERMINATED_IND                                (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x0004)
#define IWIFINANIFACE_EVENT_DISABLED_IND                                            (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x0005)
#define IWIFINANIFACE_EVENT_FOLLOWUP_RECEIVED_IND                                   (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x0006)
#define IWIFINANIFACE_EVENT_MATCH_IND                                               (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x0007)
#define IWIFINANIFACE_EVENT_MATCH_EXPIRED_IND                                       (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x0008)
#define IWIFINANIFACE_EVENT_PUBLISH_TERMINATED_IND                                  (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x0009)
#define IWIFINANIFACE_EVENT_SUBSCRIBE_TERMINATED_IND                                (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x000A)
#define IWIFINANIFACE_EVENT_TRANSMIT_FOLLOWUP_IND                                   (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x000B)
#define IWIFINANIFACE_EVENT_SUSPENSION_MODE_CHANGED_IND                             (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x000C)
#define IWIFINANIFACE_NOTIFY_CAPABILITIES_RESPONSE_IND                              (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x000D)
#define IWIFINANIFACE_NOTIFY_CONFIG_RESPONSE_IND                                    (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x000E)
#define IWIFINANIFACE_NOTIFY_CREATE_DATA_INTERFACE_RESPONSE_IND                     (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x000F)
#define IWIFINANIFACE_NOTIFY_DELETE_DATA_INTERFACE_RESPONSE_IND                     (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x0010)
#define IWIFINANIFACE_NOTIFY_DISABLE_RESPONSE_IND                                   (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x0011)
#define IWIFINANIFACE_NOTIFY_ENABLE_RESPONSE_IND                                    (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x0012)
#define IWIFINANIFACE_NOTIFY_INITIATE_DATA_PATH_RESPONSE_IND                        (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x0013)
#define IWIFINANIFACE_NOTIFY_RESPOND_TO_DATA_PATH_INDICATION_RESPONSE_IND           (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x0014)
#define IWIFINANIFACE_NOTIFY_START_PUBLISH_RESPONSE_IND                             (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x0015)
#define IWIFINANIFACE_NOTIFY_START_SUBSCRIBE_RESPONSE_IND                           (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x0016)
#define IWIFINANIFACE_NOTIFY_STOP_PUBLISH_RESPONSE_IND                              (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x0017)
#define IWIFINANIFACE_NOTIFY_STOP_SUBSCRIBE_RESPONSE_IND                            (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x0018)
#define IWIFINANIFACE_NOTIFY_TERMINATE_DATA_PATH_RESPONSE_IND                       (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x0019)
#define IWIFINANIFACE_NOTIFY_SUSPEND_RESPONSE_IND                                   (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x001A)
#define IWIFINANIFACE_NOTIFY_RESUME_RESPONSE_IND                                    (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x001B)
#define IWIFINANIFACE_NOTIFY_TRANSMIT_FOLLOWUP_RESPONSE_IND                         (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x001C)
#define IWIFINANIFACE_EVENT_PAIRING_REQUEST_IND                                     (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x001D)
#define IWIFINANIFACE_EVENT_PAIRING_CONFIRM_IND                                     (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x001E)
#define IWIFINANIFACE_NOTIFY_INITIATE_PAIRING_RESPONSE_IND                          (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x001F)
#define IWIFINANIFACE_NOTIFY_RESPOND_TO_PAIRING_INDICATION_RESPONSE_IND             (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x0020)
#define IWIFINANIFACE_EVENT_BOOTSTRAPPING_REQUEST_IND                               (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x0021)
#define IWIFINANIFACE_EVENT_BOOTSTRAPPING_CONFIRM_IND                               (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x0022)
#define IWIFINANIFACE_NOTIFY_INITIATE_BOOTSTRAPPING_RESPONSE_IND                    (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x0023)
#define IWIFINANIFACE_NOTIFY_RESPOND_TO_BOOTSTRAPPING_INDICATION_RESPONSE_IND       (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x0024)
#define IWIFINANIFACE_NOTIFY_TERMINATE_PAIRING_RESPONSE_IND                         (WifiMsg)(IWIFINANIFACE_IND_BASE + 0x0025)

#define IWIFINANIFACE_IND_COUNT                                                     38

#define IWIFIP2PIFACE_REQ_BASE                                                      ((WifiMsg)(0x0700))

#define IWIFIP2PIFACE_GET_NAME_REQ                                                  (WifiMsg)(IWIFIP2PIFACE_REQ_BASE + 0x0000)

#define IWIFIP2PIFACE_REQ_COUNT                                                     1

#define IWIFIRTTCONTROLLER_REQ_BASE                                                 ((WifiMsg)(0x0800))

#define IWIFIRTTCONTROLLER_DISABLE_RESPONDER_REQ                                    (WifiMsg)(IWIFIRTTCONTROLLER_REQ_BASE + 0x0000)
#define IWIFIRTTCONTROLLER_ENABLE_RESPONDER_REQ                                     (WifiMsg)(IWIFIRTTCONTROLLER_REQ_BASE + 0x0001)
#define IWIFIRTTCONTROLLER_GET_BOUND_IFACE_REQ                                      (WifiMsg)(IWIFIRTTCONTROLLER_REQ_BASE + 0x0002)
#define IWIFIRTTCONTROLLER_GET_CAPABILITIES_REQ                                     (WifiMsg)(IWIFIRTTCONTROLLER_REQ_BASE + 0x0003)
#define IWIFIRTTCONTROLLER_GET_RESPONDER_INFO_REQ                                   (WifiMsg)(IWIFIRTTCONTROLLER_REQ_BASE + 0x0004)
#define IWIFIRTTCONTROLLER_RANGE_CANCEL_REQ                                         (WifiMsg)(IWIFIRTTCONTROLLER_REQ_BASE + 0x0005)
#define IWIFIRTTCONTROLLER_RANGE_REQUEST_REQ                                        (WifiMsg)(IWIFIRTTCONTROLLER_REQ_BASE + 0x0006)
#define IWIFIRTTCONTROLLER_REGISTER_EVENT_CALLBACK_REQ                              (WifiMsg)(IWIFIRTTCONTROLLER_REQ_BASE + 0x0007)
#define IWIFIRTTCONTROLLER_SET_LCI_REQ                                              (WifiMsg)(IWIFIRTTCONTROLLER_REQ_BASE + 0x0008)
#define IWIFIRTTCONTROLLER_SET_LCR_REQ                                              (WifiMsg)(IWIFIRTTCONTROLLER_REQ_BASE + 0x0009)

#define IWIFIRTTCONTROLLER_REQ_COUNT                                                10

#define IWIFIRTTCONTROLLER_IND_BASE                                                 ((WifiMsg)(0x0900))

#define IWIFIRTTCONTROLLER_ON_RESULTS_IND                                           (WifiMsg)(IWIFIRTTCONTROLLER_IND_BASE + 0x0000)

#define IWIFIRTTCONTROLLER_IND_COUNT                                                1

#define IWIFISTAIFACE_REQ_BASE                                                      ((WifiMsg)(0x0A00))

#define IWIFISTAIFACE_GET_NAME_REQ                                                  (WifiMsg)(IWIFISTAIFACE_REQ_BASE + 0x0000)
#define IWIFISTAIFACE_CONFIGURE_ROAMING_REQ                                         (WifiMsg)(IWIFISTAIFACE_REQ_BASE + 0x0001)
#define IWIFISTAIFACE_DISABLE_LINK_LAYER_STATS_COLLECTION_REQ                       (WifiMsg)(IWIFISTAIFACE_REQ_BASE + 0x0002)
#define IWIFISTAIFACE_ENABLE_LINK_LAYER_STATS_COLLECTION_REQ                        (WifiMsg)(IWIFISTAIFACE_REQ_BASE + 0x0003)
#define IWIFISTAIFACE_ENABLE_ND_OFFLOAD_REQ                                         (WifiMsg)(IWIFISTAIFACE_REQ_BASE + 0x0004)
#define IWIFISTAIFACE_GET_APF_PACKET_FILTER_CAPABILITIES_REQ                        (WifiMsg)(IWIFISTAIFACE_REQ_BASE + 0x0005)
#define IWIFISTAIFACE_GET_BACKGROUND_SCAN_CAPABILITIES_REQ                          (WifiMsg)(IWIFISTAIFACE_REQ_BASE + 0x0006)
#define IWIFISTAIFACE_GET_FEATURE_SET_REQ                                           (WifiMsg)(IWIFISTAIFACE_REQ_BASE + 0x0007)
#define IWIFISTAIFACE_GET_DEBUG_RX_PACKET_FATES_REQ                                 (WifiMsg)(IWIFISTAIFACE_REQ_BASE + 0x0008)
#define IWIFISTAIFACE_GET_DEBUG_TX_PACKET_FATES_REQ                                 (WifiMsg)(IWIFISTAIFACE_REQ_BASE + 0x0009)
#define IWIFISTAIFACE_GET_FACTORY_MAC_ADDRESS_REQ                                   (WifiMsg)(IWIFISTAIFACE_REQ_BASE + 0x000A)
#define IWIFISTAIFACE_GET_LINK_LAYER_STATS_REQ                                      (WifiMsg)(IWIFISTAIFACE_REQ_BASE + 0x000B)
#define IWIFISTAIFACE_GET_ROAMING_CAPABILITIES_REQ                                  (WifiMsg)(IWIFISTAIFACE_REQ_BASE + 0x000C)
#define IWIFISTAIFACE_INSTALL_APF_PACKET_FILTER_REQ                                 (WifiMsg)(IWIFISTAIFACE_REQ_BASE + 0x000D)
#define IWIFISTAIFACE_READ_APF_PACKET_FILTER_DATA_REQ                               (WifiMsg)(IWIFISTAIFACE_REQ_BASE + 0x000E)
#define IWIFISTAIFACE_REGISTER_EVENT_CALLBACK_REQ                                   (WifiMsg)(IWIFISTAIFACE_REQ_BASE + 0x000F)
#define IWIFISTAIFACE_SET_MAC_ADDRESS_REQ                                           (WifiMsg)(IWIFISTAIFACE_REQ_BASE + 0x0010)
#define IWIFISTAIFACE_SET_ROAMING_STATE_REQ                                         (WifiMsg)(IWIFISTAIFACE_REQ_BASE + 0x0011)
#define IWIFISTAIFACE_SET_SCAN_MODE_REQ                                             (WifiMsg)(IWIFISTAIFACE_REQ_BASE + 0x0012)
#define IWIFISTAIFACE_START_BACKGROUND_SCAN_REQ                                     (WifiMsg)(IWIFISTAIFACE_REQ_BASE + 0x0013)
#define IWIFISTAIFACE_START_DEBUG_PACKET_FATE_MONITORING_REQ                        (WifiMsg)(IWIFISTAIFACE_REQ_BASE + 0x0014)
#define IWIFISTAIFACE_START_RSSI_MONITORING_REQ                                     (WifiMsg)(IWIFISTAIFACE_REQ_BASE + 0x0015)
#define IWIFISTAIFACE_START_SENDING_KEEP_ALIVE_PACKETS_REQ                          (WifiMsg)(IWIFISTAIFACE_REQ_BASE + 0x0016)
#define IWIFISTAIFACE_STOP_BACKGROUND_SCAN_REQ                                      (WifiMsg)(IWIFISTAIFACE_REQ_BASE + 0x0017)
#define IWIFISTAIFACE_STOP_RSSI_MONITORING_REQ                                      (WifiMsg)(IWIFISTAIFACE_REQ_BASE + 0x0018)
#define IWIFISTAIFACE_STOP_SENDING_KEEP_ALIVE_PACKETS_REQ                           (WifiMsg)(IWIFISTAIFACE_REQ_BASE + 0x0019)
#define IWIFISTAIFACE_SET_DTIM_MULTIPLIER_REQ                                       (WifiMsg)(IWIFISTAIFACE_REQ_BASE + 0x001A)

#define IWIFISTAIFACE_REQ_COUNT                                                     27

#define IWIFISTAIFACE_IND_BASE                                                      ((WifiMsg)(0x0B00))

#define IWIFISTAIFACE_ON_BACKGROUND_FULL_SCAN_RESULT_IND                            (WifiMsg)(IWIFISTAIFACE_IND_BASE + 0x0000)
#define IWIFISTAIFACE_ON_BACKGROUND_SCAN_FAILURE_IND                                (WifiMsg)(IWIFISTAIFACE_IND_BASE + 0x0001)
#define IWIFISTAIFACE_ON_BACKGROUND_SCAN_RESULTS_IND                                (WifiMsg)(IWIFISTAIFACE_IND_BASE + 0x0002)
#define IWIFISTAIFACE_ON_RSSI_THRESHOLD_BREACHED_IND                                (WifiMsg)(IWIFISTAIFACE_IND_BASE + 0x0003)

#define IWIFISTAIFACE_IND_COUNT                                                     4
