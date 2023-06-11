#include "KingSystem/Resource/resPlacement.h"
#include "KingSystem/Resource/resEntryFactory.h"
#include "KingSystem/Resource/resSystem.h"

namespace ksys::res {

void Placement::registerFactory(sead::Heap* heap) {
    auto* rm = sead::ResourceMgr::instance();
    if (!rm)
        return;

    if (rm->getDefaultFactory() != rm->findFactory("bplacement"))
        return;

    res::registerEntryFactory(new (heap) EntryFactory<Placement>(1.0, sizeof(Placement)),
                              "bplacement");
}

void Placement::doCreate_(u8* buffer, u32 bufferSize, sead::Heap* heap) {
    mUnknown1 = buffer;
    mUnknown2 = buffer + 0x10;  // Unknown Constant / offset
}

}  // namespace ksys::res
