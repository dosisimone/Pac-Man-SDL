#ifndef EVENTSYSTEM_H
#define EVENTSYSTEM_H

#include <vector>

template<class EventArgs>
class EventDispatcher 
{
public:
	class Listener
	{
	public:
		virtual ~Listener() = default;
		virtual void OnEvent(const EventArgs& event, const EventDispatcher& sender) = 0;
	};

private:
	std::vector<Listener*> listeners;

public:
	void Subscribe(Listener* listener) 
	{
		for (unsigned int i = 0; i < listeners.size(); ++i) 
		{
			if (listeners[i] == listener) 
			{
				return;
			}
		}
		listeners.push_back(listener);
	}

	void Unsubscribe(Listener* listener) 
	{
		for (unsigned int i = 0; i < listeners.size(); ++i)
		{
			if (listeners[i] == listener)
			{
				listeners.erase(listeners.begin() + i);
				return;
			}
		}
	}

	void Invoke(const EventArgs& eventArgs)
	{
		for (unsigned int i = 0; i < listeners.size(); ++i)
		{
			listeners[i]->OnEvent(eventArgs, *this);
		}
	}
};
#endif // EVENTSYSTEM_H
