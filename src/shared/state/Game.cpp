#include "Game.h"
#include <algorithm>
#include <random>
#include <fstream>

namespace state {
	///@brief Create an instance of the class Game
	Game::Game() :
		Observable(),
		players()
	{
	}

	///@brief Create an instance of the class Game with players specified
	///@param players Vector of pointers which designate the players of the game
	Game::Game(std::vector<Player*> players) :
		Observable(),
		players(players),
		turn(0),
		phase(PRODUCTION),
		deck(),
		isClockwise(true)
	{
	}

	///@brief Create an instance of the class Game with players specified. isTestingGame passed for the creation of a testing game.
	///@param players Vector of pointers which designate the players of the game.
	/// @param isTestingGame Define if the game is created to be played or just for testing.
	Game::Game(std::vector<Player*> players, bool isTestingGame) :
		Observable(),
		players(players),
		isTestingGame(isTestingGame)
	{
	}

	///@brief Destructor of the Class Game
	Game::~Game ()
	{
		// Delete all cards from the deck.
		for (DevelopmentCard* card : this->deck)
		{
			delete card;
		}
	}

	///@brief Initialize the game
	void Game::initGame ()
	{
		std::vector<EmpireCard*> empires = this->initEmpire();
		this->initCards();
		this->initPlayers(empires);
		this->startGame();
	}

	///@brief Create and Initialize the Cards for the game
	void Game::initCards ()
	{
		this->createCards();

		// Shuffle the cards only if the game is not for testing purpose.
		if (! this->isTestingGame)
		{
			auto rng = std::default_random_engine {};
			std::shuffle(std::begin(deck), std::end(deck), rng);
		}
	}

	/// @brief Distributes the empires to the players
	void Game::initPlayers (std::vector<EmpireCard*> empires)
	{
		// Checking if the number of players is inferior of the number of empires. We should always enter inside.
		if (this->players.size() <= empires.size())
		{
			for(Player* player : this->players)
			{
				// Initialise the empires that will be given to the players
				int empireIndex = 0;
				player->setEmpire(empires[empireIndex]);
				empireIndex++;
			}
		}
	}

	/// @brief Create all cards of the game and add them to the deck.
	void Game::createCards()
	{
		/****************************************** Beginning of PROJECT cards ******************************************/

		// Agence d'espionnage
		for (int i = 0; i < 2; i++)
		{
			sf::Texture designAgenceEspionnage;
			designAgenceEspionnage.loadFromFile("./resources/img/Cards/Development_Cards/agence_d_espionnage.png");
			DevelopmentCard* agenceEspionnage = new DevelopmentCard ("Agence d'espionnage",
			{new ResourceToProduce{ResourceType::EXPLORATION, 2, CardType::NONETYPE}},
			designAgenceEspionnage,
			new CardVictoryPoint{2, CardType::NONETYPE},
			CardType::PROJECT,
			2,
			{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},
			{},
			ResourceType::EXPLORATION);
			this->deck.push_back(agenceEspionnage);
		}

		// Ascenceur Spatial
		sf::Texture designAscenceurSpatial;
		designAscenceurSpatial.loadFromFile("./resources/img/Cards/Development_Cards/ascenceur_spatial.png");
		DevelopmentCard* ascenceurSpatial = new DevelopmentCard ("Ascenceur spatial",
		{},
		designAscenceurSpatial,
		new CardVictoryPoint{1, (int) ResourceType::FINANCIER},
		CardType::PROJECT,
		1,
		{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},
		{ResourceType::COLONEL},
		ResourceType::ENERGY);
		this->deck.push_back(ascenceurSpatial);

		// Barrage Geant
		sf::Texture designBarrageGeant;
		designBarrageGeant.loadFromFile("./resources/img/Cards/Development_Cards/barrage_geant.png");
		DevelopmentCard* barrageGeant = new DevelopmentCard ("Barrage geant",
		{new ResourceToProduce{ResourceType::ENERGY, 4, CardType::NONETYPE}},
		designBarrageGeant,
		new CardVictoryPoint{1, (int) CardType::NONETYPE},
		CardType::PROJECT,
		1,
		{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},
		{},
		ResourceType::ENERGY);
		this->deck.push_back(barrageGeant);

		// Base Lunaire
		sf::Texture designBaseLunaire;
		designBaseLunaire.loadFromFile("./resources/img/Cards/Development_Cards/base_lunaire.png");
		DevelopmentCard* baseLunaire = new DevelopmentCard ("Base lunaire",
		{},
		designBaseLunaire,
		new CardVictoryPoint{10, (int) CardType::NONETYPE},
		CardType::PROJECT,
		1,
		{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::KRYSTALLIUM, false}},
		{ResourceType::COLONEL, ResourceType::COLONEL},
		ResourceType::EXPLORATION);
		this->deck.push_back(baseLunaire);

