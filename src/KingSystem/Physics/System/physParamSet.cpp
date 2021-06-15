#include "KingSystem/Physics/System/physParamSet.h"
#include "KingSystem/Physics/Cloth/physClothParam.h"
#include "KingSystem/Physics/Ragdoll/physRagdollParam.h"
#include "KingSystem/Physics/RigidBody/physEdgeRigidBodyParam.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySetParam.h"
#include "KingSystem/Physics/SupportBone/physSupportBoneParam.h"
#include "KingSystem/Physics/System/physCharacterControllerParam.h"
#include "KingSystem/Physics/System/physContactInfoParam.h"
#include "KingSystem/Resource/Actor/resResourcePhysics.h"

namespace ksys::phys {

ParamSet::ParamSet()
    : use_rigid_body_set_num(0, "use_rigid_body_set_num", &obj),
      use_character_controller(false, "use_character_controller", &obj),
      use_ragdoll(false, "use_ragdoll", &obj), use_support_bone(false, "use_support_bone", &obj),
      use_cloth(false, "use_cloth", &obj), use_contact_info(false, "use_contact_info", &obj),
      use_system_group_handler(true, "use_system_group_handler", &obj),
      use_edge_rigid_body_num(false, "use_edge_rigid_body_num", &obj) {}

ParamSet::~ParamSet() {
    finalize();
}

bool ParamSet::parse(res::Physics* bphysics, agl::utl::ResParameterArchive archive,
                     sead::Heap* heap) {
    if (!archive.isValid())
        return false;

    if (!doParse(bphysics, archive, heap)) {
        finalize();
        return false;
    }

    return true;
}

template <typename T>
static void safeDelete(T*& ptr) {
    if (!ptr)
        return;
    delete ptr;
    ptr = nullptr;
}

void ParamSet::finalize() {
    rigid_body_sets.freeBuffer();
    safeDelete(character_controller);
    safeDelete(contact_info);
    safeDelete(cloth_set);
    safeDelete(ragdoll);
    safeDelete(support_bone);
    safeDelete(edge_rigid_body_set);
    *use_rigid_body_set_num = 0;
    *use_ragdoll = false;
    *use_cloth = false;
    *use_support_bone = false;
    *use_edge_rigid_body_num = 0;
}

bool ParamSet::doParse(res::Physics* bphysics, agl::utl::ResParameterArchive archive,
                       sead::Heap* heap) {
    const auto ParamSet = archive.getRootList().getResParameterList(0);
    if (ParamSet.getResParameterObjNum() < 1)
        return false;

    const auto header_obj = ParamSet.getResParameterObj(0);
    obj.applyResParameterObj(header_obj);

    const int num_rigid_body_sets = *use_rigid_body_set_num;
    if (num_rigid_body_sets > 0) {
        rigid_body_sets.allocBufferAssert(num_rigid_body_sets, heap);

        const auto RigidBodySet = agl::utl::getResParameterList(ParamSet, "RigidBodySet");
        if (!RigidBodySet)
            return false;

        for (auto it = RigidBodySet.listBegin(), end = RigidBodySet.listEnd(); it != end; ++it) {
            if (!rigid_body_sets[it.getIndex()].parse(it.getList(), heap))
                return false;
        }
    }

    if (*use_character_controller) {
        character_controller = new (heap) CharacterControllerParam;
        if (!character_controller->parse(
                agl::utl::getResParameterList(ParamSet, "CharacterController"), heap)) {
            return false;
        }
    }

    if (*use_contact_info) {
        contact_info = new (heap) ContactInfoParam;
        if (!contact_info->parse(agl::utl::getResParameterList(ParamSet, "RigidContactInfo"), heap))
            return false;
    }

    if (*use_support_bone) {
        support_bone = new (heap) SupportBoneParam;
        addObj(support_bone, "SupportBone");
    }

    if (*use_ragdoll) {
        ragdoll = new (heap) RagdollParam;
        addObj(ragdoll, "Ragdoll");
    }

    if (*use_cloth) {
        cloth_set = new (heap) ClothSetParam;
        const auto list = agl::utl::getResParameterList(ParamSet, "Cloth");
        if (list) {
            addList(cloth_set, "Cloth");
            if (!cloth_set->parse(list, heap))
                return false;
        }
    }

    if (*use_edge_rigid_body_num > 0) {
        edge_rigid_body_set = new (heap) EdgeRigidBodySetParam;
        edge_rigid_body_set->parse(*use_edge_rigid_body_num, heap);
        addList(edge_rigid_body_set, "EdgeRigidBody");
    }

    applyResParameterList(ParamSet);

    num_rigid_bodies_with_link_matrix = 0;
    for (int set_idx = 0; set_idx < num_rigid_body_sets; ++set_idx) {
        auto& set = rigid_body_sets[set_idx];

        const int num_rigid_bodies = set.getNumRigidBodies();
        for (int body_idx = 0; body_idx < num_rigid_bodies; ++body_idx) {
            if (!set.rigid_bodies[body_idx].info.link_matrix->isEmpty())
                ++num_rigid_bodies_with_link_matrix;
        }
    }

    bphysics->addList(this, "ParamSet");
    return true;
}

RigidBodySetParam& ParamSet::getRigidBodySet(int idx) {
    return rigid_body_sets[idx];
}

}  // namespace ksys::phys
