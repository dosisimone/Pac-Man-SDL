#ifndef GAMECONTROLLERCOMPONENT_H
#define GAMECONTROLLERCOMPONENT_H

#include "Component.h"
#include <vector>
#include "../EventSystem/Events.h"
#include "../Timer.h"

class PlayerBehaviourComponent;
class GhostBehaviourComponent;

class GameControllerComponent : public Component
{
public:
	enum class GameState : short
	{
		Paused,
		Playing,
		Restart,
		GameOver
	};

private:
	GameState state = GameState::Paused;
	Timer changeStateTimer;

	GameObject* playerObject = nullptr;
	std::vector<GameObject*> ghostObjects;

public:
	GameControllerComponent();
	~GameControllerComponent() override;
	void Start() override;	
	void SetDurationChangeState(const float duration);

protected:
	void _Update(const float& deltaTime) override;
};
#endif // GAMECONTROLLERCOMPONENT_H