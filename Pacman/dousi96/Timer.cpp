#include "Timer.h"

Timer::Timer()
{
	this->duration = -1.f;
	this->timer = 0.f;
}

void Timer::SetDuration(const float& duration)
{
	this->duration = duration;
}

void Timer::Increment(const float& deltaTime)
{
	this->timer += deltaTime;
}

bool Timer::Check() const
{
	return timer >= duration;
}

void Timer::Reset()
{
	this->timer = 0.f;
}
