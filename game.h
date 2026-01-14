#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <cmath> // for pow() function
#include <string> // For displayin score, level and number of lines

#include "I.h"
#include "J.h"
#include "L.h"
#include "O.h"
#include "S.h"
#include "T.h"
#include "Z.h"

#include <thread> // for flash animation
#include <chrono> // for flash animation

#include <algorithm> // for find() function

using namespace std;
using namespace std::chrono;
using namespace sf;

VideoMode desktopMode = VideoMode::getDesktopMode();

bool MainMenu()
{
    //Main menu
    RenderWindow mainMenu(VideoMode(1050, 550), "Main Menu", Style::Default);
    mainMenu.setFramerateLimit(60);
    mainMenu.setSize(Vector2u(desktopMode.width + 10, desktopMode.height - 20));
    mainMenu.setPosition(Vector2i(-15, -45));

    mainMenu.setFramerateLimit(60);

    //Font
    Font font;
    font.loadFromFile("KnightWarrior.otf");


    RectangleShape background1(Vector2f(1050, 550));
    Texture bg;
    bg.loadFromFile("Backgrounds/menubackground2.jpg");
    background1.setTexture(&bg);

    // Audio
    SoundBuffer mm;
    Sound main;
    mm.loadFromFile("Sound/menubackground4.mp3");
    main.setBuffer(mm);

    main.play();
    main.setLoop(true);

    Text title, resumeP, sng, controls, exitG;

    //Title
    title.setFont(font);
    title.setCharacterSize(70);
    title.setPosition(150.f, 100.f);
    title.setString("The Last Drop");
    title.setFillColor(Color::Red);

    //Start new game
    sng.setFont(font);
    sng.setCharacterSize(15);
    sng.setPosition(150.f, 350.f);
    sng.setString("Press Enter to Start New Game");
    sng.setFillColor(Color::White);

    //Controls
    controls.setFont(font);
    controls.setCharacterSize(15);
    controls.setPosition(150.f, 400.f);
    controls.setString("Press C to show controls");
    controls.setFillColor(Color::White);

    //Exit
    exitG.setFont(font);
    exitG.setCharacterSize(15);
    exitG.setPosition(150.f, 450.f);
    exitG.setString("Press Esc to exit");
    exitG.setFillColor(Color::White);

    while (mainMenu.isOpen())
    {
        Event evnt;
        while (mainMenu.pollEvent(evnt))
        {
            if (evnt.type == Event::Closed)
            {
                return false;
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
            {
                return false;
            }
            else if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
            {

                mainMenu.close();
                main.stop();
                return true;
            }
            else if (Keyboard::isKeyPressed(Keyboard::Key::C))
            {

                bool openC = true;
                Texture c;
                RectangleShape control(Vector2f(276.f, 150.f));
                control.setPosition(100.f, 50.f);
                c.loadFromFile("controls.jpg");
                control.setTexture(&c);
                while (openC == true)
                {
                    mainMenu.clear();
                    mainMenu.draw(background1);
                    mainMenu.draw(control);
                    mainMenu.display();
                    if (Keyboard::isKeyPressed(Keyboard::Key::E))
                    {
                        openC = false;
                    }
                }
            }
        }



        mainMenu.clear();
        mainMenu.draw(background1);
        mainMenu.draw(title);
        mainMenu.draw(sng);
        mainMenu.draw(controls);
        mainMenu.draw(exitG);
        mainMenu.display();
    }
}

bool gameOver()
{
    //Font
    Font font;
    font.loadFromFile("KnightWarrior.otf");

    Sound gameoverS;

    SoundBuffer gOver;
    gOver.loadFromFile("Sound/gameover.mp3");


    Sound backGround;
    gameoverS.setBuffer(gOver);

    cout << "YOU DIED! :(" << endl;
    gameoverS.play();

    RenderWindow endgame(VideoMode(1050, 550), "GameOver", Style::Default);
    endgame.setFramerateLimit(60);

    //Auto maximise
    endgame.setSize(Vector2u(desktopMode.width + 10, desktopMode.height - 20));
    endgame.setPosition(Vector2i(-15, -45));

    RectangleShape background(Vector2f(1015.f, 595.f));
    Texture bg;
    bg.loadFromFile("Backgrounds/background2.jpg");
    background.setTexture(&bg);

    Text gameover, exit, restart;

    //Gameover
    gameover.setFont(font);
    gameover.setCharacterSize(150);
    gameover.setPosition(235.f, 50.f);
    gameover.setString("GAME OVER");

    //Restart
    restart.setFont(font);
    restart.setCharacterSize(30);
    restart.setPosition(365.f, 300.f);
    restart.setString("Press R to restart level");


    //Exit
    exit.setFont(font);
    exit.setCharacterSize(30);
    exit.setPosition(365.f, 400.f);
    exit.setString("Press Esc to exit");

    while (endgame.isOpen())
    {
        Event evnt;;
        while (endgame.pollEvent(evnt))
        {
            if (evnt.type == Event::Closed)
            {
                endgame.close();
            }

        }
        if (Keyboard::isKeyPressed(Keyboard::Key::R))
        {

            endgame.close();
            return true;
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
        {

            endgame.close();
            return false;
        }
        endgame.clear();
        endgame.draw(background);
        endgame.draw(gameover);
        endgame.draw(restart);
        endgame.draw(exit);
        endgame.display();
    }
}

void clearGrid(int arrGrid[20][10]) // Clears a grid when a new level starts
{
    for (int i = 0;i < 20;i++)
    {
        for (int j = 0;j < 10;j++)
        {
            arrGrid[i][j] = 0; // 0 represents gridBlock
        }
    }
}

void handleLevelIntroAndMusic(int arrGrid[20][10], bool& levelStart, int& currentLevel, bool gameWon, RenderWindow& window,
    Sound& backGround, SoundBuffer& bg, Font& font, RectangleShape& background, Texture& bground, VideoMode desktopMode)
{
    backGround.stop();
    cout << "NISHAN E AQAL WALON K LIYE KAAFI HAI!!!!!" << endl;

    if (levelStart && currentLevel >= 1 && currentLevel <= 8) {
        vector<vector<string>> levelDialogues = {
            { "Level 1: A mere warm-up.", "Don’t get too confident now." },
            { "Level 2: Still standing? Impressive.", "Let’s see how long that lasts." },
            { "Level 3: You're starting to amuse me.", "But amusement is fleeting." },
            { "Level 4: You’re persistent, I’ll give you that.", "Persistence won’t save you." },
            { "Level 5: Getting closer… or so you think.", "You’re not ready for what’s next." },
            { "Level 6: Why do you keep going?", "You already know how this ends." },
            { "Level 7: One step from the edge.", "Do you feel the pressure now?" },
            { "Level 8: This is it.", "There is no turning back now.", "Win or lose... does it even matter?" }
        };

        vector<string>& dialogues = levelDialogues[currentLevel - 1];

        RenderWindow win(VideoMode(1050, 550), "Tetris : Level Intro", Style::Default);
        win.setFramerateLimit(60);
        win.setSize(Vector2u(desktopMode.width + 10, desktopMode.height - 20));
        win.setPosition(Vector2i(-15, -45));

        sf::Sound winS;
        sf::SoundBuffer winB;
        winB.loadFromFile("Sound/layton.mp3");
        winS.setBuffer(winB);

        winS.play();

        sf::Text dialogueText;
        dialogueText.setFont(font);
        dialogueText.setCharacterSize(50);
        dialogueText.setFillColor(sf::Color::Red);
        dialogueText.setPosition(35.f, 240.f);

        size_t dialogueIndex = 0;
        sf::Clock dialogue;

        while (win.isOpen()) {
            sf::Time dTime = dialogue.getElapsedTime();
            sf::Event event;
            while (win.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    win.close();
            }

            if (dTime.asSeconds() > 3.5f) {
                if (dialogueIndex < dialogues.size() - 1) {
                    dialogueIndex++;
                    dialogue.restart();
                }
                else {
                    win.close();
                }
            }

            dialogueText.setString(dialogues[dialogueIndex]);
            win.clear();
            win.draw(dialogueText);
            win.display();
        }

        levelStart = false;
    }
    else if (gameWon) {
        vector<string> finalCutscene = {
            "YOU WON...", "Or did you?", "You really thought this was about winning?",
            "You danced to my tune all along.", "Each block, each line, each move...",
            "All leading here.", "To this moment.", "You see, victory is just another illusion.",
            "And you... were just another player in my game.", "Goodbye.", "Credits : ",
            "Syed Abdullah", "3...", "2...", "1..."
        };

        sf::Sound winS, evilS;
        sf::SoundBuffer winB, evilB;
        winB.loadFromFile("Sound/violin.mp3");
        evilB.loadFromFile("Sound/laugh.mp3");
        winS.setBuffer(winB);
        evilS.setBuffer(evilB);
        winS.play();

        RenderWindow win(VideoMode(1050, 550), "Tetris : Finale", Style::Default);
        win.setFramerateLimit(60);
        win.setSize(Vector2u(desktopMode.width + 10, desktopMode.height - 20));
        win.setPosition(Vector2i(-15, -45));

        sf::Text dialogueText;
        dialogueText.setFont(font);
        dialogueText.setCharacterSize(50);
        dialogueText.setFillColor(sf::Color::Red);
        dialogueText.setPosition(35.f, 240.f);

        size_t dialogueIndex = 0;
        sf::Clock dialogue;
        int count = 0;

        while (win.isOpen()) {
            sf::Time dTime = dialogue.getElapsedTime();
            sf::Event event;
            while (win.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    win.close();
            }

            if (dTime.asSeconds() > 3.5f) {
                count++;
                if (count == 1) evilS.play();
                if (dialogueIndex < finalCutscene.size() - 1) {
                    dialogueIndex++;
                    dialogue.restart();
                }
                else {
                    win.close();
                }
            }

            dialogueText.setString(finalCutscene[dialogueIndex]);
            win.clear();
            win.draw(dialogueText);
            win.display();
        }

        currentLevel = 1;
        clearGrid(arrGrid);
    }

    // Background and music loading
    string musicPath = "Sound/level" + to_string(currentLevel) + ".mp3";
    if (currentLevel == 1) {
        bground.loadFromFile("Backgrounds/alps.jpg");
    }
    else if (currentLevel == 8) {
        bground.loadFromFile("Backgrounds/hell.jpg");
    }

    bg.loadFromFile(musicPath);
    background.setTexture(&bground);
    backGround.setBuffer(bg);
    backGround.play();
}

void assignNewTetrimino(shape*& currentShape, int& currentIndex, int& nextIndex, bool& assign)
{
    delete currentShape;
    currentIndex = nextIndex; // assigning next shape to current shape
    nextIndex = rand() % 7; // genereating a random shape to be sent next

    switch (currentIndex)
    {
    case 0:
        currentShape = new I();
        break;
    case 1:
        currentShape = new J();
        break;
    case 2:
        currentShape = new L();
        break;
    case 3:
        currentShape = new O();
        break;
    case 4:
        currentShape = new S();
        break;
    case 5:
        currentShape = new T();
        break;
    case 6:
        currentShape = new Z();
        break;
    }
    assign = false; // stop generating new shape
}

void drawGridAndShapes(RenderWindow& gameplay, int arrGrid[20][10], int level)
{
    // Blocks to display
    RectangleShape block(Vector2f(25.f, 25.f)), gridblock(Vector2f(25.f, 25.f));
    block.setOutlineColor(Color(50, 50, 50));
    block.setOutlineThickness(1);
    if (level == 8)
        gridblock.setOutlineColor(Color(200, 0, 0));
    else
    {
        gridblock.setOutlineColor(Color(10, 50, 50));
    }

    gridblock.setOutlineThickness(1);

    // Draw the grid

    // Simple logic is that 0 in the main gridArray represents an empty space i.e a grid, and all other 
    // numbers from 1 to 7 represents a shape block or filled position

    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            int cell = arrGrid[i][j];

            // Set fill color based on cell value
            switch (cell)
            {
            case 0:
                //gridblock.setTexture(&gridBlock); 
                gridblock.setFillColor(Color(0, 0, 0, 200));
                break; // Default block
            case 1:
                //block.setTexture(&Iblock);
                block.setFillColor(Color::Cyan);
                break;       // I
            case 2:
                //block.setTexture(&Jblock);
                block.setFillColor(Color::Blue);
                break;       // J
            case 3:
                //block.setTexture(&Lblock);
                block.setFillColor(Color(255, 165, 0));
                break; // L
            case 4:
                //block.setTexture(&Oblock);
                block.setFillColor(Color::Yellow);
                break;     // O
            case 5:
                //block.setTexture(&Sblock);
                block.setFillColor(Color::Green);
                break;      // S
            case 6:
                //block.setTexture(&Tblock);
                block.setFillColor(Color(160, 32, 240));
                break; // T
            case 7:
                //block.setTexture(&Zblock);
                block.setFillColor(Color::Red);
                break;        // Z
            }
            if (cell == 0)
            {
                gridblock.setPosition(j * 25 + 400, i * 25 + 40);
                gameplay.draw(gridblock);
            }
            else
            {
                block.setPosition(j * 25 + 400, i * 25 + 40);
                gameplay.draw(block);
            }
        }
    }
}

