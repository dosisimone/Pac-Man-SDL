#ifndef UILIVESLABELCOMPONENT_H
#define UILIVESLABELCOMPONENT_H

#include "../Component.h"
#include "../../EventSystem/Events.h"

class UITextComponent;

class UILivesLabelComponent : public Component, LivesValueUpdatedEventListener
{
private:
	UITextComponent* textComponent = nullptr;

public:
	UILivesLabelComponent();
	~UILivesLabelComponent() override;
	void Awake() override;
	void Start() override;
	void OnEvent(const LivesValueUpdatedEventArgs& event, const LivesValueUpdatedEventDispatcher& sender) override;
	void ForceLivesToShow(const unsigned short lives);
};
#endif // UILIVESLABELCOMPONENT_H