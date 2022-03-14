// Include Pre-Processors
#include "FEHLCD.h"
#include "FEHUtility.h"
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstring>
#include <iostream>
using namespace std;

// Class Function named Game
class Game 
{
    // Public variables -- Has all the functions
    public:
        Game();
        void Intro_Scene(); // Function for the Intro Scene
        void main_menu(); // Function for the Main Menu -- Buttons for Options
        void button_maker(); // Function that makes the Buttons
        void create_Background(); // Function that creates the background in the game
        void play_Button(); // Function for the play Button
        void credits_Button(); // Function for the credits Button
        void manual_Button(); // Function for the instructions
        void stats_Button(); // Function for the stats
        void jump(); // Function for the jumping of green character
        void obstacle(); // Function for making and moving obstacle
        void dinoGame(); // Function for running the game
        bool collision(); // Function for collisions
        void enteringgame(); // Function for entering the game screen
        void gameOver(); // Function for gameOver Screen
        void Updatescore(); // Function for Updating the Score in real time while game is going on

    // Private Variables -- Has all the global variables
    private:
        FEHIcon::Icon play_button; //Assign an icon name
        FEHIcon::Icon credits_button;
        FEHIcon::Icon manual_button;
        FEHIcon::Icon stats_button;
        float x,y, player, obst; // Assign global floats and ints
        int countobst, high_score;
};

// Int Main Function -- RUNS GAME IN REAL TIME.
int main() 
{
    printf ("******************************************************\n");
	printf ("*  Name: Vraj Shah and Aidan Ormsbee  Date: 12/07/21 *\n");
	printf ("*  Team: F1    File: dinogame.cpp                    *\n");
	printf ("*  Instructor: Clingan 10:20                         *\n");
	printf ("******************************************************\n\n");

    // Specify name for Game prototype
    Game game;
    // Call the Certain Functions to run full game.
    game.Intro_Scene();
    game.main_menu();

    // Update in real time.
    while (1) {
        LCD.Update();
    }
    return 0;
}

/* ---------------------------- FUNCTIONS ------------------------------------ */

// Game Prototype Function
Game::Game()
{
    // Initialize all counter variables to beginning values.
    obst = 200;
    countobst = 0;
    high_score = 0;
    player = 100;
}

// Intro Scene Function
void Game::Intro_Scene()
{
    // Set Background Color
    LCD.SetBackgroundColor(BLACK);
    LCD.Clear();
    // Set Font Color
    LCD.SetFontColor(LCD.White);
    Sleep(1.0);
    // Write text with the row and columns specified
    LCD.WriteRC(".",6, 12);
    // Sleep in between each load session animation.
    Sleep(1.0);
    LCD.WriteRC(".",6, 13);
    Sleep(1.0);
    LCD.WriteRC(".",6, 14);
    Sleep(1.5);
    LCD.Clear();

    // Write more things for Intro Scene 
    LCD.WriteRC("No Internet", 4, 7);
    Sleep(2.0);

    LCD.WriteRC("LOADING",6, 8);
    Sleep(1.0);
    LCD.WriteRC(".",6, 15);
    Sleep(1.0);
    LCD.WriteRC(".",6, 16);
    Sleep(1.0);
    LCD.WriteRC(".",6, 17);
    Sleep(2.0);
}

// Creating the Background Function
void Game::create_Background()
{
    LCD.Clear();
    // Add Shapes with different colors to add to Background
    LCD.SetFontColor(LIGHTBLUE);
    LCD.FillRectangle(0, 0, 320, 120);
    // Make Sun
    LCD.SetFontColor(YELLOW);
    LCD.FillCircle(20, 20, 10);
    LCD.SetFontColor(TAN);
    LCD.FillRectangle(120, 120, 320, 120);
    LCD.SetFontColor(WHITE);
    // Make the clouds
    LCD.FillRectangle(30, 80, 20, 10);
    LCD.FillRectangle(35, 75, 10, 5);
    LCD.FillRectangle(40, 30, 20, 10);
    LCD.FillRectangle(45, 25, 10, 5);
    LCD.FillRectangle(110, 50, 20, 10);
    LCD.FillRectangle(115, 45, 10, 5);
    LCD.FillRectangle(225, 70, 20, 10);
    LCD.FillRectangle(230, 65, 10, 5);
    LCD.FillRectangle(245, 30, 20, 10);
    LCD.FillRectangle(250, 25, 10, 5);

}

// Button Making function
void Game::button_maker()
{
    // Use the SetProperties built-in function to create Icons
    play_button.SetProperties("PLAY", 50, 50, 80, 80, WHITE, BLACK);

    credits_button.SetProperties("CREDIT", 200, 50, 80, 80, WHITE, BLACK);

    manual_button.SetProperties("MANUAL", 50, 150, 80, 80, WHITE, BLACK);

    stats_button.SetProperties("STATS", 200, 150, 80, 80, WHITE, BLACK);
}

