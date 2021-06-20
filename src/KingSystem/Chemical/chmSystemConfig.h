#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterIO.h>
#include <agl/Utils/aglParameterList.h>
#include <agl/Utils/aglParameterObj.h>
#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>

namespace ksys::chm {

class SystemConfig : public agl::utl::IParameterIO, public sead::hostio::Node {
    SEAD_SINGLETON_DISPOSER(SystemConfig)
    SystemConfig() : agl::utl::IParameterIO("chmres", 0) {}
    ~SystemConfig() override;

public:
    struct Element : agl::utl::IParameterObj, sead::hostio::Node {
        Element();
        ~Element() override;

        agl::utl::Parameter<sead::FixedSafeString<64>> name;
        agl::utl::Parameter<sead::FixedSafeString<256>> label;
        agl::utl::Parameter<int> effect_type;
        agl::utl::Parameter<u32> attribute;
        agl::utl::Parameter<float> life_frames;
        agl::utl::Parameter<float> temperature;
        agl::utl::Parameter<int> type;
        agl::utl::Parameter<float> wetting_rate;
        agl::utl::Parameter<float> wind_speed;
        agl::utl::Parameter<float> electric_charge;
        agl::utl::Parameter<float> shock_wave_speed;
        agl::utl::Parameter<int> fire_level;
        agl::utl::Parameter<float> moisture;
    };

    struct Material : agl::utl::IParameterObj, sead::hostio::Node {
        Material();
        ~Material() override;

        agl::utl::Parameter<sead::FixedSafeString<64>> id;
        agl::utl::Parameter<sead::FixedSafeString<256>> label;
        agl::utl::Parameter<u32> attribute;
        agl::utl::Parameter<float> heat_capacity;
        agl::utl::Parameter<float> thermal_conductivity;
        agl::utl::Parameter<float> electrical_resistivity;
        agl::utl::Parameter<float> electrical_capacitance;
        agl::utl::Parameter<float> electromotive_force;
        agl::utl::Parameter<int> fire_proof_level;
        agl::utl::Parameter<float> ignition_point;
        agl::utl::Parameter<float> burn_speed;
        agl::utl::Parameter<float> wetting_amount;
        agl::utl::Parameter<float> wind_force_remain_rate;
        agl::utl::Parameter<sead::FixedSafeString<64>> burn_res_element_name;
        agl::utl::Parameter<sead::FixedSafeString<64>> warm_res_element_name;
        agl::utl::Parameter<sead::FixedSafeString<64>> exp_res_element_name;
        agl::utl::Parameter<sead::FixedSafeString<64>> exp_res_element_name1;
        agl::utl::Parameter<sead::FixedSafeString<64>> electricity_res_element_name;
        agl::utl::Parameter<sead::FixedSafeString<64>> ice_magic_res_element_name;
        agl::utl::Parameter<sead::FixedSafeString<64>> water_res_element_name;
    };

    struct World : agl::utl::IParameterObj, sead::hostio::Node {
        World();
        ~World() override;

        agl::utl::Parameter<sead::FixedSafeString<64>> id;
        agl::utl::Parameter<sead::FixedSafeString<256>> label;
        agl::utl::Parameter<float> evaporation_speed_rate;
        agl::utl::Parameter<float> heat_transfer_speed_rate;
        agl::utl::Parameter<float> fire_heat_transfer_speed_rate;
        agl::utl::Parameter<float> conduction_speed_rate_log;
        agl::utl::Parameter<float> burn_speed_rate;
        agl::utl::Parameter<float> fire_extra_radius;
        agl::utl::Parameter<float> player_fire_margin;
        agl::utl::Parameter<float> electricity_extra_radius_rate;
        agl::utl::Parameter<float> electric_water_extra_radius_rate;
        agl::utl::Parameter<float> min_ice_size;
        agl::utl::Parameter<float> ice_heat_cheat_threshold;
        agl::utl::Parameter<float> ice_heat_cheat_rate;
        agl::utl::Parameter<float> ice_melt_ratio_env_temp;
        agl::utl::Parameter<float> ice_melt_ratio_warm_air;
        agl::utl::Parameter<float> ice_melt_ratio_fire;
        agl::utl::Parameter<float> ice_melt_ratio_fire2;
        agl::utl::Parameter<float> wind_lift_rate;
        agl::utl::Parameter<float> lightning_distance;
        agl::utl::Parameter<float> character_ignition_count;
        agl::utl::Parameter<float> object_ignition_count;
        agl::utl::Parameter<float> offensive_rigid_radius;
    };

    struct List : agl::utl::IParameterList, sead::hostio::Node {
        ~List() override { ; }
    };

    void init(sead::Heap* heap);

    const World& getWorld(const sead::SafeString& name) const;
    const Material& getMaterial(const sead::SafeString& name) const;
    const Element& getElement(const sead::SafeString& name) const;

private:
    sead::Buffer<Material> mMaterials;
    sead::Buffer<Element> mElements;
    sead::Buffer<World> mWorlds;
    Material mDummyMaterial;
    Element mDummyElement;
    World mDummyWorld;
    List mWorldList;
    List mMaterialList;
    List mElementList;
};

}  // namespace ksys::chm
