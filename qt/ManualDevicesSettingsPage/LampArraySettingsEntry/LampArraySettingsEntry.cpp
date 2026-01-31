/*---------------------------------------------------------*\
| LampArraySettingsEntry.cpp                                |
|                                                           |
|   User interface entry for HID LampArray configuration    |
|                                                           |
|   This file is part of the OpenRGB project                |
|   SPDX-License-Identifier: GPL-2.0-or-later               |
\*---------------------------------------------------------*/

#include "LampArraySettingsEntry.h"
#include "ui_LampArraySettingsEntry.h"

LampArraySettingsEntry::LampArraySettingsEntry(QWidget *parent) :
    BaseManualDeviceEntry(parent),
    ui(new Ui::LampArraySettingsEntry)
{
    ui->setupUi(this);
}

LampArraySettingsEntry::~LampArraySettingsEntry()
{
    delete ui;
}

void LampArraySettingsEntry::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}

void LampArraySettingsEntry::loadFromSettings(const json& data)
{
    if(data.contains("name"))
    {
        ui->NameEdit->setText(QString::fromStdString(data["name"]));
    }

    if(data.contains("usb_vid"))
    {
        ui->USBVIDEdit->setText(QString::fromStdString(data["usb_vid"]));
    }

    if(data.contains("usb_pid"))
    {
        ui->USBPIDEdit->setText(QString::fromStdString(data["usb_pid"]));
    }
}

json LampArraySettingsEntry::saveSettings()
{
    json result;
    /*-------------------------------------------------*\
    | Required parameters                               |
    \*-------------------------------------------------*/
    result["name"]     = ui->NameEdit->text().toStdString();
    result["usb_vid"]  = ui->USBVIDEdit->text().toStdString();
    result["usb_pid"]  = ui->USBPIDEdit->text().toStdString();

    return result;
}

bool LampArraySettingsEntry::isDataValid()
{
    // stub
    return true;
}

static BaseManualDeviceEntry* SpawnLampArraySettingsEntry(const json& data)
{
    LampArraySettingsEntry* entry = new LampArraySettingsEntry;
    entry->loadFromSettings(data);
    return entry;
}

static const char* LampArrayDeviceName = QT_TRANSLATE_NOOP("ManualDevice", "HID LampArray Device");

REGISTER_MANUAL_DEVICE_TYPE(LampArrayDeviceName, "HIDLampArrayDevices", SpawnLampArraySettingsEntry);
