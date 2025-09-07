#ifndef SORTERMODEL_H
#define SORTERMODEL_H

#include <vector>
#include <random>

class SorterModel
{
public:
	SorterModel(unsigned int numOfLines, unsigned int scrWidth, unsigned int scrHeight);

	const std::vector<float>& getVertices() const;
	const std::vector<float>& getLinePositions() const;
	const std::vector<float>& getLineScale() const;
	void updateForResize(unsigned int scrWidth, unsigned int scrHeight);

private:
	std::vector<float> vertices_;
	std::vector<float> linePositions_;
	std::vector<float> lineScale_;
};

#endif
