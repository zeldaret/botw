#include "filedevice/nin/seadNinSaveFileDeviceNin.h"

namespace sead
{
NinSaveFileDevice::NinSaveFileDevice(const SafeString& mount) : NinFileDeviceBase("save", mount) {}

bool NinSaveFileDevice::tryCommit()
{
    const auto result = nn::fs::CommitSaveData(mMountPoint.cstr());
    mLastError = result;

    if (result.IsSuccess())
        return true;

    SEAD_WARN(
        "nn::fs::CommitSaveData failed. module = %d desc = %d inner_value = 0x%08x mount_name=%s",
        result.GetModule(), result.GetDescription(), result.GetInnerValueForDebug(),
        mMountPoint.cstr());
    return false;
}
}  // namespace sead
