#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "../isortermodel/isortermodel.h"

#include <vector>

class QuickSort : public ISorterModel
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
    // stack of ranges
    std::vector<std::pair<int, int>> stack_;
    // current range
    int lo_ = -1, hi_ = -1;
    // pivot index
    int pivot_ = -1;
    // algorithm step counters
    size_t i_ = -1, j_ = -1;
    // is partitioning bool
    bool partitioning_ = false;
};

#endif
