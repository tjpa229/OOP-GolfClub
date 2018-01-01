//----------------------------------------------------------------------------
//                              Golf Club App
//----------------------------------------------------------------------------
// CS 215 - Spring 2017 - Project 3
// Name:    Tirth Patel
// Section:  011
// Date:     April 7, 2017
// An application to manage data for a Golf Club, including:
// - individual scores on a single hole of golf
// - total scores for a game
// - a list of games for one player
// - a list of players for the whole club
//----------------------------------------------------------------------------
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include<iomanip>
using namespace std;

const int MAX_PLAYERS = 10;		// max number of players in a club
const int MAX_HOLES = 18;		// max number of holes in a game
const int MAX_GAMES = 10;		// max number of games for a player
const int NOT_FOUND = -1;		// return code for search
const int EXIT_OPTION = 7;		// main menu option for EXIT

struct aGame {					// WRITE a structure for aGame. Members:
	string name;				// course      - string         - name of golf course
	string date;				// date        - string         - date game was played
	int totalScore;				// totalScore  - integer        - total score for the game
	int hole[MAX_HOLES];		// hole        - array of ints  - list of scores for each hole
	int numHoles;				// numHoles    - integers       - number of holes played
};
struct aPlayer {
	string name;				// name of player
	float  avgScore;			// player's average score on all games
	int    numGames;			// number of games this player has played
	aGame  game[MAX_GAMES];		// list of games played by this player
};

struct aClub {
	string  name;				// name of the club
	int     numPlayers;			// number of players in the club
	int		holeAvg;			// used to calculate total score for players
	aPlayer player[MAX_PLAYERS];// list of players in this club
};

//----------------------------------------------------------------
//                         printLogo
//----------------------------------------------------------------
// design a new logo if you wish (include your Name and Section)
void printLogo() {
	system("cls");
	cout << "+------------------------------------------------+\n";
	cout << "|                GOLB CLUB EXPRESS PRO           |\n";
	cout << "|               by Tirth Patel - SECTION 011     | \n";
	cout << "+------------------------------------------------+\n";
} // printLogo()


  //-----------------------------------------------------------------------------
  //                                 initGame
  //-----------------------------------------------------------------------------
void initGame(aGame & g) {
	g.name = "";
	g.date = "";
	g.numHoles = 0;
	g.totalScore = 0;
	for (int i = 0; i < MAX_HOLES; i++) {
	
		g.hole[i] = 0;
	}
} // initGame()

  //-----------------------------------------------------------------------------
  //                                 initPlayer
  //-----------------------------------------------------------------------------
void initPlayer(aPlayer & p) {

	p.name = "";
	p.avgScore = 0;
	p.numGames = 0;
	for (int i = 0; i < MAX_GAMES; i++) {
		initGame(p.game[i]);
	}
} // initPlayer()

  //-----------------------------------------------------------------------------
  //                                 initClub
  //-----------------------------------------------------------------------------
void initClub(aClub & c) {
	c.holeAvg = 0;
	c.name = "";
	c.numPlayers = 0;
	for (int i = 0; i < MAX_PLAYERS; i++) {
		initPlayer(c.player[i]);
	}
} // initClub()
void calcTotalScore(aClub & c) {
	////(sum of hole scores) + ((18 – number_holes_played) X Club Hole Average)
	int sum = 0;
	for (int i = 0; i < c.numPlayers; i++) {
		for (int j = 0; j < c.player[i].numGames;j++) 
			if (c.player[i].game[j].numHoles >= 18) {
				for (int k = 0; k < c.player[i].game[j].numHoles; k++) {
					c.player[i].game[j].totalScore = c.player[i].game[j].totalScore + c.player[i].game[j].hole[k];
				}
			}
			else {
				for (int k = 0; k < c.player[i].game[j].numHoles; k++) {
					sum = sum + c.player[i].game[j].hole[k];
				}
				c.player[i].game[j].totalScore = sum + ((18 - c.player[i].game[j].numHoles)*c.holeAvg);
			}

			
		}
	}
	

