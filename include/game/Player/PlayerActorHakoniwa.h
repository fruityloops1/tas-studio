#pragma once
/**
 * @file PlayerActorBase.h
 * @brief Main Class for the PlayerActor (Mario)
 * Player Pose: TQGMSV
 *  Vtable loc: 1D780C0
 */

#include "HackCap.h"
#include "PlayerActorBase.h"
#include "PlayerAnimator.h"
#include "PlayerInput.h"
#include "PlayerModelKeeper.h"
#include "PlayerRecoverySafetyPoint.h"
#include "al/LiveActor/LiveActor.h"
#include "game/Interfaces/IUseDimension.h"
#include "game/Player/PlayerColliderHakoniwa.h"
#include "game/Player/PlayerDamageKeeper.h"
#include "game/Player/PlayerHackKeeper.h"

class PlayerStateJump {
  public:
    spad(gap, 0x60);
    PlayerAnimator* mPlayerAnimator;
};

class PlayerActorHakoniwa : public PlayerActorBase, public IUseDimension {
  public:
    int* getPortNo(void) const;
    void startDemoMainShineGet();
    void endDemoMainShineGet();
    void startDemoPuppetable();
    void endDemoPuppetable();
    void startDemoShineGet();
    void tryActionStartSpinAttack();
    spad(gap, 0x30);
    PlayerInput* mPlayerInput; // 0x138
    spad(gap2, 0x8);
    HackCap* mHackCap; // 0x148
    spad(gap3, 0x6);
    PlayerModelKeeper* mPlayerModelKeeper; // 0x158
    spad(gap4, 0x8);
    PlayerAnimator* mPlayerAnimator; // 0x168
    PlayerColliderHakoniwa* mPlayerCollider;
    spad(gap5, 0x20);
    PlayerDamageKeeper* mDamageKeeper;
    spad(gap6, 0x68);
    PlayerHackKeeper* mHackKeeper;
    spad(gap7, 0x5F);
    PlayerRecoverySafetyPoint* mPlayerRecoverPoint; // 0x270
    spad(gap8, 0x50);
    PlayerStateJump* mPlayerStateJump;
    spad(gap9, 0x238);
};