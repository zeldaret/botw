#include "KingSystem/Resource/resResourceArchive.h"

namespace ksys::res {

Archive::Archive() = default;

Archive::~Archive() = default;

void Archive::doCreate_(u8* data, u32 size, sead::Heap* heap) {
    sead::ArchiveRes::doCreate_(data + mDataOffset, size, heap);
}

}  // namespace ksys::res
