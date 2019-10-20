#pragma once

/// Describes an element of the user interface
class Component
{
public:
	Component() noexcept;

	virtual ~Component() noexcept;

	void hide();

	void show();

	virtual void userTriedToCloseWindow();

	virtual void toFront();

	virtual void toBack();

	virtual bool isMouseOver();

	virtual bool isMouseButtonDown();

	virtual bool isMouseOverDragging();

	unsigned int getMouseX();
	unsigned int getMouseY();

protected:

	bool isHidden = false;

};

