/*---------------------------------------------------------*\
| HIDLampArrayControllerDetect.cpp                          |
|                                                           |
|   Detector for HID LampArray Devices                      |
|                                                           |
|   Adam Honse (calcprogrammer1@gmail.com)      26 Mar 2024 |
|   Angel Talero (angelgotalero@outlook.com)    30 Jan 2026 |
|                                                           |
|   This file is part of the OpenRGB project                |
|   SPDX-License-Identifier: GPL-2.0-only                   |
\*---------------------------------------------------------*/

#include <vector>
#include <hidapi.h>
#include "Detector.h"
#include "HIDLampArrayController.h"
#include "RGBController.h"
#include "RGBController_HIDLampArray.h"
#include "SettingsManager.h"

/*-----------------------------------------------------*\
| Usage and Usage Page                                  |
\*-----------------------------------------------------*/
#define LAMPARRAY_USAGE_PAGE                    0x59
#define LAMPARRAY_USAGE                         0x01

void DetectHIDLampArrayControllers(hid_device_info* info, const std::string& name)
{
    hid_device* dev = hid_open_path(info->path);

    if(dev)
    {
        HIDLampArrayController*     controller     = new HIDLampArrayController(dev, info->path, name);
        RGBController_HIDLampArray* rgb_controller = new RGBController_HIDLampArray(controller);

        ResourceManager::get()->RegisterRGBController(rgb_controller);
    }
}

void RegisterHIDLampArrayDetectors()
{
    /*-------------------------------------------------*\
    | Get HID LampArray settings                        |
    \*-------------------------------------------------*/
    json lamparray_settings = ResourceManager::get()->GetSettingsManager()->GetSettings("HIDLampArrayDevices");

    if(lamparray_settings.contains("devices"))
    {
        for(unsigned int device_idx = 0; device_idx < lamparray_settings["devices"].size(); device_idx++)
        {
            if( lamparray_settings["devices"][device_idx].contains("usb_pid")
             && lamparray_settings["devices"][device_idx].contains("usb_vid")
             && lamparray_settings["devices"][device_idx].contains("name"))
            {
                std::string usb_pid_str = lamparray_settings["devices"][device_idx]["usb_pid"];
                std::string usb_vid_str = lamparray_settings["devices"][device_idx]["usb_vid"];
                std::string name        = lamparray_settings["devices"][device_idx]["name"];

                /*-------------------------------------*\
                | Parse hex string to integer           |
                \*-------------------------------------*/
                unsigned short usb_pid  = std::stoi(usb_pid_str, 0, 16);
                unsigned short usb_vid  = std::stoi(usb_vid_str, 0, 16);

                REGISTER_DYNAMIC_HID_DETECTOR_PU(name, DetectHIDLampArrayControllers, usb_vid, usb_pid, LAMPARRAY_USAGE_PAGE, LAMPARRAY_USAGE);
            }
        }
    }
}

REGISTER_DYNAMIC_DETECTOR("HID LampArray Devices", RegisterHIDLampArrayDetectors);
