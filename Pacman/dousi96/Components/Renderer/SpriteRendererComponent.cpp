#include "SpriteRendererComponent.h"
#include "../../GameObject.h"
#include "../../GameController.h"
#include "../../../Drawer.h"

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
	GameController::Instance->GetDrawer()->Draw(spritePath, GetOwner()->Position, flipX, flipY, rotation);
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
