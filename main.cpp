#include<iostream>
using namespace std;
#include <ctime>
#include <stdlib.h>
#include <fstream>
#include <map>
#include <iterator>
#include <iomanip>
#include <set>

void userGuessing();
void mainMenu();
void computerGuessing();
void gobacktomain();
void waits(int seconds);
void playAgain();
void enterUserName();
void userGame();
void getDataFromFile();
void updateData();

string username;
int mistakesCount=0;

struct comp
{
  template<typename T>
  bool operator()(const T& l, const T& r) const
  {
    if (l.second != r.second){
    return l.second < r.second;}

    return l.first < r.first;
  }
};

void gobacktomain()
{
  cout << "Type 0 to go back to main Menu "; 
  int goback;
  while (true) {
    cin >> goback;
    if (!cin)
    {
      cin.clear();
        cin.ignore( numeric_limits <streamsize> ::max(), '\n');
        cout<<"Tyoe 0 to go back to main Menu: ";
    }
    else if( goback != 0) { cout<<"Tyoe 0 to go back to main Menu: "; }
    else { mainMenu(); break; }
  }
}
void mainMenu()
{
  system("clear");
  int choice;
  bool wrongInput = true;
  cout << "******************************************\n";
  cout << "*\033[1;31m                Main Menu\033[0m               *\n";
  cout << "* 1 - Guess the computer's number        *\n";
  cout << "* 2 - let computer guess your number     *\n";
  cout << "* 3 - instructions                       *\n";
  cout << "* 4 - leaderboard                        *\n";
  cout << "* 5 - Exit                               *\n";
  cout << "******************************************\n";
  cout << "welcome " << username<<"!\n";
  while (wrongInput)
  {
    cin >> choice;
    if (!cin)
    {
      cin.clear();
      cin.ignore( numeric_limits <streamsize> ::max(), '\n');
      cout<<"please enter a number between 1 and 5\n";
    }
    else if (choice > 5 || choice < 1)
    {
      cout << "please enter a number between 1 and 5\n";
    }
    else
    {
      wrongInput = false;
    }
  }
  switch (choice)
  {
    case 1:
      userGuessing();
      break;
    case 2: 
      computerGuessing();
      break;
    case 3:
      system("clear"); 
      cout <<"***************************************************************************\n";
      cout << "*\033[1;31m                              Instructions\033[0m                               *\n";
      cout <<"*  There are two players in this game, You and the computer!              *\n";
      cout <<"*  Option1: you can have the computer pick a number and you guess it      *\n";
      cout <<"*  Option2: you can guess a number and have the computer guess it         *\n";
      cout <<"*  game ends when the number is guessed and you have the option to restart*\n";
      cout <<"*  you can view the game leaderBoard in the mainMenu!                     *\n";
      cout <<"***************************************************************************\n";
      gobacktomain();
      break;
    case 4:
      system("clear");
      cout << "Here are the top 10 players with the fewest guesses made!\n";
      cout<<'\t'<<"rank\t"<<"score\t"<<"username\n";
      getDataFromFile();
      gobacktomain();
    case 5:
      cout << "\033[1;32mThank you for playing!\033[0m\n";
      exit (EXIT_FAILURE);
      break;
    default:
      break;
   }
}