void checkAndClearFilledRowsWithAnimation(int arrGrid[20][10], RenderWindow& gameplay, int& lines)
{
    // Detect filled lines first
    vector<int> fullRows;
    for (int i = 19; i >= 0;i--) // Start searhing from bottom
    {
        int filled = 0;
        for (int j = 0; j < 10; j++)
        {
            if (arrGrid[i][j] != 0)
                filled++;
            else
                break;
        }
        if (filled == 10)
        {
            fullRows.push_back(i);
        }
    }

    // Animate flash for full rows
    if (!fullRows.empty())
    {
        RectangleShape flashBlock(Vector2f(25.f, 25.f));
        for (int flash = 0; flash < 6; flash++)
        { // 3 flashes
            for (int i : fullRows)
            {
                for (int j = 0; j < 10; j++)
                {
                    flashBlock.setPosition(j * 25 + 400, i * 25 + 40);
                    if (flash % 2 == 0)
                        flashBlock.setFillColor(Color::White);
                    else
                        flashBlock.setFillColor(Color::Black);
                    gameplay.draw(flashBlock);
                }
            }
            gameplay.display();
            this_thread::sleep_for(chrono::milliseconds(80));
        }
    }

    // Clearing the rows above

    int targetRow = 19; // Start from the bottom row
    for (int row = 19; row >= 0; row--)
    {
        // If the current row is not found in fullRows vector i.e that row is not full
        if (find(fullRows.begin(), fullRows.end(), row) == fullRows.end())
        {
            for (int col = 0; col < 10; col++)
            {
                arrGrid[targetRow][col] = arrGrid[row][col];
            }
            targetRow--; // Only move up targetRow if we copied something i.e we dont decrement targetRow until we find a not filled row
            // This helps us to overcome the issue of some filled rows being skipped when consecutive filled rows occur
        }
        else
            lines++;
    }

    // Fill the shifted rows with 0 (from top to where targetRow ended i.e the top most row with atleast one block filled) 
    for (int row = targetRow; row >= 0; row--)
    {
        for (int col = 0; col < 10; col++)
        {
            arrGrid[row][col] = 0;
        }
    }
}

