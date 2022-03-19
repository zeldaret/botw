#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Collide/Shape/hkpShapeBase.h>

class hkpShapeKeyTable {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpShapeKeyTable)
    HK_DECLARE_REFLECTION()

    enum { NUM_LISTS = 32, NUM_SLOTS_PER_BLOCK = 63 };

    // A block of shape key slots.
    // Free slots have a value of HK_INVALID_SHAPEKEY.
    struct Block {
        HK_DECLARE_CLASS_ALLOCATOR(Block)
        HK_DECLARE_REFLECTION()

        Block();
        ~Block();

        alignas(16) hkpShapeKey m_slots[NUM_SLOTS_PER_BLOCK];
        Block* m_next;
    };

    enum { NUM_BYTES_PER_BLOCK = sizeof(Block) };

    hkpShapeKeyTable();
    explicit hkpShapeKeyTable(hkFinishLoadedObjectFlag flag);
    ~hkpShapeKeyTable();

    void insert(hkpShapeKey key);
    void remove(hkpShapeKey key);
    bool exists(hkpShapeKey key) const;

    bool isEmpty() const { return (m_occupancyBitField == 0); }
    void clear();
    void getDistribution(hkArray<int>& counts) const;

protected:
    Block* m_lists;
    hkUint32 m_occupancyBitField;
};
