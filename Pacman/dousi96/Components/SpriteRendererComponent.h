#ifndef SPRITERENDERERCOMPONENT_H
#define SPRITERENDERERCOMPONENT_H

#include "Component.h"
#include "../../Drawer.h"

class SpriteRendererComponent : public Component
{	
private:
	Drawer* drawer;
	const char* spritePath;
	bool flipX = false;
	bool flipY = false;
	float rotation = 0.f;

public:
	SpriteRendererComponent();
	~SpriteRendererComponent() override;
	void Draw() const override;
	void Update(const float deltaTime) override {}
	void SetSprite(const char* spritePath);
	void SetDrawer(Drawer* drawer);
	void SetFlip(const bool x, const bool y);
	void SetRotation(const float angle);
};
#endif // SPRITERENDERERCOMPONENT_H
