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

	//Creation of the window
	sf::RenderWindow window(sf::VideoMode(1920,1080),"It's a Wonderful World!",sf::Style::Titlebar|sf::Style::Close);

	//Creation of the instance of sf::Event class that will received user's inputs.
	sf::Event event;

	//Main Loop active while the window is still open
	while (window.isOpen())
		{
			//Clear the content of the window
			window.clear();

			//Test if an event happens and save it in "event"
			while (window.pollEvent(event))
			{
				//Command to close the window
				if (event.type == sf::Event::Closed){
					window.close();}
				/*TODO USER INPUT
				 if (event.type == sf::Event::KeyPressed) {
					c = event.text.unicode;
					if (event.key.code <= 36){
	                input += KEY_NAMES[event.key.code];}
	            */
			}

			//Draw the differents sprite in the window
			window.draw(scene.getBackground());

			//Display the new content of the window
			window.display();
		}
    cout << "It worked !" << endl;

    return 0;
}
