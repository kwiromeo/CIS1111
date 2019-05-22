/*
Name:			Irere Romeo Kwihangana
Class:			CIS 1111
Description:	Simple Movie 'Database'.
				This program gives users the ability to store a list of movies
				to a file, display movies seen, and count total movies in on
				file

*/

#include <iostream>
#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

// Function declations
void showMenu();
char promptUser();
void addMovie(string);
bool titleFormat(string);
void countMovies();
void countMovies(int year);
void listMovies();
bool optionValid(char option);
bool optionQuit(char option);
bool yearFormat(int);


// Main program

int main() {

	char userSelect;
	bool selectionValid;
	bool quitProgram;
	
	// Display menu to user
	showMenu();
	
	// Prompt user for input
	userSelect = promptUser();
	while (!optionQuit(userSelect)) {
		
	
		// option A
		if (userSelect == 'A' || userSelect == 'a') {
			//cout << "this is option A" << endl << endl;
			listMovies();
			showMenu();
			userSelect = promptUser();
		
		}

		// Option B - Add a movie to database
		else if (userSelect == 'B' || userSelect == 'b') {
			// cout << "this is option B" << endl;
			
			cout << "  Enter a movie to add to the database. Use the format" << endl
				 << "  [movie title][comma][space][year XXXX]" << endl
				 << "     Title: ";

			string movieTitle;
			cin.ignore();
			getline(cin, movieTitle);

			while (!titleFormat(movieTitle)) {
				cout << endl;
				cout << "  The movie titled entered does not meet the format noted." << endl
					 << "  Please use format [movie title][comma][space][year XXXX]" << endl
					 << "    Title: ";
				//cin.ignore();
				getline(cin, movieTitle);
			}

			addMovie(movieTitle);

			cout << endl << "  " << movieTitle << " has been added to database." << endl;
			
			showMenu();
			userSelect = promptUser();

		}

		// Option C
		else if (userSelect == 'C' || userSelect == 'c') {
			// cout << "this is option C" << endl;
			cout << endl;
			countMovies();
			showMenu();
			userSelect = promptUser();

		}
		// Option D
		else if (userSelect == 'D' || userSelect == 'd') {
			// cout << "This is option D" << endl;
			int year;
			cout << "Enter a year to see releases in the database: ";
			cin >> year;
			
			while (!yearFormat(year)) {

				cout << endl;
				cout << "  The year entered does not meet the format noted." << endl
					 << "  Please use format [XXXX]" << endl
					 << "    year: ";
				cin.ignore();
				cin >> year;
			}

			countMovies(year);
			
			showMenu();
			userSelect = promptUser();
		
		}

	}

	cout << "You are exiting the program. " << endl;
	system("pause");
	return 0;

}


void showMenu() {
	
	// Print out program menu
	string appName = "====== Simple Movie Database - Options ======";
	for (int k = 0; k < appName.length(); k++) cout << "=";
	cout << endl << appName << endl;
	for (int k = 0; k < appName.length(); k++) cout << "=";
	cout << endl;
	// Create menu options
	string opt0, opt1, opt2, opt3, opt4;
	opt0 = "Show movies stored";
	opt1 = "Add a movie to database";
	opt2 = "Count all movies";
	opt3 = "Show movies from a specific year";
	opt4 = "Quit program";
	

	char option[] = {'A', 'B', 'C', 'D', 'Q'};
	string optionName[] = {opt0, opt1, opt2, opt3, opt4};
	
	// Display menu
	for (int k = 0; k < 5; k++)
		cout << option[k] << " - " << optionName[k] << endl;

	for (int k = 0; k < appName.length(); k++) cout << "-";
	cout << endl;

}

char promptUser()
{
	
	char userSelect;
	bool selectionValid;
	
	// Prompt user for option
	cout << endl << "Enter option: ";
	cin >> userSelect;

	// validate user selection
	selectionValid = optionValid(userSelect);
	if (!selectionValid) {

		do {
			cout << endl;
			cout << "You have entered an invalid option." << endl
				 << "     Please enter again" << endl;
			cout << "Enter option: ";
			cin >> userSelect;

			selectionValid = optionValid(userSelect);

		} while (!selectionValid);

	}
	return userSelect;
}

