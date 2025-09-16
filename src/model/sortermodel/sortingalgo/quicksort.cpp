#include "quicksort.h"

//--- PUBLIC ---//
void QuickSort::attach(std::vector<float>* values)
{
    vals_ = values;
    reset();
} // end of attach()

bool QuickSort::step()
{
    if (!vals_ || vals_->empty()) return true;

    // If currently partitioning
    if (partitioning_) {
        if (j_ < hi_) {
            if ((*vals_)[j_] < (*vals_)[pivot_]) {
                ++i_;
                std::swap((*vals_)[i_], (*vals_)[j_]);
            }
            ++j_;
            return false; // still working in this partition
        }
        else {
            // Final pivot swap
            std::swap((*vals_)[i_ + 1], (*vals_)[pivot_]);
            int p = i_ + 1;

            // Push subranges onto stack
            if (p - 1 > lo_) stack_.push_back({ lo_, p - 1 });
            if (p + 1 < hi_) stack_.push_back({ p + 1, hi_ });

            partitioning_ = false;
        }
    }

    // If no active partition, grab next from stack
    if (!partitioning_ && !stack_.empty()) {
        auto [lo, hi] = stack_.back();
        stack_.pop_back();

        lo_ = lo;
        hi_ = hi;
        pivot_ = hi_;
        i_ = lo - 1;
        j_ = lo;

        partitioning_ = true;
        return false;
    }

    // If nothing left in stack, sorting is done
    return stack_.empty();
} // end of step()

void QuickSort::reset()
{
    stack_.clear();

    if (vals_ && !vals_->empty()) {
        stack_.push_back({ 0, (int)vals_->size() - 1 });
    }

    lo_ = -1;
    hi_ = -1;
    pivot_ = -1;
    i_ = -1;
    j_ = -1;
    partitioning_ = false;
} // end of reset()