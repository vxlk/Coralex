#include "component.h"
namespace ui {
Component::Component() noexcept{}

Component::~Component() noexcept{}

void Component::hide(){}

void Component::show(){}

void Component::userTriedToCloseWindow(){}

void Component::toFront(){}

void Component::toBack(){}

bool Component::isMouseOver() { return false; }

bool Component::isMouseButtonDown() { return false; }

bool Component::isMouseOverDragging() { return false; }

unsigned int Component::getMouseX() { return 0; }

unsigned int Component::getMouseY() { return 0; }

}//namespace ui