bool optionValid(char option) {

	if (option == 'A' || option == 'a' ||
		option == 'B' || option == 'b' ||
		option == 'C' || option == 'c' ||
		option == 'D' || option == 'd' ||
		option == 'Q' || option == 'q') {
		return true;
	}
	else {
		return false;
	}
}

bool optionQuit(char option) {
	if (option == 'Q' || option == 'q') {
		return true;
	}
	else{
		return false;
	}
}

void listMovies() {
	
	string filename = "movie-db.txt";
	string curr_movie;
	string error_msg = "Error opening database file 'movie-db.txt'\n ";
	
	// create filestream to read the movies in the text file
	ifstream fileRead;
	fileRead.open(filename);

	if (fileRead.fail()) {

		cout << error_msg;
	}
	else
	{
		cout << endl << "Here are the movies in the database: " << endl;
		// Output movies from the file onto console
		while (getline(fileRead, curr_movie)) {

			cout << "  - " << curr_movie << endl;
		}
	}
	
	fileRead.close();

}

void addMovie(string movie) {

	ofstream writeFile;
	string filename = "movie-db.txt";
	
	writeFile.open(filename, ios::out | ios::app);
	writeFile << endl << movie;
	writeFile.close();

}

bool titleFormat(string movieTitle) {
	// Validate movie title format
	// Expected format: [movie title][comma][space][year (XXXX)]
	
	regex format(".+\\b, \\d{4}"); // regex for movie title expected format
	smatch found_match;			 // object to store the found match
	bool formatGood;
	regex_search(movieTitle, found_match, format);
	if (found_match.ready() == true && found_match.empty() == false) {
		formatGood = true;
	}
	else {
		formatGood = false;
	}
	
	return (formatGood);

}

bool yearFormat(int year) {
	
	regex format("\\d{4}");
	smatch found_match;
	string year_str = to_string(year);
	bool formatGood;
	regex_search(year_str, found_match, format);
	if (found_match.ready() == true && found_match.empty() == false) {
		formatGood = true;
	}
	else {
		formatGood = false;
	}

	return (formatGood);
 
}

void countMovies() {

	string filename = "movie-db.txt";
	string curr_movie;
	string error_msg = "Error opening database file 'movie-db.txt'\n ";
	int count = 0;

	// create filestream to read the movies in the text file
	ifstream fileRead;
	fileRead.open(filename);

	if (fileRead.fail()) {

		cout << error_msg;
	}
	else
	{
		// Count total of movies in database
		while (getline(fileRead, curr_movie)) {
			count++;
		}
	}

	fileRead.close();
	
	cout << " There are " << count << " movies in the database" << endl;

}

void countMovies(int year) {

	string filename = "movie-db.txt";
	string curr_movie;
	string all_movies;
	string error_msg = "Error opening database file 'movie-db.txt'\n ";
	string re_str;

	// create filestream to read the movies in the text file
	ifstream fileRead;
	fileRead.open(filename);

	if (fileRead.fail()) {

		cout << error_msg;
	}
	else
	{
		// Get all movies and add them to a a single string
		while (getline(fileRead, curr_movie)) {
			all_movies += (curr_movie + "\n");
		}
	}

	fileRead.close();

	// create search regex string format
	re_str = ".+ " + to_string(year);
	regex format(re_str);	// regex for movie title expected format
	smatch search_results;	// object to store the found movies

	// error case
	regex_search(all_movies, search_results, format);

	if (search_results.empty() && search_results.ready()) {
		cout << endl << "No movie from that year is in the database" << endl;
	}

	// if found
	while (regex_search(all_movies, search_results, format)) {
		cout << search_results.str() << endl;
		all_movies = search_results.suffix();
	}
	
	
	
	cout << endl;
}