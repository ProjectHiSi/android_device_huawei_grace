# Copyright (C) 2017 The LineageOS Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Inherit from those products. Most specific first.
$(call inherit-product, $(SRC_TARGET_DIR)/product/core_64_bit.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/aosp_base_telephony.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/locales_full.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/product_launched_with_m.mk)

# Inherit some common CM stuff.
$(call inherit-product, vendor/cm/config/common_full_phone.mk)

# Inherit from kiwi device
$(call inherit-product, device/huawei/grace/device.mk)

# Boot animation
TARGET_SCREEN_HEIGHT := 1920
TARGET_SCREEN_WIDTH := 1080

PRODUCT_GMS_CLIENTID_BASE := android-huawei

PRODUCT_NAME := lineage_grace
PRODUCT_DEVICE := grace
PRODUCT_BRAND := Huawei
PRODUCT_MANUFACTURER := HUAWEI
PRODUCT_MODEL := HUAWEI-P8

PRODUCT_BUILD_PROP_OVERRIDES += \
    BUILD_FINGERPRINT="HUAWEI/GRA-L09/HWGRA:6.0/HUAWEIGRA-L09/C109B379:user/release-keys" \
    PRIVATE_BUILD_DESC="GRA-L09-user 6.0 HUAWEIGRA-L09 C109B379 release-keys" \
    TARGET_DEVICE=hi3635
