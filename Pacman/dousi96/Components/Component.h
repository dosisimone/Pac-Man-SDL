#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

class Component 
{
private:
	GameObject* Owner = nullptr;
	bool isActive = true;

public:
	Component();
	virtual ~Component() = default;
	void Register(GameObject* gameObject);
	virtual void Awake() {};
	virtual void Start() {};
	void Update(const float& deltaTime);
	void Draw() const;
	void SetActive(const bool active);
	bool IsActive() const;
	GameObject* GetOwner() const;

protected:
	virtual void _Update(const float& deltaTime) {};
	virtual void _Draw() const {};
};
#endif // COMPONENT_H
