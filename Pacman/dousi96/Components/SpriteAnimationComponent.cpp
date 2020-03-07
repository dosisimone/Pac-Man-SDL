#include "SpriteAnimationComponent.h"
#include "SpriteRendererComponent.h"

SpriteAnimationComponent::SpriteAnimationComponent()
{
	this->spriteRenderer = nullptr;
	this->actualFrameIndex = 0;
	this->secondsCounter = 0.f;
}

SpriteAnimationComponent::~SpriteAnimationComponent()
{
}

void SpriteAnimationComponent::Start()
{
	this->spriteRenderer = Owner->GetComponent<SpriteRendererComponent>();
}

void SpriteAnimationComponent::Update(const float deltaTime)
{
	secondsCounter += deltaTime;
	if (secondsCounter >= animations[actualAnimationIndex].secondsBtwFrames)
	{
		actualFrameIndex = (actualFrameIndex + 1) % animations[actualAnimationIndex].sprites.size();
		secondsCounter = 0.f;
		this->spriteRenderer->SetSprite(animations[actualAnimationIndex].sprites[actualFrameIndex]);
	}
}

void SpriteAnimationComponent::AddAnimation(const Animation& animation)
{
	if (animation.sprites.size() < 1) 
	{
		return;
	}
	animations.push_back(animation);
}

void SpriteAnimationComponent::SetCurrentAnimation(const std::string& name)
{
	for (unsigned int i = 0; i < animations.size(); ++i) 
	{
		if (name.compare(animations[i].name) == 0) 
		{
			actualAnimationIndex = i;
			actualFrameIndex = 0;
			this->spriteRenderer->SetSprite(animations[actualAnimationIndex].sprites[actualFrameIndex]);
		}
	}
}

void SpriteAnimationComponent::SetFlip(const bool x, const bool y)
{
	this->spriteRenderer->SetFlip(x, y);
}

void SpriteAnimationComponent::SetRotation(const float angle)
{
	this->spriteRenderer->SetRotation(angle);
}
