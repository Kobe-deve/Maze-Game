#include "game_handler.h"

// g++ display_test.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -static-libstdc++ -std=c++11 -Wl,-rpath,./ -o display_test

// handles menu boxes in the game 
class menuHandler
{
	public:
		menuHandler(){}
		menuHandler(game_handler * g)
		{
			r = g->renderer;
			assets = image("resources/sprites/menu.png",g->renderer);
		}
		void display()
		{
			assets.flip = SDL_FLIP_NONE;
			assetShower = {0,0,50,50};
			assets.render(r,600,10,&assetShower,0);
			
			assetShower = {50,0,50,50};
			assets.render(r,650,10,&assetShower,0);
			assets.render(r,700,10,&assetShower,0);
			assets.render(r,750,10,&assetShower,0);
			assets.render(r,800,10,&assetShower,0);
			assetShower = {100,0,50,50};
			assets.render(r,850,10,&assetShower,0);
			
			assetShower = {150,0,50,50};
			assets.render(r,650,60,&assetShower,0);
			assets.render(r,700,60,&assetShower,0);
			assets.render(r,750,60,&assetShower,0);
			assets.render(r,800,60,&assetShower,0);
			
			assets.flip = SDL_FLIP_VERTICAL;
			assets.render(r,650,110,&assetShower,0);
			assets.render(r,700,110,&assetShower,0);
			assets.render(r,750,110,&assetShower,0);
			assets.render(r,800,110,&assetShower,0);
			
			assetShower = {50,0,50,50};
			assets.render(r,650,160,&assetShower,0);
			assets.render(r,700,160,&assetShower,0);
			assets.render(r,750,160,&assetShower,0);
			assets.render(r,800,160,&assetShower,0);
			
			assetShower = {0,0,50,50};
			assets.render(r,600,160,&assetShower,0);
			
			assets.flip = SDL_FLIP_NONE;
			assets.angle=180;
			assets.render(r,850,160,&assetShower,0);
			
			assetShower = {50,0,50,50};
			
			assets.angle=90;
			assets.render(r,850,60,&assetShower,0);
			assets.render(r,850,110,&assetShower,0);
			assets.angle=270;
			assets.render(r,600,60,&assetShower,0);
			assets.render(r,600,110,&assetShower,0);
			
			assets.angle=0;
			
		}
	private:
		SDL_Rect assetShower = {0,0,50,50};
		SDL_Renderer * r;
		image assets;
};

enum viewerMode{ CAMERA = 1,
				 GAMEPLAY = 2};

// top of brick size: (31,17)
class tester : public system_handler
{
	public:
		tester(){}
		tester(game_handler * g)
		{
			main_game = g;
			menu = menuHandler(g);
			
			brick = image("resources/sprites/brick.png",g->renderer);
			blank = image("resources/sprites/blank.png",g->renderer);
			stair = image("resources/sprites/stair.png",g->renderer);
			player = image("resources/sprites/player.png",g->renderer);
			
			enemy_test = image("resources/sprites/enemy_test.png",g->renderer);
			
			enemy_test.scale = 10;
			brick.scale = scale;
			blank.scale = scale;
			stair.scale = scale;
			player.scale = scale;
		}
		void display() override
		{
			brick.scale = scale;
			blank.scale = scale;
			stair.scale = scale;
			player.scale = scale;
			
			for(int z=0;z<10;z++)
			{
				for(int y=0;y<10;y++)
				{
					for(int x=0;x<10;x++)
					{
						switch(map[z][y][x])
						{
							case 1:
							brick.render(main_game->renderer,cameraX + x*40*scale,cameraY + y*20*scale);
							break;
						}
					}	
				}
			}
			
			menu.display();
			switch(mode)
			{
				case CAMERA:
				main_game->displayText.display("CAMERA",630,60);
				break;
				case GAMEPLAY:
				main_game->displayText.display("GAMEPLAY",630,60);
				cameraX = SCREEN_WIDTH/2-playerX;
				cameraY = SCREEN_HEIGHT/2-playerY;
				break;
			}
			
			player.render(main_game->renderer,cameraX+playerX,cameraY+playerY);
			
			/*
			brick.render(main_game->renderer,200,200 - 20*scale); // up left
			brick.render(main_game->renderer,200 + 20*scale,200 - 10*scale); // up
			brick.render(main_game->renderer,200 + 40*scale,200); // up right
			brick.render(main_game->renderer,200 - 20*scale,200 - 10*scale); // left 
			blank.render(main_game->renderer,200,200);
			brick.render(main_game->renderer,200-40*scale,200); // down left
			brick.render(main_game->renderer,200 - 20*scale,200 + 10*scale); // down 
			brick.render(main_game->renderer,200 + 20*scale,200 + 10*scale); // down right
			brick.render(main_game->renderer,200,200 + 20*scale); // right
			*/
		}
		void handler() override
		{
			switch(mode)
			{
				case CAMERA:
				switch(main_game->input.state)
				{
					case SELECT:
					break;
					case CANCEL:
					mode = GAMEPLAY;
					scale = 2;
					break;
					case UP:
					cameraY-=10;
					break;
					case DOWN:
					cameraY+=10;
					break;
					case RIGHT:
					cameraX+=10;
					break;
					case LEFT:
					cameraX-=10;
					break;
				}
				break;
				case GAMEPLAY:
				switch(main_game->input.state)
				{
					case SELECT:
					break;
					case CANCEL:
					mode = CAMERA;
					scale = 2;
					break;
					
					case DOWN:
					playerY+=40;
					break;
					case UP:
					playerY-=40;
					break;
					case LEFT:
					playerX-=80;
					break;
					case RIGHT:
					playerX+=80;
					break;
				}
				break;
			}
		}
	private:
		int map[10][10][10] = {{1,1,0,1,1,1,1,1,1,1,
							   0,1,0,1,1,1,1,1,1,1,
						   	   0,1,0,1,1,1,1,1,1,1,
						   	   0,1,1,0,1,1,1,1,1,1,
						   	   1,1,1,1,1,1,1,1,1,1,
						   	   0,1,1,1,1,1,1,1,1,1,
						   	   1,0,1,1,1,1,1,1,1,1,
						   	   1,1,0,1,1,1,1,1,1,1,
						   	   1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1}};
		
			
		viewerMode mode = CAMERA;
		menuHandler menu;
		
		int cameraX = 200;
		int cameraY = 200;
		
		int playerX = 0;
		int playerY = 0;
		
		int scale = 2;
		image brick;
		image stair;
		image blank;
		image player;
		image enemy_test;
};

int main()
{
	game_handler game = game_handler(0);
	
	
	game.backgroundOn = true;
	
	tester test = tester(&game);
	
	game.currentGame = &test;
	
	while(game.input.state != EXIT)
	{
		game.runSystem();
	}
	
	game.close();
	return 0;
}