void computerGuessing()
{
  int high = 101;
  int low = 1; 
  int takeNumber;
  int computerGuess;
  int computerMistakes=0;
  system("clear");  
  cout << "Welcome! you can go back and view the instructions of how to play!\n";
  cout << "Type 0 anytime to go back to main menu\n"; 
  cout <<"please enter a number between 1 and 100 for the computer to guess\n";
  while (true) {
    cin >> takeNumber;
    if (!cin)
    {
      cin.clear();
      cin.ignore( numeric_limits <streamsize> ::max(), '\n');
      cout<<"please enter a number between 1 and 100\n";
    }
    else if( takeNumber == 0 )
    {
      mainMenu();
    }
    else if(takeNumber > 100 || takeNumber < 1)
    {
      cout<<"please enter a number between 1 and 100\n";
    }
    else { break; }
  }
  while (true)
  {
    srand(time(NULL));
    computerGuess = rand() % (high - low) + low;
    if ( computerGuess == takeNumber )
    {
      cout << "\033[1;32mcomputer guessed your number!\033[0m\n";
      cout <<"it took " << computerMistakes << " tries to guess your number\n";
      playAgain();
      break;
    }
    else if (computerGuess > takeNumber){
      high = computerGuess;
      cout << "computer guessed: " << computerGuess<<" and it was too high               ";
      computerMistakes++;
      cout << "\033[1;33mcomputer mistakes:\033[0m"<<computerMistakes<<"\n";
    }
    else if (computerGuess < takeNumber) {
      low = computerGuess+1;
      cout << "computer guessed: " << computerGuess<<" and it was too low               ";
      computerMistakes++;
      cout << "\033[1;33mcomputer mistakes:\033[0m"<<computerMistakes<<"\n";
    }
    waits(1);
  }
}

void userGuessing()
{
  mistakesCount=0;
  system("clear");
  cout << "Welcome! you can go back and view the instructions of how to play!\n";
  cout << "Type 0 anytime to go back to main menu\n"; 
  userGame();
}

void waits (int seconds)
{
  clock_t endwait;
  endwait = clock() + seconds * CLOCKS_PER_SEC ;
  while (clock() < endwait) {}
}
void playAgain()
{
  string input;
  cout<<"would you like to play again?: ";
  while (true) {
    cin >> input;
    if(input == "y" || input == "Y")
    {
      mainMenu();
      break;
    }
    else if(input == "n" || input == "N") { 
      cout << "\033[1;32mThank you for playing!\033[0m\n";
      exit (EXIT_FAILURE); break; 
    }
      else { cout <<"please enter y or n: "; }
   }
}
 
void enterUserName()
{
  int originalSize = 1000;
  int checkArray=0;
  bool endWhileLoop = true;
  string userNameArray[originalSize];
  
  system("clear");
  cout <<"please enter your username: ";
  ifstream myfile("usernames.txt");
  if(!myfile){
    cout<<"Error opening the file\n";
    system("pause");
  }
  while(!myfile.eof()) {
    for(int i=0;i<originalSize;i++) { 
      getline(myfile,userNameArray[i],'\n');
      
    }
  }
  while (endWhileLoop)
  { 
    checkArray=0;
    cin>>username;
    for (int i=0; i<originalSize;i++)
    {
      if ( username == userNameArray[i]) {
        
        cout<<"userName already exists enter a different one: ";
        break;
      }
      if(username!=userNameArray[i]) { checkArray++; }
    }
    if (checkArray==1000){
      endWhileLoop=false;}
  }
  ofstream userFile("usernames.txt", ios::out | ios::app);
  if (userFile.is_open()){
    userFile << username<<"\n";
    userFile.close();
  }
  else {
    cout<<"file not found";
  }   
}

