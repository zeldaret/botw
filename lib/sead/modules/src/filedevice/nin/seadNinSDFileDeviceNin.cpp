#include "filedevice/nin/seadNinSDFileDeviceNin.h"
#include "filedevice/seadFileDeviceMgr.h"

namespace sead
{
NinSDFileDevice::NinSDFileDevice() : NinFileDeviceBase("sd", "sd") {}

bool NinSDFileDevice::doIsAvailable_() const
{
    return FileDeviceMgr::instance()->hasMountedSd();
}
}  // namespace sead
