#ifndef SPRITERENDERERCOMPONENT_H
#define SPRITERENDERERCOMPONENT_H

#include "../Component.h"
#include "../../../Drawer.h"

class SpriteRendererComponent : public Component
{	
private:
	const char* spritePath;
	bool flipX = false;
	bool flipY = false;
	float rotation = 0.f;

public:
	SpriteRendererComponent();
	~SpriteRendererComponent() override;	
	void SetSprite(const char* spritePath);
	void SetFlip(const bool x, const bool y);
	void SetRotation(const float angle);

protected:
	void _Draw() const override;
};
#endif // SPRITERENDERERCOMPONENT_H
