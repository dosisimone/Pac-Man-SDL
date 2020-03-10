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

void UIPointsLabelComponent::Awake()
{
	this->textComponent = GetOwner()->GetOrAddComponent<UITextComponent>();
}

void UIPointsLabelComponent::Start()
{	
	//subscribe to the player event
	GameControllerComponent* gameControllerComponent = GameController::Instance->GetComponent<GameControllerComponent>();
	if (gameControllerComponent != nullptr) 
	{
		gameControllerComponent->Subscribe((PointsValueUpdatedEventListener*)this);
	}
}

void UIPointsLabelComponent::OnEvent(const PointsValueUpdatedEventArgs& event, const PointsValueUpdatedEventDispatcher& sender)
{
	ForcePointsToShow(event.points);
}

void UIPointsLabelComponent::ForcePointsToShow(const unsigned int points)
{
	std::string text;
	std::stringstream textStream;
	textStream << points;
	text = textStream.str();
	this->textComponent->SetText(text);
}
