#include "UITextComponent.h"
#include "../../GameObject.h"
#include "../../../Drawer.h"
#include "UIPointsLabelComponent.h"
#include <string>
#include <sstream>

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
}

void UIPointsLabelComponent::OnEvent(const PointsValueUpdatedEventArgs& event, const PointsValueUpdatedEventDispatcher& sender)
{
	std::string text;
	std::stringstream textStream;
	textStream << event.points;
	text = textStream.str();
	this->textComponent->SetText(text);
}
