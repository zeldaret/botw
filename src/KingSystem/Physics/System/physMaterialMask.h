#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Physics/System/physDefines.h"
#include "KingSystem/Utils/BitField.h"

namespace ksys::phys {

union MaterialMaskData {
    constexpr explicit MaterialMaskData(u32 raw_ = 0) : raw(raw_) {}
    constexpr MaterialMaskData(const MaterialMaskData&) = default;
    constexpr MaterialMaskData& operator=(const MaterialMaskData& other) {
        raw = other.raw;
        return *this;
    }

    static constexpr bool isValidSubMaterialIdx(int idx) {
        return u32(idx) < (1 << decltype(sub_material)::NumBits());
    }

    void setFlag(bool b) {
        if (!b)
            clearFlag();
        else
            setFlag();
    }
    void setFlag() { flag = 1; }
    void clearFlag() { flag = 0; }

    u32 raw;
    util::BitField<0, 6, u32> material;
    util::BitField<6, 4, int, u32> sub_material;
    util::BitField<10, 5, u32> floor;
    util::BitField<15, 5, u32> wall;
    // TODO: rename
    util::BitField<23, 1, u32> flag_23;
    // TODO: rename once we figure out what this flag is
    util::BitField<31, 1, u32> flag;
};
static_assert(sizeof(MaterialMaskData) == sizeof(u32));

class MaterialMask {
public:
    MaterialMask();
    explicit MaterialMask(MaterialMaskData data);
    MaterialMask(Material mat, FloorCode floor, WallCode wall, bool flag);
    MaterialMask(Material mat, const char* submat_name, FloorCode floor, WallCode wall, bool flag);
    MaterialMask(Material mat, int submat_idx, FloorCode floor, WallCode wall, bool flag);
    MaterialMask(const MaterialMask& other) : mData(other.mData) {}

    // XXX: this doesn't need to be virtual.
    virtual ~MaterialMask();

    MaterialMask& operator=(const MaterialMask& other) {
        mData = other.mData;
        mSubMaterialNameCache = nullptr;
        return *this;
    }

    MaterialMaskData& getData() { return mData; }
    const MaterialMaskData& getData() const { return mData; }
    u32 getRawData() const { return mData.raw; }
    Material getMaterial() const { return Material::ValueType(mData.material.Value()); }
    int getSubMaterialIdx() const { return mData.sub_material; }

    const char* getMaterialName() const;
    const char* getSubMaterialName() const;

    void setMaterial(Material mat);
    void clearSubMaterialNameCache() { mSubMaterialNameCache = nullptr; }

    static int getSubMaterialIdx(Material mat, const sead::SafeString& submat_name);
    static const sead::SafeString& getSubMaterialName(Material mat, int submat_idx);
    static int getNumSubMaterials(Material mat);
    static const sead::SafeString& getSubMaterialName(int mat, int submat_idx);

private:
    MaterialMaskData mData{};
    /// Fetching the name of a sub-material from the MaterialTable is an expensive operation,
    /// so it is only done once and the result is cached.
    mutable const char* mSubMaterialNameCache{};
};

}  // namespace ksys::phys
