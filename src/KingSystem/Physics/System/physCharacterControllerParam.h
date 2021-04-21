#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterList.h>
#include <agl/Utils/aglParameterObj.h>
#include <container/seadBuffer.h>
#include <prim/seadEnum.h>

namespace ksys::phys {

struct ShapeParam;

SEAD_ENUM(NavMeshCharacterType,
Player,
Horse,
Enemy,
Guardian,
NPC,
NPCGoron,
NPCSwimmer,
NPCGerudoPassable,
Fish,
Animal,
SmallAnimal,
DomesticAnimal,
PoorSwimmer,
GoodSwimmer,
IceSwimmer,
FireEnemy,
WolfLink,
GiantEnemy,
GiantSwimmer,
TallEnemy,
Lynel)

bool navMeshCharacterTypeFromText(NavMeshCharacterType& value, const sead::SafeString& text);

struct ICharacterControllerParam {
    virtual int getNumForms() = 0;
    // TODO: return type
    virtual void* createForm(int form_idx, sead::Heap* heap) = 0;
};

struct CharacterControllerParam : agl::utl::ParameterList, ICharacterControllerParam {
    struct Form : agl::utl::ParameterList {
        Form();
        ~Form() override;
        Form(const Form&) = delete;
        auto operator=(const Form&) = delete;

        bool parse(agl::utl::ResParameterList res_list, sead::Heap* heap);

        // TODO: return type
        void* createForm(sead::Heap* heap);

        agl::utl::ParameterObj form_header_obj;
        agl::utl::Parameter<int> shape_num;
        agl::utl::Parameter<sead::FixedSafeString<32>> form_type;
        sead::Buffer<ShapeParam> shape_params;
    };

    CharacterControllerParam();
    ~CharacterControllerParam() override;
    CharacterControllerParam(const CharacterControllerParam&) = delete;
    auto operator=(const CharacterControllerParam&) = delete;

    int getNumForms() override { return forms.size(); }
    void* createForm(int form_idx, sead::Heap* heap) override;

    // TODO: return type
    void* createController(sead::Heap* heap);
    // TODO: types
    void* createControllerState(const sead::SafeString& name, void* ctrl, void* x, bool y,
                                sead::Heap* heap);
    // TODO: return type
    void* createNavMeshCharacter(const sead::SafeString& name, sead::Heap* heap,
                                 const sead::Vector3f& scale);

    int findFormIdx(const sead::SafeString& form_type) const;
    bool parse(agl::utl::ResParameterList res_list, sead::Heap* heap);

    agl::utl::ParameterObj obj;
    agl::utl::Parameter<float> mass;
    agl::utl::Parameter<float> volume;
    agl::utl::Parameter<float> max_force;
    agl::utl::Parameter<int> form_num;
    agl::utl::Parameter<sead::FixedSafeString<32>> layer;
    agl::utl::Parameter<sead::FixedSafeString<32>> groundhit;
    agl::utl::Parameter<sead::FixedSafeString<32>> initial_state;
    agl::utl::Parameter<sead::FixedSafeString<32>> initial_form;
    agl::utl::Parameter<float> max_impulse;
    agl::utl::Parameter<sead::FixedSafeString<32>> contact_point_info;
    agl::utl::Parameter<sead::FixedSafeString<32>> collision_info;
    agl::utl::Parameter<bool> use_nav_mesh_character;
    agl::utl::Parameter<float> nav_mesh_character_radius;
    agl::utl::Parameter<float> nav_mesh_character_height;
    agl::utl::Parameter<u32> nav_mesh_character_avoidance_priority;
    agl::utl::Parameter<float> nav_mesh_character_max_speed;
    agl::utl::Parameter<float> nav_mesh_character_max_acceleration;
    agl::utl::Parameter<float> nav_mesh_character_max_angular_velocity;
    agl::utl::Parameter<sead::SafeString> nav_mesh_character_type;
    agl::utl::Parameter<bool> enable_water_effect;
    agl::utl::Parameter<bool> enable_force_fall_cliff_edge;
    agl::utl::Parameter<float> water_effective_height;
    agl::utl::Parameter<float> water_flow_effective_rate;
    agl::utl::Parameter<float> water_attn_effective_rate;
    agl::utl::Parameter<float> max_force_scale_NPC;
    agl::utl::Parameter<float> water_buoyancy_scale;
    agl::utl::Parameter<float> magne_mass_scaling_factor;
    agl::utl::Parameter<float> height_enable_hitting_wall;
    sead::Buffer<Form> forms;
};

}  // namespace ksys::phys
