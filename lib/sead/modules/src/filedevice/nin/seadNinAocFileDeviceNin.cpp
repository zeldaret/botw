#include "filedevice/nin/seadNinAocFileDeviceNin.h"

namespace sead
{
NinAocFileDevice::NinAocFileDevice(const SafeString& mount) : NinFileDeviceBase("aoc", mount) {}
}  // namespace sead
