#include "selectionsort.h"

//--- PUBLIC ---//
void SelectionSort::attach(std::vector<float>* values)
{
    vals_ = values;
    reset();
} // end of attach()

bool SelectionSort::step()
{
    // check for sorting done
    if (!vals_ || vals_->empty()) return true;

    // outer loop index (outer pass)
    if (i_ < vals_->size() - 1)
    {
        // check unsorted portion of vector
        if (j_ < vals_->size())
        {
            // compare current element to current minimum
            if ((*vals_)[j_] < (*vals_)[minIndex_])
            {
                // update min index
                minIndex_ = j_;
            }
            ++j_;
        }
        // finished scan of unsorted portion
        else
        {
            // swap min into place
            std::swap((*vals_)[i_], (*vals_)[minIndex_]);

            // move to next pass
            ++i_;
            j_ = i_ + 1;
            minIndex_ = i_;
        }
        // sorting still ongoing
        return false;
    }
    // sorting done
    return true;
} // end of step()

void SelectionSort::reset()
{
    i_ = 0;
    j_ = i_ + 1;
    minIndex_ = i_;
} // end of reset()