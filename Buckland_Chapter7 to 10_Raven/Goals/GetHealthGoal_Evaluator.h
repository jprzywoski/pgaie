#ifndef RAVEN_HEALTH_EVALUATOR
#define RAVEN_HEALTH_EVALUATOR

// -----------------------------------------------------------------------------
//
// Name:   GetHealthGoal_Evaluator.h
//
// Author: Mat Buckland (www.ai-junkie.com)
//
// Desc:   class to calculate how desirable the goal of fetching a health item
// is
// -----------------------------------------------------------------------------

#include "../Raven_Bot.h"
#include "Goal_Evaluator.h"

class GetHealthGoal_Evaluator: public Goal_Evaluator
{
public:
    GetHealthGoal_Evaluator(double bias): Goal_Evaluator(bias) {}
    double CalculateDesirability(Raven_Bot *pBot);

    void SetGoal(Raven_Bot *pEnt);

    void RenderInfo(Vector2D Position, Raven_Bot *pBot);
};

#endif
