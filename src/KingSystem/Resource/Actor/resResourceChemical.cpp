#include "KingSystem/Resource/Actor/resResourceChemical.h"

namespace ksys::res {

Chemical::Chemical() : ParamIO("chemical", 0) {
    addList(&mRoot, "chemical_root");
}

void Chemical::doCreate_(u8* buffer, u32 buffer_size, sead::Heap* heap) {}

bool Chemical::parse_(u8* data, size_t size, sead::Heap* heap) {
    if (!data)
        return true;

    agl::utl::ResParameterArchive archive{data};

    const auto chemical_root_list =
        agl::utl::getResParameterList(archive.getRootList(), "chemical_root");
    mRoot.parse(chemical_root_list, heap);

    return true;
}

}  // namespace ksys::res
