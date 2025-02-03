#include "raylib.h"

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define CELL_SIZE 200

enum Cell { EMPTY, PLAYER_X, PLAYER_O };
enum GameState { NONE, PLAYER_X_WON, PLAYER_O_WON, DRAW };

Cell board[3][3];
GameState state;
int currentPlayer;

bool isMenuActive = true;

void InitGame() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = EMPTY;
        }
    }
    state = NONE;
    currentPlayer = PLAYER_X;
}

void DrawBoard() {
    for (int i = 1; i < 3; i++) {
        DrawLine(i * CELL_SIZE, 0, i * CELL_SIZE, SCREEN_HEIGHT, WHITE);
        DrawLine(0, i * CELL_SIZE, SCREEN_WIDTH, i * CELL_SIZE, WHITE);
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == PLAYER_X) {
                DrawLineEx({ static_cast<float>(j * CELL_SIZE) + 20, static_cast<float>(i * CELL_SIZE) + 20 },
                    { static_cast<float>((j + 1) * CELL_SIZE) - 20, static_cast<float>((i + 1) * CELL_SIZE) - 20 },
                    10, RED);
                DrawLineEx({ static_cast<float>((j + 1) * CELL_SIZE) - 20, static_cast<float>(i * CELL_SIZE) + 20 },
                    { static_cast<float>(j * CELL_SIZE) + 20, static_cast<float>((i + 1) * CELL_SIZE) - 20 },
                    10, RED);
            }
            else if (board[i][j] == PLAYER_O) {
                int thickness = 10; // Adjust this value to make the O thicker or thinner
                for (int k = 0; k < thickness; k++) {
                    DrawCircleLines(static_cast<float>(j * CELL_SIZE) + CELL_SIZE / 2,
                        static_cast<float>(i * CELL_SIZE) + CELL_SIZE / 2,
                        CELL_SIZE / 2 - 10 - k, BLUE);
                }
            }
        }
    }
}

GameState CheckWin() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != EMPTY)
            return (board[i][0] == PLAYER_X) ? PLAYER_X_WON : PLAYER_O_WON;

        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != EMPTY)
            return (board[0][i] == PLAYER_X) ? PLAYER_X_WON : PLAYER_O_WON;
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != EMPTY)
        return (board[0][0] == PLAYER_X) ? PLAYER_X_WON : PLAYER_O_WON;

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != EMPTY)
        return (board[0][2] == PLAYER_X) ? PLAYER_X_WON : PLAYER_O_WON;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) {
                return NONE;
            }
        }
    }

    return DRAW;
}

void UpdateGame() {
    if (state == NONE) {
        Vector2 mousePos = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            int col = mousePos.x / CELL_SIZE;
            int row = mousePos.y / CELL_SIZE;
            if (col >= 0 && col < 3 && row >= 0 && row < 3 && board[row][col] == EMPTY) {
                board[row][col] = static_cast<Cell>(currentPlayer);
                currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
                state = CheckWin();
            }
        }
    }
}

void DrawGame() {
    BeginDrawing();
    ClearBackground(BLACK); // Change background color to black
    DrawBoard();

    if (state == PLAYER_X_WON) {
        DrawText("Player X Wins!", 200, 280, 40, YELLOW);
    }
    else if (state == PLAYER_O_WON) {
        DrawText("Player O Wins!", 200, 280, 40, YELLOW);
    }
    else if (state == DRAW) {
        DrawText("It's a Draw!", 240, 280, 40, YELLOW);
    }

    EndDrawing();
}

// Function to handle menu
void Menu() {
    while (isMenuActive) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Tic Tac Toe", SCREEN_WIDTH / 2 - MeasureText("Tic Tac Toe", 50) / 2, SCREEN_HEIGHT / 2 - 50, 50, YELLOW);
        if (CheckCollisionPointRec(GetMousePosition(), { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2, 200, 50 })) {
            DrawRectangleRec({ SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2, 200, 50 }, RED);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                InitGame();
                isMenuActive = false;
            }
        }
        else {
            DrawRectangleRec({ SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2, 200, 50 }, MAROON);
        }
        DrawText("Play", SCREEN_WIDTH / 2 - MeasureText("Play", 40) / 2, SCREEN_HEIGHT / 2 + 5, 40, YELLOW);
        EndDrawing();
    }
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tic Tac Toe with Raylib");

    InitGame();

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (isMenuActive) {
            Menu();
        }
        else {
            UpdateGame();
            DrawGame();
        }
    }

    CloseWindow();

    return 0;
}
