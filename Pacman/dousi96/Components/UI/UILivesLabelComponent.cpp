#include "UILivesLabelComponent.h"
#include "../../GameController.h"
#include "../../GameObject.h"
#include "../../../Drawer.h"
#include "UITextComponent.h"
#include <string>
#include <sstream>
#include "../GameControllerComponent.h"

UILivesLabelComponent::UILivesLabelComponent()
{
	this->textComponent = nullptr;
}

UILivesLabelComponent::~UILivesLabelComponent()
{
}

void UILivesLabelComponent::Awake()
{
	this->textComponent = GetOwner()->GetOrAddComponent<UITextComponent>();
}

void UILivesLabelComponent::Start()
{
	//subscribe to the event
	GameControllerComponent* gameControllerComponent = GameController::Instance->GetComponent<GameControllerComponent>();
	if (gameControllerComponent != nullptr) 
	{
		gameControllerComponent->Subscribe((LivesValueUpdatedEventListener*)this);
	}
}

void UILivesLabelComponent::OnEvent(const LivesValueUpdatedEventArgs& event, const LivesValueUpdatedEventDispatcher& sender)
{
	ForceLivesToShow(event.lives);
}

void UILivesLabelComponent::ForceLivesToShow(const unsigned short lives)
{
	std::string text;
	std::stringstream textStream;
	textStream << lives;
	text = textStream.str();
	this->textComponent->SetText(text);
}
