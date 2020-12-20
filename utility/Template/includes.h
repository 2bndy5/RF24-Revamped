/**
 * @file includes.h
 * Configuration defines for RF24/Linux
 */

#ifndef __RF24_INCLUDES_H__
#define __RF24_INCLUDES_H__

/**
 * Define a specific platform for this configuration. For example.
 * our platform is named "BBB".
 */
#define RF24_BBB

/**
 * Load the correct configuration for this platform
 */
#include "BBB/RF24_arch_config.h"

#endif
