#include "agl/Utils/aglParameterStringMgr.h"

namespace agl::utl {

SEAD_SINGLETON_DISPOSER_IMPL(ParameterStringMgr)

ParameterStringMgr::ParameterStringMgr() {
#ifdef SEAD_DEBUG
    setNodeName("utl::ParameterStringMgr");
    setNodeMeta("Icon=NOTE");
#endif
}

ParameterStringMgr::~ParameterStringMgr() {
    mStrings.freeBuffer();
}

void ParameterStringMgr::initialize(sead::Heap* heap) {
    mHeap = heap;
    if (heap) {
        mStrings.allocBuffer(0x20000, heap);
        mStrings.clear();
    }
}

}  // namespace agl::utl