void userGame() {
  bool endGame=true;
  int computerGuess;
  int myGuess;
  srand(time(NULL));
  computerGuess = rand() % 100 + 1;
  int difficulty;
  cout<<computerGuess; 
  cout<<"please select dificulty\n";
  cout<<"1 - easy (unlimited tries)\n";
  cout<<"2 - medium (7 tries)\n";
  cout<<"3 - hard (3 tries)\n";
  while (true)
  {
    cin >> difficulty;
    if (!cin)
    {
      cin.clear();
      cin.ignore( numeric_limits <streamsize> ::max(), '\n');
      cout<<"please enter a number between 1 and 3\n";
    }
    else if (difficulty == 0) { mainMenu(); }
    else if (difficulty > 3 || difficulty < 1)
    {
      cout << "please enter a number between 1 and 3\n";
    }
    else
    {
      break;
    }
  }
  switch(difficulty) {
    case 1:
      cout<<"you selected easy mode\n";
      break;
    case 2:
      cout<<"you selected medium mode\n";
      break;
    case 3: 
      cout<<"you selected hard mode\n";
      break;
  }
  while(endGame)
  {
    cout << "Guess a number (between 1 and 100): "; 
    cin >> myGuess;
    if (!cin)
    {
      cin.clear();
      cin.ignore( numeric_limits <streamsize> ::max(), '\n');
      cout<<"please enter a number between 1 and 100\n";
    }
    else if( myGuess == 0 )
    {
       mainMenu();
    }
    else if(myGuess > 100 || myGuess < 1)
    {
      cout<<"please enter a number between 1 and 100\n";
    }
    else if ( myGuess > computerGuess )
    {
      cout << "\033[1;31mwrong number nice try!\033[0m       ";
      mistakesCount++;
      cout<<"the number is lower than that        ";
      cout<<"number of mistakes: "<< mistakesCount<< "\n";
    }
    else if ( myGuess < computerGuess ) {
      cout << "\033[1;31mwrong number nice try!\033[0m       ";
      mistakesCount++;
      cout<<"the number is higher than that        ";
      cout<<"number of mistakes: "<< mistakesCount<< "\n";
    }
    else if ( myGuess == computerGuess )
    {
      string input;
      endGame=false;
      cout << "\033[1;32m You got it!\033[0m       ";
      cout<<"total number of mistakes: "<<mistakesCount<<"\n";
      updateData();
      playAgain();
    }
    switch(difficulty) {
    case 1:
      break;
    case 2:
      if(mistakesCount >= 7) {
        cout << "\033[1;33mGame Over! you made more than 7 mistakes:\033[0m\n";
        endGame=false;
        playAgain();
      }
      break;
    case 3: 
      if(mistakesCount >= 3) {
        cout << "\033[1;33mGame Over! you made more than 3 mistakes:\033[0m\n";
        endGame=false;
        playAgain();
      }
      break;
  }
  }
}

void getDataFromFile()
{
  int i=0;
  int rank=1;
  ifstream file;
  file.open("leaderBoard.txt");
  if(!file.is_open()) {return;}
  string word;
  string data[20];
  while(file >> word)
  {
    data[i]=word;
    i++;
  }
  file.close();
  
  map<string,int> leaderBoard;
  for(int k=0;k<20;k=k+2) {
      leaderBoard.insert(pair<string,int>(data[k],std::stoi(data[k+1])));
  }
        
  std::set<std::pair<std::string,int>, comp> set(leaderBoard.begin(), leaderBoard.end()); 
  for (auto const &pair: set) {
    std::cout<<'\t'<<rank<<'\t'<<pair.second <<'\t'<<pair.first <<'\n';
    rank++;
  }

}

void updateData() {
  
  int i=0;
  ifstream file;
  file.open("leaderBoard.txt");
  bool findUserName=false;
  if(!file.is_open()) {return;}
  string word;
  string data[20];
  while(file >> word)
  {
    data[i]=word;
    i++;
  }
  file.close();
 
  for(int w=0;w<20;w=w+2) {
    if((mistakesCount < std::stoi(data[w+1]))&&(data[w]==username)) {
      data[w+1]=std::to_string(mistakesCount);
      break;
    }
    else if((mistakesCount < std::stoi(data[w+1]))&&(data[w]!=username)) {
      data[w]=username;
      data[w+1]=std::to_string(mistakesCount);
      break;
    }
  }
  ofstream leaderBoardFile("leaderBoard.txt");
  if (leaderBoardFile.is_open()){
    for(int h=0;h<20;h=h+2) {
      leaderBoardFile<<data[h]<<" "<<data[h+1]<<"\n";
    }
  }
  else {
    cout<<"file not found";
  }
  leaderBoardFile.close();
}  
int main()
{
  enterUserName();
  mainMenu();
  return 0;
}
