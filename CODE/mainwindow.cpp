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
 * opp.num. 150500492
 * henri.m.laitinen@tuni.fi
 *
 *
 * */




#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "gameboard.hh"
#include <string>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    ui->resetButton->setDisabled(true);

    //Set up the pointers that indicate which tile is chousen
    QPixmap image_pointer(":/pointer.png");
    image_pointer=image_pointer.scaled(ui->whitePointer->size());
    ui->blackPointer->setPixmap(image_pointer);
    ui->whitePointer->setPixmap(image_pointer);   
    ui->whitePointer->hide();
    ui->blackPointer->hide();

    //set up gridSize spinBox
    ui->gridSize->setValue(3);





    //hide random/input objects before choise
    ui->minutesLabel->hide();
    ui->secondsLabel->hide();
    ui->youWonText->hide();
    ui->randomLabel->hide();
    ui->randomSeedSpinBox->hide();
    ui->inputLabel->hide();
    ui->inputTextEdit->hide();
    ui->undoPushButton->hide();
    ui->inputCreatePushButton->hide();
    ui->randomCreatePushButton->hide();
    ui->lcdSeconds->hide();
    ui->lcdMinutes->hide();
    ui->label_2->hide();
    ui->label->hide();
    ui->pointsLabel->hide();
    ui->pointCounter->hide();




    //set button colors
    ui->randomCreatePushButton->setStyleSheet("background-color: #1adb5b");
    ui->inputCreatePushButton->setStyleSheet("background-color: #1adb5b");
    ui->closePushButton->setStyleSheet("background-color: red");

    //set up fonts
    QFont errorFont;
    errorFont.setPointSize(18);
    ui->errorMessage->setFont(errorFont);
    ui->errorMessage->setStyleSheet("color: red");

    QFont gameFont;
    gameFont.setPointSize(16);
    ui->gameError->setFont(gameFont);
    ui->gameError->setStyleSheet("color: red");

    QFont pointFont;
    pointFont.setPointSize(50);
    ui->pointCounter->setFont(pointFont);
    ui->pointCounter->setStyleSheet("color: green");

    //set random seed spinbox max and min
    ui->randomSeedSpinBox->setMinimum(0);
    ui->randomSeedSpinBox->setMaximum(50);


    //Connects pushing the random input button to randomButtonClicked function
    connect(ui->randomPushButton, &QPushButton::clicked, this, &MainWindow::randomButtonClicked);
    //connects pushing the input button to a function inputButtonClicked
    connect(ui->inputPushButton, &QPushButton::clicked, this, &MainWindow::inputButtonClicked);
    //connects clicking the undo button to undoButtonClicked function
    connect(ui->undoPushButton, &QPushButton::clicked, this, &MainWindow::undoButtonClicked);
    //connects clicking the close button to closeButtonClicked function
    connect(ui->closePushButton, &QPushButton::clicked, this, &MainWindow::closeButtonClicked);

    //connects either of the create buttons being clicked to the createButtonClicked function
    connect(ui->randomCreatePushButton, &QPushButton::clicked, this, &MainWindow::createButtonClicked);
    connect(ui->inputCreatePushButton, &QPushButton::clicked, this, &MainWindow::createButtonClicked);

    //Connects changing value of size SpinBox to sizeChanged function that changes the size of gameboard
    connect(ui->gridSize, &QSpinBox::valueChanged, this, &MainWindow::sizeChanged);

    //connects pressing reset button to resetButtonClicked
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::resetButtonClicked);





}

MainWindow::~MainWindow()
{
    delete ui;
}

//a spinWheel appears to let player choose a seed (0-50), and a create button
//to create a random gamboard using said seed
void MainWindow::randomButtonClicked()
{
    randomInputCondition=true;
    ui->randomPushButton->hide();
    ui->inputPushButton->hide();

    ui->undoPushButton->show();
    ui->randomLabel->show();
    ui->randomSeedSpinBox->show();
    ui->randomCreatePushButton->show();


}

