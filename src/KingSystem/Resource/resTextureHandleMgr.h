#pragma once

namespace ksys::res {

class ArchiveWork;

// TODO: very incomplete
class TextureHandleMgr {
public:
    virtual ~TextureHandleMgr();

    ArchiveWork* getArchiveWork() const;
    void clearAllCache();
};

}  // namespace ksys::res
