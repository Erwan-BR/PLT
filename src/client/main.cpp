#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>


void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include <state.h>
#include <render2.h>

using namespace std;
using namespace state;
using namespace render2;

int main(int argc,char* argv[])
{
	//Creation of testing instances of Player class
	Player* player1 = new Player();
	Player* player2 = new Player();

	//Creation of the vector players
	vector<Player*> players;
	players.push_back(player1);
	players.push_back(player2);

	//Creation of the instance of the Game class
	Game* game = new Game(players);

	//Creation of the instance of the Scene class
	Scene scene = Scene(game);

	//Enter the Displaying loop
	while (scene.isOpen())
		{
			//Erase the content of the window
			scene.erase();


			//Redraw the new content of the window
			scene.draw();

			//Display the new content of the window
			scene.display();
		}

    cout << "It worked !" << endl;

    return 0;
}
