/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#ifndef _CONFIG_EVENT_H_
#define _CONFIG_EVENT_H_

/**
 * @brief Config Event
 * @defgroup config_event Config Event
 * @{
 */

#include "event_manager.h"
#include "hid_report_desc.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Configuration channel event received from user via wireless or wired
 * transport. Used to change firmware parameters at runtime.
 */
struct config_event {
	struct event_header header;

	u8_t id;
	u8_t data[REPORT_SIZE_USER_CONFIG - 1];
};

EVENT_TYPE_DECLARE(config_event);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* _LED_EVENT_H_ */