// Main Menu Function
void Game::main_menu()
{
    while(1)
    {
        // Set Background and Game Name
        LCD.SetBackgroundColor(RED);
        LCD.Clear();

        LCD.SetFontColor(LCD.Black);
        LCD.DrawRectangle(0,0,320,240);
        LCD.WriteRC("DINOSAURUS RUN!!!", 1, 5);

        button_maker();
        // Draw the variables from the Icon into the main menu.
        play_button.Draw();
        credits_button.Draw();
        manual_button.Draw();
        stats_button.Draw();
    
        // While Not Touched
        while(!LCD.Touch(&x, &y));        
        // While Touched
        while(LCD.Touch(&x, &y)){}
        // If the Icon is pressed in specific x and y coordinate
        if (play_button.Pressed(x,y,0))
        {
            // Call and Run Specified Function
            play_Button();
            // Break out of menu while loop.
            break;
        }
        if (credits_button.Pressed(x,y,0))
        {
            credits_Button();
        }
        if (manual_button.Pressed(x,y,0))
        {
            manual_Button();
        }
        if (stats_button.Pressed(x,y,0))
        {
            stats_Button();
        }
    }
}

// The Play Button Function
void Game::play_Button()
{
    // Call three functions:
    enteringgame(); // Enter game loading screen

    create_Background(); // Create the background
 
    dinoGame(); // Run the Dinosaur Game
}

// The Credits Button function
void Game::credits_Button()
{
    // Add Background and text for Credits using FEHLCD.h library
    LCD.SetBackgroundColor(LIGHTBLUE);
    LCD.Clear();
    LCD.SetFontColor(BLACK);
    LCD.WriteRC("Created by Vraj Shah", 1, 3);
    LCD.WriteRC("and Aidan Ormsbee", 2, 4);
    LCD.WriteRC("- Used the FEH", 4, 5);
    LCD.WriteRC("Proteus Site.", 5, 5);
    LCD.SetFontColor(TAN);
    LCD.DrawHorizontalLine(110,40,280);
    LCD.SetFontColor(BLACK);
    LCD.WriteRC("Click AGAIN to go", 11, 1);
    LCD.WriteRC("back to menu!", 12, 1);
    // Going back to the main_menu()
    while(!LCD.Touch(&x, &y));
    while(LCD.Touch(&x, &y));
    LCD.Clear();
    main_menu();
}

// The Manual Button function
void Game::manual_Button()
{
    // Add Background and text for Manual using FEHLCD.h library
    LCD.SetBackgroundColor(LIGHTBLUE);
    LCD.Clear();
    LCD.SetFontColor(BLACK);
    LCD.WriteRC("- Tap to jump.", 1, 3); 
    LCD.WriteRC("- Avoid RED obstacles!", 2, 3);
    LCD.WriteRC("- Get the High Score!", 3, 3);
    LCD.SetFontColor(TAN);
    LCD.DrawHorizontalLine(80,40,280);
    LCD.SetFontColor(BLACK);
    LCD.WriteRC("Click AGAIN to go", 11, 1);
    LCD.WriteRC("back to menu!", 12, 1);
    // Going back to the main_menu()
    while(!LCD.Touch(&x, &y));
    while(LCD.Touch(&x, &y)){}
    LCD.Clear();
    main_menu();
}

// The Stats Button Functions
void Game::stats_Button()
{
    // Add Background and text for Credits using FEHLCD.h library
    LCD.SetBackgroundColor(LIGHTBLUE);
    LCD.Clear();
    LCD.SetFontColor(BLACK);
    LCD.WriteRC("HIGHEST SCORE: ",6, 7);
    LCD.WriteRC(high_score, 7, 7);
    LCD.SetFontColor(BLACK);
    LCD.WriteRC("Click AGAIN to go", 11, 1);
    LCD.WriteRC("back to menu!", 12, 1);
    // Going back to the main_menu()
    while(!LCD.Touch(&x, &y));
    while(LCD.Touch(&x, &y));
    LCD.Clear();
    main_menu();
}