//a textEdit appears to let player enter own gameboard, and a create button
//to create said gameboard
void MainWindow::inputButtonClicked()
{
    randomInputCondition=false;
    ui->randomPushButton->hide();
    ui->inputPushButton->hide();

    ui->undoPushButton->show();
    ui->inputLabel->show();
    ui->inputTextEdit->show();
    ui->inputCreatePushButton->show();

}


//resets the start screen when needed
void MainWindow::undoButtonClicked()
{
    //hide and show to reset the start
    ui->randomLabel->hide();
    ui->randomSeedSpinBox->hide();
    ui->inputLabel->hide();
    ui->inputTextEdit->hide();
    ui->undoPushButton->hide();
    ui->randomPushButton->show();
    ui->inputPushButton->show();
    ui->undoPushButton->hide();
    ui->inputCreatePushButton->hide();
    ui->randomCreatePushButton->hide();

    //set values back to 0 and empty
    ui->randomSeedSpinBox->setValue(0);
    ui->inputTextEdit->setText("");
    ui->errorMessage->setText("");


}

//closes the window if the close button is pressed
void MainWindow::closeButtonClicked()
{
    this->close();

}


//Tries to crate the gameboard according to players input of random seed
//if successfull starts the game
//if not successfull shows error ot player
void MainWindow::createButtonClicked()
{
    if(randomInputCondition){
        unsigned int random_seed=ui->randomSeedSpinBox->value();

        if(board.fill_randomly(random_seed)){

            ui->errorMessage->setText("");
            startGame();
        }else{
            ui->errorMessage->setText("BAD SEED!");

        }

    }else{
        QString inputTextQstring=ui->inputTextEdit->toPlainText();
        string inputText=inputTextQstring.toStdString();
        string oneLineInput="\"";

        for(char letter:inputText){
            if(letter!='\n'){
                if(letter=='-'){
                    oneLineInput+=" ";

                }else{
                    oneLineInput+=letter;
                }

            }
        }
        oneLineInput+="\"";
        if(board.fill_from_input(oneLineInput)){
            ui->errorMessage->setText("");
            startGame();
        }else{
            ui->errorMessage->setText("WRONG INPUT!");
        }



    }
}


//Starts the game. Hides objects needed before game and show objects needed in game like timer, score etc
//creates and starts timer and calls initGameboard and initChoises
void MainWindow::startGame()
{

    ui->randomLabel->hide();
    ui->randomSeedSpinBox->hide();
    ui->inputLabel->hide();
    ui->inputTextEdit->hide();
    ui->undoPushButton->hide();
    ui->randomPushButton->hide();
    ui->inputPushButton->hide();
    ui->undoPushButton->hide();
    ui->inputCreatePushButton->hide();
    ui->randomCreatePushButton->hide();
    ui->infoText->hide();
    ui->selectLabel->hide();
    ui->label_3->hide();
    ui->randomSeedSpinBox->hide();
    ui->gridSize->hide();
    ui->gridSizeLabel->hide();



    ui->label_2->show();
    ui->lcdSeconds->show();
    ui->lcdMinutes->show();
    ui->secondsLabel->show();
    ui->minutesLabel->show();
    ui->pointCounter->show();
    ui->pointsLabel->show();
    ui->pointCounter->setText(QString::number(points));

    ui->errorMessage->setText("");

    initGameboard();
    initChoises();

    timer=new QTimer(this);
    timer->start(1000);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimer);

    ui->resetButton->setEnabled(true);




}

