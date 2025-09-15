#ifndef IVIEW_H
#define IVIEW_H

// pure abstract IView interface
class IView
{
public:
	virtual ~IView() = default;
	virtual void upload() = 0;
	virtual void onResize(int width, int height) = 0;
};

#endif