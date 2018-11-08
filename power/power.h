/*
 * Copyright (C) 2016 The CyanogenMod Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "HI3635 PowerHAL"

#define STATE_ON "state=1"

#define KERNEL_HMP_PATH "/sys/kernel/hmp/"
#define GPUFREQ_PATH "/sys/class/devfreq/gpufreq/"

#define CPUFREQ_PATH0 "/sys/devices/system/cpu/cpu0/cpufreq/"
#define CPUFREQ_PATH1 "/sys/devices/system/cpu/cpu4/cpufreq/"

#define INTERACTIVE_PATH0 "/sys/devices/system/cpu/cpu0/cpufreq/interactive/"
#define INTERACTIVE_PATH1 "/sys/devices/system/cpu/cpu4/cpufreq/ondemand/"

#define TAP_TO_WAKE_NODE "/sys/touchscreen/easy_wakeup_gesture"
#define TAP_TO_WAKE_UP "/sys/touchscreen/wakeup_gesture_enable"

#define VID_ENC_TIMER_RATE 30000
#define VID_ENC_IO_IS_BUSY 0

enum {
    PROFILE_POWER_SAVE = 0,
    PROFILE_BALANCED,
    PROFILE_HIGH_PERFORMANCE,
    PROFILE_MAX
};

typedef struct governor_settings {
    // cpu0
    int boost;
    int boostpulse_duration;
    int go_hispeed_load;
    int go_hispeed_load_off;
    int hispeed_freq;
    int hispeed_freq_off;
    int io_is_busy;
    char *target_loads;
    char *target_loads_off;
    // cpu4
    int sampling_down_factor;
    int sampling_rate;
    int up_threshold; 
    // freq.
    unsigned long scaling_max_freq;
    unsigned long scaling_min_freq;
    // gpu
    unsigned long max_freq;
    unsigned long min_freq;
    int polling_interval;
    // kernel hmp
    int kernel_down_threshold;
    int kernel_up_threshold;
    int kernel_up_prio;
} power_profile;

static power_profile profiles0[PROFILE_MAX] = {
    [PROFILE_POWER_SAVE] = {
        .boost = 0,
        .boostpulse_duration = 80000,
        .go_hispeed_load = 99,
        .go_hispeed_load_off = 110,
        .hispeed_freq = 1209600,
        .hispeed_freq_off = 1516800,
        .io_is_busy = 0,
        .target_loads = "95",
        .target_loads_off = "95",
        .scaling_max_freq = 1516800,
        .scaling_min_freq = 403200,
	.max_freq = 680000000,
	.min_freq = 288000000,
	.polling_interval = 20,
	.kernel_down_threshold = 768,
	.kernel_up_threshold = 1008,
	.kernel_up_prio = 140,
    },
    [PROFILE_BALANCED] = {
        .boost = 0,
        .boostpulse_duration = 80000,
        .go_hispeed_load = 99,
        .go_hispeed_load_off = 110,
        .hispeed_freq = 1209600,
        .hispeed_freq_off = 1516800,
        .io_is_busy = 1,
        .target_loads = "70:604800:75:806400:90:1209600:95",
        .target_loads_off = "95 1516800:99",
        .scaling_max_freq = 1516800,
        .scaling_min_freq = 403200,
	.max_freq = 680000000,
	.min_freq = 288000000,
	.polling_interval = 40,
	.kernel_down_threshold = 672,
	.kernel_up_threshold = 978,
	.kernel_up_prio = 140,
    },
    [PROFILE_HIGH_PERFORMANCE] = {
        .boost = 1,
        .boostpulse_duration = 160000,
        .go_hispeed_load = 95,
        .go_hispeed_load_off = 110,
        .hispeed_freq = 1516800,
        .hispeed_freq_off = 1516800,
        .io_is_busy = 1,
        .target_loads = "30:604800:40:806400:50:1209600:85",
        .target_loads_off = "95 1516800:99",
        .scaling_max_freq = 1516800,
        .scaling_min_freq = 403200,
	.max_freq = 680000000,
	.min_freq = 360000000,
	.polling_interval = 50,
	.kernel_down_threshold = 200,
	.kernel_up_threshold = 500,
	.kernel_up_prio = 140,
    },
};

static power_profile profiles4[PROFILE_MAX] = {
    [PROFILE_POWER_SAVE] = {
        .io_is_busy = 0,
	.sampling_down_factor = 1,
	.sampling_rate = 10000,
	.up_threshold = 99,
        .scaling_max_freq = 2016000,
        .scaling_min_freq = 1017600,
	.max_freq = 680000000,
	.min_freq = 288000000,
	.polling_interval = 20,
	.kernel_down_threshold = 768,
	.kernel_up_threshold = 1008,
	.kernel_up_prio = 140,
    },
    [PROFILE_BALANCED] = {
        .io_is_busy = 0,
	.sampling_down_factor = 2,
	.sampling_rate = 20000,
	.up_threshold = 95,
        .scaling_max_freq = 2016000,
        .scaling_min_freq = 1017600,
	.max_freq = 680000000,
	.min_freq = 288000000,
	.polling_interval = 40,
	.kernel_down_threshold = 672,
	.kernel_up_threshold = 978,
	.kernel_up_prio = 140,
    },
    [PROFILE_HIGH_PERFORMANCE] = {
        .io_is_busy = 1,
	.sampling_down_factor = 4,
	.sampling_rate = 50000,
	.up_threshold = 85,
        .scaling_max_freq = 2016000,
        .scaling_min_freq = 1017600,
	.max_freq = 680000000,
	.min_freq = 360000000,
	.polling_interval = 50,
	.kernel_down_threshold = 200,
	.kernel_up_threshold = 500,
	.kernel_up_prio = 140,
    },
};
