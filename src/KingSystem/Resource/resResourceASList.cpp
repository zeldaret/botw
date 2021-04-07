#include "KingSystem/Resource/resResourceASList.h"

namespace ksys::res {

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

}  // namespace ksys::res
