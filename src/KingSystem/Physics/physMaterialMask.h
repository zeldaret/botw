#pragma once

#include <basis/seadTypes.h>
#include <prim/seadEnum.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Utils/BitField.h"

namespace ksys::phys {

union MaterialMaskData {
    // FIXME: incomplete
    SEAD_ENUM(CustomFlag, _0)

    constexpr explicit MaterialMaskData(u32 raw_ = 0) : raw(raw_) {}
    constexpr MaterialMaskData(const MaterialMaskData&) = default;
    constexpr MaterialMaskData& operator=(const MaterialMaskData& other) {
        raw = other.raw;
        return *this;
    }

    static constexpr bool isValidSubMaterialIdx(int idx) {
        return u32(idx) < (1 << decltype(sub_material)::NumBits());
    }

    Material getMaterial() const { return int(material.Value()); }
    int getSubMaterialIndex() const { return int(sub_material.Value()); }
    FloorCode getFloorCode() const { return int(floor.Value()); }
    WallCode getWallCode() const { return int(wall.Value()); }

    void setFlag31(bool b) {
        if (!b)
            clearFlag31();
        else
            setFlag31();
    }
    void setFlag31() { flag31 = 1; }
    void clearFlag31() { flag31 = 0; }

    void setCustomFlag(CustomFlag custom_flag) {
        raw |= 1 << (decltype(custom_flags)::StartBit() + custom_flag);
    }

    u32 raw;
    util::BitField<0, 6, u32> material;
    util::BitField<6, 4, int, u32> sub_material;
    util::BitField<10, 5, u32> floor;
    util::BitField<15, 5, u32> wall;
    // TODO: rename once we figure out what these flags are
    util::BitField<23, 7, u32> custom_flags;
    util::BitField<30, 1, u32> flag30;
    util::BitField<31, 1, u32> flag31;
};
static_assert(sizeof(MaterialMaskData) == sizeof(u32));

class MaterialMask {
public:
    MaterialMask();
    explicit MaterialMask(u32 data);
    explicit MaterialMask(u64 havok_user_data) : MaterialMask(static_cast<u32>(havok_user_data)) {}
    MaterialMask(Material mat, FloorCode floor, WallCode wall, bool flag = false);
    MaterialMask(Material mat, const char* submat_name, FloorCode floor, WallCode wall,
                 bool flag = false);
    MaterialMask(Material mat, int submat_idx, FloorCode floor, WallCode wall, bool flag = false);
    MaterialMask(const MaterialMask& other) : mData(other.mData) {}

    // XXX: this doesn't need to be virtual.
    virtual ~MaterialMask();

    MaterialMask& operator=(const MaterialMask& other) {
        set(other.mData);
        return *this;
    }

    MaterialMask& operator=(MaterialMaskData data) {
        set(data);
        return *this;
    }

    MaterialMaskData& getData() { return mData; }
    const MaterialMaskData& getData() const { return mData; }
    u32 getRawData() const { return mData.raw; }

    Material getMaterial() const { return mData.getMaterial(); }
    int getSubMaterialIdx() const { return mData.getSubMaterialIndex(); }
    FloorCode getFloorCode() const { return mData.getFloorCode(); }
    WallCode getWallCode() const { return mData.getWallCode(); }

    const char* getMaterialName() const;
    const char* getSubMaterialName() const;

    void set(MaterialMaskData data) {
        mData = data;
        mSubMaterialNameCache = nullptr;
    }

    void set(u32 data) { set(MaterialMaskData{data}); }
    void reset() { set(0); }

    void setMaterial(Material mat);

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