//Creates as many buttons (PushButton) as needed to create the created gameboard
// Sets Icons to buttons according the value of the gametile in each cordinate
//saves pointers to vector gameboardButtons
//connects each buttons push to the function gameTileClicked();
void MainWindow::initGameboard()
{
    QPixmap image_empty(":/empty.png");
    QPixmap image_black(":/black.png");
    QPixmap image_white(":/white.png");
    QGridLayout* buttonLayout = ui->buttonGrid;

    for (char c=1; c<=sizeMain*sizeMain; ++c){

        QPushButton* pushButton=new QPushButton("", this);

        if(ui->gridSize->value()>=4){
            pushButton->setFixedHeight(35);
            pushButton->setFixedWidth(35);
        }else if(ui->gridSize->value()==3){
            pushButton->setFixedHeight(45);
            pushButton->setFixedWidth(45);
        }else if(ui->gridSize->value()==2){
            pushButton->setFixedHeight(55);
            pushButton->setFixedWidth(55);
        }else{
            pushButton->setFixedHeight(65);
            pushButton->setFixedWidth(65);
        }



        gameboardButtons.push_back(pushButton);
        QSize button_size=pushButton->size();
        int y = (c - 1) / sizeMain;
        int x = (c - 1) % sizeMain;

        QString y_qstring=QString::number(y);
        QString x_qstring=QString::number(x);
        QString kordinates=x_qstring+"-"+y_qstring;
        pushButton->setObjectName(kordinates);

        if(board.get_board().at(y).at(x)==ZERO){
            pushButton->setIcon(image_white);
            pushButton->setIconSize(button_size);

        }else if (board.get_board().at(y).at(x)==ONE){
            pushButton->setIcon(image_black);
            pushButton->setIconSize(button_size);
        }else{
            pushButton->setIcon(image_empty);
            pushButton->setIconSize(button_size);
        }
        buttonLayout->addWidget(pushButton, y, x);

        connect(pushButton, &QPushButton::clicked, this, &MainWindow::gameTileClicked);


    }
}

//creates two pushButtons that are used as choises which tile is to be placed next
//saves pointers to vector
//connect click to function choiseClicked
void MainWindow::initChoises()
{
    ui->gameError->setText("");
    QPixmap image_black(":/black.png");
    QPixmap image_white(":/white.png");
    ui->label->show();
    QGridLayout* choises_layout=ui->choisesLayout;

    for(char c=1; c<=2;++c){

        QPushButton* choise_button= new QPushButton("", this);

        choise_button->setFixedHeight(40);
        choise_button->setFixedWidth(40);
        QString name=QString::number(c);
        choise_button->setObjectName(name);


        choises.push_back(choise_button);
        QSize button_size=choise_button->size();
        if(c==1){
            choise_button->setIcon(image_white);
            choise_button->setIconSize(button_size);
        }else{
            choise_button->setIcon(image_black);
            choise_button->setIconSize(button_size);

        }




        choises_layout->addWidget(choise_button, 0, c-1);

        connect(choise_button, &QPushButton::clicked, this, &MainWindow::choiseClicked);
    }
}

//When game is over (no more empty tiles) stops and gets the time using stopTimer()
//prints winning text telling time
void MainWindow::gameWon()
{
    QString time=stopTimer();
    QString winningText="YOU WON!\nYou won with "+QString::number(points)+" points in: "+time+"\nTo play again; press reset\nTo quit; press close";
    QFont font;
    font.setPointSize(16);
    ui->youWonText->setFont(font);
    ui->youWonText->setStyleSheet("color: green");

    ui->youWonText->setText(winningText);
    ui->youWonText->show();

    this->setStyleSheet("background-color: lightblue");



}

//stops timer and saves the passed time to QString winningTime and returns it
QString MainWindow::stopTimer()
{
    timer->stop();
    if (timerMinutes>0){
        QString winningTime=QString::number(timerMinutes)+"min "+QString::number(timerSecond)+"sec";
        timerMinutes=0;
        timerSecond=0;
        return winningTime;

    }else{
        QString winningTime=QString::number(timerSecond)+"sec";
        timerMinutes=0;
        timerSecond=0;
        return winningTime;
    }

}

//Figures out which tile was chousen to be placed
// Saves choises Enum value to toBePlaced
// Shows lbel with picture under the choise to indicate which choise was made
void MainWindow::choiseClicked()
{

    ui->whitePointer->hide();
    ui->blackPointer->hide();


    for (auto& button: choises){
        if (button==sender()){
            if(button->objectName()=='1'){
                ui->whitePointer->show();
                toBePlaced=ZERO;
                return;

            }else {
                ui->blackPointer->show();
                toBePlaced=ONE;
                return;
            }



        }
    }
}

