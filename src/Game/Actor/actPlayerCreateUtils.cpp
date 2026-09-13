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

// Separately-addressed target function (0x72b82c, 48 bytes); kept with external linkage to
// match rather than folded into an anonymous namespace.
// NOLINTNEXTLINE(misc-use-internal-linkage) doesn't match with static
const sead::Vector3f& getPlayerPosition() {
    if (!ksys::act::PlayerInfo::instance())
        return sead::Vector3f::zero;

    return ksys::act::PlayerInfo::instance()->getPlayerPos();
}

// NON_MATCHING: 56 bytes vs. the target's 1732. Gap is in the "obstructed, drop near player"
// branch, where makeMtxFrontUpPos's own setTranslation and the explicit one right after don't
// fold together the way they do in target.
void dropActorFromPorchCalculateMtx(sead::Matrix34f* mtx, ksys::act::Actor* actor) {
    const auto* weapon_common = actor->getParam()->getRes().mGParamList->getWeaponCommon();
    const sead::Vector3f drop_rot = weapon_common->mDropFromPorchRot.ref();

    sead::Matrix34f rot_mtx;
    rot_mtx.makeRT({sead::Mathf::deg2rad(drop_rot.x), sead::Mathf::deg2rad(drop_rot.y),
                    sead::Mathf::deg2rad(drop_rot.z)},
                   sead::Vector3f::zero);
    mtx->setMul(*mtx, rot_mtx);

    sead::Vector3f half_offset;
    auto* rigid_body = actor->getMainBody();
    if (rigid_body) {
        sead::BoundBox3f local_aabb;
        rigid_body->getAabbInLocal(&local_aabb);
        const sead::Vector3f center = rigid_body->getCenterOfMassInLocal();
        half_offset.setRotated(*mtx, {center.x, 0.0f, local_aabb.getSizeZ()});
        half_offset.y = -local_aabb.getSizeY() * 0.5f;
    } else {
        half_offset.setRotated(*mtx, {0.0f, 0.0f, 0.3f});
        half_offset.y = -0.2f;
    }

    sead::Vector3f pos;
    mtx->getTranslation(pos);

    sead::Vector3f drop_pos = pos - half_offset;
    sead::Vector3f hit_pos;
    sead::Vector3f hit_normal;
    sead::Vector3f start = pos;
    sead::Vector3f end = pos - half_offset * 1.25f;

    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    query.enableGroundHitLayers();
    query.enableLayer(ksys::phys::ContactLayer::EntityObject);
    start.y += 0.2f;
    end.y += 0.2f;
    query.setStartAndEnd(start, end);

    if (query.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
        query.getHitPosition(&hit_pos);
        query.getHitNormal(&hit_normal);
        hit_normal.y *= 0.5f;
        hit_normal.normalize();
        hit_normal *= half_offset.length() * 0.5f;
        // NOLINTNEXTLINE(readability-use-std-min-max) matches target closer than max()
        if (hit_normal.y < 0.0f)
            hit_normal.y = 0.0f;
        drop_pos = (pos + hit_pos) * 0.5f + hit_normal;
        sead::Vector3f drop_pos_end = drop_pos + half_offset;

        query.resetCastResult();
        query.setStartAndEnd(drop_pos, drop_pos_end);
        if (query.worldRayCast(ksys::phys::ContactLayerType::Entity) &&
            ksys::act::hasValidPlayerActor()) {
            sead::Vector3f player_pos = getPlayerPosition();
            const sead::Vector3f almost_up{0.0f, 1.0f, 0.01f};
            // Target really does add this as a double, promoting player_pos.y and back.
            player_pos.y += 0.4;
            ksys::util::makeMtxFrontUpPos(mtx, almost_up, sead::Vector3f::ez, player_pos);
            mtx->setTranslation(player_pos);
        }
    } else {
        end.y -= 0.6f;
        query.resetCastResult();
        query.setStartAndEnd(start, end);
        if (query.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
            query.getHitPosition(&hit_pos);
            query.getHitNormal(&hit_normal);
            hit_normal.y *= 0.5f;
            hit_normal.normalize();
            hit_normal *= half_offset.length() * 0.6f;
            // NOLINTNEXTLINE(readability-use-std-min-max) matches target closer than max()
            if (hit_normal.y < 0.0f)
                hit_normal.y = 0.0f;
            drop_pos = (pos + hit_pos) * 0.5f + hit_normal;
        }
    }
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
