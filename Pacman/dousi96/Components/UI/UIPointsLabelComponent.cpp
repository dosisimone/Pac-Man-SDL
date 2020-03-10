#include "UITextComponent.h"
#include "../../GameController.h"
#include "../../GameObject.h"
#include "../../../Drawer.h"
#include "UIPointsLabelComponent.h"
#include <string>
#include <sstream>
#include "../GameControllerComponent.h"

UIPointsLabelComponent::UIPointsLabelComponent()
{
	this->textComponent = nullptr;
}

UIPointsLabelComponent::~UIPointsLabelComponent()
{
}

void UIPointsLabelComponent::Start()
{
	this->textComponent = GetOwner()->GetComponent<UITextComponent>();
	//subscribe to the player event
	GameControllerComponent* gameControllerComponent = GameController::Instance->GetComponent<GameControllerComponent>();
	gameControllerComponent->Subscribe((PointsValueUpdatedEventListener*)this);
}

void UIPointsLabelComponent::OnEvent(const PointsValueUpdatedEventArgs& event, const PointsValueUpdatedEventDispatcher& sender)
{
	std::string text;
	std::stringstream textStream;
	textStream << event.points;
	text = textStream.str();
	this->textComponent->SetText(text);
}
