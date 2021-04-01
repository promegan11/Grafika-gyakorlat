#include "game.h"
#include "draw.h"
#include "GL/glut.h"


static double p1_score=0;
static double p2_score=0;
void resize_game(Game* game, int width, int height)
{
    game->width = width;
    game->height = height;
    game->left_pad.size = 200;
    game->right_pad.size = 200;
    restart_game(game);
}

void restart_game(Game* game)
{
    float center_x;
    float center_y;

    center_x = game->width / 2;
    center_y = game->height / 2;

    move_pad(&(game->left_pad), center_y, game->height);
    move_pad(&(game->right_pad), center_y, game->height);
    start_ball(&(game->ball), center_x, center_y);
}

void update_game(Game* game, double time)
{
    if(p1_score >=3 && p2_score >=3){
    update_ball(&(game->ball), time*((float)(p1_score+p2_score+1)/5));
    }else{
        update_ball(&(game->ball), time*0.7);
    }
    if (game->ball.x - game->ball.radius < 50 && (game->ball.y + game->ball.radius > game->left_pad.position && game->ball.y - game->ball.radius < game->left_pad.position + game->left_pad.size )) {
        game->ball.x = game->ball.radius + 50;
        game->ball.speed_x *= -1;
        p2_score+=1;
        draw_score('2',p2_score);
    }else if(game->ball.x - game->ball.radius < 45){
        game->ball.x = game->width/2;
        if(p2_score > 1)
        p2_score-=1;
        draw_score('2',p2_score);
    }
    if (game->ball.x + game->ball.radius > game->width - 50 && (game->ball.y + game->ball.radius > game->right_pad.position && game->ball.y - game->ball.radius < game->right_pad.position + game->right_pad.size )) {
        game->ball.x = game->width - game->ball.radius - 50;
        
        game->ball.speed_x *= -1;
        p1_score+=1;
        draw_score('1',p1_score);
    }else if(game->ball.x + game->ball.radius > game->width - 45){
        game->ball.x = game->width/2;
        if(p1_score > 1)
        p1_score-=1;
        draw_score('1',p1_score);
    }
    if (game->ball.y - game->ball.radius < 0) {
        game->ball.y = game->ball.radius;
        game->ball.speed_y *= -1;

    }
    if (game->ball.y + game->ball.radius > game->height) {
        game->ball.y = game->height - game->ball.radius;
        game->ball.speed_y *= -1;
    }


}

void move_left_pad(Game* game, float position)
{
    move_pad(&(game->left_pad), position, game->height);
}

void move_right_pad(Game* game, float position)
{
    move_pad(&(game->right_pad), position, game->height);
}

