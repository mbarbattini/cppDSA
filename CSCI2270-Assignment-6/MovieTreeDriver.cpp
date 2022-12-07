#include "MovieTree.hpp"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {

	MovieTree m = MovieTree();
	// read all the movies
	ifstream file("Movies.csv");
	string title, ranking, year, rating;
	
	while(getline(file, ranking, ',')) {
		getline(file, title, ',');
		getline(file, year, ',');
		getline(file, rating);
		m.addMovieNode(stoi(ranking), title, stoi(year), stof(rating));
	}

	//m.addMovieNode(4, "Interstellar", 2014, 9.8);
	//m.addMovieNode(2, "Good Will Hunting", 1990, 8.9);
	//m.addMovieNode(10, "Zoo", 7474, 9.3);
	//m.addMovieNode(90, "Goodgood", 2088, 1.5);

	m.printMovieInventory();

	//m.findMovie("Oldboy");
	//m.findMovie("asdkjf");

	m.findMovie("Interstellar");

	//m.queryMovies(9.0, 1900);
	m.averageRating();
}
