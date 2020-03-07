#ifndef TIMER_H
#define TIMER_H

class Timer
{
private:
	float duration = -1.f;
	float timer = 0.f;

public:
	Timer();
	~Timer() = default;
	void SetDuration(const float& duration);
	void Increment(const float& deltaTime);
	bool Check() const;
	void Reset();
};
#endif // TIMER_H