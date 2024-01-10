#include "CreateAllCards.h"

#include <iostream>
#include <fstream>
#include <json/json.h>
#include <sys/types.h>
#include <dirent.h>
#include <utility>
#include <algorithm>

namespace state
{
    /// @brief Create all development cards for a game.
    /// @return Vector of all development cards.
    std::vector<std::shared_ptr<DevelopmentCard>> CreateAllCards::createAllDevelopmentCards (bool isTestingGame) const
    {
        std::vector<std::shared_ptr<DevelopmentCard>> returnValue = {};

        const std::string folderPath = "./resources/cardsJSON/";  // Update this with your actual folder path

        const std::vector<std::string> cardsNameToRetrieve = {"Tour geante", "Tresor de barbe noire", "Zeppelin", "Zeppelin", "Zeppelin", "Zeppelin", "Zeppelin", "Zeppelin", "Ile d avalon", "Centre De La Terre", "Brise glace", "Brise glace", "Brise glace", "Juggernaut"};

        std::vector<std::pair<std::string, std::shared_ptr<DevelopmentCard>>> cards ;

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
                    std::shared_ptr<DevelopmentCard> card = std::make_shared<DevelopmentCard>(root);
                    bool willBeAdded = true;

                    // If it's a testing game, we have to keep in mind the index to retrieve it at the end.
                    if (isTestingGame)
                    {
                        const std::string cardName = card->getName();
                        auto indexOfName = std::find(cardsNameToRetrieve.begin(), cardsNameToRetrieve.end(), cardName);
                        
                        // If the card name is found we have to check if an vesion of this card has been stored
                        if (cardsNameToRetrieve.end() != indexOfName)
                        {
                            for (std::pair<std::string, std::shared_ptr<DevelopmentCard>>& pair: cards)
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
            for (std::pair<std::string, std::shared_ptr<DevelopmentCard>> pair: cards)
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
    std::vector<std::shared_ptr<EmpireCard>> CreateAllCards::createAllEmpireCards (bool isFaceA) const
    {
        std::shared_ptr<EmpireCard> africa = this->createEmpireAFRICA(isFaceA);
        std::shared_ptr<EmpireCard> noram = this->createEmpireNORAM(isFaceA);
        std::shared_ptr<EmpireCard> europe = this->createEmpireEUROPE(isFaceA);
        std::shared_ptr<EmpireCard> asia = this->createEmpireASIA(isFaceA);
        std::shared_ptr<EmpireCard> aztec = this->createEmpireAZTEC(isFaceA);

        std::vector<std::shared_ptr<EmpireCard>> empires = {asia, aztec, africa, noram, europe};
        
        return empires;
    }

    /// @brief Create the empire card AFRICA.
    /// @param isFaceA State if the empire is played with face A or B.
    /// @return Pointer to the AFRICA empire.
    std::shared_ptr<EmpireCard> CreateAllCards::createEmpireAFRICA (bool isFaceA) const
    {
        std::vector<ResourceToProduce*> productionGainB = this->createFaceBOfEmpires();
        
        ResourceToProduce* firstResourceToProduceAFRICA = new ResourceToProduce{ResourceType::MATERIAL, 2, CardType::NONETYPE};
        ResourceToProduce* secondResourceToProduceAFRICA = new ResourceToProduce{ResourceType::SCIENCE, 2, CardType::NONETYPE};
        std::vector<ResourceToProduce*> productionGainAFRICA = {firstResourceToProduceAFRICA, secondResourceToProduceAFRICA};
        
        std::string africa_FaceA = "./resources/img/Cards/Empire_Face_A/Panafricaine.png";
        std::string africa_FaceB = "./resources/img/Cards/Empire_Face_B/Panafricaine.png";
        
        CardVictoryPoint* victoryPointsAFRICA  = new CardVictoryPoint{2,CardType::RESEARCH};
        
        std::shared_ptr<EmpireCard> africa = std::make_shared<EmpireCard>("AFRICA", productionGainAFRICA, africa_FaceA, victoryPointsAFRICA, productionGainB, AFRICA, africa_FaceB, isFaceA);
        
        return africa;
    }

    /// @brief Create the empire card ASIA.
    /// @param isFaceA State if the empire is played with face A or B.
    /// @return Pointer to the ASIA empire.
    std::shared_ptr<EmpireCard> CreateAllCards::createEmpireASIA (bool isFaceA) const
    {
        std::vector<ResourceToProduce*> productionGainB = this->createFaceBOfEmpires();

        ResourceToProduce* firstResourceToProduceASIA = new ResourceToProduce{ResourceType::MATERIAL, 1, CardType::NONETYPE};
        ResourceToProduce* secondResourceToProduceASIA = new ResourceToProduce{ResourceType::GOLD, 2, CardType::NONETYPE};
        std::vector<ResourceToProduce*> productionGainASIA = {firstResourceToProduceASIA, secondResourceToProduceASIA};
        
        std::string asia_FaceA = "./resources/img/Cards/Empire_Face_A/Asia.png";
        std::string asia_FaceB = "./resources/img/Cards/Empire_Face_B/Asia.png";
        
        CardVictoryPoint* victoryPointsASIA  = new CardVictoryPoint{2, CardType::PROJECT};
        
        std::shared_ptr<EmpireCard> asia = std::make_shared<EmpireCard>("ASIA", productionGainASIA, asia_FaceA, victoryPointsASIA, productionGainB, ASIA, asia_FaceB, isFaceA);
        
        return asia;
    }
    
    /// @brief Create the empire card AZTEC.
    /// @param isFaceA State if the empire is played with face A or B.
    /// @return Pointer to the AZTEC empire.
    std::shared_ptr<EmpireCard> CreateAllCards::createEmpireAZTEC (bool isFaceA) const
    {
        std::vector<ResourceToProduce*> productionGainB = this->createFaceBOfEmpires();

        ResourceToProduce* firstResourceToProduceAZTEC = new ResourceToProduce{ResourceType::ENERGY, 2, CardType::NONETYPE};
        ResourceToProduce* secondResourceToProduceAZTEC = new ResourceToProduce{ResourceType::EXPLORATION, 1, CardType::NONETYPE};
        std::vector<ResourceToProduce*> productionGainAZTEC = {firstResourceToProduceAZTEC, secondResourceToProduceAZTEC};

        std::string aztec_FaceA = "./resources/img/Cards/Empire_Face_A/Azteca.png";
        std::string aztec_FaceB = "./resources/img/Cards/Empire_Face_B/Azteca.png";

        CardVictoryPoint* victoryPointsAZTEC  = new CardVictoryPoint{3, CardType::DISCOVERY};

        std::shared_ptr<EmpireCard> aztec = std::make_shared<EmpireCard>("AZTEC", productionGainAZTEC, aztec_FaceA, victoryPointsAZTEC, productionGainB, AZTEC, aztec_FaceB, isFaceA);

        return aztec;
    }
    
    /// @brief Create the empire card EUROPE.
    /// @param isFaceA State if the empire is played with face A or B.
    /// @return Pointer to the EUROPE empire.
    std::shared_ptr<EmpireCard> CreateAllCards::createEmpireEUROPE (bool isFaceA) const
    {
        std::vector<ResourceToProduce*> productionGainB = this->createFaceBOfEmpires();

        ResourceToProduce* firstResourceToProduceEUROPE = new ResourceToProduce{ResourceType::MATERIAL, 2, CardType::NONETYPE};
        ResourceToProduce* secondResourceToProduceEUROPE = new ResourceToProduce{ResourceType::ENERGY, 1, CardType::NONETYPE};
        ResourceToProduce* thirdResourceToProduceEUROPE = new ResourceToProduce{ResourceType::SCIENCE, 1, CardType::NONETYPE};
        std::vector<ResourceToProduce*> productionGainEUROPE = {firstResourceToProduceEUROPE, secondResourceToProduceEUROPE, thirdResourceToProduceEUROPE};
        
        std::string europe_FaceA = "./resources/img/Cards/Empire_Face_A/Europa.png";
        std::string europe_FaceB = "./resources/img/Cards/Empire_Face_B/Europa.png";
        
        CardVictoryPoint* victoryPointsEUROPE  = new CardVictoryPoint{1, ResourceType::COLONEL};
        
        std::shared_ptr<EmpireCard> europe = std::make_shared<EmpireCard>("EUROPE", productionGainEUROPE, europe_FaceA, victoryPointsEUROPE, productionGainB, EUROPE, europe_FaceB, isFaceA);
    
        return europe;
    }
    
    /// @brief Create the empire card NORAM.
    /// @param isFaceA State if the empire is played with face A or B.
    /// @return Pointer to the NORAM empire.
    std::shared_ptr<EmpireCard> CreateAllCards::createEmpireNORAM (bool isFaceA) const
    {
        std::vector<ResourceToProduce*> productionGainB = this->createFaceBOfEmpires();

        ResourceToProduce* firstResourceToProduceNORAM = new ResourceToProduce{ResourceType::MATERIAL, 3, CardType::NONETYPE};
        ResourceToProduce* secondResourceToProduceNORAM = new ResourceToProduce{ResourceType::GOLD, 1, CardType::NONETYPE};
        std::vector<ResourceToProduce*> productionGainNORAM = {firstResourceToProduceNORAM, secondResourceToProduceNORAM};
        
        std::string noram_FaceA = "./resources/img/Cards/Empire_Face_A/Noram.png";
        std::string noram_FaceB = "./resources/img/Cards/Empire_Face_B/Noram.png";
        
        CardVictoryPoint* victoryPointsNORAM  = new CardVictoryPoint{1, ResourceType::FINANCIER};

        std::shared_ptr<EmpireCard> noram = std::make_shared<EmpireCard>("NORAM", productionGainNORAM, noram_FaceA, victoryPointsNORAM, productionGainB, NORAM, noram_FaceB, isFaceA);
    
        return noram;
    }

    /// @brief Create the B face of the empires, that are all the same.
    /// @return Vector of resources to produce when face B is played.
    std::vector<ResourceToProduce*> CreateAllCards::createFaceBOfEmpires () const
    {
        ResourceToProduce* firstResourceToProduce = new ResourceToProduce{ResourceType::MATERIAL, 2, CardType::NONETYPE};
        ResourceToProduce* secondResourceToProduce = new ResourceToProduce{ResourceType::ENERGY, 1, CardType::NONETYPE};
        ResourceToProduce* thirdResourceToProduce = new ResourceToProduce{ResourceType::SCIENCE, 1, CardType::NONETYPE};
        std::vector<ResourceToProduce*> productionGainB = {firstResourceToProduce,secondResourceToProduce, thirdResourceToProduce};

        return productionGainB;
    }
}