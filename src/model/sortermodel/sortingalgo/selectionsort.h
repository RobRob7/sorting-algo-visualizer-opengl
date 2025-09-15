#ifndef SELECTIONSORT_H
#define SELECTIONSORT_H

#include "../isortermodel/isortermodel.h"

class SelectionSort : public ISorterModel
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
    size_t i_ = 0, j_ = 1;
    // minimum element index
    size_t minIndex_ = 0;
};

#endif
