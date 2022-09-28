/*
  ==============================================================================

    Constants.h
    Created: 11 Sep 2022 9:21:26pm
    Author:  pwmag

  ==============================================================================
*/

#pragma once

// Parameter tree IDs
#define GAIN_ID     "GAIN"
#define SAT_ID      "SATURATION"
#define DIODE_1_ID  "DIODE_1"
#define DIODE_2_ID  "DIODE_2"
#define VF_ID       "FORWARD_VOLTAGE"
#define VB_ID       "BREAKDOWN_VOLTAGE"
#define TRR_ID      "RECOVERY_TIME"
#define MIX_ID      "MIX"
#define DC_OFF_ID   "DC_OFF"
#define HUE_ID      "HUE"

// Parameter names
#define GAIN_NAME       "Gain"
#define SAT_NAME        "Sat"
#define DIODE_1_NAME    "Positive Diode"
#define DIODE_2_NAME    "Negative Diode"
#define VF_NAME         "Forward Voltage"
#define VB_NAME         "Breakdown Voltage"
#define TRR_NAME        "Reverse Recovery Time"
#define MIX_NAME        "Mix"
#define DC_OFF_NAME     "Remove DC Offset"
#define HUE_NAME        "UI Hue"

// Fonts
#define FONT_MAIN       BinaryData::RalewayMedium_ttf
#define FONT_MAIN_SIZE  BinaryData::RalewayMedium_ttfSize
#define FONT_BOLD       BinaryData::RalewayRegular_ttf
#define FONT_BOLD_SIZE  BinaryData::RalewayRegular_ttfSize
#define FONT_LIGHT      BinaryData::RalewayLight_ttf
#define FONT_LIGHT_SIZE BinaryData::RalewayLight_ttfSize

// Images
#define IMAGE_LOGO      BinaryData::diodine_logo_svg
#define IMAGE_LOGO_SIZE BinaryData::diodine_logo_svgSize
#define IMAGE_BG        BinaryData::diodine_bg_svg
#define IMAGE_BG_SIZE   BinaryData::diodine_bg_svgSize

// Window properties
#define WIDTH               720u
#define HEIGHT              520u
#define MAX_SCALE           2.f
#define LOCAL_WIDTH_ID      "WIDTH"
#define LOCAL_HEIGHT_ID     "HEIGHT"