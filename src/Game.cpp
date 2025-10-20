# include "Game.h"


void Game::drawFadeIn(double t) const
{
	draw();
	Circle{ Scene::Size().x / 2, Scene::Size().y / 2, Scene::Size().x }
	.drawFrame(((1 - t) * Scene::Size().x), 0, ColorF{ 0.2, 0.3, 0.4 });



}

void Game::drawFadeOut(double t) const
{
	draw();
	Circle{ Scene::Size().x / 2, Scene::Size().y / 2, Scene::Size().x }
	.drawFrame((t * Scene::Size().x), 0, ColorF{ 0.2, 0.3, 0.4 });
}

void Game::update()
{
	if(MouseL.pressed()){
		changeScene(U"Title", 1.5s);
	}
}

void Game::draw() const
{
	
}
