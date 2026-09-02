#include "Game/Actor/actPlayerCreateUtils.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actPlayerCreateMgr.h"
#include "Game/Actor/actWeapon.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectWeaponCommon.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::act {

void requestCreateWeaponByRawLife(const char* actor_class, const sead::Matrix34f& matrix, f32 scale,
                                  sead::Heap* heap, ksys::act::BaseProcHandle* handle, s32 life,
                                  bool is_player_put, const WeaponModifierInfo* modifier,
                                  s32 task_lane_id, s32 res_lane_id) {
    ksys::act::InstParamPack params;
    params->add(is_player_put, "IsPlayerPut");
    if (modifier) {
        modifier->addModifierParams(params);
    }
    params->add(true, "IsWeaponCreateByRawLife");
    params->addResourceLane(res_lane_id);

    ksys::act::WeaponBase::requestCreateWeaponActor(actor_class, matrix, scale, heap, handle, life,
                                                    &params, task_lane_id);
}

// NON_MATCHING: instruction-scheduling spread across two large, near-identical NEON/FP blocks
// rotation matrix construction, then normal-vector normalize-and-clamp, done once per raycast
// attempt.
void dropActorFromPorchCalculateMtx(sead::Matrix34f* mtx, ksys::act::Actor* actor) {
    const auto* weapon_common = actor->getParam()->getRes().mGParamList->getWeaponCommon();
    const auto& drop_rot = weapon_common->mDropFromPorchRot.ref();

    sead::Matrix34f rot_mtx;
    rot_mtx.makeR({sead::Mathf::deg2rad(drop_rot.x), sead::Mathf::deg2rad(drop_rot.y),
                   sead::Mathf::deg2rad(drop_rot.z)});
    mtx->setMul(*mtx, rot_mtx);

    // half_offset clears the actor's own bounding box, from its rigid body AABB if it has one.
    const sead::Vector3f row0 = mtx->getBase(0);
    const sead::Vector3f row2 = mtx->getBase(2);

    sead::Vector3f half_offset;
    auto* rigid_body = actor->getMainBody();
    if (rigid_body) {
        sead::BoundBox3f local_aabb;
        rigid_body->getAabbInLocal(&local_aabb);
        const sead::Vector3f center = rigid_body->getCenterOfMassInLocal();
        const sead::Vector3f local_offset{center.x, 0.0f, local_aabb.getSizeZ()};
        half_offset.x = (local_offset.x * row0.x) + (local_offset.z * row0.z);
        half_offset.y = -local_aabb.getSizeY() * 0.5f;
        half_offset.z = (local_offset.x * row2.x) + (local_offset.z * row2.z);
    } else {
        const sead::Vector3f local_offset{0.0f, 0.0f, 0.3f};
        half_offset.x = local_offset.z * row0.z;
        half_offset.y = -0.2f;
        half_offset.z = local_offset.z * row2.z;
    }

    const sead::Vector3f pos = mtx->getTranslation();

    sead::Vector3f drop_pos = pos - half_offset;
    sead::Vector3f start = pos;
    sead::Vector3f end = pos - half_offset * 1.25f;
    start.y += 0.2f;
    end.y += 0.2f;

    // Midpoint between pos and hit_pos, nudged along the hit normal by normal_scale * |half_offset|
    auto calcRestingPos = [&](const sead::Vector3f& hit_pos, const sead::Vector3f& hit_normal_in,
                              f32 normal_scale) {
        sead::Vector3f normal = hit_normal_in;
        normal.y *= 0.5f;

        f32 normal_len = sead::Mathf::sqrt((normal.x * normal.x) + (normal.y * normal.y) +
                                           (normal.z * normal.z));
        if (normal_len > 0.0f)
            normal *= 1.0f / normal_len;

        f32 half_offset_len =
            sead::Mathf::sqrt((half_offset.x * half_offset.x) + (half_offset.y * half_offset.y) +
                              (half_offset.z * half_offset.z)) *
            normal_scale;
        normal *= half_offset_len;
        normal.y = sead::Mathf::max(normal.y, 0.0f);

        return (pos + hit_pos) * 0.5f + normal;
    };

    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    query.enableGroundHitLayers();
    query.enableLayer(ksys::phys::ContactLayer::EntityObject);
    query.setStartAndEnd(start, end);

    sead::Vector3f hit_pos;
    sead::Vector3f hit_normal;
    if (query.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
        query.getHitPosition(&hit_pos);
        query.getHitNormal(&hit_normal);
        drop_pos = calcRestingPos(hit_pos, hit_normal, 0.5f);
        sead::Vector3f drop_pos_end = drop_pos + half_offset;

        query.resetCastResult();
        query.setStartAndEnd(drop_pos, drop_pos_end);
        if (query.worldRayCast(ksys::phys::ContactLayerType::Entity) &&
            ksys::act::hasValidPlayerActor()) {
            sead::Vector3f target = ksys::act::PlayerInfo::instance() ?
                                        ksys::act::PlayerInfo::instance()->getPlayerPos() :
                                        sead::Vector3f::zero;
            target.y += 0.4f;
            drop_pos = target;

            const sead::Vector3f almost_up{0.0f, 1.0f, 0.01f};
            const sead::Vector3f world_z{0.0f, 0.0f, 1.0f};
            ksys::util::calcMatrixFromZAxis(mtx, almost_up, world_z, drop_pos);
        }
    } else {
        end.y -= 0.6f;
        query.resetCastResult();
        query.setStartAndEnd(start, end);
        if (query.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
            query.getHitPosition(&hit_pos);
            query.getHitNormal(&hit_normal);
            drop_pos = calcRestingPos(hit_pos, hit_normal, 0.6f);
        }
    }

    mtx->setTranslation(drop_pos);
}

