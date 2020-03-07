#include "SpriteAnimationComponent.h"
#include "SpriteRendererComponent.h"

SpriteAnimationComponent::SpriteAnimationComponent()
{
	this->spriteRenderer = nullptr;
	this->actualFrameIndex = 0;
	animationTimer.Reset();
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
	animationTimer.Increment(deltaTime);
	if (animationTimer.Check())
	{
		actualFrameIndex = (actualFrameIndex + 1) % animations[actualAnimationIndex].sprites.size();
		this->spriteRenderer->SetSprite(animations[actualAnimationIndex].sprites[actualFrameIndex]);
		animationTimer.Reset();
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
			animationTimer.SetDuration(animations[actualAnimationIndex].secondsBtwFrames);
			animationTimer.Reset();			
			this->spriteRenderer->SetSprite(animations[actualAnimationIndex].sprites[actualFrameIndex]);
			return;
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
