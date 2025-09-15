#include "insertionsort.h"

//--- PUBLIC ---//
void InsertionSort::attach(std::vector<float>* values)
{
    vals_ = values;
    reset();
} // end of attach()

bool InsertionSort::step()
{
    // check for sorting done
    if (!vals_ || vals_->empty()) return true;

    // ensure valid number of passes
    if (i_ < vals_->size())
    {
        // ensure valid index of current comparison
        if (j_ > 0 && (*vals_)[j_] < (*vals_)[j_ - 1])
        {
            std::swap((*vals_)[j_], (*vals_)[j_ - 1]);
            --j_;
        }
        // pass finished
        else
        {
            ++i_;
            j_ = i_;
        }
        // still sorting
        return false;
    }
    // finished sorting
    return true;
} // end of step()

void InsertionSort::reset()
{
    i_ = 0;
    j_ = 0;
} // end of reset()