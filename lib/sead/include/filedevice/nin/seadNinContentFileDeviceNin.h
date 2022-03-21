#pragma once

#include "filedevice/nin/seadNinFileDeviceBaseNin.h"

namespace sead
{
class NinContentFileDevice : public NinFileDeviceBase
{
    SEAD_RTTI_OVERRIDE(NinContentFileDevice, NinFileDeviceBase)

public:
    NinContentFileDevice();
};
}  // namespace sead
