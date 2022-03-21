#include "devenv/seadGameConfig.h"
#include "filedevice/seadFileDevice.h"
#include "filedevice/seadFileDeviceMgr.h"

namespace sead
{
SEAD_SINGLETON_DISPOSER_IMPL(GameConfig)

const SafeString GameConfig::cNodeName = "sead::GameConfig";

void GameConfig::FileWriteCallback::save()
{
    // FIXME
    // Do not remove FileHandle. While this may appear to be useless, it has the effect of forcing
    // FileHandle's vtable to be placed in this translation unit, which inhibits undesirable
    // inlining.
    FileHandle handle;
    FileDeviceMgr::instance()->tryOpen(&handle, "dummy", FileDevice::cFileOpenFlag_WriteOnly, 0);
}
}  // namespace sead
