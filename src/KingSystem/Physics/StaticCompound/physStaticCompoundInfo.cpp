#include "KingSystem/Physics/StaticCompound/physStaticCompoundInfo.h"

namespace ksys::phys {

int StaticCompoundInfo::getActorIdx(u32 hash_id, u32 srt_hash) const {
    for (int i = 0; i < m_ActorInfo.getSize(); ++i) {
        const auto& info = m_ActorInfo[i];
        if (info.m_HashId == hash_id && u32(info.m_SRTHash) == srt_hash)
            return i;
    }
    return -1;
}

int StaticCompoundInfo::getShapeInfoStart(int actor_idx) const {
    if (actor_idx < 0 || actor_idx >= m_ActorInfo.getSize())
        return -1;
    return m_ActorInfo[actor_idx].m_ShapeInfoStart;
}

int StaticCompoundInfo::getShapeInfoEnd(int actor_idx) const {
    if (actor_idx < 0 || actor_idx >= m_ActorInfo.getSize())
        return -1;
    return m_ActorInfo[actor_idx].m_ShapeInfoEnd;
}

const ShapeInfo* StaticCompoundInfo::getShapeInfo(int shape_idx) const {
    if (shape_idx < 0 || shape_idx >= m_ShapeInfo.getSize())
        return nullptr;
    return &m_ShapeInfo[shape_idx];
}

static ContactLayer getContactLayerForBodyLayerType(BodyLayerType type) {
    ContactLayer map[NumBodyLayerTypes];
    map[int(BodyLayerType::EntityGround)] = ContactLayer::EntityGround;
    map[int(BodyLayerType::EntityGroundSmooth)] = ContactLayer::EntityGroundSmooth;
    map[int(BodyLayerType::EntityGroundRough)] = ContactLayer::EntityGroundRough;
    map[int(BodyLayerType::EntityObject)] = ContactLayer::EntityObject;
    map[int(BodyLayerType::EntityGroundObject)] = ContactLayer::EntityGroundObject;
    map[int(BodyLayerType::EntityTree)] = ContactLayer::EntityTree;
    map[int(BodyLayerType::SensorInDoor)] = ContactLayer::SensorInDoor;
    map[int(BodyLayerType::EntityNoHit)] = ContactLayer::EntityNoHit;
    map[int(BodyLayerType::EntityWallForClimb)] = ContactLayer::EntityWallForClimb;
    map[int(BodyLayerType::EntityWater)] = ContactLayer::EntityWater;
    return map[int(type)];
}

BodyLayerType getBodyLayerType(ContactLayer layer) {
    for (int i = 0; i < NumBodyLayerTypes; ++i) {
        auto type = static_cast<BodyLayerType>(i);
        if (int(getContactLayerForBodyLayerType(type)) == int(layer))
            return type;
    }
    return BodyLayerType::Invalid;
}

}  // namespace ksys::phys
