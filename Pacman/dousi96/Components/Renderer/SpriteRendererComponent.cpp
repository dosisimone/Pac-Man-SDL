#include "SpriteRendererComponent.h"
#include "../../GameController.h"

SpriteRendererComponent::SpriteRendererComponent()
{	
	spritePath = nullptr;
	flipX = false;
	flipY = false;
	rotation = 0.f;
}

SpriteRendererComponent::~SpriteRendererComponent()
{
}

void SpriteRendererComponent::_Draw() const
{
	GameController::Instance->GetDrawer()->Draw(spritePath, Owner->Position, flipX, flipY, rotation);
}

void SpriteRendererComponent::SetSprite(const char* spritePath)
{
	this->spritePath = spritePath;
}

void SpriteRendererComponent::SetFlip(const bool x, const bool y)
{
	this->flipX = x;
	this->flipY = y;
}

void SpriteRendererComponent::SetRotation(const float angle)
{
	this->rotation = angle;
}
