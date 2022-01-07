#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Collide/Shape/hkpShape.h>

class hkMotionState;
class hkpCollidable;

class hkpCdBody {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpCdBody)
    friend class hkpCollidable;

    HK_FORCE_INLINE hkpCdBody() {}

    HK_FORCE_INLINE hkpCdBody(const hkpShape* shape, const hkMotionState* motionState);
    HK_FORCE_INLINE hkpCdBody(const hkpShape* shape, const hkTransform* t);

    HK_FORCE_INLINE hkpCdBody(const hkpCdBody& body) = delete;

    HK_FORCE_INLINE const hkTransform& getTransform() const;
    HK_FORCE_INLINE const hkpShape* getShape() const;
    HK_FORCE_INLINE const hkpCollidable* getRootCollidable() const;
    HK_FORCE_INLINE hkpShapeKey getShapeKey() const;
    HK_FORCE_INLINE hkpShapeKey getTopLevelShapeKey() const;
    HK_FORCE_INLINE const hkpCdBody* getParent() const;

    // Internal functions, for collision agents.
    explicit HK_FORCE_INLINE hkpCdBody(const hkpCdBody* parent);
    HK_FORCE_INLINE hkpCdBody(const hkpCdBody* parent, const hkMotionState* ms);
    HK_FORCE_INLINE hkpCdBody(const hkpCdBody* parent, const hkTransform* t);
    HK_FORCE_INLINE void setShape(const hkpShape* shape, hkpShapeKey key);
    HK_FORCE_INLINE const hkMotionState* getMotionState() const;
    HK_FORCE_INLINE void setMotionState(const hkMotionState* state);
    HK_FORCE_INLINE void setTransform(const hkTransform* t);

    const hkpShape* m_shape;
    hkpShapeKey m_shapeKey;

private:
    // hkTransform or hkMotionState.
    const void* m_motion;

public:
    const hkpCdBody* m_parent;
};

inline hkpCdBody::hkpCdBody(const hkpShape* shape, const hkMotionState* motionState) {
    m_shape = shape;
    setMotionState(motionState);
    m_parent = nullptr;
    m_shapeKey = HK_INVALID_SHAPE_KEY;
}

inline hkpCdBody::hkpCdBody(const hkpShape* shape, const hkTransform* t) {
    m_shape = shape;
    setTransform(t);
    m_parent = nullptr;
    m_shapeKey = HK_INVALID_SHAPE_KEY;
}

inline const hkTransform& hkpCdBody::getTransform() const {
    return *static_cast<const hkTransform*>(m_motion);
}

inline const hkpShape* hkpCdBody::getShape() const {
    return m_shape;
}

inline const hkpCollidable* hkpCdBody::getRootCollidable() const {
    const hkpCdBody* body = this;
    while (body->m_parent) {
        body = body->m_parent;
    }
    return reinterpret_cast<const hkpCollidable*>(body);
}

inline hkpShapeKey hkpCdBody::getShapeKey() const {
    return m_shapeKey;
}

inline hkpShapeKey hkpCdBody::getTopLevelShapeKey() const {
    const hkpCdBody* body = this;
    const hkpCdBody* top = body;
    while (body->m_parent) {
        top = body;
        body = body->m_parent;
    }
    return top->m_shapeKey;
}

inline const hkpCdBody* hkpCdBody::getParent() const {
    return m_parent;
}

inline hkpCdBody::hkpCdBody(const hkpCdBody* parent) {
    m_parent = parent;
    m_motion = parent->m_motion;
}

inline hkpCdBody::hkpCdBody(const hkpCdBody* parent, const hkMotionState* ms) {
    m_parent = parent;
    setMotionState(ms);
}

inline hkpCdBody::hkpCdBody(const hkpCdBody* parent, const hkTransform* t) {
    m_parent = parent;
    setTransform(t);
}

inline void hkpCdBody::setShape(const hkpShape* shape, hkpShapeKey key) {
    m_shape = shape;
    m_shapeKey = key;
}

inline const hkMotionState* hkpCdBody::getMotionState() const {
    return static_cast<const hkMotionState*>(m_motion);
}

inline void hkpCdBody::setMotionState(const hkMotionState* state) {
    m_motion = state;
}

inline void hkpCdBody::setTransform(const hkTransform* t) {
    m_motion = t;
}