// Main gameplay loop function: Handles shape assignment, input, movement, rendering, line clearing, scoring, and level progression.
void runTheGame()
{
    // --------------------------------------------------
    // Setup game window
    // --------------------------------------------------
    RenderWindow gameplay(VideoMode(1050, 550), "Tetris : Level 1", Style::Default);
    gameplay.setFramerateLimit(60);  // Limit FPS to 60 to avoid excessive CPU usage

    // Automatically maximize to fit screen (slightly offset to look clean on desktop)
    gameplay.setSize(Vector2u(desktopMode.width + 10, desktopMode.height - 20));
    gameplay.setPosition(Vector2i(-15, -45));

    // --------------------------------------------------
    // Load background image and set it on a rectangle
    // --------------------------------------------------

    RectangleShape background(Vector2f(desktopMode.width, desktopMode.height));
    background.setPosition(0, 0);

    Texture bground;
    bground.loadFromFile("Backgrounds/alps.jpg");  // Load background image
    background.setTexture(&bground);  // Apply it to rectangle

    // --------------------------------------------------
    // Load font for displaying score/level/lines
    // --------------------------------------------------

    Font font;
    font.loadFromFile("KnightWarrior.otf");

    // --------------------------------------------------
    // Prepare text elements for score, level, and lines
    // --------------------------------------------------

    Text score, level, numOfLines;

    score.setFont(font);
    score.setCharacterSize(50);
    score.setPosition(700.f, 125.f);  // Right side of the screen

    level.setFont(font);
    level.setCharacterSize(50);
    level.setPosition(700.f, 225.f);

    numOfLines.setFont(font);
    numOfLines.setCharacterSize(50);
    numOfLines.setPosition(700.f, 325.f);

    // --------------------------------------------------
    // Load sound effects and assign to sound buffers
    // --------------------------------------------------

    SoundBuffer bg;
    Sound backGround;

    SoundBuffer place, tap;
    place.loadFromFile("Sound/position2.mp3");  // Sound for placing block
    tap.loadFromFile("Sound/click2.mp3");       // Sound for any key click

    Sound position, click;
    position.setBuffer(place);
    click.setBuffer(tap);

    // --------------------------------------------------
    // Initialize key game state variables
    // --------------------------------------------------

    int currentLevel = 1, lines = 0;  // Score tracker: 10 lines = 1 level up
    bool levelStart = true;          // Used to display level intro screen

    int arrGrid[20][10] = { 0 };     // Main grid (20 rows x 10 columns) storing block IDs

    int currentIndex, nextIndex;     // Stores shape IDs (0–6)
    srand(time(0));                  // Randomize next block shape
    nextIndex = rand() % 7;

    shape* currentShape = new I();   // First shape initialized as I (avoids uninitialized pointer)
    bool assign = true;              // Flag to assign new shape
    bool gameWon = false;            // Flag to trigger final dialogue after level 8

    // --------------------------------------------------
    // Timing variables for automatic movement
    // --------------------------------------------------

    Clock autoDown;                  // Timer for automatic down movement
    float initialDelay = 0.7167f;    // Base time interval between downward steps (will be adjusted per level)

    Clock slideClock;                // Timer for "sliding" window when shape hits ground
    bool onGround = false;
    bool sliding = false;
    float slideDelay = 0.4f;         // Allow 0.4 seconds to shift/rotate after hitting bottom

    backGround.play();               // Start playing background music

    // --------------------------------------------------
    // Main game loop begins
    // --------------------------------------------------

    while (gameplay.isOpen())
    {
        // Loop background music if it stops
        if (backGround.getStatus() == sf::Sound::Stopped)
            backGround.play();

        // Handle level intro cutscene (with music and dialogue)
        if (levelStart)
            handleLevelIntroAndMusic(arrGrid, levelStart, currentLevel, gameWon, gameplay, backGround, bg, font, background, bground, desktopMode);

        // Assign new shape if flagged
        if (assign == true)
        {
            assignNewTetrimino(currentShape, currentIndex, nextIndex, assign);
        }

        // Clear old position of the shape from the grid before processing movement
        currentShape->clearFromGrid(arrGrid);

        // --------------------------------------------------
        // Handle player input and window events
        // --------------------------------------------------

        Event evnt;
        while (gameplay.pollEvent(evnt))
        {

            if (evnt.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Key::Escape))
            {
                gameplay.close();
                return;  // Exit the game
            }

            if (evnt.type == Event::KeyPressed)
            {

                if (!sliding && Keyboard::isKeyPressed(Keyboard::Up))
                {
                    click.play();  // Play a click sound for feedback
                    currentShape->rotate(arrGrid);  // Try to rotate if not sliding
                }

                if (evnt.key.code == Keyboard::Left || evnt.key.code == Keyboard::A)
                {
                    click.play();  // Play a click sound for feedback
                    currentShape->moveLeft(arrGrid);
                }

                if (evnt.key.code == Keyboard::Right || evnt.key.code == Keyboard::D)
                {
                    click.play();  // Play a click sound for feedback
                    currentShape->moveRight(arrGrid);
                }

                if (evnt.key.code == Keyboard::Down || evnt.key.code == Keyboard::S)
                {
                    click.play();  // Play a click sound for feedback
                    currentShape->moveDown(arrGrid);
                }
            }
        }

        // --------------------------------------------------
        // Handle automatic downward movement with level-based delay
        // --------------------------------------------------

        float currentDelay = initialDelay * pow(0.9, currentLevel);  // Each level decreases delay by 10%
        if (autoDown.getElapsedTime().asSeconds() > currentDelay)
        {
            bool moved = currentShape->autoMoveDown(arrGrid);  // Attempt to move down

            autoDown.restart();  // Restart timer

            if (!moved)  // Can't move further down
            {
                if (!sliding)
                {
                    slideClock.restart();  // Start grace period
                    sliding = true;
                }
                else if (slideClock.getElapsedTime().asSeconds() > slideDelay)
                {
                    // Shape is locked into grid
                    assign = currentShape->lockTheShapeInTheGrid(arrGrid, currentIndex + 1);
                    if (assign)
                        position.play();  // Play lock sound

                    sliding = false;  // Reset sliding state
                    currentShape->clearFromGrid(arrGrid);  // Clean up after locking
                }
            }
            else
            {
                // Shape moved successfully, so cancel sliding
                sliding = false;
                currentShape->clearFromGrid(arrGrid);
            }
        }

        // --------------------------------------------------
        // Check and clear full lines (with visual animation)
        // --------------------------------------------------

        if (!sliding)
            checkAndClearFilledRowsWithAnimation(arrGrid, gameplay, lines);

        // --------------------------------------------------
        // Check for game over: if top row is filled
        // --------------------------------------------------

        for (int i = 0; i < 10; i++)
        {
            if (arrGrid[0][i] != 0)
            {
                backGround.stop();
                bool keepRunning = gameOver();  // Ask user to play again or exit

                if (keepRunning) // restart game
                {
                    currentLevel = 1;
                    lines = 0;
                    clearGrid(arrGrid);
                    assign = true;
                    levelStart = true;
                    backGround.play();  // Restart everything
                }
                else
                    return;  // Quit game
            }
        }

        // --------------------------------------------------
        // Finalize shape position in grid before drawing
        // --------------------------------------------------

        currentShape->setMainArrayGrid(arrGrid, currentIndex + 1);

        // --------------------------------------------------
        // Update text elements
        // --------------------------------------------------

        score.setString("Score: " + to_string(lines * 100));
        level.setString("Level: " + to_string(currentLevel));
        numOfLines.setString("Lines cleared: " + to_string(lines));

        // --------------------------------------------------
        // Draw everything on the screen
        // --------------------------------------------------

        gameplay.clear();
        gameplay.draw(background);  // Background

        drawGridAndShapes(gameplay, arrGrid, currentLevel);  // Draw all fixed blocks

        currentShape->printNextShape(nextIndex, gameplay, font);  // Preview of next shape

        gameplay.draw(score);
        gameplay.draw(level);
        gameplay.draw(numOfLines);

        gameplay.display();  // Push everything to screen

        // --------------------------------------------------
        // Handle level progression
        // --------------------------------------------------

        if (lines >= 1)
        {
            currentLevel++;  // Level up
            lines = 0;       // Reset line count

            levelStart = true;  // Show new level dialogue

            if (currentLevel > 8)
                gameWon = true;  // Final dialogue trigger

            // Delay to let player catch breath
            Clock temp;
            while (temp.getElapsedTime().asSeconds() < 1)
            {
                ;  // Do nothing
            }
        }
    }

    // Cleanup memory
    delete currentShape;
}