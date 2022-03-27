#pragma once

class hkBaseObject {
public:
    HK_DECLARE_PLACEMENT_ALLOCATOR()

    HK_FORCE_INLINE explicit hkBaseObject(hkFinishLoadedObjectFlag flag) {}

    virtual ~hkBaseObject() = default;
    virtual void __first_virtual_table_function__() {}  // NOLINT(bugprone-reserved-identifier)

protected:
    HK_FORCE_INLINE hkBaseObject() = default;
};
