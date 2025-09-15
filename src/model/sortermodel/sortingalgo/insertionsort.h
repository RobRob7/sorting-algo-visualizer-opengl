#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include "../isortermodel/isortermodel.h"

class InsertionSort : public ISorterModel
{
public:
    // set line values when algorithm set, begin anew
    void attach(std::vector<float>* values) override;

    // perform exactly one atomic step (comparison/swap/move)
    // return true when the array is fully sorted.
    bool step() override;

    // reset internal state
    void reset() override;

private:
    // value of lines
    std::vector<float>* vals_ = nullptr;
    // algorithm step counters
    size_t i_ = 0, j_ = 0;
};

#endif
