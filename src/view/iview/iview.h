#ifndef IVIEW_H
#define IVIEW_H

#include <glm/glm.hpp>

// pure abstract view interface
class IView
{
public:
	virtual ~IView() = default;
	virtual void upload() = 0;
	virtual void render(const glm::mat4& projection, const glm::mat4& view) = 0;
};

#endif