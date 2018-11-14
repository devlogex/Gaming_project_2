#include "MainScreen.h"
#include"KeyGame.h"
#include"MegamanXScene.h"


void MainScreen::init()
{
	background = new Texture("Data\\Map\\mainScreen\\background.png", D3DCOLOR_XRGB(0, 0, 0));
	button = new DrawableObject();
	button->sprite = new Sprite("Data\\Map\\mainScreen\\button.png", "Data\\Map\\mainScreen\\button.txt");
}

void MainScreen::update()
{
	if (isStart)
	{
		if (timeDraw.canCreateFrame())
			isDraw = false;

		if (button->curAnimation == BUTTON_START && timeDraw.isTerminated())
		{
			if (MegamanXScene::megamanXScene != 0)
				delete MegamanXScene::megamanXScene;
			Scene::changeScene(new MegamanXScene());
		}
		else
			if (button->curAnimation == BUTTON_CONTINUE && timeDraw.isTerminated())
			{
				if (MegamanXScene::megamanXScene != 0)
				{
					Scene::changeScene(MegamanXScene::megamanXScene,true,false);
					if (Stage::curStage->index == Stage::curStages->size() - 1)
						Stage::curStage = Stage::curStages->at(Stage::curStage->index - 1);
					Stage::loadStagePrev();
				}
				else
				{
					isDraw = true;
					isStart = false;
					timeDraw.start();
				}
			}
	}

	if (KEY->keyUpPress || KEY->keyDownPress )
		button->curAnimation = (button->curAnimation + 1) % 2;
	if (KEY->keyEnterPress)
		isStart = true;
}

void MainScreen::draw()
{
	if (isDraw)
	{
		background->RenderTexture(0, 0, NULL);
		button->sprite->draw(80, 135, button->curAnimation, button->curFrame);
	}
}

MainScreen::MainScreen()
{
	isStart = false;
	isDraw = true;
	timeDraw.init(0.3, 5);
	timeDraw.start();
}


MainScreen::~MainScreen()
{
	delete background;
	delete button;
}
