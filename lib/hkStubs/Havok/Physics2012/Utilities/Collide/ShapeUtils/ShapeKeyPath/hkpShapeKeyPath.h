#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Collide/Shape/hkpShape.h>
#include <Havok/Physics2012/Collide/Shape/hkpShapeBuffer.h>

class hkpContactPointEvent;
struct hkpRootCdPoint;
struct hkpShapeRayBundleCastOutput;
struct hkpWorldRayCastOutput;

class hkpShapeKeyPath {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpShapeKeyPath)

    class Iterator;

    hkpShapeKeyPath(const hkpContactPointEvent& event, int bodyIdx);
    explicit hkpShapeKeyPath(const hkpWorldRayCastOutput& output);
    hkpShapeKeyPath(const hkpShape* shape, const hkpShapeRayCastOutput& output);

    hkpShapeKey getShapeKey(int keyIndex) const;

    Iterator getIterator() const;

    void getShapes(int maxShapesOut, hkpShapeBuffer* buffers, const hkpShape** shapesOut,
                   int& numShapesOut);

    class Iterator {
    public:
        HK_DECLARE_CLASS_ALLOCATOR(Iterator)

        friend class hkpShapeKeyPath;

        /// Returns nullptr if the iterator is invalid.
        const hkpShape* getShape() const;

        /// @warning This can invalidate the shape.
        void next();

        hkBool isValid() const;

    private:
        Iterator(const hkpShapeKeyPath* path, const hkpShape* rootShape);
        void nextImpl(hkpShapeBuffer* buf);

        const hkpShapeKeyPath* m_path;
        const hkpShape* m_currentShape;
        int m_currentKeyIdx;
        hkBool m_isValid;
        hkpShapeBuffer m_tempBuffer;
    };

private:
    void init(const hkpShape* shape, const hkpShapeKey* keys, int maxKeys);

    const hkpShape* m_rootShape;
    const hkpShapeKey* m_keys;
    int m_numKeys;
    hkBool m_isOrderLeafToRoot;
};

inline hkpShapeKeyPath::Iterator hkpShapeKeyPath::getIterator() const {
    return {this, m_rootShape};
}

inline const hkpShape* hkpShapeKeyPath::Iterator::getShape() const {
    return m_currentShape;
}

inline void hkpShapeKeyPath::Iterator::next() {
    return nextImpl(&m_tempBuffer);
}

inline hkBool hkpShapeKeyPath::Iterator::isValid() const {
    return m_isValid;
}
