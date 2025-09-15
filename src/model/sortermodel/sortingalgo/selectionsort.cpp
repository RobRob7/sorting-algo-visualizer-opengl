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

    if (i_ < vals_->size() - 1) {
        if (j_ < vals_->size()) {
            // Compare current element to current minimum
            if ((*vals_)[j_] < (*vals_)[minIndex_]) {
                minIndex_ = j_;
            }
            ++j_;
        }
        else {
            // Done scanning unsorted part, swap min into place
            std::swap((*vals_)[i_], (*vals_)[minIndex_]);

            // Move to next pass
            ++i_;
            j_ = i_ + 1;
            minIndex_ = i_;
        }
        return false; // still sorting
    }

    return true; // all sorted
} // end of step()

void SelectionSort::reset()
{
    i_ = 0;
    j_ = i_ + 1;
    minIndex_ = i_;
} // end of reset()