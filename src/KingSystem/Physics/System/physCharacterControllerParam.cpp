#include "KingSystem/Physics/System/physCharacterControllerParam.h"
#include "KingSystem/Physics/System/physShapeParam.h"

namespace ksys::phys {

bool navMeshCharacterTypeFromText(NavMeshCharacterType& value, const sead::SafeString& text) {
    for (auto type : NavMeshCharacterType()) {
        if (sead::SafeString(type.text()) == text) {
            value = type;
            return true;
        }
    }
    return false;
}

CharacterControllerParam::CharacterControllerParam()
    : mass(100.0, "mass", &obj), volume(1.0, "volume", &obj), max_force(20.0, "max_force", &obj),
      form_num(0, "form_num", &obj), layer({"EntityNPC"}, "layer", &obj),
      groundhit({"HitAll"}, "groundhit", &obj), initial_state({"Default"}, "initial_state", &obj),
      initial_form({"Standing"}, "initial_form", &obj), max_impulse(-1.0, "max_impulse", &obj),
      contact_point_info(sead::SafeString::cEmptyString, "contact_point_info", &obj),
      collision_info(sead::SafeString::cEmptyString, "collision_info", &obj),
      use_nav_mesh_character(false, "use_nav_mesh_character", &obj),
      nav_mesh_character_radius(0.0, "nav_mesh_character_radius", &obj),
      nav_mesh_character_height(0.0, "nav_mesh_character_height", &obj),
      nav_mesh_character_avoidance_priority(0, "nav_mesh_character_avoidance_priority", &obj),
      nav_mesh_character_max_speed(0.0, "nav_mesh_character_max_speed", &obj),
      nav_mesh_character_max_acceleration(0.0, "nav_mesh_character_max_acceleration", &obj),
      nav_mesh_character_max_angular_velocity(0.0, "nav_mesh_character_max_angular_velocity", &obj),
      nav_mesh_character_type(sead::SafeString::cEmptyString, "nav_mesh_character_type", &obj),
      enable_water_effect(false, "enable_water_effect", &obj),
      enable_force_fall_cliff_edge(false, "enable_force_fall_cliff_edge", &obj),
      water_effective_height(1.0, "water_effective_height", &obj),
      water_flow_effective_rate(0.0, "water_flow_effective_rate", &obj),
      water_attn_effective_rate(0.0, "water_attn_effective_rate", &obj),
      max_force_scale_NPC(100.0, "max_force_scale_NPC", &obj),
      water_buoyancy_scale(1.0, "water_buoyancy_scale", &obj),
      magne_mass_scaling_factor(1.0, "magne_mass_scaling_factor", &obj),
      height_enable_hitting_wall(0.1, "height_enable_hitting_wall", &obj) {}

CharacterControllerParam::~CharacterControllerParam() {
    forms.freeBuffer();
}

bool CharacterControllerParam::parse(agl::utl::ResParameterList res_list, sead::Heap* heap) {
    if (!res_list || res_list.getResParameterObjNum() < 1)
        return false;

    obj.applyResParameterObj(res_list.getResParameterObj(0));

    const int num_forms = *form_num;
    if (num_forms < 0)
        return false;

    if (num_forms == 0)
        return true;

    forms.allocBufferAssert(num_forms, heap);
    for (int i = 0; i < num_forms; ++i) {
        if (!forms[i].parse(res_list.getResParameterList(i), heap))
            return false;

        addList(&forms[i], sead::FormatFixedSafeString<32>("Form_%d", i));
    }

    return true;
}

void* CharacterControllerParam::createForm(int form_idx, sead::Heap* heap) {
    if (form_idx >= getNumForms() || form_idx < 0)
        return nullptr;
    return forms[form_idx].createForm(heap);
}

CharacterControllerParam::Form::Form()
    : shape_num(0, "shape_num", &form_header_obj),
      form_type(sead::SafeString::cEmptyString, "form_type", &form_header_obj) {
    addObj(&form_header_obj, "FormHeader");
}

CharacterControllerParam::Form::~Form() {
    shape_params.freeBuffer();
}

bool CharacterControllerParam::Form::parse(agl::utl::ResParameterList res_list, sead::Heap* heap) {
    if (!res_list || res_list.getResParameterObjNum() < 2)
        return false;

    form_header_obj.applyResParameterObj(res_list.getResParameterObj(0));

    const int num_shapes = *shape_num;
    if (num_shapes < 1)
        return true;

    shape_params.allocBufferAssert(num_shapes, heap);
    for (int i = 0; i < num_shapes; ++i) {
        if (!shape_params[i].parse(res_list.getResParameterObj(i + 1), heap))
            return false;
        addObj(&shape_params[i], sead::FormatFixedSafeString<32>("ShapeParam_%d", i));
    }

    return true;
}

int CharacterControllerParam::findFormIdx(const sead::SafeString& form_type) const {
    for (int i = 0, n = forms.size(); i < n; ++i) {
        if (form_type == *forms[i].form_type)
            return i;
    }
    return -1;
}

}  // namespace ksys::phys
