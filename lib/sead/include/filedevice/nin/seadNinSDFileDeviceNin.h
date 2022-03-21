#pragma once

#include "filedevice/nin/seadNinFileDeviceBaseNin.h"

namespace sead
{
class NinSDFileDevice : public NinFileDeviceBase
{
    SEAD_RTTI_OVERRIDE(NinSDFileDevice, NinFileDeviceBase)

public:
    NinSDFileDevice();

    bool doIsAvailable_() const override;
};
}  // namespace sead