bool calcValidDropPosition(sead::Vector3f* out_pos, const sead::Vector3f& pos) {
    out_pos->x = pos.x;
    out_pos->y = pos.y;
    out_pos->z = pos.z;

    sead::Vector3f to_player{0.0f, 0.0f, 0.0f};
    sead::Vector3f player_pos{0.0f, 0.0f, 0.0f};
    if (ksys::act::hasValidPlayerActor()) {
        player_pos = ksys::act::PlayerInfo::instance() ?
                         ksys::act::PlayerInfo::instance()->getPlayerPos() :
                         sead::Vector3f::zero;
        to_player = pos - player_pos;
        f32 len = sead::Mathf::sqrt((to_player.x * to_player.x) + (to_player.y * to_player.y) +
                                    (to_player.z * to_player.z));
        if (len > 0.0f)
            to_player *= 1.0f / len;
    }

    sead::Vector3f start{pos.x, pos.y + 0.5f, pos.z};
    sead::Vector3f end{pos.x, pos.y - 0.5f, pos.z};

    f32 end_y = end.y;
    f32 end_x = pos.x;
    f32 end_z = pos.z;
    {
        ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
        query.enableCommonHitLayers();
        query.setStartAndEnd(start, end);
        if (query.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
            sead::Vector3f hit_pos;
            query.getHitPosition(&hit_pos);
            end_y = hit_pos.y + 0.005f;
            *out_pos = hit_pos;
            end_x = hit_pos.x;
            end_z = hit_pos.z;
        }
    }

    start = sead::Vector3f{player_pos.x, player_pos.y + 0.5f, player_pos.z};
    end = sead::Vector3f{end_x, end_y, end_z};

    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    query.enableCommonHitLayers();
    query.setStartAndEnd(start, end);
    if (!query.worldRayCast(ksys::phys::ContactLayerType::Entity))
        return false;

    sead::Vector3f hit_pos;
    query.getHitPosition(&hit_pos);
    out_pos->x = hit_pos.x - (to_player.x * 0.25f);
    out_pos->y = hit_pos.y - (to_player.y * 0.25f);
    out_pos->z = hit_pos.z - (to_player.z * 0.25f);
    return true;
}

}  // namespace uking::act
