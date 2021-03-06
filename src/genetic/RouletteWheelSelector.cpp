#include <cassert>
#include "RouletteWheelSelector.hpp"
#include "utils/Random.hpp"

namespace tsp
{

    RouletteWheelSelector::RouletteWheelSelector()
    {
    }

    RouletteWheelSelector::~RouletteWheelSelector()
    {
    }

    void RouletteWheelSelector::select(const Population &population,
                                       std::vector<int> &parents)
    {
        unsigned int parentCount = 0;
        while(parentCount < parents.size()) {
            // generate target fitness value
            double selectFitness = Random::nextDouble();
            double accumFitness = 0;
            for(unsigned int i = 0; i < population.getIndividuals().size(); ++i) {
                // calculated accumulated fitness
                accumFitness += population.getIndividuals()[i].getNormalizedFitness();
                // check if random fitness is in interval
                if(accumFitness >= selectFitness) {
                    // check if previous parent was same
                    if(parentCount % 2 == 1 && parents[parentCount - 1] == static_cast<int>(i))
                        continue;
                    parents[parentCount] = i;
                    ++parentCount;
                    break;
                }
            }
        }
    }

}
