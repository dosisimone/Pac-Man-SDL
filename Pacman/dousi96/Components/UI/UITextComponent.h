#ifndef UITEXTCOMPONENT_H
#define UITEXTCOMPONENT_H

#include "../Component.h"
#include <string>

class Drawer;

class UITextComponent : public Component
{
private:
	const char* fontPath;
	std::string text;
	unsigned int screenPositionX = 0;
	unsigned int screenPositionY = 0;

public:
	UITextComponent();
	~UITextComponent() override;
	void Draw() const override;
	void Update(const float deltaTime) override {}
	void SetFont(const char* fontPath);
	unsigned int GetScreenPositionX() const;
	unsigned int GetScreenPositionY() const;
	void SetScreenPosition(const unsigned int x, const unsigned int y);
	void SetText(const std::string& text);
};
#endif // UITEXTCOMPONENT_H