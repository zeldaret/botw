#include <resource/seadArchiveRes.h>

namespace sead
{
s32 ArchiveRes::getLoadDataAlignment() const
{
    return 0x80;
}

void ArchiveRes::doCreate_(u8* buf, u32, Heap*)
{
    mEnable = prepareArchive_(buf);
}

bool ArchiveRes::isExistFileImpl_(const SafeString& path) const
{
    return convertPathToEntryIDImpl_(path) != -1;
}
}  // namespace sead
