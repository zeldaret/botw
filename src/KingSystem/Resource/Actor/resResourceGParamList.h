#pragma once

#include <container/seadBuffer.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListTraits.h"
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamList : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(GParamList, Resource)
public:
    GParamList() : ParamIO("bgparamlist", 0) {}
    ~GParamList() override = default;

    bool ParamIO_m0(char* data) override { return false; }
    void doCreate_(u8* buffer, u32 bufferSize, sead::Heap* heap) override;
    bool needsParse() const override { return true; }

    static u32 getResourceFactoryFallbackSize();

    template <GParamListObjType Type>
    const auto* get() const {
        using Traits = GParamListObjTypeTraits<Type>;
        return reinterpret_cast<const typename Traits::type*>(mObjects[Traits::index]);
    }

#define KSYS_GPARAM_DEFINE_GETTER_(NAME)                                                           \
    const auto* get##NAME() const { return get<GParamListObjType::NAME>(); }

    KSYS_GPARAM_DEFINE_GETTER_(System)
    KSYS_GPARAM_DEFINE_GETTER_(General)
    KSYS_GPARAM_DEFINE_GETTER_(Enemy)
    KSYS_GPARAM_DEFINE_GETTER_(EnemyLevel)
    KSYS_GPARAM_DEFINE_GETTER_(EnemyRace)
    KSYS_GPARAM_DEFINE_GETTER_(AttackInterval)
    KSYS_GPARAM_DEFINE_GETTER_(EnemyShown)
    KSYS_GPARAM_DEFINE_GETTER_(BindBone)
    KSYS_GPARAM_DEFINE_GETTER_(Attack)
    KSYS_GPARAM_DEFINE_GETTER_(WeaponCommon)
    KSYS_GPARAM_DEFINE_GETTER_(WeaponThrow)
    KSYS_GPARAM_DEFINE_GETTER_(Sandworm)
    KSYS_GPARAM_DEFINE_GETTER_(SmallSword)
    KSYS_GPARAM_DEFINE_GETTER_(Rod)
    KSYS_GPARAM_DEFINE_GETTER_(LargeSword)
    KSYS_GPARAM_DEFINE_GETTER_(Spear)
    KSYS_GPARAM_DEFINE_GETTER_(Shield)
    KSYS_GPARAM_DEFINE_GETTER_(Bow)
    KSYS_GPARAM_DEFINE_GETTER_(WeaponOption)
    KSYS_GPARAM_DEFINE_GETTER_(MasterSword)
    KSYS_GPARAM_DEFINE_GETTER_(GuardianMiniWeapon)
    KSYS_GPARAM_DEFINE_GETTER_(Player)
    KSYS_GPARAM_DEFINE_GETTER_(Camera)
    KSYS_GPARAM_DEFINE_GETTER_(Grab)
    KSYS_GPARAM_DEFINE_GETTER_(Armor)
    KSYS_GPARAM_DEFINE_GETTER_(ArmorEffect)
    KSYS_GPARAM_DEFINE_GETTER_(ArmorHead)
    KSYS_GPARAM_DEFINE_GETTER_(ArmorUpper)
    KSYS_GPARAM_DEFINE_GETTER_(ShiekerStone)
    KSYS_GPARAM_DEFINE_GETTER_(SeriesArmor)
    KSYS_GPARAM_DEFINE_GETTER_(Liftable)
    KSYS_GPARAM_DEFINE_GETTER_(Item)
    KSYS_GPARAM_DEFINE_GETTER_(Rupee)
    KSYS_GPARAM_DEFINE_GETTER_(Arrow)
    KSYS_GPARAM_DEFINE_GETTER_(Bullet)
    KSYS_GPARAM_DEFINE_GETTER_(CureItem)
    KSYS_GPARAM_DEFINE_GETTER_(CookSpice)
    KSYS_GPARAM_DEFINE_GETTER_(LumberjackTree)
    KSYS_GPARAM_DEFINE_GETTER_(Npc)
    KSYS_GPARAM_DEFINE_GETTER_(NpcEquipment)
    KSYS_GPARAM_DEFINE_GETTER_(Zora)
    KSYS_GPARAM_DEFINE_GETTER_(Traveler)
    KSYS_GPARAM_DEFINE_GETTER_(Prey)
    KSYS_GPARAM_DEFINE_GETTER_(AnimalFollowOffset)
    KSYS_GPARAM_DEFINE_GETTER_(ExtendedEntity)
    KSYS_GPARAM_DEFINE_GETTER_(BindActor)
    KSYS_GPARAM_DEFINE_GETTER_(EatTarget)
    KSYS_GPARAM_DEFINE_GETTER_(AnimalUnit)
    KSYS_GPARAM_DEFINE_GETTER_(Insect)
    KSYS_GPARAM_DEFINE_GETTER_(Fish)
    KSYS_GPARAM_DEFINE_GETTER_(Rope)
    KSYS_GPARAM_DEFINE_GETTER_(Horse)
    KSYS_GPARAM_DEFINE_GETTER_(HorseUnit)
    KSYS_GPARAM_DEFINE_GETTER_(HorseObject)
    KSYS_GPARAM_DEFINE_GETTER_(HorseRider)
    KSYS_GPARAM_DEFINE_GETTER_(HorseCreator)
    KSYS_GPARAM_DEFINE_GETTER_(GiantArmorSlot)
    KSYS_GPARAM_DEFINE_GETTER_(GiantArmor)
    KSYS_GPARAM_DEFINE_GETTER_(Guardian)
    KSYS_GPARAM_DEFINE_GETTER_(MonsterShop)
    KSYS_GPARAM_DEFINE_GETTER_(Swarm)
    KSYS_GPARAM_DEFINE_GETTER_(GelEnemy)
    KSYS_GPARAM_DEFINE_GETTER_(Nest)
    KSYS_GPARAM_DEFINE_GETTER_(Wizzrobe)
    KSYS_GPARAM_DEFINE_GETTER_(StalEnemy)
    KSYS_GPARAM_DEFINE_GETTER_(GuardianMini)
    KSYS_GPARAM_DEFINE_GETTER_(ClothReaction)
    KSYS_GPARAM_DEFINE_GETTER_(Global)
    KSYS_GPARAM_DEFINE_GETTER_(Beam)
    KSYS_GPARAM_DEFINE_GETTER_(AutoGen)
    KSYS_GPARAM_DEFINE_GETTER_(ChemicalType)
    KSYS_GPARAM_DEFINE_GETTER_(Golem)
    KSYS_GPARAM_DEFINE_GETTER_(HorseTargetedInfo)
    KSYS_GPARAM_DEFINE_GETTER_(WolfLink)
    KSYS_GPARAM_DEFINE_GETTER_(Event)
    KSYS_GPARAM_DEFINE_GETTER_(GolemIK)
    KSYS_GPARAM_DEFINE_GETTER_(PictureBook)
    KSYS_GPARAM_DEFINE_GETTER_(AirWall)
    KSYS_GPARAM_DEFINE_GETTER_(Motorcycle)

#undef KSYS_GPARAM_DEFINE_GETTER_

protected:
    bool parse_(u8* data, size_t size, sead::Heap* heap) override;
    void finalize_() override;

private:
    sead::Buffer<GParamListObject*> mObjects;
};
KSYS_CHECK_SIZE_NX150(GParamList, 0x2c0);

class DummyGParamList : public GParamList {
    SEAD_RTTI_OVERRIDE(DummyGParamList, GParamList)
public:
    using GParamList::GParamList;
    ~DummyGParamList() override = default;

    void doCreate_(u8* buffer, u32 bufferSize, sead::Heap* heap) override;

private:
    bool parse_(u8* data, size_t size, sead::Heap* heap) override;
};

}  // namespace ksys::res
