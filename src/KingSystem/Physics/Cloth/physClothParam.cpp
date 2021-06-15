#include "KingSystem/Physics/Cloth/physClothParam.h"
#include <filedevice/seadPath.h>

namespace ksys::phys {

ClothSetParam::ClothSetParam()
    : cloth_setup_file_path(sead::SafeString::cEmptyString, "cloth_setup_file_path",
                            "Clothセットアップファイル(.hkt)", &cloth_header_obj),
      cloth_num(0, "cloth_num", "cloth_num", &cloth_header_obj) {
    addObj(&cloth_header_obj, "ClothHeader");
    addObj(&sub_wind, "ClothSubWind");
}

ClothSetParam::~ClothSetParam() = default;

bool ClothSetParam::parse(const agl::utl::ResParameterList& res_list, sead::Heap* heap) {
    if (!res_list)
        return false;

    cloth_header_obj.applyResParameterObj(res_list.getResParameterObj(0));

    const int num_cloths = cloth_num.ref();
    if (num_cloths <= 0)
        return false;

    cloths.allocBufferAssert(num_cloths, heap);
    for (int i = 0; i < num_cloths; ++i) {
        addObj(&cloths[i], sead::FormatFixedSafeString<32>("Cloth_%d", i));
    }

    sead::Path::getFileName(&cloth_setup_file_name, cloth_setup_file_path.ref());

    return true;
}

const ClothParam* ClothSetParam::getCloth(const sead::SafeString& name) const {
    int index = -1;
    for (int i = 0, n = *cloth_num; i < n; ++i) {
        if (name == *cloths[i].name) {
            index = i;
            break;
        }
    }
    return index >= 0 && index < *cloth_num ? &cloths[index] : nullptr;
}

ClothParam::ClothParam()
    : wind_drag(5.0, "wind_drag", this), wind_frequency(5.0, "wind_frequency", this),
      wind_min_speed(-4.0, "wind_mind_speed", this), wind_max_speed(10.0, "wind_max_speed", this),
      sub_wind_factor_main(1.0, "sub_wind_factor_main", this),
      sub_wind_factor_add(0.0, "sub_wind_factor_add", this), wind_enable(true, "wind_enable", this),
      writeback_to_local(false, "writeback_to_local", this),
      name(sead::SafeString::cEmptyString, "name", this), base_bone("Root", "base_bone", this) {}

ClothSubWindParam::ClothSubWindParam()
    : sub_wind_direction(sead::Vector3f::ey, "sub_wind_direction", this),
      sub_wind_frequency(0.2, "sub_wind_frequency", this),
      sub_wind_speed(0.0, "sub_wind_speed", this) {}

}  // namespace ksys::phys
