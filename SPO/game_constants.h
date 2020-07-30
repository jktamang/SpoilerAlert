#pragma once
#include <string>

//Math Variables
const float PI = 3.14159f;

//Game Configuration
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int MAP_WIDTH = 3 * SCREEN_WIDTH;
const int MAP_HEIGHT = 3 * SCREEN_HEIGHT;
const int FPS = 60;

//Player Configuration
const int PLAYER_HEIGHT = 32;
const int PLAYER_WIDTH = 32;
const float PLAYER_ROTATION_SPEED = 5.0f;
const float PLAYER_MOVE_SPEED = 5.0f;
const int PLAYER_HEALTH = 100;
const int INVINCIBILITY_FRAMES = 30;
const std::string PLAYER_SPRITE_PATH = "Resources\\player.png";

//Enemy Configuration
const int ENEMY_COUNT = 2000;
const int ENEMY_WIDTH = 32;
const int ENEMY_HEIGHT = 32;
const int ENEMY_HEALTH = 1;
const float ENEMY_ROTATION_SPEED = 3.0f;
const float ENEMY_MOVE_SPEED = 4.0f;
const std::string ENEMY_SPRITE_PATH1 = "Resources\\enemy_dies.png";
const std::string ENEMY_SPRITE_PATH2 = "Resources\\enemy_lives.png";

//Bullet Configuration
const int BULLET_WIDTH = 8;
const int BULLET_HEIGHT = 8;
const float BULLET_MOVE_SPEED = 10.0f;
const int BULLET_HEALTH = 1;
const int BULLET_COUNT = 100;
const std::string BULLET_SPRITE_PATH = "Resources\\popcorn.png";

//Power Up Configuration
const int POWER_UP_DURATION = 10 * FPS;
const int POWER_UP_WIDTH = 32;
const int POWER_UP_HEIGHT = 32;
const int BUCKET_COUNT = 2;
const int SODA_COUNT = 2;
const std::string POWER_UP_SPRITE_PATH1 = "Resources\\bucket.png";
const std::string POWER_UP_SPRITE_PATH2 = "Resources\\soda.png";

//Obstacle Stats
const int OBSTACLE_WIDTH = 32;
const int OBSTACLE_HEIGHT = 64;
const int OBSTACLE_COUNT = 50;
const std::string OBSTACLE_SPRITE_PATH = "Resources\\pillar.png";

//UI Image Paths
const std::string BACKGROUND_IMAGE_PATH = "Resources\\background.png";
const std::string MENU_IMAGE_PATH = "Resources\\menu.png";
const std::string GAME_OVER_IMAGE_PATH = "Resources\\game_over.png";
const std::string PAUSE_IMAGE_PATH = "Resources\\pause_menu.png";

//Other File Paths
const std::string BACKGROUND_MUSIC_PATH = "Resources\\background.mp3";
const std::string GAME_OVER_MUSIC_PATH = "Resources\\game_over.mp3";
const std::string POWER_UP_SOUND_PATH = "Resources\\power_up.wav";
const std::string DEATH_SOUND_PATH = "Resources\\death.mp3";
const std::string SCORE_FILE_PATH = "score.spo";

//Grid Stats
const int CELL_SIZE = 64;
const int GRID_WIDTH = (MAP_WIDTH/CELL_SIZE) + 1;
const int GRID_HEIGHT = (MAP_HEIGHT/CELL_SIZE) + 1;

//Colors
const SDL_Color GREEN = {0x00, 0xFF, 0x00};
const SDL_Color YELLOW = {0xFF, 0xFF, 0x00};
const SDL_Color RED = {0xFF, 0x00, 0x00};
const SDL_Color BLACK = {0x00, 0x00, 0x00};
const SDL_Color WHITE = {0xFF, 0xFF, 0xFF};