#pragma once

#include <container/seadBuffer.h>
#include <prim/seadSafeString.h>

namespace ksys::act {
class Actor;
}

namespace ksys::act::ai {

class Query;
struct QueryFactory;

class Queries {
public:
    Queries();
    ~Queries();

    void finalize();

    bool init(Actor* actor, sead::Heap* heap);
    bool updateForPreDelete() const;
    void onPreDelete() const;

    const sead::Buffer<Query*>& getClasses() const { return mClasses; }
    Query* getQuery(const sead::SafeString& name) const;

    static QueryFactory* getFactory(const sead::SafeString& name);
    static void setFactories(int count, QueryFactory* factories);

private:
    static sead::Buffer<QueryFactory> sFactories;
    sead::Buffer<Query*> mClasses;
    // Non-owning buffer.
    sead::Buffer<Query*> mOnPreDeleteCbs;
    // Non-owning buffer.
    sead::Buffer<Query*> mUpdateForPreDeleteCbs;
};

}  // namespace ksys::act::ai
