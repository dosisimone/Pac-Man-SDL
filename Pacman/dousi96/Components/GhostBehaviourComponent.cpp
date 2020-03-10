#include "GhostBehaviourComponent.h"
#include <cstdlib>
#include "../GameController.h"
#include "../GameObject.h"
#include "Renderer/SpriteAnimationComponent.h"
#include "TileMap/TileMapPositionComponent.h"
#include "TileMap/TileMovementComponent.h"
#include "TileMap/GhostPathfinderComponent.h"
#include "../TileMap.h"
#include "PlayerBehaviourComponent.h"

GhostBehaviourComponent::GhostBehaviourComponent()
{
	this->status = GhostStatus::Paused;
	this->tilePosition = nullptr;
	this->tileMovement = nullptr;
	this->pathfinder = nullptr;
	this->animationRenderer = nullptr;	
}

GhostBehaviourComponent::~GhostBehaviourComponent()
{
}

void GhostBehaviourComponent::Awake()
{
	this->tilePosition = GetOwner()->GetComponent<TileMapPositionComponent>();
	this->tileMovement = GetOwner()->GetComponent<TileMovementComponent>();
	this->pathfinder = GetOwner()->GetComponent<GhostPathfinderComponent>();
	this->animationRenderer = GetOwner()->GetComponent<SpriteAnimationComponent>();	
	_InitAnimations();
}

void GhostBehaviourComponent::Start()
{
	Tile* ghostHouseTile = _GetGhostHouseTargetTile();
	this->tileMovement->SetCurrentTile(ghostHouseTile->x, ghostHouseTile->y);
	this->tileMovement->SetActive(false);
	this->pathfinder->SetActive(false);
	//setup animations
	this->animationRenderer->SetCurrentAnimation("default");
	// subscribe to events
	PlayerBehaviourComponent* playerBehaviour = GameController::Instance->GetComponent<PlayerBehaviourComponent>();
	playerBehaviour->Subscribe((BigDotCollectedEventListener*)this);	
}


GhostBehaviourComponent::GhostStatus GhostBehaviourComponent::GetStatus() const
{
	return this->status;
}

void GhostBehaviourComponent::ForceTimer(const float seconds)
{
	if (seconds < 0.f) 
	{
		return;
	}
	statusTimer.SetDuration(seconds);
	statusTimer.Reset();
}

void GhostBehaviourComponent::Kill()
{
	if (this->status != GhostStatus::Frightened)
	{
		return;
	}
	this->status = GhostStatus::Dead;
	this->animationRenderer->SetCurrentAnimation("dead");
	this->pathfinder->SetStrictObstacleAvoidance(false);
	Tile* ghostHouseTile = _GetGhostHouseTargetTile();
	this->pathfinder->SetTarget(ghostHouseTile->x, ghostHouseTile->y);
}

void GhostBehaviourComponent::OnEvent(const BigDotCollectedEventArgs& event, const BigDotCollectedEventDispatcher& sender)
{
	_SetFrightenedStatus();
}

void GhostBehaviourComponent::_Update(const float& deltaTime)
{
	switch (status)
	{
		case GhostStatus::Dead:
		{
			if (this->pathfinder->IsAtFinalDestination())
			{
				_SetPausedStatus();
			}
			return;
		}
		break;
		case GhostStatus::LeavingHouse:
		{
			if (!this->pathfinder->IsAtFinalDestination())
			{
				return;
			}			
		}
		break;
	}

	//check status change timer
	statusTimer.Increment(deltaTime);
	if (statusTimer.Check())
	{
		_NextStatus();
	}	

	switch (status)
	{
	case GhostStatus::Frightened:
	{
		if (this->pathfinder->IsAtFinalDestination())
		{
			Tile* randomTile = _GetRandomPlayerWalkableTile();
			this->pathfinder->SetTarget(randomTile->x, randomTile->y);
		}
	}
	break;
	}
}

void GhostBehaviourComponent::_NextStatus()
{
	switch (status) 
	{
	case GhostStatus::Dead: 
	{}
	break;

	case GhostStatus::Paused:
	{
		_SetLeavingGhostHouseStatus();
	}
	break;

	case GhostStatus::LeavingHouse:
	{
		if (this->pathfinder->IsAtFinalDestination()) 
		{
			_SetScatterStatus();
		}
	}
	break;

	default:
	{
		if (statusPhaseIndex < 5)
		{
			if (status == GhostStatus::Chase)
			{
				_SetScatterStatus();
				statusPhaseIndex++;
			}
			else
			{
				_SetChaseStatus();
			}
		}
		else
		{
			_SetChaseStatus();
		}
	}
	break;
	}
}