		// Base Lunaire
		sf::Texture designBasePolaire;
		designBasePolaire.loadFromFile("./resources/img/Cards/Development_Cards/base_polaire.png");
		DevelopmentCard* basePolaire = new DevelopmentCard ("Base polaire",
		{new ResourceToProduce{ResourceType::EXPLORATION, 3, CardType::NONETYPE}},
		designBasePolaire,
		new CardVictoryPoint{2, (int) CardType::DISCOVERY},
		CardType::PROJECT,
		1,
		{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},
		{ResourceType::COLONEL},
		ResourceType::EXPLORATION);
		this->deck.push_back(basePolaire);

		// Canon Solaire
		sf::Texture designCanonSolaire;
		designCanonSolaire.loadFromFile("./resources/img/Cards/Development_Cards/canon_solaire.png");
		DevelopmentCard* canonSolaire = new DevelopmentCard ("Canon solaire",
		{},
		designCanonSolaire,
		new CardVictoryPoint{1, (int) ResourceType::COLONEL},
		CardType::PROJECT,
		1,
		{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},
		{ResourceType::COLONEL},
		ResourceType::ENERGY);
		this->deck.push_back(canonSolaire);

		// Centre de propagande
		for (int i = 0; i < 2; i++)
		{
			sf::Texture designCentrePropagande;
			designCentrePropagande.loadFromFile("./resources/img/Cards/Development_Cards/centre_de_propagande.png");
			DevelopmentCard* centrePropagande = new DevelopmentCard ("Centre de propagande",
			{new ResourceToProduce{ResourceType::GOLD, 1, CardType::PROJECT}},
			designCentrePropagande,
			new CardVictoryPoint{1, (int) CardType::NONETYPE},
			CardType::PROJECT,
			2,
			{new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},
			{ResourceType::COLONEL},
			ResourceType::GOLD);
			this->deck.push_back(centrePropagande);
		}

