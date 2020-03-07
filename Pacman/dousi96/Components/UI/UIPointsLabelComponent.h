#ifndef UIPOINTSLABELCOMPONENT_H
#define UIPOINTSLABELCOMPONENT_H

#include "../Component.h"
#include "UITextComponent.h"
#include "../../EventSystem/Events.h"

class UIPointsLabelComponent : public Component, PointsValueUpdatedEventListener
{
private:
	UITextComponent* textComponent = nullptr;

public:
	UIPointsLabelComponent();
	~UIPointsLabelComponent() override;
	void Start() override;
	void OnEvent(const PointsValueUpdatedEventArgs& event, const PointsValueUpdatedEventDispatcher& sender) override;
};
#endif // UIPOINTSLABELCOMPONENT_H