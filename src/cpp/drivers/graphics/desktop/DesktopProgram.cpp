#include "DesktopProgram.h"
#include "System.h"

DesktopProgram::DesktopProgram(const char* name, const OSImage& icon)
{
	this->setBackground(ColorPalette::transparent());
	this->setPositioning(Positioning::CENTER);

	this->_icon.setImage(icon);
	this->_label.setText(name);
	this->_label.setForeground(Theme::DESKTOP_TEXT_COLOR);
	this->add(this->_label);
	this->add(this->_icon);

	this->addEventHandler(EventType::ENTER,
						  [this](const Event& event)
						  {
							  this->setBackground(Theme::COMPONENT_BACKGROUND);
							  System::getSystem().getLogger().log(LogType::DEBUG, "enter %d", event.getType());
						  });
	this->addEventHandler(EventType::LEAVE,
						  [this](const Event& event)
						  {
							  (void) event;
							  this->setBackground(ColorPalette::transparent());
							  System::getSystem().getLogger().log(LogType::DEBUG, "leave");
						  });
	this->addEventHandler(EventType::DOUBLE_CLICK,
						  [](const Event& event)
						  {
							  (void) event;
							  System::getSystem().getLogger().log(LogType::DEBUG, "double click");
						  });
	this->addEventHandler(EventType::KEYBOARD,
						  [](const Event& event)
						  {
							  (void) event;
							  System::getSystem().getLogger().log(LogType::DEBUG, "Keyboard event");
						  });
}

bool DesktopProgram::isAutonomousComponent() const
{
	return true;
}
