#ifndef OSTEST_DESKTOPPROGRAM_H
#define OSTEST_DESKTOPPROGRAM_H

#include "VerticalLayout.h"
#include "Label.h"
#include "ImageView.h"

class DesktopProgram : public VerticalLayout
{
public:
	DesktopProgram(const char* name, const OSImage& icon);

	bool isAutonomousComponent() const override;
private:
	ImageView _icon;
	Label _label;
};


#endif //OSTEST_DESKTOPPROGRAM_H
