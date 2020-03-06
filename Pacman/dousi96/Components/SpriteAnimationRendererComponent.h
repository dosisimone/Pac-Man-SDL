#ifndef SPRITEANIMATIONRENDERERCOMPONENT_H
#define SPRITEANIMATIONRENDERERCOMPONENT_H

#include "Component.h"
#include "../../Drawer.h"

class SpriteAnimationRendererComponent : public Component
{
private:
	Drawer* drawer;
	std::vector<char*> frames;
	int actualFrameIndex = 0;
	float secondsBtwFrames = 1.f;
	float secondsCounter = 0.f;
	bool flipX = false;
	bool flipY = false;
	float rotation = 0.f;	

public:
	SpriteAnimationRendererComponent();
	~SpriteAnimationRendererComponent();
	void Draw() const override;
	void Update(const float deltaTime) override;
	void SetFrames(const std::vector<char*>& frames);
	void SetSecondsBtwFrames(const float secondsBtwFrames);
	void SetDrawer(Drawer* drawer);
	void SetFlip(const bool x, const bool y);
	void SetRotation(const float angle);

	//static ComponentType GetType() { return ComponentType::tSpriteAnimationRendererComponent; }
};
#endif // SPRITEANIMATIONRENDERERCOMPONENT_H