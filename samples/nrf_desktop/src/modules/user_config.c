/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#include <assert.h>

#include <zephyr.h>

#define MODULE user_config
//#include "module_state_event.h"

#include "config_event.h"
#include "motion_event.h"

#include <logging/log.h>
LOG_MODULE_REGISTER(MODULE, CONFIG_DESKTOP_USER_CONFIG_LOG_LEVEL);

enum {
	USER_CONFIG_ID_RESERVED,
	USER_CONFIG_ID_MOUSE_CPI
};

static struct user_cfg {
	u16_t mouse_cpi; /* Mouse optical sensor resolution (counts per inch) */
} user_cfg;

static void user_cfg_process(u8_t id, u8_t *data)
{
	switch (id) {
	case USER_CONFIG_ID_MOUSE_CPI:
		/* Store configuration */
		user_cfg.mouse_cpi = (u16_t)(data[0] + (data[1] << 8));

		LOG_WRN("CPI = %u", user_cfg.mouse_cpi);

		/* Emit new configuration to module */
		struct motion_config_event *event = new_motion_config_event();

		if (event) {
			event->cpi = user_cfg.mouse_cpi;
			EVENT_SUBMIT(event);
		}
		break;
	default:
		LOG_WRN("Unsupported config id %u", id);
		break;
	}

}

static bool event_handler(const struct event_header *eh)
{
	if (is_config_event(eh)) {
		struct config_event *event = cast_config_event(eh);

		user_cfg_process(event->id, event->data);

		return false;
	}

	/* If event is unhandled, unsubscribe. */
	__ASSERT_NO_MSG(false);

	return false;
}

EVENT_LISTENER(MODULE, event_handler);
EVENT_SUBSCRIBE(MODULE, config_event);
