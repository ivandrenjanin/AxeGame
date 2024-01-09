#include "raylib.h"
#include <math.h>
#include <algorithm>

int main()
{
	// window config
	int width{ 800 };
	int height{ 600 };
	InitWindow(width, height, "Axe Game");
	SetTargetFPS(60);

	// circle config
	int circleX{ width / 2 };
	int circleY{ height / 2 };
	int moveAmount{ 10 };
	int circleRadius{ 80 };
	Color circleColor{ BLUE };

	// axe config
	int axeX{ 400 };
	int axeY{ 0 };
	int axeLength{ 150 };
	int directionY{ 2 };
	int directionX{ 2 };
	Color axeColor{ RED };

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);

		DrawCircle(circleX, circleY, circleRadius, circleColor);
		DrawRectangle(axeX, axeY, axeLength, axeLength, axeColor);

		// Move the axe in random directions on X and Y axis
		axeX += directionX;
		axeY += directionY;

		// Checking for collision between circle and axe using built-in function
		// if (CheckCollisionCircleRec(
		//	{ (float)circleX, (float)circleY }, (float)circleRadius, 
		//	{ (float)axeX, (float)axeY, (float)axeLength, (float)axeLength }))
		//{
		//	circleColor = DARKGRAY;
		//}
		//else
		//{
		//	circleColor = BLUE;
		//}

		// Checking for collision between circle and axe using math
		int p = circleX;
		int q = circleY;
		int r = circleRadius;
		double rSquared = pow(r, 2);

		int coordXa = axeX;
		int coordYa = axeY;

		double rA = pow(coordXa - p, 2) + pow(coordYa - q, 2);

		int coordXb = axeX + axeLength;
		int coordYb = axeY;

		double rB = pow(coordXb - p, 2) + pow(coordYb - q, 2);

		int coordXc = axeX;
		int coordYc = axeY + axeLength;

		double rC = pow(coordXc - p, 2) + pow(coordYc - q, 2);

		int coordXd = axeX + axeLength;
		int coordYd = axeY + axeLength;

		double rD = pow(coordXd - p, 2) + pow(coordYd - q, 2);

		int topAxeEdge = axeY;
		int bottomAxeEdge = axeY + axeLength;
		int leftAxeEdge = axeX;
		int rightAxeEdge = axeX + axeLength;

		// Circle edges coordinates
		int coordXe = p;
		int coordYe = q - r;

		int coordXg = p;
		int coordYg = q + r;

		int coordXh = p - r;
		int coordYh = q;
		
		int coordXF = p + r;
		int coordYF = q;

		// Check which sumCoord is closest to sumPQ
		int closestSumCoord = std::min({ rA, rB, rC, rD });

		// If it is closest draw a line between the two points (circle center and closest axe corner)
		if (closestSumCoord == rA)
		{
			DrawLine(p, q, coordXa, coordYa, BLACK);
		}
		else if (closestSumCoord == rB)
		{
			DrawLine(p, q, coordXb, coordYb, BLACK);
		}
		else if (closestSumCoord == rC)
		{
			DrawLine(p, q, coordXc, coordYc, BLACK);
		}
		else if (closestSumCoord == rD)
		{
			DrawLine(p, q, coordXd, coordYd, BLACK);
		}

		// Check if the circle is touching the edge of the axe
		if (coordXe >= leftAxeEdge && coordXe <= rightAxeEdge && coordYe >= topAxeEdge && coordYe <= bottomAxeEdge ||
			coordXg >= leftAxeEdge && coordXg <= rightAxeEdge && coordYg >= topAxeEdge && coordYg <= bottomAxeEdge ||
			coordXh >= leftAxeEdge && coordXh <= rightAxeEdge && coordYh >= topAxeEdge && coordYh <= bottomAxeEdge ||
			coordXF >= leftAxeEdge && coordXF <= rightAxeEdge && coordYF >= topAxeEdge && coordYF <= bottomAxeEdge)
		{
			circleColor = DARKGRAY;
		}
		// Check if axe corner is inside the circle
		else if (rA <= rSquared || rB <= rSquared || rC <= rSquared || rD <= rSquared)
		{
			circleColor = DARKGRAY;
		}
		else
		{
			circleColor = BLUE;
		}

		// If the axe hits the edge of the screen, change direction
		if (axeX + axeLength > width || axeX < 0)
		{
			directionX = -directionX;
		}

		if (axeY + axeLength > height || axeY < 0)
		{
			directionY = -directionY;
		}

		if (IsKeyDown(KEY_D) && circleX < width)
		{
			circleX += moveAmount;
		}

		if (IsKeyDown(KEY_A) && circleX > 0)
		{
			circleX -= moveAmount;
		}

		if (IsKeyDown(KEY_S) && circleY < height)
		{
			circleY += moveAmount;
		}

		if (IsKeyDown(KEY_W) && circleY > 0)
		{
			circleY -= moveAmount;
		}

		// Game logic end
		EndDrawing();
	}
}