void calcAvg(aClub & c) {
	calcTotalScore(c);
	float avg;
	int i;
	for (int i = 0; i < c.numPlayers; i++) {
		int sum = 0;
		for (int j = 0; j < c.player[i].numGames;j++) {
			sum = sum + c.player[i].game[j].totalScore;
		}
		c.player[i].avgScore = sum / c.player[i].numGames;
	}
	
}
void newClub(aClub & c) {
	cout << "Making a new Club" << endl;
	cout << "Enter name of new club: ";
	cin >> c.name;
	cout << "Enter club hole average: ";
	cin >> c.holeAvg;
	cout << "New club initalized!" << endl;
}
void readFromFile(aClub & c, string filename) {
	ifstream f;
	f.open(filename);
	f >> c.numPlayers >> c.holeAvg;
	getline(f, c.name);
	for (int i = 0; i < c.numPlayers;i++) {
		f >> c.player[i].numGames;
		getline(f, c.player[i].name);
		for (int j = 0; j < c.player[i].numGames; j++) {

			f >> c.player[i].game[j].numHoles >> c.player[i].game[j].date;
			getline(f, c.player[i].game[j].name);
			for(int k = 0 ; k<c.player[i].game[j].numHoles;k++)
			{
				int pos;
				f >> pos;
				c.player[i].game[j].hole[k] = pos;
				
			}
		}	
	}


	cout << "Reading " << c.numPlayers << " people from file!" << endl;
	f.close();
	system("pause");
}
//-----------------------------------------------------------------------------
//                                 startUp
//-----------------------------------------------------------------------------
// Modifies: a Club structure
// Initializes the the club to "empty", then reads data from a file or
// starts a new club.
//-----------------------------------------------------------------------------
void startUp(aClub & c) {
	initClub(c);
	string filename;
	cout << "Input file name or new to start a new club: ";
	cin >> filename;
	ifstream f;
	f.open(filename);
	if (!f.fail()) {
		f.close();
		readFromFile(c, filename);
		calcAvg(c);
	}
	else if (filename == "new") {
		newClub(c);
	}
	else if (f.fail()) {
		cout << "Failure to open file!" << endl;
		newClub(c);
		system("pause");
	}
	
	
} // startUp()
void printPlayer(aClub & c) {
	for (int i = 0; i < c.numPlayers; i++) {
		cout << c.player[i].name << "	Avg: " << c.player[i].avgScore << "		#Games: " << c.player[i].numGames << endl;
		if (c.player[i].numGames > 0) {
			for (int j = 0; j < c.player[i].numGames; j++) {
				cout << "	";
				cout << c.player[i].game[j].date << " Score: " << c.player[i].game[j].totalScore;
				cout << " #Holes: " << c.player[i].game[j].numHoles << "		Course: " << c.player[i].game[j].name << endl;
				cout << " [";
				for (int k = 0; k < c.player[i].game[j].numHoles; k++) {
					int scores = c.player[i].game[j].hole[k];
					cout << scores << ", ";
				}
				cout << " ]" << endl;
			}
		}
		cout << "" << endl;
	}
}
//-----------------------------------------------------------------------------
//                                 printClub
//-----------------------------------------------------------------------------
void printClub(aClub & c) {
	cout << "			-------------------------------------" << endl;
	cout << "				" << c.name << "                " << endl;
	cout << "			-------------------------------------" << endl;
	cout << "Number of Players: " << c.numPlayers << " Club Hole Avg: " << c.holeAvg << endl;
	printPlayer(c);

}

// printClub()

//-----------------------------------------------------------------------------
//                               addPlayer
//-----------------------------------------------------------------------------
// Modifies: a club structure
// If the list of players is not full, initializes the next available element
// in the club's player list and asks the user for the new player's name.
//-----------------------------------------------------------------------------
void addPlayer(aClub & c) {
	aPlayer p;
	initPlayer(p);
	string name;
	int size = c.numPlayers;
	if (c.numPlayers < MAX_PLAYERS) {

		for (int i = 0; i <= size + 1; i++) {
			if (i == size) {

				cout << "Enter new player name: ";
				cin >> name;
				p.name = name;
				c.player[i] = p;
				c.numPlayers++;
			}
		}
		cout << "Added player!" << endl;
	}
	else {
		cout << "List is full!" << endl;
	}


} // addPlayer()

  //-----------------------------------------------------------------------------
  //                               dropPlayer
  //-----------------------------------------------------------------------------
  // Modifies: a club structure
  // Allows the user to select a player for deletion from the club's Player list
  // and deletes it.
  //-----------------------------------------------------------------------------
void dropPlayer(aClub & c) {
	cout << "Player list: " << endl;
	string playerName;
	for (int i = 0; i <= c.numPlayers; i++) {
		cout << c.player[i].name << endl;
	}
	string name;
	cout << "Enter player name: ";
	cin >> name;
	for (int i = 0; i <= c.numPlayers; i++)
	{
		if (c.player[i].name == name) {
			c.player[i] = c.player[i + 1];
		}
	}
	cout << "Player dropped." << endl;
	c.numPlayers--;
} // dropPlayer()

  //-----------------------------------------------------------------------------
  //                               addGame
  //-----------------------------------------------------------------------------
  // Modifies: a club structure
  // Adds game data for a new game to a player in the club
  //-----------------------------------------------------------------------------
