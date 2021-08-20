#pragma once

namespace ksys::res {

class ArchiveWork;

// TODO: very incomplete
class TextureHandleMgr {
public:
    virtual ~TextureHandleMgr();

    void preCalc();
    void calc();

    ArchiveWork* getArchiveWork() const;
    void clearAllCache();
};

}  // namespace ksys::res
