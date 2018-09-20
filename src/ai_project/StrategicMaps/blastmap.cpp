#include "StrategicMaps/blastmap.h"


BlastMap::BlastMap(const HeatMap &myWalkableMap, std::vector<Bomb*> myBombs)
    : HeatMap(myWalkableMap.getLayout(), 100) 
{
    // Step 1: adjust the walkable map because a blast passes through a bomb according to the rules
    HeatMap myWalkCopy = myWalkableMap;
    for (auto e : myBombs)
    {
        Location bombLoc = e->getLocation();
        myWalkCopy.setValueByLocation(1, bombLoc);
    }

    // Step 2: for every action (up down left right, update the blast map
    // the code has to be refactored. (it has too many repetitions which can cause many errors)
    for (auto e : myBombs)
    {
        // add blast timer at the bomb location
        Location bombLoc = e->getLocation();
        int bombDuration = e->getDuration();
        int bombPower = 3;
        // add blast timer at the bomb location
        int durationHere = this->getValueByLocation(bombLoc);
        int durationSet = std::min(durationHere, bombDuration);
        this->setValueByLocation(durationSet, bombLoc);
        //this->setValueByLocation(bombDuration,bombLoc);

        // I think that a bomb acts as a wall so that the blast of another bomb does not reach it
        //m_BlastMap[getIndexByLocation(bombLoc)] = std::min( m_BlastMap[getIndexByLocation(bombLoc)], bombDuration);

        // add blasts in the up direction
        Location locUp = bombLoc;
        locUp.y += -1;
        int n_up = 1;
        while (locUp.y >= 0 && myWalkCopy.getValueByLocation(locUp) && n_up <= bombPower )
        {
            int durationUp = this->getValueByLocation(locUp);
            int durationSet = std::min(durationUp, bombDuration);
            this->setValueByLocation(durationSet, locUp);
            locUp.y += -1;
            n_up += 1;
        }
        //clear locUp?/

        // add blasts in the down direction
        Location locDown = bombLoc;
        locDown.y += 1;
        n_up = 1;
        while (unsigned(locDown.y) < this->getNRow() && myWalkCopy.getValueByLocation(locDown) && n_up <= bombPower )
        {

            int durationDown = this->getValueByLocation(locDown);
            int durationSet = std::min(durationDown, bombDuration);
            this->setValueByLocation(durationSet, locDown);
            locDown.y += 1;
            n_up += 1;
        }

        // add blasts in the left direction
        Location locLeft = bombLoc;
        locLeft.x += -1;
        n_up = 1;
        while (locLeft.x >= 0  && myWalkCopy.getValueByLocation(locLeft) && n_up <= bombPower )
        {
            int durationLeft = this->getValueByLocation(locLeft);
            int durationSet = std::min(durationLeft, bombDuration);
            this->setValueByLocation(durationSet, locLeft);
            locLeft.x += -1;
            n_up += 1;
        }

        // add blasts in the right direction
        Location locRight = bombLoc;
        locRight.x += 1;
        n_up = 1;
        while (unsigned(locRight.x) < this->getNCol() && myWalkCopy.getValueByLocation(locRight) && n_up <= bombPower )
        {
            int durationRight = this->getValueByLocation(locRight);
            int durationSet = std::min(durationRight, bombDuration);
            this->setValueByLocation(durationSet, locRight);
            //this->setValueByLocation(bombDuration, locRight);
            locRight.x += 1;
            n_up += 1;
        }

    }
}




