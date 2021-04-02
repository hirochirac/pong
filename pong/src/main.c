#include <raylib.h>
#include <stdio.h>

typedef enum Direction { UP = 0, DOWN = 1 } Direction;
typedef enum Bool { FALSE = 0, TRUE = 1 } Bool;

#define WIDTH  800
#define HEIGHT 600

struct SPaddle {
	Vector2 position;
	Vector2 size;
	Color color;
};

struct SBall {
	Vector2 position;
	float dirX;
	float dirY;
	float ray;
	Color c;
};

typedef struct SPaddle Paddle;
typedef struct SBall Ball;

int paddle1 = 0;
int paddle2 = 0;

void limit();
void score();

int main (int argc, char** argv) {

	Bool start = FALSE;

	Ball b;
	b.position = (Vector2){WIDTH / 2,HEIGHT / 2};
	b.dirX = -1;
	b.dirY = -1;
	b.ray = 7;
	b.c = WHITE;

	Paddle p1;
	p1.color = WHITE;
	p1.position = (Vector2){10,HEIGHT/2-50};
	p1.size     = (Vector2){5,100};

	Paddle p2;
	p2.color = WHITE;
	p2.position = (Vector2){WIDTH-10,HEIGHT/2-50};
	p2.size = (Vector2){5,100};

	InitWindow(WIDTH,HEIGHT,"Pong");


	while (!WindowShouldClose()){

		BeginDrawing();
		ClearBackground(BLACK);

		if (IsKeyDown(KEY_SPACE) && start == FALSE){
			start = TRUE;
		} else {
			score(paddle1,paddle2);
		}

		if (start == TRUE){
			b.position.x += 0.07f * b.dirX;
			b.position.y += 0.07f * b.dirY;


			if (b.position.x < 0 || b.position.x > WIDTH) {

				if (b.position.x < 0){
					paddle2++;
					score(paddle1,paddle2);
				}

				if (b.position.x > WIDTH){
					paddle1++;
					score(paddle1,paddle2);
				}

				start = FALSE;
				b.position = (Vector2){WIDTH / 2,HEIGHT / 2};
				b.dirX = -1;
				b.dirY = -1;
				b.ray = 7;
				b.c = WHITE;
			}

			if (b.position.y <= 0 || b.position.y >= HEIGHT - b.ray){
				b.dirY = -b.dirY;
			}

			if (b.position.x <= p1.position.x && b.position.y >= p1.position.y && b.position.y <= p1.position.y + p1.size.y){
				b.dirX = -b.dirX;
			}

			if (b.position.x >= p2.position.x && b.position.y >= p2.position.y && b.position.y <= p2.position.y + p2.size.y){
				b.dirX = -b.dirX;
			}

		}

		if (IsKeyDown(KEY_KP_7)) {
			p1.position.y -= 0.09f;
		}

		if (p1.position.y < 0.0) {
			p1.position.y = 0.0;
		}

		if (IsKeyDown(KEY_KP_1)) {
			p1.position.y += 0.09f;
		}

		if (p1.position.y > HEIGHT-100.0f) {
			p1.position.y = HEIGHT-100.0f;
		}

		if (IsKeyDown(KEY_KP_9)) {
			p2.position.y -= 0.09f;
		}

		if (p2.position.y < 0.0) {
			p2.position.y = 0.0;
		}

		if (IsKeyDown(KEY_KP_3)) {
			p2.position.y += 0.09f;
		}

		if (p2.position.y > HEIGHT-100.0f) {
			p2.position.y = HEIGHT-100.0f;
		}

		DrawCircleV(b.position,b.ray, b.c);
		DrawRectangleV(p1.position,p1.size, p1.color);
		DrawRectangleV(p2.position,p2.size, p2.color);

		limit();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}



/**
 *
 */
void score(int pPaddle1, int pPaddle2) {
	DrawText(TextFormat("%i",pPaddle1), WIDTH/2-50, 0, 12, WHITE);
	DrawText(TextFormat("%i",pPaddle2), WIDTH/2+50, 0, 12, WHITE);
}


/**
 *
 */
void limit() {
	DrawLine(WIDTH/2, 0, WIDTH/2, HEIGHT, WHITE);
}
