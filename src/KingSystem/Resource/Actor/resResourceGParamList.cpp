#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include <agl/Utils/aglParameter.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/actActorParamMgr.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAirWall.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAnimalFollowOffset.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAnimalUnit.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectArmor.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectArmorEffect.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectArmorHead.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectArmorUpper.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectArrow.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttackInterval.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAutoGen.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectBeam.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectBindActor.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectBindBone.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectBow.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectBullet.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectCamera.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectChemicalType.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectClothReaction.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectCookSpice.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectCureItem.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEatTarget.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEnemy.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEnemyLevel.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEnemyRace.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEnemyShown.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEvent.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectExtendedEntity.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectFish.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGelEnemy.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGeneral.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGiantArmor.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGiantArmorSlot.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGlobal.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGolem.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGolemIK.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGrab.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGuardian.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGuardianMini.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGuardianMiniWeapon.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectHorse.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectHorseCreator.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectHorseObject.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectHorseRider.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectHorseTargetedInfo.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectHorseUnit.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectInsect.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectItem.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectLargeSword.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectLiftable.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectLumberjackTree.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectMasterSword.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectMonsterShop.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectMotorcycle.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectNest.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectNpc.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectNpcEquipment.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectPictureBook.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectPlayer.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectPrey.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectRod.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectRope.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectRupee.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectSandworm.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectSeriesArmor.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectShiekerStone.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectShield.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectSmallSword.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectSpear.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectStalEnemy.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectSwarm.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectSystem.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectTraveler.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectWeaponCommon.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectWeaponOption.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectWeaponThrow.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectWizzrobe.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectWolfLink.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectZora.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListTraits.h"

