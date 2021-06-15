#include "KingSystem/Resource/Actor/resResourceASList.h"
#include "KingSystem/Resource/Actor/resResourceAS.h"

namespace ksys::res {

namespace {
[[maybe_unused]] sead::SafeArray<sead::FixedSafeString<128>, 3> sStrings;
}

ASList::ASList() : ParamIO("aslist", 0) {}

ASList::~ASList() {
    mASDefines.freeBuffer();
    for (auto& cf : mCFDefines) {
        cf.posts.freeBuffer();
        cf.excepts.freeBuffer();
    }
    mCFDefines.freeBuffer();
    mAddReses.freeBuffer();
}

void ASList::doCreate_(u8* buffer, u32 buffer_size, sead::Heap* heap) {}

bool ASList::parse_(u8* data, size_t size, sead::Heap* heap) {
    if (!data)
        return false;

    agl::utl::ResParameterArchive archive{data};
    const auto root = archive.getRootList();

    const auto ASDefines = agl::utl::getResParameterList(root, "ASDefines");
    auto ASDefine_name = sead::FixedSafeString<32>{"ASDefine_"};
    const auto ASDefine_prefix_len = ASDefine_name.calcLength();
    if (!ASDefines.ptr())
        return true;
    const auto ASDefines_num = ASDefines.getResParameterObjNum();
    if (ASDefines_num != 0) {
        if (!mASDefines.tryAllocBuffer(ASDefines_num, heap))
            return false;
        for (auto it = mASDefines.begin(), end = mASDefines.end(); it != end; ++it) {
            it->name.init("", "Name", "", &it->obj);
            it->file_name.init("", "Filename", "", &it->obj);
            it->as = nullptr;

            ASDefine_name.trim(ASDefine_prefix_len);
            ASDefine_name.appendWithFormat("%d", it.getIndex());
            mASDefinesList.addObj(&it->obj, ASDefine_name);
        }
        addList(&mASDefinesList, "ASDefines");

        const auto CFDefines = agl::utl::getResParameterList(root, "CFDefines");
        if (int CFDefines_num;
            CFDefines.ptr() && (CFDefines_num = CFDefines.getResParameterListNum()) != 0) {
            if (!mCFDefines.tryAllocBuffer(CFDefines_num, heap))
                return false;

            auto CFDefine_name = sead::FixedSafeString<32>{"CFDefine_"};
            const auto CFDefine_prefix_len = CFDefine_name.calcLength();

            auto CFPost_name = sead::FixedSafeString<32>{"CFPost_"};
            const auto CFPost_prefix_len = CFPost_name.calcLength();

            auto Name_name = sead::FixedSafeString<32>{"Name_"};
            const auto Name_prefix_len = Name_name.calcLength();

            for (auto it = mCFDefines.begin(), end = mCFDefines.end(); it != end; ++it) {
                CFDefine_name.trim(CFDefine_prefix_len);
                CFDefine_name.appendWithFormat("%d", it.getIndex());
                mCFDefinesList.addList(&it->list, CFDefine_name);
                const auto CFDefine = agl::utl::getResParameterList(CFDefines, CFDefine_name);

                const auto CFPosts = agl::utl::getResParameterList(CFDefine, "CFPosts");
                if (int num; CFPosts.ptr() && (num = CFPosts.getResParameterObjNum()) != 0) {
                    if (!it->posts.tryAllocBuffer(num, heap))
                        return false;
                    for (auto post = it->posts.begin(), post_end = it->posts.end();
                         post != post_end; ++post) {
                        post->name.init("", "Name", "", &post->obj);
                        post->frame.init(0, "Frame", "", &post->obj);
                        post->start_frame_rate.init(0, "StartFrameRate", "", &post->obj);

                        CFPost_name.trim(CFPost_prefix_len);
                        CFPost_name.appendWithFormat("%d", post.getIndex());
                        it->posts_list.addObj(&post->obj, CFPost_name);
                    }
                }

                const auto CFExcepts = agl::utl::getResParameterObj(CFDefine, "CFExcepts");
                if (int num; CFExcepts.ptr() && (num = CFExcepts.getNum()) != 0) {
                    if (!it->excepts.tryAllocBuffer(num, heap))
                        return false;
                    for (auto except = it->excepts.begin(), except_end = it->excepts.end();
                         except != except_end; ++except) {
                        Name_name.trim(Name_prefix_len);
                        Name_name.appendWithFormat("%d", except.getIndex());
                        except->name.init("", Name_name, "", &it->excepts_obj);
                    }
                }

                it->name.init("", "Name", "", &it->pre_obj);
                it->list.addObj(&it->pre_obj, "CFPre");
                it->list.addList(&it->posts_list, "CFPosts");
                it->list.addObj(&it->excepts_obj, "CFExcepts");
            }

            addList(&mCFDefinesList, "CFDefines");
        }
    }

    const auto AddReses = agl::utl::getResParameterList(root, "AddReses");
    if (int num; AddReses.ptr() && (num = AddReses.getResParameterObjNum()) != 0) {
        if (!mAddReses.tryAllocBuffer(num, heap))
            return false;

        auto AddRes_name = sead::FixedSafeString<32>{"AddRes_"};
        const auto AddRes_prefix_len = AddRes_name.calcLength();
        for (auto it = mAddReses.begin(), end = mAddReses.end(); it != end; ++it) {
            it->anim.init("", "Anim", "", &it->obj);
            it->retarget_model.init("", "RetargetModel", "", &it->obj);
            it->retarget_no_correct.init(false, "RetargetNoCorrect", "", &it->obj);

            AddRes_name.trim(AddRes_prefix_len);
            AddRes_name.appendWithFormat("%d", it.getIndex());
            mAddResesList.addObj(&it->obj, AddRes_name);
        }
        addList(&mAddResesList, "AddReses");
    }

    if (agl::utl::getResParameterObj(root, "Common").ptr()) {
        const sead::SafeString name = "RateAll";
        const sead::SafeString label = "";
        mCommon->rate_all.init(1.0, name, label, &mCommon->obj);
        addObj(&mCommon->obj, "Common");
    } else {
        mCommon->rate_all = 1.0;
    }

    applyResParameterArchive(agl::utl::ResParameterArchive{data});
    return true;
}

bool ASList::finishParsing_() {
    return true;
}

bool ASList::m7_() {
    for (auto& as : mASDefines)
        as.as = nullptr;

    _2b0 = 0;
    _2b1 = 0;
    _2b2 = 0;
    _2b3 = 0;
    return true;
}

void ASList::addAS_(s32 index, AS* as) {
    mASDefines[index].as = as;

    _2b0 = _2b0 > as->_3b8 ? _2b0 : as->_3b8;

    const auto as_counter = as->_3b9;
    if (_2b1 == 0) {
        _2b1 = as_counter;
        _2b3 = as->_3bb;
    } else {
        u8* flags1;
        u8* flags2;
        if (as_counter > _2b1) {
            _2b1 = as_counter;
            flags1 = &as->_3bb;
            flags2 = &_2b3;
        } else {
            flags1 = &_2b3;
            flags2 = &as->_3bb;
        }

        for (int i = 0; i < 6; ++i) {
            const auto mask = 1u << i;
            if ((*flags1 & mask) == 0 && (*flags2 & mask) != 0) {
                _2b3 |= mask;
                _2b1++;
            }
        }
    }

    _2b2 |= as->_3ba;
}

const char* ASList::getASFileName(const sead::SafeString& name) const {
    const int idx = findASDefine(name);
    if (idx == -1)
        return nullptr;
    return mASDefines[idx].getFileName();
}

int ASList::findASDefine(const sead::SafeString& name) const {
    return mASDefines.binarySearch(
        name, +[](const ASDefine& define, const sead::SafeString& key) {
            return define.name->compare(key);
        });
}

int ASList::findCFDefine(const sead::SafeString& name) const {
    return mCFDefines.binarySearch(
        name, +[](const CFDefine& define, const sead::SafeString& key) {
            return define.name->compare(key);
        });
}

int ASList::CFExcept::compare(const ASList::CFExcept& o, const sead::SafeString& n) {
    return o.name->compare(n);
}

int ASList::CFPost::compare(const ASList::CFPost& o, const sead::SafeString& n) {
    return o.name->compare(n);
}

bool ASList::getCFDefineInfo(float* frame, float* start_frame_value, const sead::SafeString& name,
                             const sead::SafeString& post_name, bool* is_default) const {
    const int idx = findCFDefine(name);
    *is_default = false;
    if (idx == -1)
        return false;

    const auto& cfdefine = mCFDefines[idx];

    const int except_idx = cfdefine.excepts.binarySearch(post_name, CFExcept::compare);
    if (except_idx >= 0)
        return false;

    const CFPost* post = nullptr;
    const int post_idx = cfdefine.posts.binarySearch(post_name, CFPost::compare);
    if (post_idx != -1) {
        post = std::addressof(cfdefine.posts[post_idx]);
    } else {
        post = std::addressof(cfdefine.posts[0]);
        if (!post->name->isEmpty())
            return false;
        *is_default = true;
    }

    if (!post)
        return false;

    *frame = *post->frame;
    *start_frame_value = *post->start_frame_rate;
    return true;
}

}  // namespace ksys::res
