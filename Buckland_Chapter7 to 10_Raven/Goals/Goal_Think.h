#ifndef GOAL_THINK_H
#define GOAL_THINK_H

// -----------------------------------------------------------------------------
//
// Name:   Goal_Think .h
//
// Author: Mat Buckland (www.ai-junkie.com)
//
// Desc:   class to arbitrate between a collection of high level goals, and
// to process those goals.
// -----------------------------------------------------------------------------
#include <string>
#include <vector>

#include "../Raven_Bot.h"
#include "2d/Vector2D.h"
#include "Goal_Evaluator.h"
#include "Goals/Goal_Composite.h"

class Goal_Think: public Goal_Composite<Raven_Bot>
{
private:
    typedef std::vector<Goal_Evaluator *> GoalEvaluators;

private:
    GoalEvaluators m_Evaluators;

public:
    Goal_Think(Raven_Bot *pBot);
    ~Goal_Think();

    // this method iterates through each goal evaluator and selects the one
    // that has the highest score as the current goal
    void Arbitrate();

    // returns true if the given goal is not at the front of the subgoal list
    bool notPresent(unsigned int GoalType) const;

    // the usual suspects
    int Process();
    void Activate();

    void Terminate() {}
    // top level goal types
    void AddGoal_MoveToPosition(Vector2D pos);
    void AddGoal_GetItem(unsigned int ItemType);
    void AddGoal_Explore();
    void AddGoal_AttackTarget();

    // this adds the MoveToPosition goal to the *back* of the subgoal list.
    void QueueGoal_MoveToPosition(Vector2D pos);

    // this renders the evaluations (goal scores) at the specified location
    void RenderEvaluations(int left, int top) const;
    void Render();
};

#endif
