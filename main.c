#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"

#define MAX_INPUT_CHARS 256

int main(void)
{
    // Inizializza la finestra
    InitWindow(0, 0, "Magic 8");
    ToggleFullscreen();

    // Imposta il colore di sfondo della finestra
    SetTargetFPS(60); // Imposta il framerate a 60 fps

    // Inizializza il generatore di numeri casuali
    srand(time(NULL));

    // Crea il cerchio
    int circleRadius = 100;
    Vector2 circlePosition = {(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 + 80};
    Color grayColor = GRAY;
    Color greenColor = GREEN;
    Color redColor = RED;
    Color lastAnswerColor = grayColor;

    // Ciclo principale del gioco
    char inputText[MAX_INPUT_CHARS] = ""; // Testo inserito dall'utente
    bool answerGenerated = false; // Indica se una risposta è stata generata
    bool backspacePressed = false; // Indica se l'utente ha premuto il tasto freccia indietro

    while (!WindowShouldClose()) // Verifica se la finestra è stata chiusa
    {
        // Pulisce lo schermo
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Chiedi all'utente di fare una domanda
        Vector2 questionTextPosition = {(float)GetScreenWidth() / 2 - MeasureText("Fai una domanda e premi INVIO", 30) / 2, (float)GetScreenHeight() / 2 - 300};
        DrawText("Fai una domanda e premi INVIO", questionTextPosition.x, questionTextPosition.y, 30, BLACK);

        // Disegna il testo inserito dall'utente
        Vector2 inputTextPosition = {(float)GetScreenWidth() / 2 - MeasureText(inputText, 20) / 2, (float)GetScreenHeight() / 2 - 200};
        DrawText(inputText, inputTextPosition.x, inputTextPosition.y, 20, BLACK);

        // Verifica se l'utente ha premuto il tasto INVIO
        if (IsKeyPressed(KEY_ENTER))
        {
            if (!answerGenerated && strlen(inputText) > 0) // Se una risposta non è stata già generata e il testo non è vuoto
            {
                // Genera una risposta casuale
                int randomNum = rand() % 2; // Genera un numero casuale tra 0 e 1

                switch (randomNum)
                {
                case 0:
                    lastAnswerColor = greenColor;
                    break;
                case 1:
                    lastAnswerColor = redColor;
                    break;
                }

                answerGenerated = true;
                inputText[0] = '\0'; // Cancella il testo
            }
        }
        else
        {
            answerGenerated = false;
        }

        // Verifica se l'utente ha premuto il tasto freccia indietro per cancellare il testo inserito
        if (IsKeyPressed(KEY_BACKSPACE))
        {
            backspacePressed = true;
        }
        else if (IsKeyReleased(KEY_BACKSPACE))
        {
            backspacePressed = false;
        }

        // Acquisisce l'input dell'utente
        if (!answerGenerated && !backspacePressed)
        {
            int keyPressed = GetKeyPressed();
            if (keyPressed > 0 && keyPressed != KEY_ENTER && strlen(inputText) < MAX_INPUT_CHARS - 1)
            {
                char keyStr[2] = {(char)keyPressed, '\0'};
                strcat(inputText, keyStr);
            }
        }
        else if (backspacePressed && strlen(inputText) > 0)
        {
            inputText[strlen(inputText) - 1] = '\0'; // Cancella l'ultimo carattere
        }

        // Disegna il cerchio
        DrawCircleV(circlePosition, circleRadius, lastAnswerColor);

        EndDrawing();
    }

    // Chiude la finestra
    CloseWindow();

    return 0;
}
