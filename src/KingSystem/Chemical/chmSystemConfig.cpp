#include "KingSystem/Chemical/chmSystemConfig.h"

namespace ksys::chm {

SEAD_SINGLETON_DISPOSER_IMPL(SystemConfig)

SystemConfig::~SystemConfig() {
    mMaterials.freeBuffer();
    mWorlds.freeBuffer();
}

void SystemConfig::init(sead::Heap* heap) {
    mMaterials.allocBufferAssert(128, heap);
    mElements.allocBufferAssert(128, heap);
    mWorlds.allocBufferAssert(8, heap);

    addList(&mWorldList, "world");
    addList(&mMaterialList, "material");
    addList(&mElementList, "element");

    for (auto it = mWorlds.begin(), end = mWorlds.end(); it != end; ++it)
        mWorldList.addObj(&*it, sead::FormatFixedSafeString<1024>("%d", it.getIndex()));
    for (auto it = mMaterials.begin(), end = mMaterials.end(); it != end; ++it)
        mMaterialList.addObj(&*it, sead::FormatFixedSafeString<1024>("%d", it.getIndex()));
    for (auto it = mElements.begin(), end = mElements.end(); it != end; ++it)
        mElementList.addObj(&*it, sead::FormatFixedSafeString<1024>("%d", it.getIndex()));
}

const SystemConfig::World& SystemConfig::getWorld(const sead::SafeString& name) const {
    for (auto it = mWorlds.begin(), end = mWorlds.end(); it != end; ++it) {
        if (name == it->id.ref())
            return *it;
    }
    return mDummyWorld;
}

const SystemConfig::Material& SystemConfig::getMaterial(const sead::SafeString& name) const {
    for (auto it = mMaterials.begin(), end = mMaterials.end(); it != end; ++it) {
        if (name == it->id.ref())
            return *it;
    }
    return mDummyMaterial;
}

const SystemConfig::Element& SystemConfig::getElement(const sead::SafeString& name) const {
    for (auto it = mElements.begin(), end = mElements.end(); it != end; ++it) {
        if (name == it->name.ref())
            return *it;
    }
    return mDummyElement;
}

}  // namespace ksys::chm
