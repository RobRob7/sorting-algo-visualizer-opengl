#include "bubblesort.h"

//--- PUBLIC ---//
void BubbleSort::attach(std::vector<float>* values)
{
    vals_ = values;
    reset();
} // end of attach()

bool BubbleSort::step()
{
    // check for sorting done
    if (!vals_ || vals_->empty()) return true;

    // ensure valid number of passes
    if (i_ < vals_->size() - 1)
    {
        // ensure valid index of current comparison
        if (j_ < vals_->size() - i_ - 1)
        {
            // compare neighbors (check for out of order)
            if ((*vals_)[j_] > (*vals_)[j_ + 1])
            {
                // swap neighbors
                std::swap((*vals_)[j_], (*vals_)[j_ + 1]);
            }
            ++j_;
        }
        // pass finished
        else
        {
            j_ = 0;
            ++i_;
        }
        // still sorting
        return false;
    }
    // finished sorting
    return true;
} // end of step()

void BubbleSort::reset()
{
    i_ = 0;
    j_ = 0;
} // end of reset()