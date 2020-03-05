#include "SDL.h"
#include "GameController.h"
#include "GameObject.h"
#include "Components/SpriteRendererComponent.h"
#include "Components/PlayerBehaviourComponent.h"
#include "Persistence/TileMapTxtReader.h"

GameController::GameController(Drawer* drawer)
{
	this->drawer = drawer;
}

GameController::~GameController()
{
	if (tileMap != nullptr) 
	{
		delete tileMap;
		tileMap = nullptr;
	}
}

void GameController::Start()
{
	//load the map
	{
		TileMapTxtReader mapTxtReader;
		tileMap = mapTxtReader.Read("map.txt");
	}

	//background object
	{
		GameObject* backgroundObject = new GameObject();
		SpriteRendererComponent* spriteRenderer = backgroundObject->AddComponent<SpriteRendererComponent>();
		spriteRenderer->SetDrawer(drawer);
		spriteRenderer->SetSprite("playfield.png");
		_gameObjects.push_back(backgroundObject);
	}


	{
		float halfSizeTileMapXf = ((float)tileMap->GetSizeX()) / 2.f;
		float halfSizeTileMapYf = ((float)tileMap->GetSizeY()) / 2.f;
		for (int x = 0; x < tileMap->GetSizeX(); ++x)
		{
			for (int y = 0; y < tileMap->GetSizeY(); ++y)
			{
				const Tile& tile = tileMap->GetTile(x, y);
				if (tile.type != TileType::Dot && tile.type != TileType::BigDot)
				{
					continue;
				}

				Vector2f position{ (float)x , (float)y };
				position /= 2.f;
				position.X -= halfSizeTileMapXf / 2.f;
				position.Y -= halfSizeTileMapYf / 2.f;
				position.X += 0.75f;
				position.Y += 0.25f;

				GameObject* smallDotObject = new GameObject(position);
				SpriteRendererComponent* spriteRenderer = smallDotObject->AddComponent<SpriteRendererComponent>();
				spriteRenderer->SetDrawer(drawer);
				spriteRenderer->SetSprite((tile.type == TileType::Dot) ? "Small_Dot_32.png" : "Big_Dot_32.png");
				_gameObjects.push_back(smallDotObject);
			}
		}
	}

	//player object
	{
		GameObject* playerObject = new GameObject(Vector2f(0.f, +0.5f));
		SpriteRendererComponent* spriteRenderer = playerObject->AddComponent<SpriteRendererComponent>();
		spriteRenderer->SetDrawer(drawer);
		spriteRenderer->SetSprite("open_32.png");
		PlayerBehaviourComponent* playerBehaviourComponent = playerObject->AddComponent<PlayerBehaviourComponent>();
		playerBehaviourComponent->SetGameController(this);
		playerBehaviourComponent->SetSpeed(10.f);
		_gameObjects.push_back(playerObject);
	}
}

bool GameController::Update(const float deltaTime)
{
	if (!_UpdateInput()) 
	{
		return false;
	}

	for (GameObject* obj : _gameObjects)
	{
		obj->Update(deltaTime);
	}
	return true;
}

void GameController::Draw() const
{
	for (GameObject* obj : _gameObjects)
	{
		obj->Draw();
	}
}

Vector2f GameController::GetInput() const
{
	return input;
}

bool GameController::_UpdateInput()
{
	input = Vector2f::ZERO;

	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_ESCAPE])
	{
		return false;
	}

	if (keystate[SDL_SCANCODE_UP])
	{
		input = Vector2f::UP;
	}
	else if (keystate[SDL_SCANCODE_DOWN])
	{
		input = Vector2f::DOWN;
	}
	else if (keystate[SDL_SCANCODE_RIGHT])
	{
		input = Vector2f::RIGHT;
	}
	else if (keystate[SDL_SCANCODE_LEFT])
	{
		input = Vector2f::LEFT;
	}
	return true;
}