		// Congres Mondial
		sf::Texture designCongresMondial;
		designCongresMondial.loadFromFile("./resources/img/Cards/Development_Cards/congres_mondial.png");
		DevelopmentCard* congresMondial = new DevelopmentCard ("Congres mondial",
		{},
		designCongresMondial,
		new CardVictoryPoint{3, (int) CardType::PROJECT},
		CardType::PROJECT,
		1,
		{new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::FINANCIER, false}, new ResourceToPay{ResourceType::FINANCIER, false}},
		{},
		ResourceType::GOLD);
		this->deck.push_back(congresMondial);

		// Exposition universelle
		sf::Texture designExpositionUniverselle;
		designExpositionUniverselle.loadFromFile("./resources/img/Cards/Development_Cards/exposition_universelle.png");
		DevelopmentCard* expositionUniverselle = new DevelopmentCard ("Exposition Universelle",
		{},
		designExpositionUniverselle,
		new CardVictoryPoint{3, (int) CardType::PROJECT},
		CardType::PROJECT,
		1,
		{new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::FINANCIER, false}, new ResourceToPay{ResourceType::FINANCIER, false}},
		{},
		ResourceType::GOLD);
		this->deck.push_back(expositionUniverselle);
		
		// Laboratoire secret
		for (int i = 0; i < 2; i++)
		{
			sf::Texture designLaboratoireSecret;
			designLaboratoireSecret.loadFromFile("./resources/img/Cards/Development_Cards/laboratoire_secret.png");
			DevelopmentCard* laboratoireSecret = new DevelopmentCard ("Laboratoire secret",
			{new ResourceToProduce{ResourceType::SCIENCE, 1, CardType::NONETYPE}},
			designLaboratoireSecret,
			new CardVictoryPoint{1, (int) CardType::RESEARCH},
			CardType::PROJECT,
			2,
			{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},
			{ResourceType::KRYSTALLIUM},
			ResourceType::SCIENCE);
			this->deck.push_back(laboratoireSecret);
		}

		// Monument national
		sf::Texture designMonumentNational;
		designMonumentNational.loadFromFile("./resources/img/Cards/Development_Cards/monument_national.png");
		DevelopmentCard* monumentNational = new DevelopmentCard ("Monument national",
		{},
		designMonumentNational,
		new CardVictoryPoint{2, (int) CardType::PROJECT},
		CardType::PROJECT,
		1,
		{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},
		{},
		ResourceType::SCIENCE);
		this->deck.push_back(monumentNational);

		// Musee
		for (int i = 0; i < 2; i++)
		{
			sf::Texture designMusee;
			designMusee.loadFromFile("./resources/img/Cards/Development_Cards/musee.png");
			DevelopmentCard* musee = new DevelopmentCard ("Musee",
			{},
			designMusee,
			new CardVictoryPoint{2, (int) CardType::DISCOVERY},
			CardType::PROJECT,
			2,
			{new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},
			{},
			ResourceType::EXPLORATION);
			this->deck.push_back(musee);
		}

		// Societe secrete
		for (int i = 0; i < 2; i++)
		{
			sf::Texture designSocieteSecrete;
			designSocieteSecrete.loadFromFile("./resources/img/Cards/Development_Cards/societe_secrete.png");
			DevelopmentCard* societeSecrete = new DevelopmentCard ("Societe secrete",
			{},
			designSocieteSecrete,
			new CardVictoryPoint{1, (int) ResourceType::FINANCIER},
			CardType::PROJECT,
			2,
			{new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::KRYSTALLIUM, false}},
			{},
			ResourceType::GOLD);
			this->deck.push_back(societeSecrete);
		}

		// Tour geante
		sf::Texture designTourGeante;
		designTourGeante.loadFromFile("./resources/img/Cards/Development_Cards/tour_geante.png");
		DevelopmentCard* tourGeante = new DevelopmentCard ("Tour geante",
		{},
		designTourGeante,
		new CardVictoryPoint{10, (int) CardType::NONETYPE},
		CardType::PROJECT,
		1,
		{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::FINANCIER, false}},
		{},
		ResourceType::GOLD);
		this->deck.push_back(tourGeante);

		// Train magnetique
		sf::Texture designTrainMagnetique;
		designTrainMagnetique.loadFromFile("./resources/img/Cards/Development_Cards/train_magnetique.png");
		DevelopmentCard* tourGeante = new DevelopmentCard ("Train magnetique",
		{new ResourceToProduce{ResourceType::GOLD, 1, CardType::STRUCTURE}},
		designTrainMagnetique,
		new CardVictoryPoint{2, (int) CardType::NONETYPE},
		CardType::PROJECT,
		1,
		{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},
		{ResourceType::FINANCIER, ResourceType::FINANCIER},
		ResourceType::GOLD);
		this->deck.push_back(tourGeante);

		// Universite
		sf::Texture designUniversite;
		designUniversite.loadFromFile("./resources/img/Cards/Development_Cards/universite.png");
		DevelopmentCard* universite = new DevelopmentCard ("Universite",
		{new ResourceToProduce{ResourceType::SCIENCE, 1, CardType::PROJECT}},
		designUniversite,
		new CardVictoryPoint{2, (int) CardType::NONETYPE},
		CardType::PROJECT,
		1,
		{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},
		{},
		ResourceType::SCIENCE);
		this->deck.push_back(universite);

		// Ville-casino
		for (int i = 0; i < 2; i++)
		{
			sf::Texture designVilleCasino;
			designVilleCasino.loadFromFile("./resources/img/Cards/Development_Cards/ville_casino.png");
			DevelopmentCard* villeCasino = new DevelopmentCard ("Ville casino",
			{new ResourceToProduce{ResourceType::GOLD, 2, CardType::NONETYPE}},
			designVilleCasino,
			new CardVictoryPoint{1, (int) ResourceType::FINANCIER},
			CardType::PROJECT,
			2,
			{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},
			{ResourceType::FINANCIER},
			ResourceType::GOLD);
			this->deck.push_back(villeCasino);
		}

		// Ville sous-marine
		for (int i = 0; i < 2; i++)
		{
			sf::Texture designVilleSousMarine;
			designVilleSousMarine.loadFromFile("./resources/img/Cards/Development_Cards/ville_sous_marine.png");
			DevelopmentCard* villeSousMarine = new DevelopmentCard ("Ville sous-marine",
			{new ResourceToProduce{ResourceType::SCIENCE, 1, CardType::NONETYPE}, new ResourceToProduce{ResourceType::EXPLORATION, 2, CardType::NONETYPE}},
			designVilleSousMarine,
			new CardVictoryPoint{3, (int) CardType::NONETYPE},
			CardType::PROJECT,
			2,
			{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},
			{},
			ResourceType::EXPLORATION);
			this->deck.push_back(villeSousMarine);
		}

		// Ville souterraine
		for (int i = 0; i < 2; i++)
		{
			sf::Texture designVilleSouterraine;
			designVilleSouterraine.loadFromFile("./resources/img/Cards/Development_Cards/ville_souterraine.png");
			DevelopmentCard* villeSouterraine = new DevelopmentCard ("Ville souterraine",
			{new ResourceToProduce{ResourceType::MATERIAL, 2, CardType::NONETYPE}, new ResourceToProduce{ResourceType::ENERGY, 2, CardType::NONETYPE}},
			designVilleSouterraine,
			new CardVictoryPoint{3, (int) CardType::NONETYPE},
			CardType::PROJECT,
			2,
			{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},
			{ResourceType::KRYSTALLIUM},
			ResourceType::ENERGY);
			this->deck.push_back(villeSouterraine);
		}

		// Zone portuaire
		for (int i = 0; i < 2; i++)
		{
			sf::Texture designZonePortuaire;
			designZonePortuaire.loadFromFile("./resources/img/Cards/Development_Cards/zone_portuaire.png");
			DevelopmentCard* zonePortuaire = new DevelopmentCard ("Zone portuaire",
			{new ResourceToProduce{ResourceType::MATERIAL, 2, CardType::NONETYPE}, new ResourceToProduce{ResourceType::GOLD, 2, CardType::NONETYPE}},
			designZonePortuaire,
			new CardVictoryPoint{2, (int) CardType::NONETYPE},
			CardType::PROJECT,
			2,
			{new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},
			{ResourceType::FINANCIER, ResourceType::FINANCIER},
			ResourceType::GOLD);
			this->deck.push_back(zonePortuaire);
		}

		/****************************************** Beginning of RESEARCH cards ******************************************/
		// Amelioration genetique
		sf::Texture designAmeliorationGenetique;
		designAmeliorationGenetique.loadFromFile("./resources/img/Cards/Development_Cards/amelioration_genetique.png");
		DevelopmentCard* ameliorationGenetique = new DevelopmentCard ("Amelioration genetique",
		{},
		designAmeliorationGenetique,
		new CardVictoryPoint{3, (int) CardType::NONETYPE},
		CardType::RESEARCH,
		1,
		{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},
		{ResourceType::FINANCIER, ResourceType::FINANCIER},
		ResourceType::SCIENCE);
		this->deck.push_back(ameliorationGenetique);

		/* Arguments de DevelopmentCard
		std::string name,
		std::vector<ResourceToProduce*> productionGain,
		sf::Texture design,
		CardVictoryPoint* victoryPoints,
		CardType type,
		int numberOfCopies,
		std::vector<ResourceToPay*> costToBuild,
		std::vector<ResourceType> instantGain,
		ResourceType discardGain*/

		// Pour en ajouter un, copier coller l'amélioration génétique, changer les valeurs puis replier le code de l'amélioration géntique. Puis recommencer encore et encore.
	}

	///@brief Create and Initialize the Empire for the game
	std::vector<EmpireCard*> Game::initEmpire ()
	{	
		// face B
		ResourceToProduce* firstResourceToProduce = new ResourceToProduce{ResourceType::MATERIAL, 2, CardType::NONETYPE};
    	ResourceToProduce* secondResourceToProduce = new ResourceToProduce{ResourceType::ENERGY, 1, CardType::NONETYPE};
    	ResourceToProduce* thirdResourceToProduce = new ResourceToProduce{ResourceType::SCIENCE, 1, CardType::NONETYPE};
		std::vector<ResourceToProduce*> productionGainB = {firstResourceToProduce,secondResourceToProduce, thirdResourceToProduce};		

		// empire AFRICA
		ResourceToProduce* firstResourceToProduceAFRICA = new ResourceToProduce{ResourceType::MATERIAL, 2, CardType::NONETYPE};
    	ResourceToProduce* secondResourceToProduceAFRICA = new ResourceToProduce{ResourceType::SCIENCE, 2, CardType::NONETYPE};
		std::vector<ResourceToProduce*> productionGainAFRICA = {firstResourceToProduceAFRICA, secondResourceToProduceAFRICA};
		sf::Texture designAFRICA;
		designAFRICA.loadFromFile("./resources/img/Cards/Empire_Face_A/Panafricaine.png");
		sf::Texture designAFRICA_FaceB;
		//designAFRICA_FaceB.loadFromFile("./resources/img/Cards/Empire_Face_B/Panafricaine.png");
   		CardVictoryPoint* victoryPointsAFRICA  = new CardVictoryPoint{2,CardType::RESEARCH};
		EmpireCard* africa = new EmpireCard("AFRICA", productionGainAFRICA, designAFRICA, victoryPointsAFRICA, productionGainB, {0}, AFRICA, designAFRICA_FaceB);
	
		// empire NORAM
		ResourceToProduce* firstResourceToProduceNORAM = new ResourceToProduce{ResourceType::MATERIAL, 3, CardType::NONETYPE};
    	ResourceToProduce* secondResourceToProduceNORAM = new ResourceToProduce{ResourceType::GOLD, 1, CardType::NONETYPE};
		std::vector<ResourceToProduce*> productionGainNORAM = {firstResourceToProduceNORAM, secondResourceToProduceNORAM};
		sf::Texture designNORAM;
		designNORAM.loadFromFile("./resources/img/Cards/Empire_Face_A/Noram.png");
		sf::Texture designNORAM_FaceB;
		//designNORAM_FaceB.loadFromFile("./resources/img/Cards/Empire_Face_B/Noram.png");
   		CardVictoryPoint* victoryPointsNORAM  = new CardVictoryPoint{1, ResourceType::FINANCIER};
		EmpireCard* noram = new EmpireCard("NORAM", productionGainNORAM, designNORAM, victoryPointsNORAM, productionGainB, {0}, NORAM, designNORAM_FaceB);
		
		// empire ASIA
		ResourceToProduce* firstResourceToProduceASIA = new ResourceToProduce{ResourceType::MATERIAL, 1, CardType::NONETYPE};
    	ResourceToProduce* secondResourceToProduceASIA = new ResourceToProduce{ResourceType::GOLD, 2, CardType::NONETYPE};
		std::vector<ResourceToProduce*> productionGainASIA = {firstResourceToProduceASIA, secondResourceToProduceASIA};
		sf::Texture designASIA;
		designASIA.loadFromFile("./resources/img/Cards/Empire_Face_A/Asia.png");
		sf::Texture designASIA_FaceB;
		//designASIA_FaceB.loadFromFile("./resources/img/Cards/Empire_Face_B/Asia.png");
   		CardVictoryPoint* victoryPointsASIA  = new CardVictoryPoint{2, CardType::PROJECT};
		EmpireCard* asia = new EmpireCard("ASIA", productionGainASIA, designASIA, victoryPointsASIA, productionGainB, {0}, ASIA, designASIA_FaceB);
		
		// empire EUROPE
		ResourceToProduce* firstResourceToProduceEUROPE = new ResourceToProduce{ResourceType::MATERIAL, 2, CardType::NONETYPE};
    	ResourceToProduce* secondResourceToProduceEUROPE = new ResourceToProduce{ResourceType::ENERGY, 1, CardType::NONETYPE};
    	ResourceToProduce* thirdResourceToProduceEUROPE = new ResourceToProduce{ResourceType::SCIENCE, 1, CardType::NONETYPE};
		std::vector<ResourceToProduce*> productionGainEUROPE = {firstResourceToProduceEUROPE, secondResourceToProduceEUROPE, thirdResourceToProduceEUROPE};
		sf::Texture designEUROPE;
		designEUROPE.loadFromFile("./resources/img/Cards/Empire_Face_A/Europa.png");
		sf::Texture designEUROPE_FaceB;
		//designEUROPE_FaceB.loadFromFile("./resources/img/Cards/Empire_Face_B/Europa.png");
   		CardVictoryPoint* victoryPointsEUROPE  = new CardVictoryPoint{1, ResourceType::COLONEL};
		EmpireCard* europe = new EmpireCard("EUROPE", productionGainEUROPE, designEUROPE, victoryPointsEUROPE, productionGainB, {0}, EUROPE, designEUROPE_FaceB);
		
		// empire AZTEC
		ResourceToProduce* firstResourceToProduceAZTEC = new ResourceToProduce{ResourceType::ENERGY, 2, CardType::NONETYPE};
    	ResourceToProduce* secondResourceToProduceAZTEC = new ResourceToProduce{ResourceType::EXPLORATION, 1, CardType::NONETYPE};
		std::vector<ResourceToProduce*> productionGainAZTEC = {firstResourceToProduceAZTEC, secondResourceToProduceAZTEC};
		sf::Texture designAZTEC;
		designAZTEC.loadFromFile("./resources/img/Cards/Empire_Face_A/Azteca.png");
		sf::Texture designAZTEC_FaceB;
		//designAZTEC.loadFromFile("./resources/img/Cards/Empire_Face_B/Azteca.png");
   		CardVictoryPoint* victoryPointsAZTEC  = new CardVictoryPoint{3, CardType::DISCOVERY};
		EmpireCard* aztec = new EmpireCard("AZTEC", productionGainAZTEC, designAZTEC, victoryPointsAZTEC, productionGainB, {0}, AZTEC, designAZTEC_FaceB);

		std::vector<EmpireCard*> empires = {africa, noram, asia, europe, aztec};
		
		// Shuffle if not a testing game.
		if (! this->isTestingGame)
		{
			auto rng = std::default_random_engine {};
			std::shuffle(std::begin(empires), std::end(empires), rng);
		}
		
    	return(empires);
	}

	///@brief Start the game
	void Game::startGame ()
	{
		this->nextPhase();
	}

	///@brief Manage the progress of the game and start the next phase among Draft, Planification and Production
	void Game::nextPhase ()
	{
		if(GamePhase::DRAFT == this->phase)
		{
			this->phase = GamePhase::PLANIFICATION;
			this->initPlanification();
		}
		else if(GamePhase::PLANIFICATION == this->phase)
		{
			this->phase = GamePhase::PRODUCTION;
			this->initProduction();
		}
		else if(GamePhase::PRODUCTION == this->phase)
		{
			this->newTurn();
			this->phase = GamePhase::DRAFT;
			this->initDraft();
		}
		this->notifyObservers();
	}

	///@brief Start one of the four turn of the game
	void Game::newTurn ()
	{
		this->turn = this->turn + 1;
		if ((1 == this->turn && this->isTestingGame) || (4 == this->turn && ! this->isTestingGame))
		{
			this->endGame();
		}

		// Invert the sens for the draft phase
		this->isClockwise = ! this->isClockwise;

		this->notifyObservers();
	}

	///@brief Initialize the Draft part of the game during which players select their cards
	void Game::initDraft ()
	{
		// Deck of cards to send to a player.
		std::vector<DevelopmentCard*> draftingDeck;

		for(Player* player : this->players)
		{
			// Re-Initialise the cards that will be given to the players
			draftingDeck = {};

			for(int i = 0; i < 7; i++)
			{
				// Add a card to draft and delete it from the deck.
				draftingDeck.push_back(this->deck.back());
				this->deck.pop_back();
			}
			
			// Send cards to players.
			player->setDraftingCards(draftingDeck);
		}
		this->notifyObservers();
		this->nextDraft ();
	}

	///@brief Launch the next draft.
	void Game::nextDraft ()
	{
		// Retrieve the number of cards to draft.
		int numberOfCardsToDraft = this->players[0]->getDraftingCards().size();

		// If there is no cards left, we can continue to play.
		if(0 == numberOfCardsToDraft)
		{
			this->endDraft();
		}

		// According of how we are turning cards, behaviour are differents.
		if (this->isClockwise)
		{
			// Memorize the first player deck to give it to the last player.
			std::vector<DevelopmentCard*> firstPlayerDeck = this->players[0]->getDraftingCards();

			// Iterating among all players (except the last one) to make the draft.
			for (long unsigned int playerIndex = 0; playerIndex < this->players.size() - 1; playerIndex++)
			{
				this->players[playerIndex]->setDraftingCards(this->players[(playerIndex + 1)]->getDraftingCards());
			}

			// Giving the deck of the first player to the last one.
			this->players[this->players.size()-1]->setDraftingCards(firstPlayerDeck);
		}
		else
		{
			// Memorize the last player deck to give it to the first player.
			std::vector<DevelopmentCard*> lastPlayerDeck = this->players[(this->players.size()-1)]->getDraftingCards();

			// Iterating among all players (except the first one) to make the draft.
			for (long unsigned int playerIndex = (this->players.size()-1); playerIndex > 0; playerIndex--)
			{
				this->players[playerIndex]->setDraftingCards(this->players[(playerIndex - 1)]->getDraftingCards());
			}

			// Giving the deck of the first player to the last one.
			this->players[0]->setDraftingCards(lastPlayerDeck);
		}

		// Notify observers that the draft is done.
		this->notifyObservers();
	}

	///@brief End the current Draft phase
	void Game::endDraft ()
	{
		this->nextPhase();
	}

	///@brief Initialize the Planification phase during which players choose the cards they will try to build
	void Game::initPlanification ()
	{
		// To-do
		this->endPlanification();
	}

	/// @brief End the planification phase to start the next phase.
	void Game::endPlanification ()
	{
		this->nextPhase();
	}

	/// @brief Init the production phase.
	void Game::initProduction ()
	{
		this->resourceProducing = ResourceType::MATERIAL;
		this->notifyObservers();
		this->nextProduction();
	}

	/// @brief Launch the next production phase if a production phase arrives, launch the next draft phase if not.
	void Game::nextProduction ()
	{
		if (ResourceType::MATERIAL == this->resourceProducing)
		{
			this->produceResource();
			this->resourceProducing = ResourceType::ENERGY;
			this->notifyObservers();
			this->nextProduction ();
		}
		else if (ResourceType::ENERGY == this->resourceProducing)
		{
			this->produceResource();
			this->resourceProducing = ResourceType::SCIENCE;
			this->notifyObservers();
			this->nextProduction ();
		}
		else if (ResourceType::SCIENCE == this->resourceProducing)
		{
			this->produceResource();
			this->resourceProducing = ResourceType::GOLD;
			this->notifyObservers();
			this->nextProduction ();
		}
		else if (ResourceType::GOLD == this->resourceProducing)
		{
			this->produceResource();
			this->resourceProducing = ResourceType::EXPLORATION;
			this->notifyObservers();
			this->nextProduction ();
		}
		else
		{
			this->produceResource();
			this->resourceProducing = ResourceType::KRYSTALLIUM;
			this->notifyObservers();
			this->endProduction();
		}
	}

	///@brief Manage the phase of production for all player and one resource
	void Game::produceResource ()
	{
		// Production of the player in the following loop.
		int playerProduction;

		// Two integers to find the players that win the most of a resources to give him a bonus.
		int playerIndexBiggestProduction = -1;
		int biggestProduction = -1;
		
		bool multipleBiggestProduction = false;

		// Current index of the loop - to update the plkayer with the biggest production
		int index = 0;

		// Iterating among all players.
		for(Player* player : this->players)
		{
			playerProduction = player->getProductionGain(this->resourceProducing);

			player->receiveResources(this->resourceProducing, playerProduction);

			if (playerProduction > biggestProduction)
			{
				// Updating who won the most of the current produced ressource.
				playerIndexBiggestProduction = index;
				biggestProduction = playerProduction;
				multipleBiggestProduction = false;
			}
			else if (playerProduction == biggestProduction)
			{
				playerIndexBiggestProduction = -1;
				multipleBiggestProduction = true;
			}
			index++;
		}

		// Checking who won's the most of this resources for the bonus.
		if (!multipleBiggestProduction)
		{
			// Send the financier token
			if (ResourceType::MATERIAL == this->resourceProducing || ResourceType::GOLD == this->resourceProducing)
			{
				this->players[playerIndexBiggestProduction]->receiveResources(ResourceType::FINANCIER, 1);
			}
			// Send the colonel token
			else if (ResourceType::ENERGY == this->resourceProducing || ResourceType::EXPLORATION == this->resourceProducing)
			{
				this->players[playerIndexBiggestProduction]->receiveResources(ResourceType::COLONEL, 1);
			}
			// Send the token choosen by the player
			else
			{
				// Retrieve which token the player wants to get.
				bool chooseColonel = this->players[playerIndexBiggestProduction]->chooseColonelToken();

				if (chooseColonel)
				{
					this->players[playerIndexBiggestProduction]->receiveResources(ResourceType::COLONEL, 1);
				}
				else
				{
					this->players[playerIndexBiggestProduction]->receiveResources(ResourceType::FINANCIER, 1);
				}
			}
		}
	}

	/// @brief End the production phase.
	void Game::endProduction ()
	{
		this->nextPhase();
	}

	/// @brief Ends the game, counts every player's victory points and compares them to give a podium
	void Game::endGame ()
	{
		std::vector<int> points;
		for(Player* player : this->players)
		{
			points.push_back(player->computeVictoryPoint());
		}
	}

	///@brief Debug method to check the state of the instance of Game
	///@return String explaining the state of Game
	std::string Game::toString () const
	{
		return "";
	}

    /************************************* Setters & Getters *************************************/

	/// @brief Get Players in the game.
	/// @return All players inside the game.
	std::vector<Player*> Game::getPlayers () const
	{
		return this->players;
	}

    /// @brief Get the number of the turn (1 to 4)
    /// @return Number of the turn.
    int Game::getTurn () const
	{
		return this->turn;
	}

    /// @brief Get the phase of the game (planificiation, production, draft)
    /// @return Current phase of the game.
    GamePhase Game::getPhase () const
	{
		return this->phase;
	}

	/// @brief Allows to get the resource that is produced. Returns Krystallium if production is finished.
	/// @return Resource produced / Next one to be produced according to the moment.
	ResourceType Game::getResourceProducing () const
	{
		return this->resourceProducing;
	}
}