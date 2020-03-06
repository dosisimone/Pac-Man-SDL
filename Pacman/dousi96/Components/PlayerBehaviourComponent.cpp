#include "PlayerBehaviourComponent.h"
#include "SpriteAnimationRendererComponent.h"

PlayerBehaviourComponent::PlayerBehaviourComponent()
{
	this->animationRenderer = nullptr;
	this->speed = 1.f;
}

PlayerBehaviourComponent::~PlayerBehaviourComponent()
{
}

void PlayerBehaviourComponent::Start()
{
	this->animationRenderer = Owner->GetComponent<SpriteAnimationRendererComponent>();
}

void PlayerBehaviourComponent::Update(const float deltaTime)
{
	const Vector2f kInput = Owner->GetController()->GetInput();
	if (kInput.X == 0.f && kInput.Y == 0.f) 
	{
		return;
	}
	//update position
	Owner->Position += kInput * speed * deltaTime;

	//update renderer
	bool flipX = (kInput.X < 0.f);
	float rotation = 0.f;
	if (kInput.Y > 0.f) 
	{
		rotation = 90.f;
	}
	else if (kInput.Y < 0.f) 
	{
		rotation = -90.f;
	}
	if (!flipX)
	{
		rotation *= -1;
	}
	this->animationRenderer->SetFlip(flipX, false);
	this->animationRenderer->SetRotation(rotation);	
}

void PlayerBehaviourComponent::SetSpeed(const float speed)
{
	if (speed <= 0.0f) 
	{
		return;
	}
	this->speed = speed;
}
