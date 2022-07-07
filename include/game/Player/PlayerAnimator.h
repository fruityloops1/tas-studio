#pragma once

#include "PlayerAnimFrameCtrl.h"
#include "sead/prim/seadSafeString.h"
#include "types.h"

class PlayerAnimator {
  public:
    void startAnim(const sead::SafeString& animName);
    void startAnimCommon(const sead::SafeString&);
    void startSubAnim(const sead::SafeString& animName);

    bool isAnim(const sead::SafeString& animName) const;
    bool isSubAnimEnd() const;

    float getAnimFrame() const;
    float getAnimFrameMax() const;
    float getAnimFrameRate() const;
    float getSubAnimFrame() const;
    float getBlendWeight(int index);

    void setAnimFrame(float frame);
    void setSubAnimFrame(float frame);
    void setBlendWeight(float, float, float, float, float, float);

    void forceCapOff();
    void forceCapOn();

    unsigned char padding_18[0x18];
    PlayerAnimFrameCtrl* mAnimFrameCtrl;
    undefined8 padding_4;
    char* mCurrentAnim;
    undefined padding_58[0x50];
    char* mCurrentSubAnim;
};