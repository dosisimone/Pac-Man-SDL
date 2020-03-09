#include "UILivesLabelComponent.h"
#include "../../GameController.h"
#include "../../GameObject.h"
#include "../../../Drawer.h"
#include "UITextComponent.h"
#include <string>
#include <sstream>
#include "../PlayerBehaviourComponent.h"

UILivesLabelComponent::UILivesLabelComponent()
{
	this->textComponent = nullptr;
}

UILivesLabelComponent::~UILivesLabelComponent()
{
}

void UILivesLabelComponent::Start()
{
	this->textComponent = GetOwner()->GetComponent<UITextComponent>();
	//subscribe to the player event
	PlayerBehaviourComponent* playerBehaviour = GameController::Instance->GetComponent<PlayerBehaviourComponent>();
	playerBehaviour->Subscribe((LivesValueUpdatedEventListener*)this);
}

void UILivesLabelComponent::OnEvent(const LivesValueUpdatedEventArgs& event, const LivesValueUpdatedEventDispatcher& sender)
{
	std::string text;
	std::stringstream textStream;
	textStream << event.lives;
	text = textStream.str();
	this->textComponent->SetText(text);
}
