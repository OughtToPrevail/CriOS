#ifndef OSTEST_WINDOW_H
#define OSTEST_WINDOW_H

#include "VerticalLayout.h"

class Window : public VerticalLayout
{
public:
	explicit Window(Layout* layout);

	bool isAutonomousComponent() const override;
};

#endif //OSTEST_WINDOW_H
