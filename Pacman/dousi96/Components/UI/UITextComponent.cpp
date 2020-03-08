#include "UITextComponent.h"
#include "../../GameController.h"
#include "../../../Drawer.h"

UITextComponent::UITextComponent()
{
	this->screenPositionX = 0;
	this->screenPositionY = 0;
}

UITextComponent::~UITextComponent()
{
}

void UITextComponent::_Draw() const
{
	GameController::Instance->GetDrawer()->DrawText(text.c_str(), fontPath, screenPositionX, screenPositionY);
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
