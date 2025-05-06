#include "KingSystem/Map/mapObjectLink.h"
#include <container/seadBuffer.h>
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectGenGroup.h"
#include "KingSystem/Map/mapRail.h"

namespace ksys::map {

struct MapLinkDefinition {
    const char* name;
    const char* desc;
    MapLinkDefType type;
};

static constexpr u32 sNumTypes = 42;
static constexpr sead::SafeArray<MapLinkDefinition, sNumTypes> sMapLinkDefinitions{{
    {"-AxisX", "マイナスX軸シグナル", MapLinkDefType::NAxisX},
    {"-AxisY", "マイナスY軸シグナル", MapLinkDefType::NAxisY},
    {"-AxisZ", "マイナスZ軸シグナル", MapLinkDefType::NAxisZ},
    {"AreaCol", "エリア(センサ)指定", MapLinkDefType::AreaCol},
    {"AxisX", "X軸シグナル", MapLinkDefType::AxisX},
    {"AxisY", "Y軸シグナル", MapLinkDefType::AxisY},
    {"AxisZ", "Z軸シグナル", MapLinkDefType::AxisZ},
    {"BAndSCs", "ボール＆ソケットCS", MapLinkDefType::BAndSCs},
    {"BAndSLimitAngYCs", "Y角速度制限付ボール＆ソケットCS", MapLinkDefType::BAndSLimitAngYCs},
    {"BasicSig", "基本シグナル", MapLinkDefType::BasicSig},
    {"BasicSigOnOnly", "オンのみ基本シグナル", MapLinkDefType::BasicSigOnOnly},
    {"ChangeAtnSig", "アテンション変更時シグナル", MapLinkDefType::ChangeAtnSig},
    {"CogWheelCs", "歯車CS", MapLinkDefType::CogWheelCs},
    {"CopyWaitRevival", "配置自動セーブ継承", MapLinkDefType::CopyWaitRevival},
    {"Create", "生成", MapLinkDefType::Create},
    {"DeadUp", "死んだらオン", MapLinkDefType::DeadUp},
    {"DemoMember", "デモ参加", MapLinkDefType::DemoMember},
    {"FixedCs", "固定CS", MapLinkDefType::FixedCs},
    {"ForSale", "売り物", MapLinkDefType::ForSale},
    {"ForbidAttention", "アテンションタイプ変更", MapLinkDefType::ForbidAttention},
    {"Freeze", "凍結", MapLinkDefType::Freeze},
    {"GimmickSuccess", "ネタ成功シグナル", MapLinkDefType::GimmickSuccess},
    {"HingeCs", "ヒンジCS", MapLinkDefType::HingeCs},
    {"LifeZero", "ライフ0", MapLinkDefType::LifeZero},
    {"LimitHingeCs", "制限付ヒンジCS", MapLinkDefType::LimitHingeCs},
    {"ModelBind", "モデルバインド", MapLinkDefType::ModelBind},
    {"MtxCopyCreate", "位置継承生成", MapLinkDefType::MtxCopyCreate},
    {"OffWaitRevival", "配置自動セーブオフ", MapLinkDefType::OffWaitRevival},
    {"PhysSystemGroup", "物理システムグループ", MapLinkDefType::PhysSystemGroup},
    {"PlacementLOD", "配置LOD", MapLinkDefType::PlacementLOD},
    {"PulleyCs", "滑車CS", MapLinkDefType::PulleyCs},
    {"RackAndPinionCs", "ラック＆ピニオンCS", MapLinkDefType::RackAndPinionCs},
    {"Recreate", "再生成", MapLinkDefType::Recreate},
    {"Reference", "参照", MapLinkDefType::Reference},
    {"Remains", "遺物シグナル", MapLinkDefType::Remains},
    {"SensorBind", "センサバインド", MapLinkDefType::SensorBlind},
    {"SliderCs", "スライダーCS", MapLinkDefType::SliderCs},
    {"Stable", "安定", MapLinkDefType::Stable},
    {"StackLink", "スタック", MapLinkDefType::StackLink},
    {"SyncLink", "生成グループ", MapLinkDefType::SyncLink},
    {"VelocityControl", "速度制御シグナル", MapLinkDefType::VelocityControl},
}};

const char* ObjectLink::getDescription() const {
    return getDescriptionForType(type);
}

const char* ObjectLink::getDescriptionForType(MapLinkDefType t) {
    const char* desc = "不定";  // invalid

    for (int i = 0; i < sMapLinkDefinitions.size(); ++i) {
        if (sMapLinkDefinitions[i].type == t) {
            desc = sMapLinkDefinitions[i].desc;
            break;
        }
    }

    return desc;
}

MapLinkDefType ObjectLink::getTypeForName(const sead::SafeString& name) {
    sead::Buffer<const MapLinkDefinition> buf{sMapLinkDefinitions.size(),
                                              sMapLinkDefinitions.getBufferPtr()};

    s32 idx = buf.binarySearchC(
        [&](const MapLinkDefinition& item) { return sead::SafeString(item.name).compare(name); });

    if (idx == -1)
        return MapLinkDefType::Invalid;
    return buf[idx].type;
}

bool ObjectLink::sub_7100D4E310(MapLinkDefType t) {
    switch (t) {
    case MapLinkDefType::Create:
    case MapLinkDefType::Delete:
    case MapLinkDefType::MtxCopyCreate:
    case MapLinkDefType::Freeze:
    case MapLinkDefType::ForbidAttention:
        return true;
    default:
        break;
    case MapLinkDefType::BasicSig:
    case MapLinkDefType::AxisX:
    case MapLinkDefType::AxisY:
    case MapLinkDefType::AxisZ:
    case MapLinkDefType::NAxisX:
    case MapLinkDefType::NAxisY:
    case MapLinkDefType::NAxisZ:
    case MapLinkDefType::GimmickSuccess:
    case MapLinkDefType::VelocityControl:
    case MapLinkDefType::BasicSigOnOnly:
    case MapLinkDefType::Remains:
    case MapLinkDefType::DeadUp:
    case MapLinkDefType::LifeZero:
    case MapLinkDefType::Stable:
    case MapLinkDefType::ChangeAtnSig:
        return true;
    }

    return false;
}

bool ObjectLink::isPlacementLODOrForSaleLink(MapLinkDefType t) {
    return t == MapLinkDefType::PlacementLOD || t == MapLinkDefType::ForSale;
}

act::Actor* ObjectLink::getObjectActor() const {
    if (other_obj == nullptr)
        return nullptr;

    return other_obj->tryGetActor(false);
}

bool ObjectLink::getObjectProcWithAccessor(act::ActorLinkConstDataAccess& accessor) const {
    if (other_obj == nullptr)
        return accessor.acquire(nullptr);
    else
        return other_obj->getActorWithAccessor(accessor);
}

ObjectLinkData::ObjectLinkData() = default;

void ObjectLinkData::deleteArrays() {
    if (mRails) {
        delete[] mRails;
        mRails = nullptr;
    }

    mLinksOther.links.freeBuffer();
    mLinksCs.links.freeBuffer();
    mObjects.freeBuffer();
    mLinksToSelf.links.freeBuffer();
}

bool ObjectLinkData::allocLinks(s32 num_links_ref, s32 num_links_other, s32 num_links_cs,
                                sead::Heap* heap) {
    if (num_links_ref > 0) {
        if (!mObjects.allocBufferAssert(num_links_ref, heap)) {
            return false;
        }
        mObjects.fill(nullptr);
    }
    if (num_links_other > 0) {
        if (!mLinksOther.links.allocBufferAssert(num_links_other, heap)) {
            return false;
        }
    }
    if (num_links_cs > 0) {
        if (!mLinksCs.links.allocBufferAssert(num_links_cs, heap)) {
            return false;
        }
    }
    return true;
}

bool ObjectLinkData::allocLinksToSelf(s32 num_links, sead::Heap* heap) {
    if (num_links >= 1) {
        mLinksToSelf.links.tryAllocBuffer(num_links, heap);
        if (!mLinksToSelf.links.isBufferReady())
            return false;
    }
    return true;
}

// NON_MATCHING
bool ObjectLinkData::addLink(Object* dest, const sead::SafeString& definition_name, bool passive,
                             Object* src, MubinIter* iter) {
    MapLinkDefType type = ObjectLink::getTypeForName(definition_name);
    if (type == MapLinkDefType::Invalid) {
        return false;
    }
    if (type == MapLinkDefType::SyncLink && passive) {
        return false;
    }

    if (type == MapLinkDefType::Reference) {
        for (int i = 0; i < mObjects.size(); i++) {
            if (mObjects[i] == nullptr) {
                mObjects[i] = dest;
                return false;
            }
        }
    }

    if (dest != nullptr && passive) {
        switch (type) {
        case MapLinkDefType::Create:
        case MapLinkDefType::Delete:
        case MapLinkDefType::MtxCopyCreate:
        case MapLinkDefType::SyncLink:
        case MapLinkDefType::PlacementLOD:
        case MapLinkDefType::Reference:
            break;
        case MapLinkDefType::BasicSig:
        case MapLinkDefType::AxisX:
        case MapLinkDefType::AxisY:
        case MapLinkDefType::AxisZ:
        case MapLinkDefType::NAxisX:
        case MapLinkDefType::NAxisY:
        case MapLinkDefType::NAxisZ:
        case MapLinkDefType::GimmickSuccess:
        case MapLinkDefType::VelocityControl:
        case MapLinkDefType::BasicSigOnOnly:
        case MapLinkDefType::Remains:
        case MapLinkDefType::DeadUp:
        case MapLinkDefType::LifeZero:
        case MapLinkDefType::Stable:
        case MapLinkDefType::ChangeAtnSig:
            dest = nullptr;
            break;
        default:
            dest = nullptr;
            break;
        }
    }

    ObjectLinkArray* arr = &mLinksCs;
    if (type == MapLinkDefType::Reference || type == MapLinkDefType::Invalid) {
        arr = &mLinksOther;
    }

    if (type == MapLinkDefType::CopyWaitRevival) {
        if (dest != nullptr) {
            if (src->isLinkTag() && !src->isSetFlag8() && !src->isIncrementSave() &&
                !dest->isIncrementSave()) {
                src->setFlag8();
                src->setRevivalGameDataFlagHash(dest->getRevivalGameDataFlagHash());
            }
        }
    }

    auto& links = arr->links;
    for (auto& link : links) {
        if (link.other_obj == dest && link.type == type) {
            return false;
        }
        if (link.other_obj == nullptr && link.type == MapLinkDefType::Invalid) {
            link.type = type;
            link.other_obj = dest;
            link.iter = *iter;
            return type != MapLinkDefType::Invalid;
        }
    }
    return true;
}

ObjectLink* ObjectLinkData::findLinkWithType(MapLinkDefType t) {
    return findLinkWithType_0(t);
}

ObjectLink* ObjectLinkData::findLinkWithType_0(MapLinkDefType t) {
    switch (t) {
    case MapLinkDefType::FixedCs:
    case MapLinkDefType::HingeCs:
    case MapLinkDefType::LimitHingeCs:
    case MapLinkDefType::SliderCs:
    case MapLinkDefType::PulleyCs:
    case MapLinkDefType::BAndSCs:
    case MapLinkDefType::BAndSLimitAngYCs:
    case MapLinkDefType::CogWheelCs:
    case MapLinkDefType::RackAndPinionCs:
        return mLinksCs.findLinkWithType(t);
    default:
        return mLinksOther.findLinkWithType(t);
    }
}

bool ObjectLinkData::sub_7100D4EC40(Object* obj, ObjectLink* link, Object* dest) {
    for (auto& l : mLinksToSelf.links) {
        auto type = link->type;
        if (l.other_obj == obj && l.type == link->type) {
            return true;
        }
        if (l.other_obj == nullptr) {
            l.other_obj = obj;
            l.type = type;
            l.iter = link->iter;

            auto& iter = link->iter;
            switch (type) {
            default:
                break;
            case MapLinkDefType::BasicSig:
            case MapLinkDefType::BasicSigOnOnly: {
                bool no_auto_demo_member = false;
                if (iter.tryGetParamBoolByKey(&no_auto_demo_member, "NoAutoDemoMember")) {
                    mNoAutoDemoMember = no_auto_demo_member;
                }
                break;
            }
            case MapLinkDefType::Create:
            case MapLinkDefType::MtxCopyCreate:
                if (obj->isLinkTag()) {
                    bool appear_fade = false;
                    if (iter.tryGetParamBoolByKey(&appear_fade, "AppearFade")) {
                        mAppearFade = appear_fade;
                    }
                    mCreateLinksSrcObj = obj;
                }
                break;
            case MapLinkDefType::Delete:
                if (obj->isLinkTag()) {
                    mDeleteLinksSrcObj = obj;
                }
                break;
            }
            return true;
        }
    }
    return false;
}

void ObjectLinkData::setGenGroup(GenGroup* group) {
    if (mGenGroup == nullptr)
        mGenGroup = group;
}

bool ObjectLinkData::checkCreateLinkObjRevival() const {
    if (mCreateLinksSrcObj != nullptr) {
        return !mCreateLinksSrcObj->checkRevivalMaybe(false);
    }
    return false;
}

bool ObjectLinkData::checkDeleteLinkObjRevival() const {
    if (mDeleteLinksSrcObj != nullptr) {
        return mDeleteLinksSrcObj->checkRevivalMaybe(true);
    }
    return false;
}

// NON_MATCHING
bool ObjectLinkArray::checkLink(MapLinkDefType t, bool b) {
    bool x_exists;
    ObjectLink* link = nullptr;

    if (t != MapLinkDefType::BasicSig) {
        x_exists = false;
    } else {
        link = findLinkWithType(MapLinkDefType::BasicSigOnOnly);
        x_exists = link != nullptr;

        if (link != nullptr)
            goto done;
    }

    link = findLinkWithType(t);

    if (link == nullptr)
        return false;
    if (link->type == MapLinkDefType::VelocityControl)
        return false;

done:
    act::ActorConstDataAccess acc{};

    if (link->other_obj != nullptr)
        link->other_obj->getActorWithAccessor(acc);
    else
        acc.acquire(nullptr);
    return acc.checkLinkTagActivated(b, x_exists);
}

bool ObjectLinkData::sub_7100D4EF30(act::ActorConstDataAccess& accessor) {
    for (auto& link : mLinksOther.links) {
        if (link.type == MapLinkDefType::Recreate && link.other_obj == accessor.getMapObject()) {
            accessor.setActor687();
            return true;
        }
    }
    return false;
}

Object* ObjectLinkData::findObjectByActorName(const sead::SafeString& name) {
    for (auto obj : mObjects) {
        if (obj->getActorData().mActorName == name)
            return obj;
    }
    return nullptr;
}

ObjectLink* ObjectLinkArray::findLinkWithType(MapLinkDefType type) {
    return findLinkWithType_0(type);
}

ObjectLink* ObjectLinkArray::findLinkWithType_0(MapLinkDefType type) {
    for (auto it = links.begin(), end = links.end(); it != end; ++it) {
        if (it->type == type)
            return &*it;
    }
    return nullptr;
}

}  // namespace ksys::map
