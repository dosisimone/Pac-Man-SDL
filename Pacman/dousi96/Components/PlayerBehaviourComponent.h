#ifndef PLAYERBEHAVIOURCOMPONENT_H
#define PLAYERBEHAVIOURCOMPONENT_H

#include "Component.h"
#include "../../Drawer.h"
#include "../GameController.h"

class SpriteAnimationRendererComponent;

class PlayerBehaviourComponent : public Component
{
private:	
	float speed = 1.0f;	
	SpriteAnimationRendererComponent* animationRenderer;

public:
	PlayerBehaviourComponent();
	~PlayerBehaviourComponent();
	void Start() override;
	void Update(const float deltaTime) override;
	void SetSpeed(const float speed);

	//static ComponentType GetType() { return ComponentType::tPlayerBehaviourComponent; }
};
#endif // PLAYERBEHAVIOURCOMPONENT_H
