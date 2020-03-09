#ifndef SPRITEANIMATIONRENDERERCOMPONENT_H
#define SPRITEANIMATIONRENDERERCOMPONENT_H

#include <vector>
#include <string>
#include "../Component.h"
#include "../../Timer.h"

class SpriteRendererComponent;

class SpriteAnimationComponent : public Component
{
public:
	struct Animation
	{
		std::string name;
		std::vector<char*> sprites;
		float secondsBtwFrames = 1.f;
	};

private:
	SpriteRendererComponent* spriteRenderer;
	std::vector<Animation> animations;
	unsigned int actualAnimationIndex = 0;
	unsigned int actualFrameIndex = 0;
	Timer animationTimer;

public:
	SpriteAnimationComponent();
	~SpriteAnimationComponent() override;
	void Awake() override;	
	void AddAnimation(const Animation& animation);
	void SetCurrentAnimation(const std::string& name);
	void SetFlip(const bool x, const bool y);
	void SetRotation(const float angle);

protected:
	void _Update(const float& deltaTime) override;
};
#endif // SPRITEANIMATIONRENDERERCOMPONENT_H