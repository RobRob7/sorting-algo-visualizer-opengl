#include "quicksort.h"

//--- PUBLIC ---//
void QuickSort::attach(std::vector<float>* values)
{
    vals_ = values;
    reset();
} // end of attach()

bool QuickSort::step()
{
    // no sorting to do
    if (!vals_ || vals_->empty()) return true;

    // if currently partitioning
    if (partitioning_)
    {
        // scanning from lo_ to hi_ - 1
        if (j_ < hi_)
        {
            // swap value into spot
            if ((*vals_)[j_] < (*vals_)[pivot_])
            {
                ++i_;
                std::swap((*vals_)[i_], (*vals_)[j_]);
            }
            ++j_;
            // still working in this partition
            return false;
        }
        // finished scan of range
        else
        {
            // final pivot swap
            std::swap((*vals_)[i_ + 1], (*vals_)[pivot_]);
            int p = i_ + 1;

            // push subranges onto stack
            if (p - 1 > lo_) stack_.push_back({ lo_, p - 1 });
            if (p + 1 < hi_) stack_.push_back({ p + 1, hi_ });

            // no longer partitioning
            partitioning_ = false;
        }
    }

    // no active partition, grab next from stack
    if (!partitioning_ && !stack_.empty())
    {
        // take next range in stack
        auto [lo, hi] = stack_.back();
        stack_.pop_back();
        lo_ = lo;
        hi_ = hi;
        pivot_ = hi_;
        i_ = lo - 1;
        j_ = lo;

        // partitioning start
        partitioning_ = true;

        // still sorting
        return false;
    }

    // stack is empty, sorting is done
    return stack_.empty();
} // end of step()

void QuickSort::reset()
{
    // clear previous stack contents
    stack_.clear();

    // initialize stack
    if (vals_ && !vals_->empty())
    {
        stack_.push_back({ 0, (int)vals_->size() - 1 });
    }

    // reset counters
    lo_ = -1;
    hi_ = -1;
    pivot_ = -1;
    i_ = -1;
    j_ = -1;

    // reset partitioning
    partitioning_ = false;
} // end of reset()