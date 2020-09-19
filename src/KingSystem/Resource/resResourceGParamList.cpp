#include "KingSystem/Resource/resResourceGParamList.h"
#include <agl/Utils/aglParameter.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/actActorParamMgr.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectArmor.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttackInterval.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectBindBone.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectBow.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectCamera.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEnemy.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEnemyLevel.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEnemyRace.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEnemyShown.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGeneral.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGrab.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGuardianMiniWeapon.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectLargeSword.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectMasterSword.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectPlayer.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectRod.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectSandworm.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectShield.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectSmallSword.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectSpear.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectSystem.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectWeaponCommon.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectWeaponOption.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectWeaponThrow.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListTraits.h"

namespace ksys::res {

void GParamList::doCreate_(u8*, u32, sead::Heap*) {}

template <GParamListObjType Type>
KSYS_ALWAYS_INLINE void GParamList::add(const agl::utl::ResParameterList& list,
                                        const sead::SafeString& name, sead::Heap* heap,
                                        GParamList* dummy_list) {
    const auto pobj = agl::utl::getResParameterObj(list, name);
    if (pobj.ptr()) {
        using T = typename GParamListObjTypeTraits<Type>::type;

        auto* obj = new (heap) T;
        if (obj)
            addObj(&obj->getObj(), obj->getName());

        mObjects[s32(Type)] = obj;

    } else {
        mObjects[s32(Type)] = dummy_list ? dummy_list->mObjects[s32(Type)] : nullptr;
    }
}

bool GParamList::parse_(u8* data, size_t, sead::Heap* heap) {
    GParamList* dummy_list = nullptr;
    if (!sead::IsDerivedFrom<DummyGParamList>(this) && act::ActorParamMgr::instance())
        dummy_list = act::ActorParamMgr::instance()->getDummyGParamList();

    mObjects.allocBufferAssert(NumGParamListObjTypes, heap);

    const agl::utl::ResParameterArchive archive{data};

    add<GParamListObjType::System>(archive.getRootList(), "System", heap, dummy_list);
    add<GParamListObjType::General>(archive.getRootList(), "General", heap, dummy_list);
    add<GParamListObjType::Enemy>(archive.getRootList(), "Enemy", heap, dummy_list);
    add<GParamListObjType::EnemyLevel>(archive.getRootList(), "EnemyLevel", heap, dummy_list);
    add<GParamListObjType::EnemyRace>(archive.getRootList(), "EnemyRace", heap, dummy_list);
    add<GParamListObjType::AttackInterval>(archive.getRootList(), "AttackInterval", heap,
                                           dummy_list);
    add<GParamListObjType::EnemyShown>(archive.getRootList(), "EnemyShown", heap, dummy_list);
    add<GParamListObjType::BindBone>(archive.getRootList(), "BindBone", heap, dummy_list);
    add<GParamListObjType::Attack>(archive.getRootList(), "Attack", heap, dummy_list);
    add<GParamListObjType::WeaponCommon>(archive.getRootList(), "WeaponCommon", heap, dummy_list);
    add<GParamListObjType::WeaponThrow>(archive.getRootList(), "WeaponThrow", heap, dummy_list);
    add<GParamListObjType::Sandworm>(archive.getRootList(), "Sandworm", heap, dummy_list);
    add<GParamListObjType::SmallSword>(archive.getRootList(), "SmallSword", heap, dummy_list);
    add<GParamListObjType::Rod>(archive.getRootList(), "Rod", heap, dummy_list);
    add<GParamListObjType::LargeSword>(archive.getRootList(), "LargeSword", heap, dummy_list);
    add<GParamListObjType::Spear>(archive.getRootList(), "Spear", heap, dummy_list);
    add<GParamListObjType::Shield>(archive.getRootList(), "Shield", heap, dummy_list);
    add<GParamListObjType::Bow>(archive.getRootList(), "Bow", heap, dummy_list);
    add<GParamListObjType::WeaponOption>(archive.getRootList(), "WeaponOption", heap, dummy_list);
    add<GParamListObjType::MasterSword>(archive.getRootList(), "MasterSword", heap, dummy_list);
    add<GParamListObjType::GuardianMiniWeapon>(archive.getRootList(), "GuardianMiniWeapon", heap,
                                               dummy_list);
    add<GParamListObjType::Player>(archive.getRootList(), "Player", heap, dummy_list);
    add<GParamListObjType::Camera>(archive.getRootList(), "Camera", heap, dummy_list);
    add<GParamListObjType::Grab>(archive.getRootList(), "Grab", heap, dummy_list);
    add<GParamListObjType::Armor>(archive.getRootList(), "Armor", heap, dummy_list);

    // TODO: the rest

    if (data)
        applyResParameterArchive(archive);

    return true;
}

void GParamList::finalize_() {}

void DummyGParamList::doCreate_(u8*, u32, sead::Heap*) {}

bool DummyGParamList::parse_(u8* data, size_t size, sead::Heap* heap) {
    GParamList::parse_(data, size, heap);
    return true;
}

}  // namespace ksys::res
