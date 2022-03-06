#pragma once

#include <container/seadSafeArray.h>
#include <prim/seadBitFlag.h>
#include "KingSystem/Physics/physDefines.h"

namespace ksys::phys {

class LayerMaskBuilder {
public:
    struct Masks {
        sead::BitFlag32 layers;
        // TODO: rename
        sead::BitFlag32 layers2;
    };

    LayerMaskBuilder() = default;
    // XXX: this doesn't need to be virtual...
    virtual ~LayerMaskBuilder() = default;

    LayerMaskBuilder& addLayer(ContactLayer layer);
    LayerMaskBuilder& removeLayer(ContactLayer layer);
    bool hasLayer(ContactLayer layer) const;

    // TODO: rename
    LayerMaskBuilder& addLayer2(ContactLayer layer);
    LayerMaskBuilder& removeLayer2(ContactLayer layer);
    bool hasLayer2(ContactLayer layer) const;

    const auto& getMasks() const { return mMasks; }

private:
    sead::SafeArray<Masks, NumContactLayerTypes> mMasks;
};

inline LayerMaskBuilder& LayerMaskBuilder::addLayer(ContactLayer layer) {
    mMasks[int(getContactLayerType(layer))].layers.set(makeContactLayerMask(layer));
    return *this;
}

inline LayerMaskBuilder& LayerMaskBuilder::removeLayer(ContactLayer layer) {
    mMasks[int(getContactLayerType(layer))].layers.reset(makeContactLayerMask(layer));
    return *this;
}

inline bool LayerMaskBuilder::hasLayer(ContactLayer layer) const {
    return (mMasks[int(getContactLayerType(layer))].layers & makeContactLayerMask(layer)) != 0;
}

inline LayerMaskBuilder& LayerMaskBuilder::addLayer2(ContactLayer layer) {
    mMasks[int(getContactLayerType(layer))].layers2.set(makeContactLayerMask(layer));
    return *this;
}

inline LayerMaskBuilder& LayerMaskBuilder::removeLayer2(ContactLayer layer) {
    mMasks[int(getContactLayerType(layer))].layers2.reset(makeContactLayerMask(layer));
    return *this;
}

inline bool LayerMaskBuilder::hasLayer2(ContactLayer layer) const {
    return (mMasks[int(getContactLayerType(layer))].layers2 & makeContactLayerMask(layer)) != 0;
}

}  // namespace ksys::phys
