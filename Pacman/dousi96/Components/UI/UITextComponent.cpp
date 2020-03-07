#include "UITextComponent.h"
#include "../../../Drawer.h"

UITextComponent::UITextComponent()
{
	this->drawer = nullptr;
	this->screenPositionX = 0;
	this->screenPositionY = 0;
}

UITextComponent::~UITextComponent()
{
}

void UITextComponent::Draw() const
{
	this->drawer->DrawText(text.c_str(), fontPath, screenPositionX, screenPositionY);
}

void UITextComponent::SetDrawer(Drawer* drawer)
{
	if (drawer == nullptr) 
	{
		return;
	}
	this->drawer = drawer;
}

void UITextComponent::SetFont(const char* fontPath)
{
	this->fontPath = fontPath;
}

unsigned int UITextComponent::GetScreenPositionX() const
{
	return this->screenPositionX;
}

unsigned int UITextComponent::GetScreenPositionY() const
{
	return this->screenPositionY;
}

void UITextComponent::SetScreenPosition(const unsigned int x, const unsigned int y)
{
	this->screenPositionX = x;
	this->screenPositionY = y;
}

void UITextComponent::SetText(const std::string& text)
{
	this->text = text;
}
