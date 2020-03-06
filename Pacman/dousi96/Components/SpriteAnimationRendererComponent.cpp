#include "Component.h"
#include "SpriteAnimationRendererComponent.h"

SpriteAnimationRendererComponent::SpriteAnimationRendererComponent()
{
	this->drawer = nullptr;
	this->actualFrameIndex = 0;
	this->secondsBtwFrames = 1.f;
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
	drawer->Draw(frames[actualFrameIndex], Owner->Position, flipX, flipY, rotation);
}

void SpriteAnimationRendererComponent::Update(const float deltaTime)
{
	secondsCounter += deltaTime;
	if (secondsCounter >= secondsBtwFrames) 
	{
		actualFrameIndex = (actualFrameIndex + 1) % frames.size();
		secondsCounter = 0.f;
	}
}

void SpriteAnimationRendererComponent::SetFrames(const std::vector<char*>& frames)
{
	if (frames.size() == 0) 
	{
		return;
	}
	this->frames = frames;
}

void SpriteAnimationRendererComponent::SetSecondsBtwFrames(const float secondsBtwFrames)
{
	if (secondsBtwFrames <= 0.f) 
	{
		return;
	}
	this->secondsBtwFrames = secondsBtwFrames;
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
