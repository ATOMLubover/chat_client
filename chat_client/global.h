#pragma once

#include "EnumError.h"
#include "EnumModule.h"
#include "EnumRequestType.h"

#include <QString>
#include <QFile>
#include <QDir>
#include <QSettings>

#include <string>

extern QString gate_url_prefix;

enum TipErr {
    TIP_SUCCESS = 0,
    TIP_EMAIL_ERR = 1,
    TIP_PWD_ERR = 2,
    TIP_CONFIRM_ERR = 3,
    TIP_PWD_CONFIRM = 4,
    TIP_VARIFY_ERR = 5,
    TIP_USER_ERR = 6
};