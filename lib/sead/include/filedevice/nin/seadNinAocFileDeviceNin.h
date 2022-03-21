#pragma once

#include "filedevice/nin/seadNinFileDeviceBaseNin.h"

namespace sead
{
class NinAocFileDevice : public NinFileDeviceBase
{
    SEAD_RTTI_OVERRIDE(NinAocFileDevice, NinFileDeviceBase)

public:
    explicit NinAocFileDevice(const SafeString& mount);
};
}  // namespace sead
