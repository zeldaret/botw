#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterList.h>
#include <agl/Utils/aglParameterObj.h>
#include <container/seadBuffer.h>
#include <prim/seadSafeString.h>

namespace ksys::phys {

struct ClothSubWindParam : agl::utl::ParameterObj {
    ClothSubWindParam();

    agl::utl::Parameter<sead::Vector3f> sub_wind_direction;
    agl::utl::Parameter<float> sub_wind_frequency;
    agl::utl::Parameter<float> sub_wind_speed;
};

struct ClothParam : agl::utl::ParameterObj {
    ClothParam();

    agl::utl::Parameter<float> wind_drag;
    agl::utl::Parameter<float> wind_frequency;
    agl::utl::Parameter<float> wind_min_speed;
    agl::utl::Parameter<float> wind_max_speed;
    agl::utl::Parameter<float> sub_wind_factor_main;
    agl::utl::Parameter<float> sub_wind_factor_add;
    agl::utl::Parameter<bool> wind_enable;
    agl::utl::Parameter<bool> writeback_to_local;
    agl::utl::Parameter<sead::SafeString> name;
    agl::utl::Parameter<sead::SafeString> base_bone;
};

struct ClothSetParam : agl::utl::ParameterList {
    ClothSetParam();
    ~ClothSetParam() override;
    ClothSetParam(const ClothSetParam&) = delete;
    auto operator=(const ClothSetParam&) = delete;

    bool parse(const agl::utl::ResParameterList& res_list, sead::Heap* heap);
    const ClothParam* getCloth(const sead::SafeString& name) const;

    agl::utl::ParameterObj cloth_header_obj;
    agl::utl::Parameter<sead::SafeString> cloth_setup_file_path;
    agl::utl::Parameter<int> cloth_num;
    sead::FixedSafeString<64> cloth_setup_file_name;
    ClothSubWindParam sub_wind;
    sead::Buffer<ClothParam> cloths;
};

}  // namespace ksys::phys
