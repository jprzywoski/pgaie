#ifndef GOAL_FOLLOWPATH_H
#define GOAL_FOLLOWPATH_H

// -----------------------------------------------------------------------------
//
// Name:   Goal_FollowPath.h
//
// Author: Mat Buckland (www.ai-junkie.com)
//
// Desc:
// -----------------------------------------------------------------------------
#include "../Raven_Bot.h"
#include "../navigation/PathEdge.h"
#include "../navigation/Raven_PathPlanner.h"
#include "Goals/Goal_Composite.h"
#include "Raven_Goal_Types.h"

class Goal_FollowPath: public Goal_Composite<Raven_Bot>
{
private:
    // a local copy of the path returned by the path planner
    std::list<PathEdge> m_Path;

public:
    Goal_FollowPath(Raven_Bot *pBot, std::list<PathEdge> path);

    // the usual suspects
    void Activate();
    int Process();
    void Render();

    void Terminate() {}
};

#endif
