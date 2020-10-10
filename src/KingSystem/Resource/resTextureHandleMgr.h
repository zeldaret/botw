#pragma once

namespace ksys::res {

// TODO: very incomplete
class TextureHandleMgr {
public:
    virtual ~TextureHandleMgr();

    void clearAllCache();
};

}  // namespace ksys::res
