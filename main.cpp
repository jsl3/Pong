#include "raylib.h"   // Including the Raylib library, which is used for graphics and input handling.
#include <cstdlib>

int main() {
    // Initialization
    InitWindow(1200, 800, "Pong Game");  // Initialize the game window with a size of 1800x900 pixels and a title "Pong Game".

    srand(GetRandomValue(0, 10000));  // Seed the random number generator to generate random values later.

    float randomHeight = GetRandomValue(10, 90);  // Generate a random value between 10 and 90 and store it in randomHeight.
    int ballDirection = 1; // Initialize a variable to track the direction of the ball (up or down). 1 represents the ball going down, -1 represents the ball going up.

    // Initialize the ball's position with random height
    Vector2 ballPosition = { static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) * (randomHeight / 100) }; // Set the initial position of the ball to the middle of the screen horizontally and a random height vertically.
    int ballDirectionX = (GetRandomValue(0, 1) == 0) ? -1 : 1; // Randomly set the horizontal direction to left or right.
    int ballDirectionY = (GetRandomValue(0, 1) == 0) ? -1 : 1; // Randomly set the vertical direction to up or down.
    Vector2 ballSpeed = { 7.0f * ballDirectionX, 7.0f * ballDirectionY }; // Set the initial speed of the ball in both horizontal and vertical directions.
    
    Vector2 leftPaddlePosition = { 10.0f, static_cast<float>(GetScreenHeight()) / 2 - 40.0f }; // Set the initial position of the left paddle.
    Vector2 rightPaddlePosition = { static_cast<float>(GetScreenWidth()) - 30.0f, static_cast<float>(GetScreenHeight()) / 2 - 40.0f }; // Set the initial position of the right paddle.
    float paddleHeight = 80.0f; // Define the height of the paddles.

    float leftPaddleSpeed = 0.0f; // Initialize the speed of the left paddle.
    float rightPaddleSpeed = 0.0f; // Initialize the speed of the right paddle.

    int leftPlayerScore = 0;  // Initialize the left player's score to zero.
    int rightPlayerScore = 0; // Initialize the right player's score to zero.

    int gameState = 0; // 0 for controls screen, 1 for playing, 2 for pause, 3 for restart

    int previousBallDirectionX = 0; // Store the previous ball direction
    int previousBallDirectionY = 0; // Store the previous ball direction
    int winner = 0; // Initialize the winner player to zero.

    SetTargetFPS(60);  // Set the target frames per second to 60 for smooth gameplay.

    // Main game loop
    while (!WindowShouldClose()) {  // Continue the game loop until the window is closed.

        // Initialize background colors for both players
        Color backgroundColorTopLeft = BLUE;
        Color backgroundColorTopRight = GREEN;
        Color backgroundColorBottomLeft = DARKBLUE;
        Color backgroundColorBottomRight = DARKGREEN;

        // Drawing
        BeginDrawing();  // Begin rendering the frame.

        // Clear the background with a segmented color scheme
        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();
        int halfScreenWidth = screenWidth / 2;
        int halfScreenHeight = screenHeight / 2;

        // Draw the top-left segment
        DrawRectangle(0, 0, halfScreenWidth, halfScreenHeight, backgroundColorTopLeft);

        // Draw the top-right segment
        DrawRectangle(halfScreenWidth, 0, halfScreenWidth, halfScreenHeight, backgroundColorTopRight);

        // Draw the bottom-left segment
        DrawRectangle(0, halfScreenHeight, halfScreenWidth, halfScreenHeight, backgroundColorBottomLeft);

        // Draw the bottom-right segment
        DrawRectangle(halfScreenWidth, halfScreenHeight, halfScreenWidth, halfScreenHeight, backgroundColorBottomRight);

        // Draw paddles and ball
        DrawRectangleRec({ static_cast<float>(leftPaddlePosition.x), leftPaddlePosition.y, 20.0f, paddleHeight }, WHITE);
        DrawRectangleRec({ static_cast<float>(rightPaddlePosition.x), rightPaddlePosition.y, 20.0f, paddleHeight }, WHITE);
        DrawCircleV(ballPosition, 10.0f, WHITE);  // Draw the ball as a circle.

        // Display the scores for both players in the center of their respective sides, higher up, and with bigger text.
        DrawText(TextFormat("%d", leftPlayerScore), GetScreenWidth() / 4 - MeasureText(TextFormat("%d", leftPlayerScore), 80) / 2, 20, 80, WHITE);
        DrawText(TextFormat("%d", rightPlayerScore), 3 * GetScreenWidth() / 4 - MeasureText(TextFormat("%d", rightPlayerScore), 80) / 2, 20, 80, WHITE);

        // Display the "Press P to pause" message.
        DrawText("Press P to pause the game", halfScreenWidth - MeasureText("Press P to pause the game", 20) / 2, 20, 20, WHITE);

        if (gameState == 0) {
            // Display the controls screen
            DrawText("Pong Game Controls", halfScreenWidth - MeasureText("Pong Game Controls", 40) / 2, halfScreenHeight - 100, 40, WHITE);
            DrawText("Player 1 (Left Paddle): W (Up) - S (Down)", halfScreenWidth - MeasureText("Player 1 (Left Paddle): W (Up) - S (Down)", 30) / 2, halfScreenHeight - 50, 30, WHITE);
            DrawText("Player 2 (Right Paddle): Up Arrow (Up) - Down Arrow (Down)", halfScreenWidth - MeasureText("Player 2 (Right Paddle): Up Arrow (Up) - Down Arrow (Down)", 30) / 2, halfScreenHeight, 30, WHITE);
            DrawText("Press SPACE to Start", halfScreenWidth - MeasureText("Press SPACE to Start", 30) / 2, halfScreenHeight + 50, 30, WHITE);

            if (IsKeyPressed(KEY_SPACE)) {
                gameState = 1;  // Transition to playing state when SPACE is pressed
            };
        }

        if (gameState == 1) {
            // Update the ball's position
            ballPosition.x += ballSpeed.x;
            ballPosition.y += ballSpeed.y;
            // Handle paddle movement with boundary checks
            if (IsKeyDown(KEY_W) && leftPaddlePosition.y > 0) {  // Move the left paddle up if the 'W' key is pressed and the paddle is not at the top.
                leftPaddleSpeed = -10.0f;
            }
            else if (IsKeyDown(KEY_S) && leftPaddlePosition.y + paddleHeight < GetScreenHeight()) {  // Move the left paddle down if the 'S' key is pressed and the paddle is not at the bottom.
                leftPaddleSpeed = 10.0f;
            }
            else {
                leftPaddleSpeed = 0.0f; // Stop the left paddle if no movement key is pressed.
            }

            if (IsKeyDown(KEY_UP) && rightPaddlePosition.y > 0) {  // Move the right paddle up if the 'Up' arrow key is pressed and the paddle is not at the top.
                rightPaddleSpeed = -10.0f;
            }
            else if (IsKeyDown(KEY_DOWN) && rightPaddlePosition.y + paddleHeight < GetScreenHeight()) {  // Move the right paddle down if the 'Down' arrow key is pressed and the paddle is not at the bottom.
                rightPaddleSpeed = 10.0f;
            }
            else {
                rightPaddleSpeed = 0.0f; // Stop the right paddle if no movement key is pressed.
            }
        }
        else {
            // Pause the paddles in state 2 and 3
            leftPaddleSpeed = 0.0f;
            rightPaddleSpeed = 0.0f;
        }

        // Update the paddle positions based on their speeds
        leftPaddlePosition.y += leftPaddleSpeed;
        rightPaddlePosition.y += rightPaddleSpeed;

        // Handle ball collision with the top and bottom boundaries
        if (gameState == 1) {
            if (ballPosition.y - 21.0f <= 0 || ballPosition.y + 21.0f >= GetScreenHeight()) {
                ballSpeed.y = -ballSpeed.y;  // Reverse the vertical direction of the ball's speed to simulate bouncing.
            }
        }

        // Handle ball collision with paddles (improved collision detection)
        if (ballPosition.x - 21.0f <= leftPaddlePosition.x + 20.0f &&
            ballPosition.x - 21.0f >= leftPaddlePosition.x &&
            ballPosition.y >= leftPaddlePosition.y && ballPosition.y <= leftPaddlePosition.y + paddleHeight) {
            ballSpeed.x = -ballSpeed.x;
        }
        else if (ballPosition.x + 21.0f >= rightPaddlePosition.x &&
            ballPosition.x + 21.0f <= rightPaddlePosition.x + 20.0f &&
            ballPosition.y >= rightPaddlePosition.y && ballPosition.y <= rightPaddlePosition.y + paddleHeight) {
            ballSpeed.x = -ballSpeed.x;
        }

        if (gameState == 1) {
            if (ballPosition.x - 21.0f <= 0) {
                rightPlayerScore++;
                if (rightPlayerScore >= 9) {
                    gameState = 3; // Set the game state to restart
                    winner = 2;
                } 
                else {
                    // The following logic ensures that the score doesn't increment in state 2
                    randomHeight = GetRandomValue(10, 90);
                    ballPosition = { static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) * (randomHeight / 100) };
                    ballDirection = rightPlayerScore % 2 == 0 ? 1 : -1;
                    ballSpeed = { -7.0f, 7.0f * ballDirection };
                }
            }
        }

        if (gameState == 1) {
            if (ballPosition.x + 21.0f >= GetScreenWidth()) {
                leftPlayerScore++;
                if (leftPlayerScore >= 9) {
                    gameState = 3; // Set the game state to restart
                    winner = 1;
                } 
                else {
                    // The following logic ensures that the score doesn't increment in state 3
                    randomHeight = GetRandomValue(10, 90);
                    ballPosition = { static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) * (randomHeight / 100) };
                    ballDirection = leftPlayerScore % 2 == 0 ? 1 : -1;
                    ballSpeed = { 7.0f, 7.0f * ballDirection };
                }
            }
        }

        if (IsKeyPressed(KEY_P)) {
            if (gameState == 1) {
                gameState = 2; // Pause the game
                previousBallDirectionX = static_cast<int>(ballSpeed.x); // Store the previous horizontal direction
                previousBallDirectionY = static_cast<int>(ballSpeed.y); // Store the previous vertical direction
                ballSpeed = { 0.0f, 0.0f }; // Pause the ball
            } else if (gameState == 2) {
                gameState = 1; // Unpause the game
                // Resume the ball's speed based on the previous direction
                ballSpeed = { static_cast<float>(previousBallDirectionX), static_cast<float>(previousBallDirectionY) };
                // You can also resume any other paused elements here.
            }
        }

        if (gameState == 1) {
            // Handle game logic while playing.
        } else if (gameState == 2) {
            // Handle game logic while paused.
            // Display a "Game Paused" message on the screen.
            DrawText("Game Paused", halfScreenWidth - MeasureText("Game Paused", 40) / 2, halfScreenHeight - 20, 40, WHITE);
        } else if (gameState == 3) {
            // Handle game restart logic (e.g., resetting scores, positions, and resuming the game).
            // You can display a restart message here.
        }

        if (gameState == 3) {
            ballSpeed = { 0, 0 }; // Pause the ball
            leftPaddlePosition = { 10.0f, static_cast<float>(GetScreenHeight()) / 2 - 40.0f }; // Reset left paddle position
            rightPaddlePosition = { static_cast<float>(GetScreenWidth()) - 30.0f, static_cast<float>(GetScreenHeight()) / 2 - 40.0f }; // Reset right paddle position
            if (IsKeyPressed(KEY_R)) {
                leftPlayerScore = 0;
                rightPlayerScore = 0;
                ballDirectionX = (GetRandomValue(0, 1) == 0) ? -1 : 1; // Randomly set the horizontal direction to left or right.
                ballDirectionY = (GetRandomValue(0, 1) == 0) ? -1 : 1; // Randomly set the vertical direction to up or down.
                ballSpeed = { 7.0f * ballDirectionX, 7.0f * ballDirectionY }; // Set the ball's speed based on random directions.
                randomHeight = GetRandomValue(10, 90); // Generate a new random height
                ballPosition = { static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) * (randomHeight / 100) }; // Set the ball's initial position
                gameState = 1;
            }

            if (winner > 0) {
                // Draw the winning message
                DrawText(TextFormat("Player %d Wins!", winner), halfScreenWidth - MeasureText(TextFormat("Player %d Wins!", winner), 60) / 2, halfScreenHeight - 60, 60, WHITE);

                // Add the "Press R to restart" message
                DrawText("Press R to restart", halfScreenWidth - MeasureText("Press R to restart", 30) / 2, halfScreenHeight + 30, 30, WHITE);
            }
        }

        EndDrawing();  // End rendering the frame.
    }

    // Cleanup
    CloseWindow();  // Close the game window and release resources.

    return 0;  // Return 0 to indicate a successful execution.
}