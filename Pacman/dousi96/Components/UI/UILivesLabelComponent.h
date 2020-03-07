#ifndef UILIVESLABELCOMPONENT_H
#define UILIVESLABELCOMPONENT_H

#include "../Component.h"
#include "UITextComponent.h"
#include "../../EventSystem/Events.h"

class UILivesLabelComponent : public Component, LivesValueUpdatedEventListener
{
private:
	UITextComponent* textComponent = nullptr;

public:
	UILivesLabelComponent();
	~UILivesLabelComponent() override;
	void Start() override;
	void OnEvent(const LivesValueUpdatedEventArgs& event, const LivesValueUpdatedEventDispatcher& sender) override;
};
#endif // UILIVESLABELCOMPONENT_H