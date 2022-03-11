#include "KingSystem/Physics/physMaterialMask.h"
#include "KingSystem/Physics/System/physMaterialTable.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace ksys::phys {

MaterialMask::MaterialMask() = default;

MaterialMask::MaterialMask(u32 data) : mData(data) {}

MaterialMask::MaterialMask(Material mat, FloorCode floor, WallCode wall, bool flag) {
    mData.material.Init(mat);
    mData.floor.Init(floor);
    mData.wall.Init(wall);
    mData.setFlag31(flag);
}

MaterialMask::MaterialMask(Material mat, const char* submat_name, FloorCode floor, WallCode wall,
                           bool flag)
    : mSubMaterialNameCache(submat_name) {
    auto submat_idx = getSubMaterialIdx(mat, submat_name);
    if (!MaterialMaskData::isValidSubMaterialIdx(submat_idx))
        submat_idx = 0;
    mData.raw = {};
    mData.material.Init(mat);
    mData.sub_material.Init(submat_idx);
    mData.floor.Init(floor);
    mData.wall.Init(wall);
    mData.setFlag31(flag);
}

MaterialMask::MaterialMask(Material mat, int submat_idx, FloorCode floor, WallCode wall, bool flag)
    : mSubMaterialNameCache(getSubMaterialName(mat, submat_idx).cstr()) {
    mData.raw = {};
    mData.material.Init(mat);
    mData.sub_material.Init(submat_idx);
    mData.floor.Init(floor);
    mData.wall.Init(wall);
    mData.setFlag31(flag);
}

MaterialMask::~MaterialMask() = default;

const char* MaterialMask::getMaterialName() const {
    const Material material = getMaterial();
    if (isInvalidMaterial(material.value()))
        return "Incorrent";  // sic
    return materialToText(material);
}

const char* MaterialMask::getSubMaterialName() const {
    if (mSubMaterialNameCache != nullptr)
        return mSubMaterialNameCache;

    mSubMaterialNameCache = getSubMaterialName(getMaterial(), getSubMaterialIdx()).cstr();
    return mSubMaterialNameCache;
}

int MaterialMask::getSubMaterialIdx(Material mat, const sead::SafeString& submat_name) {
    return System::instance()->getMaterialTable()->getSubMaterialIdx(mat, submat_name);
}

const sead::SafeString& MaterialMask::getSubMaterialName(Material mat, int submat_idx) {
    return System::instance()->getMaterialTable()->getSubMaterial(mat, submat_idx);
}

int MaterialMask::getNumSubMaterials(Material mat) {
    return System::instance()->getMaterialTable()->getNumSubMaterials(mat);
}

const sead::SafeString& MaterialMask::getSubMaterialName(int mat, int submat_idx) {
    return getSubMaterialName(Material(mat), submat_idx);
}

void MaterialMask::setMaterial(Material mat) {
    mData.material = {};
    mData.material.SetUnsafe(mat);
}

}  // namespace ksys::phys
