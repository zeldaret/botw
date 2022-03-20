#pragma once

enum hkpPhantomType {
    /// hkpAabbPhantom
    HK_PHANTOM_AABB = 0,

    /// hkpSimpleShapePhantom
    HK_PHANTOM_SIMPLE_SHAPE = 1,

    /// hkpCachingShapePhantom
    HK_PHANTOM_CACHING_SHAPE = 2,

    /// User-defined types
    HK_PHANTOM_USER0,
    HK_PHANTOM_USER1,
    HK_PHANTOM_USER2,
    HK_PHANTOM_USER3,
    HK_PHANTOM_USER4,
    HK_PHANTOM_USER5,
    HK_PHANTOM_USER6,
    HK_PHANTOM_USER7,
    HK_PHANTOM_USER8,
    HK_PHANTOM_USER9,

    HK_PHANTOM_MAX_ID
};
