/*---------------------------------------------------------*\
| LampArraySettingsEntry.h                                  |
|                                                           |
|   User interface entry for HID LampArray configuration    |
|                                                           |
|   This file is part of the OpenRGB project                |
|   SPDX-License-Identifier: GPL-2.0-or-later               |
\*---------------------------------------------------------*/

#pragma once

#include "BaseManualDeviceEntry.h"

namespace Ui
{
    class LampArraySettingsEntry;
}

class LampArraySettingsEntry : public BaseManualDeviceEntry
{
    Q_OBJECT

private slots:
    void changeEvent(QEvent *event) override;

public:
    explicit LampArraySettingsEntry(QWidget *parent = nullptr);
    ~LampArraySettingsEntry();
    void loadFromSettings(const json& data);
    json saveSettings() override;
    bool isDataValid() override;

private:
    Ui::LampArraySettingsEntry *ui;
};
