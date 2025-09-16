#include "sortermodel.h"

//--- PUBLIC ---//
SorterModel::SorterModel(unsigned int numOfLines, unsigned int scrWidth, unsigned int scrHeight)
{
	// vertices
	vertices_ =
	{
		// position							// color
		0.0f, 0.0f, 0.0f,					0.0f, 0.0f, 1.0f,
		0.0f, (float)scrHeight, 0.0f,		1.0f, 1.0f, 1.0f
	};

	// set new vector size
	linePositions_.resize(numOfLines);
	lineScale_.resize(numOfLines);

	// horizontal spacing between the lines
	float horizontalSpacing = (float)scrWidth / linePositions_.size();
	for (size_t i = 0; i < linePositions_.size(); ++i)
	{
		linePositions_[i] = i * horizontalSpacing;
	} // end for

	// rand number gen [0, numOfLines-1]
	std::random_device randDev;
	std::mt19937 gen(randDev());
	std::uniform_int_distribution<int> distInt(0, numOfLines - 1);

	// min height difference of two lines
	float verticalSpacing = 1.0f / lineScale_.size();
	for (size_t i = 0; i < lineScale_.size(); ++i)
	{
		lineScale_[i] = 1.0f - distInt(gen) * verticalSpacing;
	} // end for

	// keep copy of original lineScale
	initialLineScale_ = lineScale_;
} // end of constructor

const std::vector<float>& SorterModel::getVertices() const
{
	return vertices_;
} // end of getVertices()

const std::vector<float>& SorterModel::getLinePositions() const
{
	return linePositions_;
} // end of getLinePositions()

const std::vector<float>& SorterModel::getLineScale() const
{
	return lineScale_;
} // end of getLineScale()

void SorterModel::updateForResize(unsigned int scrWidth, unsigned int scrHeight)
{
	// horizontal spacing between the lines
	float horizontalSpacing = (float)scrWidth / linePositions_.size();
	for (size_t i = 0; i < linePositions_.size(); ++i)
	{
		linePositions_[i] = i * horizontalSpacing;
	} // end for
} // end of updateForResize()

void SorterModel::setSortingAlgorithm(std::unique_ptr<ISorterModel> algo)
{
	// efficient move
	algo_ = std::move(algo);
	// if existing algorithm running
	if (algo_)
	{
		// set line scale to original positions, attach
		lineScale_ = initialLineScale_;
		algo_->attach(&lineScale_);

		// reset step counters
		algo_->reset();
	}
} // end of setSortingAlgorithm()

void SorterModel::resetSortingAlgorithm()
{
	// if existing algorithm running
	if (algo_)
	{
		// reset sorting instance
		algo_->reset();
	}
} // end of resetSortingAlgorithm()

bool SorterModel::step(int steps)
{
	// check for done sorting
	if (!algo_) return true;

	// bool for sorting done
	bool done = false;

	// compute steps each frame
	for (int s = 0; s < steps; ++s)
	{
		// check for done status
		done = algo_->step();

		// if done sorting, break
		if (done) break;
	} // end for
	return done;
} // end of step()