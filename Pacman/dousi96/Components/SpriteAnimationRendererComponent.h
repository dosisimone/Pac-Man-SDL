#ifndef SPRITEANIMATIONRENDERERCOMPONENT_H
#define SPRITEANIMATIONRENDERERCOMPONENT_H

#include <vector>
#include <string>
#include "Component.h"

class Drawer;

class SpriteAnimationRendererComponent : public Component
{
public:
	struct Animation
	{
		std::string name;
		std::vector<char*> sprites;
		float secondsBtwFrames = 1.f;
	};

private:
	Drawer* drawer;	
	std::vector<Animation> animations;
	unsigned int actualAnimationIndex = 0;
	unsigned int actualFrameIndex = 0;
	float secondsCounter = 0.f;
	bool flipX = false;
	bool flipY = false;
	float rotation = 0.f;	

public:
	SpriteAnimationRendererComponent();
	~SpriteAnimationRendererComponent() override;
	void Draw() const override;
	void Update(const float deltaTime) override;
	void AddAnimation(const Animation& animation);
	void SetCurrentAnimation(const std::string& name);
	void SetDrawer(Drawer* drawer);
	void SetFlip(const bool x, const bool y);
	void SetRotation(const float angle);
};
#endif // SPRITEANIMATIONRENDERERCOMPONENT_H