namespace ksys::res {

void GParamList::doCreate_(u8*, u32, sead::Heap*) {}

bool GParamList::parse_(u8* data, size_t, sead::Heap* heap) {
    GParamList* dummy_list = nullptr;
    if (!sead::IsDerivedFrom<DummyGParamList>(this) && act::ActorParamMgr::instance())
        dummy_list = act::ActorParamMgr::instance()->getDummyGParamList();

    mObjects.allocBufferAssert(NumGParamListObjTypes, heap);

    const agl::utl::ResParameterArchive archive{data};

#define KSYS_GPARAM_ADD_(NAME)                                                                     \
    do {                                                                                           \
        using Traits = GParamListObjTypeTraits<GParamListObjType::NAME>;                           \
        const auto pobj = agl::utl::getResParameterObj(archive.getRootList(), #NAME);              \
        if (pobj.ptr()) {                                                                          \
            auto* obj = new (heap) Traits::type;                                                   \
            if (obj)                                                                               \
                addObj(&obj->getObj(), obj->getName());                                            \
                                                                                                   \
            mObjects[Traits::index] = obj;                                                         \
                                                                                                   \
        } else {                                                                                   \
            mObjects[Traits::index] = dummy_list ? dummy_list->mObjects[Traits::index] : nullptr;  \
        }                                                                                          \
    } while (0)

    KSYS_GPARAM_ADD_(System);
    KSYS_GPARAM_ADD_(General);
    KSYS_GPARAM_ADD_(Enemy);
    KSYS_GPARAM_ADD_(EnemyLevel);
    KSYS_GPARAM_ADD_(EnemyRace);
    KSYS_GPARAM_ADD_(AttackInterval);
    KSYS_GPARAM_ADD_(EnemyShown);
    KSYS_GPARAM_ADD_(BindBone);
    KSYS_GPARAM_ADD_(Attack);
    KSYS_GPARAM_ADD_(WeaponCommon);
    KSYS_GPARAM_ADD_(WeaponThrow);
    KSYS_GPARAM_ADD_(Sandworm);
    KSYS_GPARAM_ADD_(SmallSword);
    KSYS_GPARAM_ADD_(Rod);
    KSYS_GPARAM_ADD_(LargeSword);
    KSYS_GPARAM_ADD_(Spear);
    KSYS_GPARAM_ADD_(Shield);
    KSYS_GPARAM_ADD_(Bow);
    KSYS_GPARAM_ADD_(WeaponOption);
    KSYS_GPARAM_ADD_(MasterSword);
    KSYS_GPARAM_ADD_(GuardianMiniWeapon);
    KSYS_GPARAM_ADD_(Player);
    KSYS_GPARAM_ADD_(Camera);
    KSYS_GPARAM_ADD_(Grab);
    KSYS_GPARAM_ADD_(Armor);
    KSYS_GPARAM_ADD_(ArmorEffect);
    KSYS_GPARAM_ADD_(ArmorHead);
    KSYS_GPARAM_ADD_(ArmorUpper);
    KSYS_GPARAM_ADD_(ShiekerStone);
    KSYS_GPARAM_ADD_(SeriesArmor);
    KSYS_GPARAM_ADD_(Liftable);
    KSYS_GPARAM_ADD_(Item);
    KSYS_GPARAM_ADD_(Rupee);
    KSYS_GPARAM_ADD_(Arrow);
    KSYS_GPARAM_ADD_(Bullet);
    KSYS_GPARAM_ADD_(CureItem);
    KSYS_GPARAM_ADD_(CookSpice);
    KSYS_GPARAM_ADD_(LumberjackTree);
    KSYS_GPARAM_ADD_(Npc);
    KSYS_GPARAM_ADD_(NpcEquipment);
    KSYS_GPARAM_ADD_(Zora);
    KSYS_GPARAM_ADD_(Traveler);
    KSYS_GPARAM_ADD_(Prey);
    KSYS_GPARAM_ADD_(AnimalFollowOffset);
    KSYS_GPARAM_ADD_(ExtendedEntity);
    KSYS_GPARAM_ADD_(BindActor);
    KSYS_GPARAM_ADD_(EatTarget);
    KSYS_GPARAM_ADD_(AnimalUnit);
    KSYS_GPARAM_ADD_(Insect);
    KSYS_GPARAM_ADD_(Fish);
    KSYS_GPARAM_ADD_(Rope);
    KSYS_GPARAM_ADD_(Horse);
    KSYS_GPARAM_ADD_(HorseUnit);
    KSYS_GPARAM_ADD_(HorseObject);
    KSYS_GPARAM_ADD_(HorseRider);
    KSYS_GPARAM_ADD_(HorseCreator);
    KSYS_GPARAM_ADD_(GiantArmorSlot);
    KSYS_GPARAM_ADD_(GiantArmor);
    KSYS_GPARAM_ADD_(Guardian);
    KSYS_GPARAM_ADD_(MonsterShop);
    KSYS_GPARAM_ADD_(Swarm);
    KSYS_GPARAM_ADD_(GelEnemy);
    KSYS_GPARAM_ADD_(Nest);
    KSYS_GPARAM_ADD_(Wizzrobe);
    KSYS_GPARAM_ADD_(StalEnemy);
    KSYS_GPARAM_ADD_(GuardianMini);
    KSYS_GPARAM_ADD_(ClothReaction);
    KSYS_GPARAM_ADD_(Global);
    KSYS_GPARAM_ADD_(Beam);
    KSYS_GPARAM_ADD_(AutoGen);
    KSYS_GPARAM_ADD_(ChemicalType);
    KSYS_GPARAM_ADD_(Golem);
    KSYS_GPARAM_ADD_(HorseTargetedInfo);
    KSYS_GPARAM_ADD_(WolfLink);
    KSYS_GPARAM_ADD_(Event);
    KSYS_GPARAM_ADD_(GolemIK);
    KSYS_GPARAM_ADD_(PictureBook);
    KSYS_GPARAM_ADD_(AirWall);
    KSYS_GPARAM_ADD_(Motorcycle);

#undef KSYS_GPARAM_ADD_

    if (data)
        applyResParameterArchive(archive);

    return true;
}

void GParamList::finalize_() {}

static constexpr size_t getResourceFactoryFallbackSizeConst() {
    size_t size = 0;
    size += sizeof(GParamListObjectSystem);
    size += sizeof(GParamListObjectGeneral);
    size += sizeof(GParamListObjectEnemy);
    size += sizeof(GParamListObjectEnemyLevel);
    size += sizeof(GParamListObjectEnemyRace);
    size += sizeof(GParamListObjectAttackInterval);
    size += sizeof(GParamListObjectEnemyShown);
    size += sizeof(GParamListObjectBindBone);
    size += sizeof(GParamListObjectAttack);
    size += sizeof(GParamListObjectWeaponCommon);
    size += sizeof(GParamListObjectWeaponThrow);
    size += sizeof(GParamListObjectSandworm);
    size += sizeof(GParamListObjectSmallSword);
    size += sizeof(GParamListObjectRod);
    size += sizeof(GParamListObjectLargeSword);
    size += sizeof(GParamListObjectSpear);
    size += sizeof(GParamListObjectShield);
    size += sizeof(GParamListObjectBow);
    size += sizeof(GParamListObjectWeaponOption);
    size += sizeof(GParamListObjectMasterSword);
    size += sizeof(GParamListObjectGuardianMiniWeapon);
    size += sizeof(GParamListObjectPlayer);
    size += sizeof(GParamListObjectCamera);
    size += sizeof(GParamListObjectGrab);
    size += sizeof(GParamListObjectArmor);
    size += sizeof(GParamListObjectArmorEffect);
    size += sizeof(GParamListObjectArmorHead);
    size += sizeof(GParamListObjectArmorUpper);
    size += sizeof(GParamListObjectShiekerStone);
    size += sizeof(GParamListObjectSeriesArmor);
    size += sizeof(GParamListObjectLiftable);
    size += sizeof(GParamListObjectItem);
    size += sizeof(GParamListObjectRupee);
    size += sizeof(GParamListObjectArrow);
    size += sizeof(GParamListObjectBullet);
    size += sizeof(GParamListObjectCureItem);
    size += sizeof(GParamListObjectCookSpice);
    size += sizeof(GParamListObjectLumberjackTree);
    size += sizeof(GParamListObjectNpc);
    size += sizeof(GParamListObjectNpcEquipment);
    size += sizeof(GParamListObjectZora);
    size += sizeof(GParamListObjectTraveler);
    size += sizeof(GParamListObjectPrey);
    size += sizeof(GParamListObjectAnimalFollowOffset);
    size += sizeof(GParamListObjectExtendedEntity);
    size += sizeof(GParamListObjectBindActor);
    size += sizeof(GParamListObjectEatTarget);
    size += sizeof(GParamListObjectAnimalUnit);
    size += sizeof(GParamListObjectInsect);
    size += sizeof(GParamListObjectFish);
    size += sizeof(GParamListObjectRope);
    size += sizeof(GParamListObjectHorse);
    size += sizeof(GParamListObjectHorseUnit);
    size += sizeof(GParamListObjectHorseObject);
    size += sizeof(GParamListObjectHorseRider);
    size += sizeof(GParamListObjectHorseCreator);
    size += sizeof(GParamListObjectGiantArmorSlot);
    size += sizeof(GParamListObjectGiantArmor);
    size += sizeof(GParamListObjectGuardian);
    size += sizeof(GParamListObjectMonsterShop);
    size += sizeof(GParamListObjectSwarm);
    size += sizeof(GParamListObjectGelEnemy);
    size += sizeof(GParamListObjectNest);
    size += sizeof(GParamListObjectWizzrobe);
    size += sizeof(GParamListObjectStalEnemy);
    size += sizeof(GParamListObjectGuardianMini);
    size += sizeof(GParamListObjectClothReaction);
    size += sizeof(GParamListObjectGlobal);
    size += sizeof(GParamListObjectBeam);
    size += sizeof(GParamListObjectAutoGen);
    size += sizeof(GParamListObjectChemicalType);
    size += sizeof(GParamListObjectGolem);
    size += sizeof(GParamListObjectHorseTargetedInfo);
    size += sizeof(GParamListObjectWolfLink);
    size += sizeof(GParamListObjectEvent);
    size += sizeof(GParamListObjectGolemIK);
    size += sizeof(GParamListObjectPictureBook);
    size += sizeof(GParamListObjectAirWall);
    size += sizeof(GParamListObjectMotorcycle);
    size += sizeof(GParamList);
    return size;
}

u32 GParamList::getResourceFactoryFallbackSize() {
    constexpr size_t size = getResourceFactoryFallbackSizeConst();
    static_assert(size == static_cast<u32>(size));
    return static_cast<u32>(size);
}

void DummyGParamList::doCreate_(u8*, u32, sead::Heap*) {}

bool DummyGParamList::parse_(u8* data, size_t size, sead::Heap* heap) {
    GParamList::parse_(data, size, heap);
    return true;
}

}  // namespace ksys::res
