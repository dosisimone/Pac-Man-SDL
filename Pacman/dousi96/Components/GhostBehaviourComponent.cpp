#include "GhostBehaviourComponent.h"
#include "../GameController.h"
#include "../GameObject.h"
#include "Renderer/SpriteAnimationComponent.h"
#include "PlayerBehaviourComponent.h"

GhostBehaviourComponent::GhostBehaviourComponent()
{
	this->status = GhostStatus::Paused;
}

GhostBehaviourComponent::~GhostBehaviourComponent()
{
}

void GhostBehaviourComponent::Start()
{
	this->status = GhostStatus::Chase;
	this->animationRenderer = GetOwner()->GetComponent<SpriteAnimationComponent>();
	SpriteAnimationComponent::Animation defaultGhost1Animation;
	defaultGhost1Animation.name = "default";
	defaultGhost1Animation.sprites = { "ghost_32_red.png" };
	defaultGhost1Animation.secondsBtwFrames = 60.f;
	SpriteAnimationComponent::Animation deadGhostAnimation;
	deadGhostAnimation.name = "dead";
	deadGhostAnimation.sprites = { "Ghost_Dead_32.png" };
	deadGhostAnimation.secondsBtwFrames = 60.f;
	SpriteAnimationComponent::Animation frightenedGhostAnimation;
	frightenedGhostAnimation.name = "frightened";
	frightenedGhostAnimation.sprites = { "Ghost_Vulnerable_32.png" };
	frightenedGhostAnimation.secondsBtwFrames = 60.f;
	this->animationRenderer->AddAnimation(defaultGhost1Animation);
	this->animationRenderer->AddAnimation(deadGhostAnimation);
	this->animationRenderer->AddAnimation(frightenedGhostAnimation);
	this->animationRenderer->SetCurrentAnimation("default");	
	
	// subscribe to events
	PlayerBehaviourComponent* playerBehaviour = GameController::Instance->GetComponent<PlayerBehaviourComponent>();
	playerBehaviour->Subscribe((BigDotCollectedEventListener*)this);
}


GhostBehaviourComponent::GhostStatus GhostBehaviourComponent::GetStatus() const
{
	return this->status;
}

void GhostBehaviourComponent::OnEvent(const BigDotCollectedEventArgs& event, const BigDotCollectedEventDispatcher& sender)
{
	if (this->status != GhostStatus::Chase) 
	{
		return;
	}
	_SetFrightenedStatus();
}

void GhostBehaviourComponent::_Update(const float& deltaTime)
{
	if (!IsActive())
	{
		return;
	}

	if (this->status == GhostStatus::Frightened) 
	{
		statusTimer.Increment(deltaTime);
		if (statusTimer.Check()) 
		{
			_SetChaseStatus();
		}
	}
	
}

void GhostBehaviourComponent::_SetChaseStatus()
{
	this->status = GhostStatus::Chase;
	this->animationRenderer->SetCurrentAnimation("default");
}

void GhostBehaviourComponent::_SetFrightenedStatus()
{
	this->status = GhostStatus::Frightened;
	statusTimer.SetDuration(7.f);
	statusTimer.Reset();	
	this->animationRenderer->SetCurrentAnimation("frightened");
}
