#include "CreateAllCards.h"

#include <iostream>
#include <fstream>
#include <json/json.h>
#include <sys/types.h>
#include <dirent.h>
#include <utility>
#include <algorithm>
#include <memory>

namespace state
{
    /// @brief Create all development cards for a game.
    /// @param isTestingGame True if the deck is for a testing game. WIll order some cards at the end of the deck to provide some cards we know.
    /// @return Vector of all development cards.
    constants::deckOfCards CreateAllCards::createAllDevelopmentCards (bool isTestingGame)
    {
        constants::deckOfCards returnValue = {};

        const std::string folderPath = "./resources/cardsJSON/";  // Update this with your actual folder path

        const std::vector<std::string> cardsNameToRetrieve = {"Tour geante", "Tresor de barbe noire", "Zeppelin", "Zeppelin", "Zeppelin", "Zeppelin", "Zeppelin", "Zeppelin", "Ile d avalon", "Centre De La Terre", "Brise glace", "Brise glace", "Brise glace", "Juggernaut"};

        std::vector<std::pair<std::string, constants::devCardPtr>> cards ;

        if (isTestingGame)
        {
            for (std::string nameOfCard : cardsNameToRetrieve)
            {
                cards.push_back(std::make_pair(nameOfCard, nullptr));
            }
        }

        DIR* dir = opendir(folderPath.c_str());
        if (dir == nullptr)
        {
            std::cerr << "Error opening directory: " << folderPath << std::endl;
        }

        struct dirent* entry;
        while ((entry = readdir(dir)) != nullptr)
        {
            if (entry->d_type == DT_REG)
            {
                // Open the file
                std::string filePath = folderPath + entry->d_name;
                std::ifstream file(filePath);
                if (!file.is_open())
                {
                    std::cerr << "Error opening file: " << filePath << std::endl;
                    continue;
                }

                // Read the content of the file into a string
                std::string jsonString((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

                // Parse JSON
                Json::CharReaderBuilder reader;
                Json::Value root;
                std::istringstream jsonStream(jsonString);
                Json::parseFromStream(reader, jsonStream, &root, nullptr);

                for (int i = 0; i < root["numberOfCopies"].asInt(); i++)
                {
                    constants::devCardPtr card = std::make_shared<DevelopmentCard>(root);
                    bool willBeAdded = true;

                    // If it's a testing game, we have to keep in mind the index to retrieve it at the end.
                    if (isTestingGame)
                    {
                        const std::string cardName = card->getName();
                        auto indexOfName = std::find(cardsNameToRetrieve.begin(), cardsNameToRetrieve.end(), cardName);
                        
                        // If the card name is found we have to check if an vesion of this card has been stored
                        if (cardsNameToRetrieve.end() != indexOfName)
                        {
                            for (std::pair<std::string, constants::devCardPtr>& pair: cards)
                            {
                                // Checking if the card has the good name and if it's not added.
                                if (nullptr == pair.second && cardName == pair.first)
                                {
                                    pair.second = card;
                                    willBeAdded = false;
                                    break;
                                }
                            }
                        }
                    }

                    if (willBeAdded)
                    {
                        returnValue.push_back(card);
                    }
                }
            }
        }

        closedir(dir);

        // If the game is a testing game, we have to retrieve some card to play put them at the end.
        if (isTestingGame)
        {
            for (std::pair<std::string, constants::devCardPtr> pair: cards)
            {
                if (nullptr != pair.second)
                {
                    returnValue.push_back(pair.second);
                }
            }
        }

        return returnValue;
    }

    /// @brief Create all empire cards for a game.
    /// @param isFaceA States if the game is played with face A or not.
    /// @return Vector of all empire cards.
    constants::deckOfEmpires CreateAllCards::createAllEmpireCards (bool isFaceA)
    {
        constants::empireCardPtr africa = createEmpireAFRICA(isFaceA);
        constants::empireCardPtr noram = createEmpireNORAM(isFaceA);
        constants::empireCardPtr europe = createEmpireEUROPE(isFaceA);
        constants::empireCardPtr asia = createEmpireASIA(isFaceA);
        constants::empireCardPtr aztec = createEmpireAZTEC(isFaceA);

        constants::deckOfEmpires empires = {asia, aztec, africa, noram, europe};
        
        return empires;
    }

    /// @brief Create the empire card AFRICA.
    /// @param isFaceA State if the empire is played with face A or B.
    /// @return Pointer to the AFRICA empire.
    constants::empireCardPtr CreateAllCards::createEmpireAFRICA (bool isFaceA)
    {
        constants::resourceProdList productionGainB = createFaceBOfEmpires();
        
        constants::resourceProdPtr firstResourceToProduceAFRICA = std::make_shared<ResourceToProduce>();
        firstResourceToProduceAFRICA->type = ResourceType::MATERIAL;
        firstResourceToProduceAFRICA->quantity = 2;
        firstResourceToProduceAFRICA->cardType = CardType::NONETYPE;
        
        constants::resourceProdPtr secondResourceToProduceAFRICA = std::make_shared<ResourceToProduce>();
        secondResourceToProduceAFRICA->type = ResourceType::SCIENCE;
        secondResourceToProduceAFRICA->quantity = 2;
        secondResourceToProduceAFRICA->cardType = CardType::NONETYPE;
        constants::resourceProdList productionGainAFRICA = {firstResourceToProduceAFRICA, secondResourceToProduceAFRICA};
        
        std::string africa_FaceA = "./resources/img/Cards/Empire_Face_A/Panafricaine.png";
        std::string africa_FaceB = "./resources/img/Cards/Empire_Face_B/Panafricaine.png";
        
        constants::victoryPointsPtr victoryPointsAFRICA = std::make_shared<state::CardVictoryPoint>();
        victoryPointsAFRICA->numberOfPoints = 2;
        victoryPointsAFRICA->cardOrResourceType = static_cast<int>(CardType::RESEARCH);
        
        constants::empireCardPtr africa = std::make_shared<EmpireCard>("AFRICA", productionGainAFRICA, africa_FaceA, victoryPointsAFRICA, productionGainB, AFRICA, africa_FaceB, isFaceA);
        
        return africa;
    }

    /// @brief Create the empire card ASIA.
    /// @param isFaceA State if the empire is played with face A or B.
    /// @return Pointer to the ASIA empire.
    constants::empireCardPtr CreateAllCards::createEmpireASIA (bool isFaceA)
    {
        constants::resourceProdList productionGainB = createFaceBOfEmpires();

        constants::resourceProdPtr firstResourceToProduceASIA = std::make_shared<ResourceToProduce>();
        firstResourceToProduceASIA->type = ResourceType::MATERIAL;
        firstResourceToProduceASIA->quantity = 1;
        firstResourceToProduceASIA->cardType = CardType::NONETYPE;

        constants::resourceProdPtr secondResourceToProduceASIA = std::make_shared<ResourceToProduce>();
        secondResourceToProduceASIA->type = ResourceType::GOLD;
        secondResourceToProduceASIA->quantity = 2;
        secondResourceToProduceASIA->cardType = CardType::NONETYPE;
        constants::resourceProdList productionGainASIA = {firstResourceToProduceASIA, secondResourceToProduceASIA};
        
        std::string asia_FaceA = "./resources/img/Cards/Empire_Face_A/Asia.png";
        std::string asia_FaceB = "./resources/img/Cards/Empire_Face_B/Asia.png";
        
        constants::victoryPointsPtr victoryPointsASIA  = std::make_shared<state::CardVictoryPoint>();
        victoryPointsASIA->numberOfPoints = 2;
        victoryPointsASIA->cardOrResourceType = static_cast<int>(CardType::PROJECT);
        
        constants::empireCardPtr asia = std::make_shared<EmpireCard>("ASIA", productionGainASIA, asia_FaceA, victoryPointsASIA, productionGainB, ASIA, asia_FaceB, isFaceA);
        
        return asia;
    }
    
    /// @brief Create the empire card AZTEC.
    /// @param isFaceA State if the empire is played with face A or B.
    /// @return Pointer to the AZTEC empire.
    constants::empireCardPtr CreateAllCards::createEmpireAZTEC (bool isFaceA)
    {
        constants::resourceProdList productionGainB = createFaceBOfEmpires();

        constants::resourceProdPtr firstResourceToProduceAZTEC = std::make_shared<ResourceToProduce>();
        firstResourceToProduceAZTEC->type = ResourceType::ENERGY;
        firstResourceToProduceAZTEC->quantity = 2;
        firstResourceToProduceAZTEC->cardType = CardType::NONETYPE;

        constants::resourceProdPtr secondResourceToProduceAZTEC = std::make_shared<ResourceToProduce>();
        secondResourceToProduceAZTEC->type = ResourceType::EXPLORATION;
        secondResourceToProduceAZTEC->quantity = 1;
        secondResourceToProduceAZTEC->cardType = CardType::NONETYPE;
        constants::resourceProdList productionGainAZTEC = {firstResourceToProduceAZTEC, secondResourceToProduceAZTEC};

        std::string aztec_FaceA = "./resources/img/Cards/Empire_Face_A/Azteca.png";
        std::string aztec_FaceB = "./resources/img/Cards/Empire_Face_B/Azteca.png";

        constants::victoryPointsPtr victoryPointsAZTEC  = std::make_shared<state::CardVictoryPoint>();
        victoryPointsAZTEC->numberOfPoints = 3;
        victoryPointsAZTEC->cardOrResourceType = static_cast<int>(CardType::DISCOVERY);

        constants::empireCardPtr aztec = std::make_shared<EmpireCard>("AZTEC", productionGainAZTEC, aztec_FaceA, victoryPointsAZTEC, productionGainB, AZTEC, aztec_FaceB, isFaceA);

        return aztec;
    }
    
    /// @brief Create the empire card EUROPE.
    /// @param isFaceA State if the empire is played with face A or B.
    /// @return Pointer to the EUROPE empire.
    constants::empireCardPtr CreateAllCards::createEmpireEUROPE (bool isFaceA)
    {
        constants::resourceProdList productionGainB = createFaceBOfEmpires();

        constants::resourceProdPtr firstResourceToProduceEUROPE = std::make_shared<ResourceToProduce>();
        firstResourceToProduceEUROPE->type = ResourceType::MATERIAL;
        firstResourceToProduceEUROPE->quantity = 2;
        firstResourceToProduceEUROPE->cardType = CardType::NONETYPE;

        constants::resourceProdPtr secondResourceToProduceEUROPE = std::make_shared<ResourceToProduce>();
        secondResourceToProduceEUROPE->type = ResourceType::ENERGY;
        secondResourceToProduceEUROPE->quantity = 1;
        secondResourceToProduceEUROPE->cardType = CardType::NONETYPE;

        constants::resourceProdPtr thirdResourceToProduceEUROPE = std::make_shared<ResourceToProduce>();
        thirdResourceToProduceEUROPE->type = ResourceType::SCIENCE;
        thirdResourceToProduceEUROPE->quantity = 1;
        thirdResourceToProduceEUROPE->cardType = CardType::NONETYPE;
        constants::resourceProdList productionGainEUROPE = {firstResourceToProduceEUROPE, secondResourceToProduceEUROPE, thirdResourceToProduceEUROPE};
        
        std::string europe_FaceA = "./resources/img/Cards/Empire_Face_A/Europa.png";
        std::string europe_FaceB = "./resources/img/Cards/Empire_Face_B/Europa.png";
        
        constants::victoryPointsPtr victoryPointsEUROPE  = std::make_shared<state::CardVictoryPoint>();
        victoryPointsEUROPE->numberOfPoints = 1;
        victoryPointsEUROPE->cardOrResourceType = static_cast<int>(ResourceType::COLONEL);
        
        constants::empireCardPtr europe = std::make_shared<EmpireCard>("EUROPE", productionGainEUROPE, europe_FaceA, victoryPointsEUROPE, productionGainB, EUROPE, europe_FaceB, isFaceA);
    
        return europe;
    }
    
    /// @brief Create the empire card NORAM.
    /// @param isFaceA State if the empire is played with face A or B.
    /// @return Pointer to the NORAM empire.
    constants::empireCardPtr CreateAllCards::createEmpireNORAM (bool isFaceA)
    {
        constants::resourceProdList productionGainB = createFaceBOfEmpires();

        constants::resourceProdPtr firstResourceToProduceNORAM = std::make_shared<ResourceToProduce>();
        firstResourceToProduceNORAM->type = ResourceType::MATERIAL;
        firstResourceToProduceNORAM->quantity = 3;
        firstResourceToProduceNORAM->cardType = CardType::NONETYPE;

        constants::resourceProdPtr secondResourceToProduceNORAM = std::make_shared<ResourceToProduce>();
        secondResourceToProduceNORAM->type = ResourceType::GOLD;
        secondResourceToProduceNORAM->quantity = 1;
        secondResourceToProduceNORAM->cardType = CardType::NONETYPE;
        constants::resourceProdList productionGainNORAM = {firstResourceToProduceNORAM, secondResourceToProduceNORAM};
        
        std::string noram_FaceA = "./resources/img/Cards/Empire_Face_A/Noram.png";
        std::string noram_FaceB = "./resources/img/Cards/Empire_Face_B/Noram.png";
        
        constants::victoryPointsPtr victoryPointsNORAM  = std::make_shared<state::CardVictoryPoint>();
        victoryPointsNORAM->numberOfPoints = 1;
        victoryPointsNORAM->cardOrResourceType = static_cast<int>(ResourceType::FINANCIER);

        constants::empireCardPtr noram = std::make_shared<EmpireCard>("NORAM", productionGainNORAM, noram_FaceA, victoryPointsNORAM, productionGainB, NORAM, noram_FaceB, isFaceA);
    
        return noram;
    }

    /// @brief Create the B face of the empires, that are all the same.
    /// @return Vector of resources to produce when face B is played.
    constants::resourceProdList CreateAllCards::createFaceBOfEmpires ()
    {
        constants::resourceProdPtr firstResourceToProduce = std::make_shared<ResourceToProduce>();
        firstResourceToProduce->type = ResourceType::MATERIAL;
        firstResourceToProduce->quantity = 2;
        firstResourceToProduce->cardType = CardType::NONETYPE;

        constants::resourceProdPtr secondResourceToProduce = std::make_shared<ResourceToProduce>();
        secondResourceToProduce->type = ResourceType::ENERGY;
        secondResourceToProduce->quantity = 1;
        secondResourceToProduce->cardType = CardType::NONETYPE;

        constants::resourceProdPtr thirdResourceToProduce = std::make_shared<ResourceToProduce>();
        thirdResourceToProduce->type = ResourceType::SCIENCE;
        thirdResourceToProduce->quantity = 1;
        thirdResourceToProduce->cardType = CardType::NONETYPE;
        constants::resourceProdList productionGainB = {firstResourceToProduce,secondResourceToProduce, thirdResourceToProduce};

        return productionGainB;
    }
}