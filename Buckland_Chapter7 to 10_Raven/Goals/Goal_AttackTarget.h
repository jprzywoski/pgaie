#ifndef GOAL_ATTACKTARGET_H
#define GOAL_ATTACKTARGET_H

// -----------------------------------------------------------------------------
//
// Name:   Goal_AttackTarget.h
//
// Author: Mat Buckland (ai-junkie.com)
//
// Desc:
//
// -----------------------------------------------------------------------------
#include "../Raven_Bot.h"
#include "Goals/Goal_Composite.h"
#include "Raven_Goal_Types.h"

class Goal_AttackTarget: public Goal_Composite<Raven_Bot>
{
public:
    Goal_AttackTarget(Raven_Bot *pOwner): Goal_Composite<Raven_Bot>(pOwner, goal_attack_target) {}
    void Activate();

    int Process();

    void Terminate()
    {
        m_iStatus = completed;
    }
};

#endif