void addGame(aClub & c) {
	int numHoles;
	cout << "Player list: " << endl;
	string playerName;
	for (int i = 0; i <= c.numPlayers; i++) {
		cout << c.player[i].name << endl;
	}
	cout << "Enter player name: ";
	getline(cin, playerName);
	for (int i = 0; i <= c.numPlayers; i++) {
		if (c.player[i].name == playerName) {

			cout << "Enter course name: ";
			cin >> c.player[i].game[i].name;
			cout << "Enter Date: ";
			cin >> c.player[i].game[i].date;
			cout << "Enter number of holes played: ";
			cin >> numHoles;
			c.player[i].numGames++;
			if (numHoles < 1 && numHoles>18) {
				cout << "Enter between 1 and 18:";
				cin >> numHoles;
			}
			c.player[i].game[i].numHoles = numHoles;
			for (int i = 1; i <= 1; i++) {
				cout << "Enter score for each hole, with spaces between: ";
				for (int k = 0; k < numHoles; k++) {
					cin >> c.player[k].game[k].hole[k];
				}
			}
		}
	}
}
// addGame(

//-----------------------------------------------------------------------------
//                               sortByName
//-----------------------------------------------------------------------------
// Modifies: a club structure
// Re-orders the club's list of players alphabetically by the players' names
//-----------------------------------------------------------------------------
void sortByName(aClub & c) {
	aPlayer temp;
	for (int i = 0; i < c.numPlayers-1; i++) {
		if (c.player[i].name > c.player[i + 1].name) {
			temp = c.player[i];
			c.player[i] = c.player[i + 1];
			c.player[i + 1] = temp;
			sortByName(c);
			system("cls");
		}
	}
	cout << "Players sorted by Name" << endl;

} // sortByName()

  //-----------------------------------------------------------------------------
  //                               sortByAvg
  //-----------------------------------------------------------------------------
  // Modifies:  a club structure
  // Re-orders the club's list of players by their Average Score, high to low
  //-----------------------------------------------------------------------------
void sortByAvg(aClub & c) {
	aPlayer temp;
	for (int i = 0; i < c.numPlayers; i++) {
		if (c.player[i].avgScore < c.player[i + 1].avgScore) {
			temp = c.player[i];
			c.player[i] = c.player[i + 1];
			c.player[i + 1] = temp;
			sortByAvg(c);
			system("cls");
		}
	}
	cout << "Players sorted by avg" << endl;
} // sortByAvg()

  //-----------------------------------------------------------------------------
  //                               saveData
  //-----------------------------------------------------------------------------
  // Given: a club structure
  // Asks the user for an output file name and, if successfully opened, writes
  // all club data to the file.
  //-----------------------------------------------------------------------------
void saveData(aClub & c) {
	ofstream f;
	string name;
	cout << "Enter output file name (or none):";
	cin >> name;
	f.open(name);
	if (name == "none") {
		exit;

	}
	else if (f.fail()) {
		cout << "Failed to open file" << endl;
	}
	else {
		f << c.numPlayers << c.holeAvg << c.name;
		for (int i = 0; i < c.numPlayers; i++) {
			f << c.player[i].numGames << c.player[i].name << endl;
			f << c.player[i].game[i].numHoles << c.player[i].game[i].date << c.player[i].game[i].name << endl;
			f << c.player[i].game[i].hole[i];
		}
	}
	f.close();
} // saveData()

  //-----------------------------------------------------------------------------
  //                               getMenuOption
  //-----------------------------------------------------------------------------
  // Returns: the valid menu option chosen by the user
  // Displays the main menu and gets the user's option
  //----------------------------------------------------------------------------
int getMenuOption() {
	int option;
	printLogo();
	cout << "1. Add Player \n";
	cout << "2. Drop Player \n";
	cout << "3. Add Game Data for Player \n";
	cout << "4. Print Club Report \n";
	cout << "5. Sort Players by Average \n";
	cout << "6. Sort Players by Name \n";
	cout << EXIT_OPTION << ". Exit \n";
	cin >> option;
	// ADD CODE: to ask and validate the option

	return option;
} // getMenuOption()

  //-----------------------------------------------------------------------------
  //                                 main
  //-----------------------------------------------------------------------------
void main() {
	aClub club;
	startUp(club);

	int option = 0;
	while (option != EXIT_OPTION) {
		option = getMenuOption();
		switch (option) {
		case 1: addPlayer(club);  break;
		case 2: dropPlayer(club); break;
		case 3: addGame(club);    break;
		case 4: printClub(club);  break;
		case 5: sortByAvg(club);  break;
		case 6: sortByName(club); break;
		case EXIT_OPTION: saveData(club);
		}
		system("pause");
	}
} // main()