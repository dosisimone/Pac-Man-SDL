#include "Component.h"
#include "../../Drawer.h"
#include "SpriteAnimationRendererComponent.h"

SpriteAnimationRendererComponent::SpriteAnimationRendererComponent()
{
	this->drawer = nullptr;
	this->actualFrameIndex = 0;
	this->secondsCounter = 0.f;
	this->flipX = false;
	this->flipY = false;
	this->rotation = 0.f;
}

SpriteAnimationRendererComponent::~SpriteAnimationRendererComponent()
{
}

void SpriteAnimationRendererComponent::Draw() const
{
	if (animations.size() < 1) 
	{
		return;
	}
	drawer->Draw(animations[actualAnimationIndex].sprites[actualFrameIndex], Owner->Position, flipX, flipY, rotation);
}

void SpriteAnimationRendererComponent::Update(const float deltaTime)
{
	secondsCounter += deltaTime;
	if (secondsCounter >= animations[actualAnimationIndex].secondsBtwFrames)
	{
		actualFrameIndex = (actualFrameIndex + 1) % animations[actualAnimationIndex].sprites.size();
		secondsCounter = 0.f;
	}
}

void SpriteAnimationRendererComponent::AddAnimation(const Animation& animation)
{
	if (animation.sprites.size() < 1) 
	{
		return;
	}
	animations.push_back(animation);
}

void SpriteAnimationRendererComponent::SetCurrentAnimation(const std::string& name)
{
	for (unsigned int i = 0; i < animations.size(); ++i) 
	{
		if (name.compare(animations[i].name) == 0) 
		{
			actualAnimationIndex = i;
			actualFrameIndex = 0;
		}
	}

}

void SpriteAnimationRendererComponent::SetDrawer(Drawer* drawer)
{
	this->drawer = drawer;
}

void SpriteAnimationRendererComponent::SetFlip(const bool x, const bool y)
{
	this->flipX = x;
	this->flipY = y;
}

void SpriteAnimationRendererComponent::SetRotation(const float angle)
{
	this->rotation = angle;
}
