#pragma once

#include "filedevice/nin/seadNinFileDeviceBaseNin.h"

namespace sead
{
class NinSaveFileDevice : public NinFileDeviceBase
{
    SEAD_RTTI_OVERRIDE(NinSaveFileDevice, NinFileDeviceBase)

public:
    explicit NinSaveFileDevice(const SafeString& mount);
    bool tryCommit();
};
}  // namespace sead
