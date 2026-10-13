#include <raylib.h>

int main(void)
{
    int w = 800, h = 600;

    InitWindow(w, h, "Game");
    SetTargetFPS(100);

    // Player and circle
    int plwid = 100, plhei = 40;
    Rectangle player = {w/2 - plwid/2, h - plhei, plwid, plhei};
    float radius = 30;
    Vector2 circle = {GetRandomValue(radius, w-radius), 100};
    int speed = 300;
    int over = 0;
    int score = 0;
    Color colors[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
    int colcount = sizeof(colors) / sizeof(Color);
    Color col = colors[GetRandomValue(0, colcount - 1)];
    int difficuty = 1;
    
    while (!WindowShouldClose()) {
        // Update
        float dt = GetFrameTime();
        circle.y += difficuty * speed * dt;

        // Hit
        if (circle.y + radius >= player.y
            && circle.x >= player.x && circle.x <= player.x + player.width) {
            circle = (Vector2){GetRandomValue(radius, w-radius), 100};
            col = colors[GetRandomValue(0, colcount - 1)];
            score++;
        } else if (circle.y - radius > h) {
            over = 1;
        }

        // Key Processing
        if (IsKeyDown(KEY_A) && player.x >= 0) {
            player.x -= 2 * difficuty * speed * dt;
        }
        if (IsKeyDown(KEY_D) && player.x + player.width <= w) {
            player.x += 2 * difficuty * speed * dt;
        }
        if (IsKeyPressed(KEY_S) && difficuty > 1) {
            difficuty--;
        }
        if (IsKeyPressed(KEY_W) && difficuty < 4) {
            difficuty++;
        }

        if (over) {
            if (IsKeyPressed(KEY_SPACE)) {
                score = 0;
                over = 0;
                circle = (Vector2){GetRandomValue(radius, w-radius), 100};
                col = colors[GetRandomValue(0, colcount - 1)];
                difficuty = 1;
                continue;
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(GRAY);

        if (over) {
            DrawText(TextFormat("GAME OVER, SCORE: %d\nPRESS SPACE TO RETRY", score),
                     100, 100, 50, GREEN);
            EndDrawing();
            continue;
        }

        DrawRectangleRec(player, RED);
        DrawCircle(circle.x, circle.y, radius, col);
        DrawText(TextFormat("SCORE: %d | DIF: %d", score, difficuty), 10, 10, 30, WHITE);
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
