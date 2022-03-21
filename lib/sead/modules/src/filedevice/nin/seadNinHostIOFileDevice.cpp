#include "filedevice/nin/seadNinHostIOFileDevice.h"
#include "devenv/seadEnvUtil.h"
#include "filedevice/seadFileDeviceMgr.h"

namespace sead
{
NinHostIOFileDevice::NinHostIOFileDevice() : NinFileDeviceBase("hostio", "hostio") {}

bool NinHostIOFileDevice::doIsAvailable_() const
{
#ifndef SEAD_DEBUG
    return false;
#endif
    return FileDeviceMgr::instance()->hasMountedHost();
}

bool NinHostIOFileDevice::formatPathForFS_(BufferedSafeString* out, const SafeString& path) const
{
#ifndef SEAD_DEBUG
    return false;
#endif
    EnvUtil::resolveEnvronmentVariable(out, path);
    return out->include(":") && isAvailable();
}
}  // namespace sead
