#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterObj.h>
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"

namespace ksys::res {

class Awareness : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(Awareness, Resource)
public:
    Awareness() : ParamIO("awareness", 0) {}
    ~Awareness() override = default;

    bool needsParse() const override { return true; }
    bool ParamIO_m0(char* data) override { return true; }

private:
    void doCreate_(u8*, u32, sead::Heap*) override {}
    bool parse_(u8* data, size_t size, sead::Heap* heap) override;

    agl::utl::ParameterObj mBasisObj;
    agl::utl::ParameterObj mSightObj;
    agl::utl::ParameterObj mHearingObj;
    agl::utl::ParameterObj mSenseObj;
    agl::utl::ParameterObj mWorryObj;

public:
    agl::utl::Parameter<s32> contactpoint_num;
    agl::utl::Parameter<sead::FixedSafeString<32>> base_node_name;
    agl::utl::Parameter<bool> is_bind_rot;
    agl::utl::Parameter<bool> is_bind_pos;
    agl::utl::Parameter<sead::Vector3f> base_offset;
    agl::utl::Parameter<s32> base_dir;
    agl::utl::Parameter<s32> up_dir;
    agl::utl::Parameter<sead::FixedSafeString<32>> awareness_target;
    agl::utl::Parameter<f32> interest_lv1_radius;
    agl::utl::Parameter<f32> system_radius;
    agl::utl::Parameter<bool> invalidate_wheather_ratio;

    agl::utl::Parameter<s32> sight_buffer_num;
    agl::utl::Parameter<f32> sight_radius;
    agl::utl::Parameter<f32> sight_angle;
    agl::utl::Parameter<f32> sight_height_max;
    agl::utl::Parameter<f32> sight_height_min;
    agl::utl::Parameter<f32> sight_height_near_max;
    agl::utl::Parameter<f32> sight_height_near_min;
    agl::utl::Parameter<f32> sight_alert_radius;
    agl::utl::Parameter<f32> sight_alert_angle;
    agl::utl::Parameter<f32> sight_alert_height_max;
    agl::utl::Parameter<f32> sight_alert_height_min;
    agl::utl::Parameter<f32> sight_alert_height_near_max;
    agl::utl::Parameter<f32> sight_alert_height_near_min;
    agl::utl::Parameter<f32> sight_ignore_grass_radius;
    agl::utl::Parameter<s32> sight_delay_time_max;
    agl::utl::Parameter<f32> sight_ray_check_range_max;
    agl::utl::Parameter<sead::FixedSafeString<32>> sight_base_node_name;
    agl::utl::Parameter<bool> sight_far_use;
    agl::utl::Parameter<f32> sight_radius_far;
    agl::utl::Parameter<f32> sight_angle_far;

    agl::utl::Parameter<s32> hearing_buffer_num;
    agl::utl::Parameter<f32> hearing_radius;
    agl::utl::Parameter<f32> hearing_notice_level;
    agl::utl::Parameter<f32> hearing_alert_level;
    agl::utl::Parameter<f32> hearing_blind_angle;
    agl::utl::Parameter<f32> hearing_blind_margin_angle;
    agl::utl::Parameter<f32> hearing_reduce_ratio;
    agl::utl::Parameter<s32> hearing_delay_time_max;
    agl::utl::Parameter<sead::FixedSafeString<32>> hearing_base_node_name;

    agl::utl::Parameter<s32> sense_buffer_num;
    agl::utl::Parameter<sead::FixedSafeString<32>> sense_target;
    agl::utl::Parameter<f32> sense_radius_offset;
    agl::utl::Parameter<f32> sense_angle;
    agl::utl::Parameter<s32> sense_delay_time_max;
    agl::utl::Parameter<sead::FixedSafeString<32>> sense_base_node_name;

    agl::utl::Parameter<s32> worry_buffer_num;
    agl::utl::Parameter<f32> worry_radius;
    agl::utl::Parameter<s32> worry_delay_time_max;
    agl::utl::Parameter<sead::FixedSafeString<32>> worry_base_node_name;
};

}  // namespace ksys::res
