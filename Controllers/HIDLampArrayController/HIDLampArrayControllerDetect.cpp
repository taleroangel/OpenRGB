/*---------------------------------------------------------*\
| HIDLampArrayControllerDetect.cpp                          |
|                                                           |
|   Detector for HID LampArray Devices                      |
|                                                           |
|   Adam Honse (calcprogrammer1@gmail.com)      26 Mar 2024 |
|                                                           |
|   This file is part of the OpenRGB project                |
|   SPDX-License-Identifier: GPL-2.0-only                   |
\*---------------------------------------------------------*/

#include "Detector.h"
#include "HIDLampArrayController.h"
#include "RGBController.h"
#include "RGBController_HIDLampArray.h"
#include <vector>
#include <hidapi.h>

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

REGISTER_HID_DETECTOR_PU("Arduino Zero HID Lamp Array Demo", DetectHIDLampArrayControllers, 0x2341, 0x804D, 0x59, 0x01);
