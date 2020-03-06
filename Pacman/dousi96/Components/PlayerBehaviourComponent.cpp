#include "PlayerBehaviourComponent.h"
#include "SpriteAnimationRendererComponent.h"
#include "TileMapPositionComponent.h"
#include "TileMovementComponent.h"
#include "../GameController.h"

PlayerBehaviourComponent::PlayerBehaviourComponent()
{
	this->animationRenderer = nullptr;
	this->tilePosition = nullptr;
	this->tileMovement = nullptr;
	this->speed = 1.f;
	this->oldValidInput = Vector2f::LEFT;
}

PlayerBehaviourComponent::~PlayerBehaviourComponent()
{
}

void PlayerBehaviourComponent::Start()
{
	this->animationRenderer = Owner->GetComponent<SpriteAnimationRendererComponent>();
	this->tilePosition = Owner->GetComponent<TileMapPositionComponent>();
	this->tileMovement = Owner->GetComponent<TileMovementComponent>();
}

void PlayerBehaviourComponent::Update(const float deltaTime)
{
	if (tileMovement->IsAtDestination()) 
	{
		const Vector2f kInput = GameController::Instance->GetInput();
		const unsigned int kCurrX = tileMovement->GetCurrentTileX();
		const unsigned int kCurrY = tileMovement->GetCurrentTileY();
		unsigned int nextDestinationX = (unsigned int)((int)kCurrX + (int)kInput.X);
		unsigned int nextDestinationY = (unsigned int)((int)kCurrY + (int)kInput.Y);

		if (!tileMovement->SetDestination(nextDestinationX, nextDestinationY) 
			|| kInput.Length() == 0.f)
		{
			nextDestinationX = (unsigned int)((int)kCurrX + (int)oldValidInput.X);
			nextDestinationY = (unsigned int)((int)kCurrY + (int)oldValidInput.Y);
			tileMovement->SetDestination(nextDestinationX, nextDestinationY);
		}
		else 
		{
			oldValidInput = kInput;
		}
	}

	unsigned int destX = tileMovement->GetDestinationTileX();
	unsigned int destY = tileMovement->GetDestinationTileY();
	Vector2f destination = tilePosition->GetTileWorldPosition(destX, destY);
	Vector2f direction = destination - Owner->Position;

	const float kDelta = deltaTime * speed;
	if (direction.Length() < kDelta) 
	{
		unsigned int currX = tileMovement->GetDestinationTileX();
		unsigned int currY = tileMovement->GetDestinationTileY();
		tileMovement->SetCurrentTile(currX, currY);
		Owner->Position = destination;
	}
	else 
	{
		//update position
		direction.Normalize();
		Owner->Position += direction * (speed * deltaTime);
	}	

	//update renderer	
	float rotation = 0.f;
	if (oldValidInput.Y < 0.f)
	{
		rotation = 90.f;
	}
	else if (oldValidInput.Y > 0.f)
	{
		rotation = -90.f;
	}
	this->animationRenderer->SetRotation(rotation);

	bool flipX = (oldValidInput.X < 0.f);
	if (!flipX)
	{
		rotation *= -1;
	}
	this->animationRenderer->SetFlip(flipX, false);	
}

void PlayerBehaviourComponent::SetSpeed(const float speed)
{
	this->speed = speed;
}
