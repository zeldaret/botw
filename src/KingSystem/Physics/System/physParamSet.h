#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterList.h>
#include <agl/Utils/aglParameterObj.h>
#include <container/seadBuffer.h>

namespace ksys::res {
class Physics;
}

namespace ksys::phys {

struct RigidBodySetParam;
struct CharacterControllerParam;
struct ClothSetParam;
struct RagdollParam;
struct SupportBoneParam;
struct ContactInfoParam;
struct EdgeRigidBodySetParam;

struct ParamSet : public agl::utl::ParameterList {
    ParamSet();
    ~ParamSet() override;
    ParamSet(const ParamSet&) = delete;
    auto operator=(const ParamSet&) = delete;

    bool parse(res::Physics* bphysics, agl::utl::ResParameterArchive archive, sead::Heap* heap);

    RigidBodySetParam& getRigidBodySet(int idx);

    sead::Buffer<RigidBodySetParam> rigid_body_sets{};
    CharacterControllerParam* character_controller{};
    ClothSetParam* cloth_set{};
    RagdollParam* ragdoll{};
    SupportBoneParam* support_bone{};
    ContactInfoParam* contact_info{};
    EdgeRigidBodySetParam* edge_rigid_body_set{};

    agl::utl::ParameterObj obj;
    agl::utl::Parameter<int> use_rigid_body_set_num;
    agl::utl::Parameter<bool> use_character_controller;
    agl::utl::Parameter<bool> use_ragdoll;
    agl::utl::Parameter<bool> use_support_bone;
    agl::utl::Parameter<bool> use_cloth;
    agl::utl::Parameter<bool> use_contact_info;
    agl::utl::Parameter<bool> use_system_group_handler;
    agl::utl::Parameter<int> use_edge_rigid_body_num;
    int num_rigid_bodies_with_link_matrix = 0;

private:
    void finalize();
    bool doParse(res::Physics* bphysics, agl::utl::ResParameterArchive archive, sead::Heap* heap);
};

}  // namespace ksys::phys
