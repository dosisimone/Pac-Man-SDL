#include "Component.h"
#include "SpriteRendererComponent.h"

void SpriteRendererComponent::Draw() const
{
	drawer->Draw(spritePath, Owner->Position, flipX, flipY, rotation);
}

void SpriteRendererComponent::SetSprite(const char* spritePath)
{
	this->spritePath = spritePath;
}

void SpriteRendererComponent::SetDrawer(Drawer* drawer)
{
	this->drawer = drawer;
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
