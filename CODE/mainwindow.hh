/* The goal of this program is to create an gui to the binairo game. At the start of
 * the programm on the left is choise to input own gameboard of to set random seed.
 * Players can also change the ize of grid on the spinBox that also changes the size in
 * gameboard.hh/.cpp and changes so the number of same peices on one row/collums updates.
 * After the player has entered input/seed gameboard can be created if input is correct.
 * All of the object in the beginning of the game are placed in QTDesinger and are just
 * hidden/shown during the different parts of the game. Object are connected to each other
 * and depending on what player chooses, some are show some hidden
 * When game is started pushButtons are created to be used as the gameboard. The buttons
 * are placed onto a gridLayout. Pointer to each of the buttons are saved so they can be
 * later managed. Also click of each button is connected to a function that handels tile
 * placing. At the same time choise buttons are also created in th esame fashion.
 * When choise button/gametile is clicked, can the right button be identified b going
 * through the pointer. Checks if tile can be placed and places it if able.
 * Game end when no empty tiles remain, game is also timed usin QTimer.
 * Game can be reset or quit at any point using reset and quit buttons.
 *
 * Henri Laitinen
 *
 *
 * */
#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH
#include "gameboard.hh"
#include <vector>
#include <QMainWindow>
#include <QPushButton>
#include <QTimer>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //Changing the size of the gameboard
    int sizeMain=SIZE;
    int numberOfPieces;

    //timer for timing gameplay
    QTimer* timer;



private slots:
    //is called when random fill is chousen by clicking "random" button, hides choise buttons
    //and shows seed picker
    void randomButtonClicked();

    //is called when input fill has been chousen, hides choise buttons and
    // shows input textbox wher input can be netered
    void inputButtonClicked();

    //is called, when undo buton is clicked, hides random/input boxes and shows original random/input choise buttons
    // changes made to seed picker and manual ipnut text box are re initialized
    void undoButtonClicked();

    //close button is clicked -> program is closed
    void closeButtonClicked();

    //create button has been pressed after random seed or input has been choosen
    //creates the board by calling the fill_randomly or fill_from_input from gameboard.cpp
    void createButtonClicked();

    //hides all unimportant pieces, like info label, start option .... , also calss initGameboard and initChoises
    void startGame();

    //One of the two choise pushButtons (0 or 1) has been clicked, saves the chousen enum to toBePlaced
    void choiseClicked();

    //one of the gameboard pushButton has been clicked, checks if a toBePlaced has a value of ZERO or ONE
    //checks if that tile can be placed there and places it if possible
    void gameTileClicked();

    //by changin the value of the spinBox the gameboard size changes, in mainwindow using sizeMain, in gameboard
    // the int SIZE is updated to the new size

    //Changes the sixe of the the gameboard ui and calls function in gameboard.cpp to change size on gameboard
    void sizeChanged();

    //When clicked the whole game restarts
    void resetButtonClicked();

    //updates timer on timeouts
    void updateTimer();




private:
    Ui::MainWindow *ui;
    GameBoard board;

    int points=0;




    //bool that determines if a random or input gameboard will be created when
    //create button is pressed;
    bool randomInputCondition;

    //turns true if we were able to create a valid gameboard
    bool gameboardCreated;

    //Creates the button for the game board
    void initGameboard();

    //vecotr that stores the pointers to all of the buttons of the gameboard
    vector<QPushButton*> gameboardButtons;

    //Creates the choise buttons
    void initChoises();

    //stores the pointers to the choise buttons
    vector<QPushButton*> choises;

    //Stores the Enum value of the tile the player wants to place next
    Element_type toBePlaced=EMPTY;

    //starts the timer when the game starts
    void startTimer();

    //seconds and minutes for timer
    int timerSecond=0;
    int timerMinutes=0;


    //Is called when game has been won
    void gameWon();

    //stops timer
    QString stopTimer();


    void changeGridLabel(int size);

    void addPoint();

};
#endif // MAINWINDOW_HH