void GhostBehaviourComponent::_SetPausedStatus()
{
	this->status = GhostStatus::Paused;
	statusTimer.SetDuration(5.f);
	statusTimer.Reset();
	this->animationRenderer->SetCurrentAnimation("default");
	this->tileMovement->SetActive(false);
	this->pathfinder->SetActive(false);
}

void GhostBehaviourComponent::_SetChaseStatus()
{
	if (this->status == GhostStatus::Chase)
	{
		return;
	}
	this->status = GhostStatus::Chase;
	statusTimer.SetDuration(20.f);
	statusTimer.Reset();
	this->animationRenderer->SetCurrentAnimation("default");
	this->pathfinder->SetStrictObstacleAvoidance(true);
}

void GhostBehaviourComponent::_SetScatterStatus()
{
	if (this->status == GhostStatus::Scatter) 
	{
		return;
	}
	this->status = GhostStatus::Scatter;
	statusTimer.SetDuration(7.f);
	statusTimer.Reset();
	this->animationRenderer->SetCurrentAnimation("default");
	this->pathfinder->SetStrictObstacleAvoidance(true);
	Tile* scatterStatusTarget = _GetScatterTargetTile();
	this->pathfinder->SetTarget(scatterStatusTarget->x, scatterStatusTarget->y);	
}

void GhostBehaviourComponent::_SetFrightenedStatus()
{
	const GhostStatus kPrevStatus = this->status;
	if (kPrevStatus == GhostStatus::Dead || kPrevStatus == GhostStatus::Paused)
	{
		return;
	}

	this->status = GhostStatus::Frightened;
	statusTimer.SetDuration(7.f);
	statusTimer.Reset();

	if (kPrevStatus != GhostStatus::Frightened) 
	{
		this->animationRenderer->SetCurrentAnimation("frightened");
		Tile* randomTile = _GetRandomPlayerWalkableTile();
		if (kPrevStatus != GhostStatus::LeavingHouse) 
		{
			this->pathfinder->SetTarget(randomTile->x, randomTile->y);
			this->pathfinder->SetStrictObstacleAvoidance(true);
		}
	}
}

void GhostBehaviourComponent::_SetLeavingGhostHouseStatus()
{
	if (this->status != GhostStatus::Paused) 
	{
		return;
	}
	this->status = GhostStatus::LeavingHouse;
	const unsigned int kCurrX = this->tilePosition->GetTilePositionX();
	const unsigned int kCurrY = this->tilePosition->GetTilePositionY();	
	this->pathfinder->SetTarget(kCurrX, kCurrY + 3);
	this->pathfinder->SetStrictObstacleAvoidance(false);
	this->tileMovement->SetActive(true);
	this->pathfinder->SetActive(true);	
}

Tile* GhostBehaviourComponent::_GetRandomPlayerWalkableTile() const
{
	TileMap* tileMap = this->tilePosition->GetTileMap();
	int numTotTiles = tileMap->GetSizeX() * tileMap->GetSizeY();
	Tile* tile = nullptr;
	do 
	{
		int x = rand() % tileMap->GetSizeX();
		int y = rand() % tileMap->GetSizeY();
		tile = tileMap->GetTile(x, y);
	} 
	while (!tile->isPlayerWalkable);
	return tile;
}


//RED GHOST
void RedGhostBehaviourComponent::_InitAnimations()
{
	SpriteAnimationComponent::Animation defaultGhostAnimation;
	defaultGhostAnimation.name = "default";
	defaultGhostAnimation.sprites = { "ghost_32_red.png" };
	defaultGhostAnimation.secondsBtwFrames = 60.f;
	SpriteAnimationComponent::Animation deadGhostAnimation;
	deadGhostAnimation.name = "dead";
	deadGhostAnimation.sprites = { "Ghost_Dead_32.png" };
	deadGhostAnimation.secondsBtwFrames = 60.f;
	SpriteAnimationComponent::Animation frightenedGhostAnimation;
	frightenedGhostAnimation.name = "frightened";
	frightenedGhostAnimation.sprites = { "Ghost_Vulnerable_32.png" };
	frightenedGhostAnimation.secondsBtwFrames = 60.f;
	this->animationRenderer->AddAnimation(defaultGhostAnimation);
	this->animationRenderer->AddAnimation(deadGhostAnimation);
	this->animationRenderer->AddAnimation(frightenedGhostAnimation);
}

Tile* RedGhostBehaviourComponent::_GetGhostHouseTargetTile() const
{
	return this->tilePosition->GetTileMap()->GetTile(12, 16);
}

Tile* RedGhostBehaviourComponent::_GetScatterTargetTile() const
{
	return this->tilePosition->GetTileMap()->GetTile(27, 30);
}

Tile* RedGhostBehaviourComponent::_GetChaseTargetTile() const
{
	return nullptr;
}
//END RED GHOST