// Figures out what gametile was clicked, and checks if choies can be set there
// Also after every placement checks if game is over using gameboard.is_game_over()
void MainWindow::gameTileClicked()
{
    ui->gameError->setText("");

    QPixmap image_black(":/black.png");
    QPixmap image_white(":/white.png");

    if(toBePlaced==EMPTY){
        ui->gameError->setText("Please select a tile you want to place first!");
    }else{
    for(auto& button: gameboardButtons){
        if(button==sender()){
            QString nameq=button->objectName();
            QString xQstr=nameq.at(0);
            QString yQstr=nameq.at(2);
            int xKord=xQstr.toInt();
            int yKord=yQstr.toInt();

            char c;
            if(toBePlaced==ZERO){
                c='0';
            }else{
                c='1';
            }

            if(board.add_symbol(xKord, yKord, c)){
                if(toBePlaced==ZERO){
                    button->setIcon(image_white);
                    button->setIconSize(button->size());
                    addPoint();
                    if(board.is_game_over()){
                        gameWon();
                    }

                    return;
                }else{
                    button->setIcon(image_black);
                    button->setIconSize(button->size());
                    addPoint();
                    if(board.is_game_over()){

                        gameWon();
                    }

                    return;
                }

            }else{
                ui->gameError->setText("Can't place there!");
                toBePlaced=EMPTY;
                ui->whitePointer->hide();
                ui->blackPointer->hide();
                return;

            }





        }
    }
    }
}



//Is called when gridSize spinBox value changes
// Changes tthe value of numberOfPieces and sizeMain that dictate how big gameboard is going to be
//also changes the size in gameboard.hh/.cpp using gameboard.change_size
//
void MainWindow::sizeChanged()
{
    changeGridLabel(ui->gridSize->value());
    numberOfPieces=ui->gridSize->value();
    sizeMain=2*numberOfPieces;
    board.change_size(numberOfPieces);

}

//Changes the label next to gridSize spinBox
//determines the final size of the gameboard
void MainWindow::changeGridLabel(int size)
{
    size=2*size;
    QString sizeLabel="="+ QString::number(size)+"x"+QString::number(size);
    ui->gridSizeLabel->setText(sizeLabel);
}

//Deletes all buttons created
// clears all vectors and gameboard
//stops timer, hides game objects, shows beginning objects
void MainWindow::resetButtonClicked()
{

    for (auto game_button:gameboardButtons){
        delete game_button;
    }

    gameboardButtons.clear();
    for (auto choise_button : choises){
        delete choise_button;
    }
    choises.clear();

    board.reset_board();

    stopTimer();


    ui->infoText->show();
    ui->randomPushButton->show();
    ui->inputPushButton->show();
    ui->label_3->show();
    ui->gridSize->show();
    ui->gridSizeLabel->show();

    ui->secondsLabel->hide();
    ui->minutesLabel->hide();
    ui->lcdMinutes->hide();
    ui->lcdSeconds->hide();
    ui->label_2->hide();
    ui->youWonText->hide();
    ui->blackPointer->hide();
    ui->whitePointer->hide();
    ui->label->hide();
    ui->pointCounter->hide();
    ui->pointsLabel->hide();
    points=0;

    this->setStyleSheet("");




}

//updates the seconds and minutes of timer when timer timeouts (every second)
void MainWindow::updateTimer()
{
    ++timerSecond;
    if (timerSecond<60){
        ui->lcdSeconds->display(timerSecond);
    }else{
        ++timerMinutes;
        timerSecond=0;
        ui->lcdMinutes->display(timerMinutes);
        ui->lcdSeconds->display(timerSecond);
    }

}

void MainWindow::addPoint()
{
    ++points;
    ui->pointCounter->setText(QString::number(points));

}