// Red Obstacle Function
void Game::obstacle() 
{
    // Set Colors
    LCD.SetFontColor(RED);
    // if # of obstacles past is less than, greater than, or equal too.
    if (countobst < 5)
    {
        // Change speed to make obstacle go faster.
        obst -= 4;
    }
    if (countobst >= 5 && countobst < 10)
    {
        obst -= 6;
    }
    
    if (countobst >= 10 && countobst < 15)
    {
        obst -= 8;
    }
    if (countobst >= 15 && countobst < 35)
    {
        obst -= 10;
    }
    // if # of obstacles past is 34
    if (countobst == 34) 
    {
        // Give user a warning to get Ready
        LCD.SetFontColor(BLACK);
        LCD.WriteAt("Get Ready...!", 91, 10);
        LCD.SetFontColor(RED);
    }
    if (countobst == 35) 
    {
        LCD.SetFontColor(LIGHTBLUE);
        LCD.FillRectangle(91, 10, 160, 20);
        LCD.SetFontColor(RED);
    }
    if (countobst >= 35 && countobst < 40)
    {
        obst -= 20;
    }
    // IMPOSSIBLE ROUND...
    if (countobst == 39) 
    {
        // Give user a warning to get Ready
        LCD.SetFontColor(BLACK);
        LCD.WriteAt("IMPOSSIBLE...", 91, 10);
        LCD.SetFontColor(RED);
    }
    if (countobst == 49) 
    {
        LCD.SetFontColor(LIGHTBLUE);
        LCD.FillRectangle(91, 10, 160, 20);
        LCD.SetFontColor(RED);
    }
    // Literally will make you die if you get here
    if (countobst >=40 && countobst < 999)
    {
        obst -= 25;
    }
    
    // Move Obstacle in x-direction.
    LCD.FillCircle(obst - 1, 110, 5);
    LCD.SetFontColor(LIGHTBLUE);
    LCD.FillRectangle(obst + 9, 100, 15, 20);
    LCD.Update();
    // if obstacle is less than 0
    if (obst < 0) 
    {
        // reset obstacle position
        obst = 319;
        // count how many obstacles pass through
        countobst++;
        // reset and clear background position with LIGHTBLUE
        LCD.SetFontColor(LIGHTBLUE);
        LCD.FillCircle(0, 110, 5);
        LCD.FillCircle(310, 110, 5);
    }
}

// Green Character Function
void Game::jump() 
{
    // if touch is deteced
    if (LCD.Touch(&x, &y))
    {
        // and if player is on ground
        if (player == 100)
        {
            // move player up to height of 76
            player -= 76;
        } 
    }
    // If player is less than 0
    if (player < 0)
    {
        // Reset player to 0
        player = 0; 
    }
    // Clear background with rectangle
    LCD.SetFontColor(LIGHTBLUE);
    LCD.FillRectangle(80, 0, 20, 120);
    // Move player down in intervals of 6
    player += 6;
    // If player is greater than 100
    if (player > 100)
    {
        // Reset player value to 100
        player = 100;
    }
    // Set color of player
    LCD.SetFontColor(GREEN);
    // Move Green character every interval when player is called.
    LCD.FillRectangle(80, player, 20, 20);
    // Update to make smooth transition
    LCD.Update();
}

// Collision Function
bool Game::collision() 
{
    // if obstacles width and height match players width and height
    if ((obst <= 101 && obst >= 75) && (player <= 100 && player >= 91)) 
    {
        // return the value which breaks out of loop, and stops game
        return true;
    }
    else 
    {
        return false;
    }  
}

// Dino Game Function
void Game::dinoGame() 
{
    // make a boolean named endgame thats false
    bool endgame = false;
    // while endgame is not false
    while (!endgame) 
    {
        // Call jump and obstacle function and run for each tick.
        jump();
        obstacle();
        // Call Updatescore function
        Updatescore();
        // if collision detected
        if (collision()) 
        {
            // make endgame true
            endgame = true;
            Sleep(1.0);
            // Call the gameOver() function
            gameOver();
        }
        // Update everytime in loop
        LCD.Update();
    }
}

// Update Score function
void Game::Updatescore()
{
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("SCORE:", 10, 200);
    // Updates real time 
    LCD.SetFontColor(TAN);
    LCD.FillRectangle(100, 200, 50, 20);
    LCD.SetFontColor(BLACK);
    // Set's Score Number in real-time
    LCD.WriteAt(countobst, 100, 200);
}

// Entering the game function
void Game::enteringgame()
{
    // Use Proteus FEHLCD.h library to make neat loading screen
    LCD.SetBackgroundColor(BLACK);
    LCD.Clear();
    LCD.SetFontColor(DARKGRAY);
    LCD.WriteRC("ENTERING DINO GAME",3, 6);
    // Sleep in between each load session animation.
    Sleep(500);
    LCD.WriteRC(".",6, 15);
    Sleep(500);
    LCD.WriteRC(".",6, 16);
    Sleep(500);
    LCD.WriteRC(".",6, 17);
    Sleep(500);
    LCD.Clear();
}

// Game Over Screen Function
void Game::gameOver() 
{
    // Make Background!
    LCD.Clear();
    LCD.SetBackgroundColor(BLACK);
    LCD.SetFontColor(RED);
    LCD.WriteAt("Game Over!", 94, 90);
    LCD.WriteAt("Score: ", 94, 115);
    // Write the countobst value.
    LCD.WriteAt(countobst, 190, 115);
    // if updated count obstacle variable is greater than high_score in Stats function
    if (countobst > high_score)
    {
        // Make high_score equal to real-time count of obstacle 
        high_score = countobst;
    }
    // Resets ALL GAME STATS.
    obst = 319;
    player = 100;
    countobst = 0;
    // Going back to the main_menu()
    while(!LCD.Touch(&x, &y));
    while(LCD.Touch(&x, &y)){}
    LCD.Clear();
    main_menu();
}

/* ------------------------------- END OF CODE LINE -------------------------- */