//ORANGE GHOST
void OrangeGhostBehaviourComponent::_InitAnimations()
{
	SpriteAnimationComponent::Animation defaultGhostAnimation;
	defaultGhostAnimation.name = "default";
	defaultGhostAnimation.sprites = { "ghost_32_orange.png" };
	defaultGhostAnimation.secondsBtwFrames = 60.f;
	SpriteAnimationComponent::Animation deadGhostAnimation;
	deadGhostAnimation.name = "dead";
	deadGhostAnimation.sprites = { "Ghost_Dead_32.png" };
	deadGhostAnimation.secondsBtwFrames = 60.f;
	SpriteAnimationComponent::Animation frightenedGhostAnimation;
	frightenedGhostAnimation.name = "frightened";
	frightenedGhostAnimation.sprites = { "Ghost_Vulnerable_32.png" };
	frightenedGhostAnimation.secondsBtwFrames = 60.f;
	this->animationRenderer->AddAnimation(defaultGhostAnimation);
	this->animationRenderer->AddAnimation(deadGhostAnimation);
	this->animationRenderer->AddAnimation(frightenedGhostAnimation);
}

Tile* OrangeGhostBehaviourComponent::_GetGhostHouseTargetTile() const
{
	return this->tilePosition->GetTileMap()->GetTile(15, 16);
}

Tile* OrangeGhostBehaviourComponent::_GetScatterTargetTile() const
{
	return this->tilePosition->GetTileMap()->GetTile(27, 0);
}

Tile* OrangeGhostBehaviourComponent::_GetChaseTargetTile() const
{
	return nullptr;
}
//END ORANGE GHOST

//PINK GHOST
void PinkGhostBehaviourComponent::_InitAnimations()
{
	SpriteAnimationComponent::Animation defaultGhostAnimation;
	defaultGhostAnimation.name = "default";
	defaultGhostAnimation.sprites = { "ghost_32_pink.png" };
	defaultGhostAnimation.secondsBtwFrames = 60.f;
	SpriteAnimationComponent::Animation deadGhostAnimation;
	deadGhostAnimation.name = "dead";
	deadGhostAnimation.sprites = { "Ghost_Dead_32.png" };
	deadGhostAnimation.secondsBtwFrames = 60.f;
	SpriteAnimationComponent::Animation frightenedGhostAnimation;
	frightenedGhostAnimation.name = "frightened";
	frightenedGhostAnimation.sprites = { "Ghost_Vulnerable_32.png" };
	frightenedGhostAnimation.secondsBtwFrames = 60.f;
	this->animationRenderer->AddAnimation(defaultGhostAnimation);
	this->animationRenderer->AddAnimation(deadGhostAnimation);
	this->animationRenderer->AddAnimation(frightenedGhostAnimation);
}

Tile* PinkGhostBehaviourComponent::_GetGhostHouseTargetTile() const
{
	return this->tilePosition->GetTileMap()->GetTile(14, 16);
}

Tile* PinkGhostBehaviourComponent::_GetScatterTargetTile() const
{
	return this->tilePosition->GetTileMap()->GetTile(0, 0);
}

Tile* PinkGhostBehaviourComponent::_GetChaseTargetTile() const
{
	return nullptr;
}
//END PINK GHOST

//BLUE GHOST
void BlueGhostBehaviourComponent::_InitAnimations()
{
	SpriteAnimationComponent::Animation defaultGhostAnimation;
	defaultGhostAnimation.name = "default";
	defaultGhostAnimation.sprites = { "ghost_32_cyan.png" };
	defaultGhostAnimation.secondsBtwFrames = 60.f;
	SpriteAnimationComponent::Animation deadGhostAnimation;
	deadGhostAnimation.name = "dead";
	deadGhostAnimation.sprites = { "Ghost_Dead_32.png" };
	deadGhostAnimation.secondsBtwFrames = 60.f;
	SpriteAnimationComponent::Animation frightenedGhostAnimation;
	frightenedGhostAnimation.name = "frightened";
	frightenedGhostAnimation.sprites = { "Ghost_Vulnerable_32.png" };
	frightenedGhostAnimation.secondsBtwFrames = 60.f;
	this->animationRenderer->AddAnimation(defaultGhostAnimation);
	this->animationRenderer->AddAnimation(deadGhostAnimation);
	this->animationRenderer->AddAnimation(frightenedGhostAnimation);
}

Tile* BlueGhostBehaviourComponent::_GetGhostHouseTargetTile() const
{
	return this->tilePosition->GetTileMap()->GetTile(13, 16);
}

Tile* BlueGhostBehaviourComponent::_GetScatterTargetTile() const
{
	return this->tilePosition->GetTileMap()->GetTile(0, 30);
}

Tile* BlueGhostBehaviourComponent::_GetChaseTargetTile() const
{
	return nullptr;
}
//END BLUE GHOST
