#pragma once

#include "al/actor/IUseName.h"
#include "al/audio/AudioKeeper.h"
#include "al/camera/CameraDirector.h"
#include "al/effect/EffectKeeper.h"
#include "al/hio/HioNode.h"
#include "al/layout/LayoutKeeper.h"
#include "al/layout/LayoutSceneInfo.h"
#include "al/message/MessageSystem.h"
#include "al/nerve/Nerve.h"
#include "al/nerve/NerveKeeper.h"
#include "al/scene/SceneObjHolder.h"
#include "sead/prim/seadSafeString.h"

#include "al/LiveActor/LiveActor.h"
#include "al/layout/LayoutActionKeeper.h"

namespace al {
;

class LayoutTextPaneAnimator {
};

class LayoutExecuteInfo {
};

class LayoutActor : public al::IUseHioNode, public al::IUseNerve, public al::IUseLayout, public al::IUseLayoutAction, public al::IUseMessageSystem, public al::IUseCamera, public al::IUseAudioKeeper, public al::IUseEffectKeeper, public al::IUseSceneObjHolder {
public:
    LayoutActor(const char* name);

    virtual al::NerveKeeper* getNerveKeeper() const { return mNerveKeeper; }

    virtual void appear();
    virtual void kill();
    virtual void movement();
    virtual void calcAnim(bool);

    virtual const char* getName() const { return mName.cstr(); }
    virtual al::EffectKeeper* getEffectKeeper() const { return mEffectKeeper; }
    virtual al::AudioKeeper* getAudioKeeper() const { return mAudioKeeper; }
    virtual al::LayoutActionKeeper* getLayoutActionKeeper() const { return mLytActionKeeper; }
    virtual al::LayoutKeeper* getLayoutKeeper() const { return mLytKeeper; }

    void initLayoutKeeper(al::LayoutKeeper*);
    void initActionKeeper();
    void initTextPaneAnimator(al::LayoutTextPaneAnimator*);
    void initExecuteInfo(al::LayoutExecuteInfo*);
    void initLayoutPartsActorKeeper(int);
    void initEffectKeeper(al::EffectKeeper*);
    void initAudioKeeper(al::AudioKeeper*);
    void initNerve(al::Nerve const*, int);
    void setMainGroupName(char const*);
    void syncAction();

    virtual al::CameraDirector* getCameraDirector() const { return mLytSceneInfo->mCameraDirector; }
    virtual al::SceneObjHolder* getSceneObjHolder() const { return mLytSceneInfo->mSceneObjHolder; }
    virtual al::MessageSystem* getMessageSystem() const { return mLytSceneInfo->mMessageSystem; }

    virtual void control();

    sead::FixedSafeString<0x80> mName; // 0x40
    NerveKeeper* mNerveKeeper; // 0xD8
    LayoutKeeper* mLytKeeper; // 0xE0
    LayoutActionKeeper* mLytActionKeeper; // 0xE8
    void* mTextPaneAnimator; // 0xF0
    EffectKeeper* mEffectKeeper; // 0xF8
    AudioKeeper* mAudioKeeper; // 0x100
    void* mExecuteInfo; // 0x108
    void* mHitReactionKeeper; // 0x110
    LayoutSceneInfo* mLytSceneInfo; // 0x118
    void* mLytPartsActorKeeper; // 0x120
    bool mIsAlive; // 0x128
};
} // namespace al

static_assert(sizeof(al::LayoutActor) == 0x130, "");