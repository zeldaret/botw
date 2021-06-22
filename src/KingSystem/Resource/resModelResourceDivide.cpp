#include "KingSystem/Resource/resModelResourceDivide.h"
#include "KingSystem/ActorSystem/actDebug.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Resource/resResourceMgrTask.h"
#include "KingSystem/Utils/Byaml/Byaml.h"

namespace ksys::res {

SEAD_SINGLETON_DISPOSER_IMPL(ModelResourceDivide)

ModelResourceDivide::~ModelResourceDivide() {
    if (mIter)
        delete mIter;
}

void ModelResourceDivide::init(sead::Heap* heap) {
    auto load_request = LoadRequest();
    load_request.mRequester = "ModelResourceDivide";
    load_request.mLoadCompressed = true;
    mHandle.load("System/Resource/ModelDivideTable.byml", &load_request);
    sead::DirectResource* table = mHandle.getResource();
    auto* cast_table = sead::DynamicCast<sead::DirectResource>(table);
    mIter = new (heap) al::ByamlIter(cast_table->getRawData());
}

const char* ModelResourceDivide::getModelResource(const sead::SafeString& model_name,
                                                  const sead::SafeString& fmdb_name) const {
    auto* debug = act::ActorDebug::instance();
    if (debug && !debug->hasFlag(act::ActorDebug::Flag::_20000000))
        return nullptr;

    sead::FormatFixedSafeString<128> model_path("Model/%s.bfres", model_name.cstr());
    if (ResourceMgrTask::instance()->isHostPath(model_path))
        return nullptr;

    al::ByamlIter model_iter{};
    if (!mIter->tryGetIterByKey(&model_iter, model_name.cstr()))
        return nullptr;

    sead::FormatFixedSafeString<128> fmdb_file_name("%s.fmdb", fmdb_name.cstr());

    for (int i = 0; i < model_iter.getSize(); ++i) {
        al::ByamlIter index_iter;
        if (!model_iter.tryGetIterByIndex(&index_iter, i))
            break;
        al::ByamlIter models_iter;
        if (!index_iter.tryGetIterByKey(&models_iter, "models"))
            break;
        al::ByamlIter fmdb_iter;
        const char* value;
        if (models_iter.tryGetIterByKey(&fmdb_iter, fmdb_file_name.cstr())) {
            if (index_iter.tryGetStringByKey(&value, "model_resource"))
                return value;
            return nullptr;
        }
    }
    return nullptr;
}

}  // namespace ksys::res
