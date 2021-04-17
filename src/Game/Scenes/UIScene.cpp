#include "../../Core/UI.hpp"
#include "UIScene.hpp"

UIScene::UIScene(Game* game)
	:Scene(game)
{

}

UIScene::~UIScene()
{

}

void UIScene::ProcessInput(Input& input)
{
	for (auto ui : m_UIs)
	{
		ui->ProcessInput(input);
	}
}

void UIScene::Update(float deltaTime)
{
}

void UIScene::Render(Renderer* renderer)
{
	for (auto ui : m_UIs)
	{
		ui->Draw(renderer);
	}
}
