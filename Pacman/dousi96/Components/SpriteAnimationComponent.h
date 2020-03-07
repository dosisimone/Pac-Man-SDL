#ifndef SPRITEANIMATIONRENDERERCOMPONENT_H
#define SPRITEANIMATIONRENDERERCOMPONENT_H

#include <vector>
#include <string>
#include "Component.h"

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
	float secondsCounter = 0.f;

public:
	SpriteAnimationComponent();
	~SpriteAnimationComponent() override;
	void Start() override;
	void Update(const float deltaTime) override;
	void AddAnimation(const Animation& animation);
	void SetCurrentAnimation(const std::string& name);
	void SetFlip(const bool x, const bool y);
	void SetRotation(const float angle);
};
#endif // SPRITEANIMATIONRENDERERCOMPONENT_H