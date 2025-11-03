#ifndef SORTERMODEL_H
#define SORTERMODEL_H

#include "isortermodel.h"

#include <vector>
#include <random>
#include <functional>

class SorterModel
{
public:
	SorterModel(unsigned int numOfLines, unsigned int scrWidth, unsigned int scrHeight);

	// get vertices for each line
	const std::vector<float>& getVertices() const;
	// get line positions for each line
	const std::vector<float>& getLinePositions() const;
	// get line scale/height for each line
	const std::vector<float>& getLineScale() const;
	// update line positions with updated window size
	void updateForResize(unsigned int scrWidth, unsigned int scrHeight);

	// set sorting algorithm to use
	void setSortingAlgorithm(std::unique_ptr<ISorterModel> algo);
	// reset the sorting algorithm internal states
	void resetSortingAlgorithm();
	// number of steps per frame
	bool step(int steps = 1);

private:
	// vertices for each line
	std::vector<float> vertices_;
	// line positions for each line
	std::vector<float> linePositions_;
	// line scale/height for each line
	std::vector<float> lineScale_;
	// original line scale/height to revert back to
	std::vector<float> initialLineScale_;
	// algorithm to use
	std::unique_ptr<ISorterModel> algo_;
};

#endif
