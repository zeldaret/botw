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
                              "bPlacement");
}

Placement::Placement() {
    mVar1 = 0;
    mVar2 = 0;
}

Placement::~Placement() = default;

}  // namespace ksys::res
