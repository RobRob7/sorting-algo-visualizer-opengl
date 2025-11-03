#ifndef ISORTERMODEL_H
#define ISORTERMODEL_H

#include <vector>

class ISorterModel
{
public:
    virtual ~ISorterModel() = default;

    // set line values when algorithm set, begin anew
    virtual void attach(std::vector<float>* values) = 0;

    // perform exactly one atomic step (comparison/swap/move)
    // return true when the array is fully sorted.
    virtual bool step() = 0;

    // reset internal state
    virtual void reset() = 0;
};
#endif
