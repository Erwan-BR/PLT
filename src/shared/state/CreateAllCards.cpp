#include "CreateAllCards.h"

namespace state
{
    /// @brief Create all development cards for a game.
    /// @return Vector of all development cards.
    std::vector<DevelopmentCard*> CreateAllCards::createAllDevelopmentCards () const
    {
        std::vector<DevelopmentCard*> returnValue = {};

        /****************************************** Beginning of STRUCTURE cards ******************************************/

        // Base militaire
        sf::Texture* designBaseMilitaire = new sf::Texture;
        designBaseMilitaire->loadFromFile("./resources/img/Cards/Development_Cards/base_militaire.png");
        for(int i = 0; i < 6; i++)
        {
            DevelopmentCard* baseMilitaire = new DevelopmentCard ("Base militaire",{new ResourceToProduce{ResourceType::MATERIAL,1, CardType::NONETYPE}, new ResourceToProduce{ResourceType::SCIENCE,1, CardType::NONETYPE}},designBaseMilitaire,{},CardType::STRUCTURE,6,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::ENERGY, false}},{ResourceType::COLONEL},ResourceType::MATERIAL);
            returnValue.push_back(baseMilitaire);
        }

        // Centrale nucleaire
        sf::Texture* designCentraleNucleaire = new sf::Texture;
        designCentraleNucleaire->loadFromFile("./resources/img/Cards/Development_Cards/centrale_nucleaire.png");
        for(int i=0;i<5;i++)
        {
            DevelopmentCard* centraleNucleaire = new DevelopmentCard ("Centrale nucleaire",{new ResourceToProduce{ResourceType::ENERGY,3, CardType::NONETYPE}},designCentraleNucleaire,{},CardType::STRUCTURE,5,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{},ResourceType::ENERGY);
            returnValue.push_back(centraleNucleaire);
        }

        // Centre de recherche
        for(int i = 0; i < 7; i++)
        {
            sf::Texture* designCentreDeRecherche = new sf::Texture;
            designCentreDeRecherche->loadFromFile("./resources/img/Cards/Development_Cards/centre_de_recherche.png");
            DevelopmentCard* centreDeRecherche = new DevelopmentCard ("Centre de recherche",{new ResourceToProduce{ResourceType::SCIENCE,2, CardType::NONETYPE}},designCentreDeRecherche,{},CardType::STRUCTURE,7,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::ENERGY, false}},{},ResourceType::SCIENCE);
            returnValue.push_back(centreDeRecherche);
        }

        // Complexe industriel
        sf::Texture* designComplexeIndustriel = new sf::Texture;
        designComplexeIndustriel->loadFromFile("./resources/img/Cards/Development_Cards/complexe_industriel.png");
        for(int i = 0; i < 6; i++)
        {
            DevelopmentCard* complexeIndustriel = new DevelopmentCard ("Complexe industriel",{new ResourceToProduce{ResourceType::MATERIAL,1, CardType::NONETYPE}, new ResourceToProduce{ResourceType::GOLD,1, CardType::NONETYPE}},designComplexeIndustriel,{},CardType::STRUCTURE,6,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::ENERGY, false}},{ResourceType::FINANCIER},ResourceType::GOLD);
            returnValue.push_back(complexeIndustriel);
        }

        // Eoliennes
        sf::Texture* designEoliennes = new sf::Texture;
        designEoliennes->loadFromFile("./resources/img/Cards/Development_Cards/eoliennes.png");
        for(int i = 0; i < 7; i++)
        {
            DevelopmentCard* eoliennes = new DevelopmentCard ("Eoliennes",{new ResourceToProduce{ResourceType::ENERGY,1, CardType::NONETYPE}},designEoliennes,{},CardType::STRUCTURE,7,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}},{},ResourceType::ENERGY);
            returnValue.push_back(eoliennes);
        }

        // Place financiere
        sf::Texture* designPlaceFinanciere = new sf::Texture;
        designPlaceFinanciere->loadFromFile("./resources/img/Cards/Development_Cards/place_financiere.png");
        for(int i = 0; i < 5; i++)
        {
            DevelopmentCard* placeFinanciere = new DevelopmentCard ("Place financiere",{new ResourceToProduce{ResourceType::GOLD,2, CardType::NONETYPE}},designPlaceFinanciere,{},CardType::STRUCTURE,5,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::ENERGY, false}},{ResourceType::FINANCIER},ResourceType::GOLD);
            returnValue.push_back(placeFinanciere);
        }

        // Plate-forme petroliere

        sf::Texture* designPlateFormePetroliere = new sf::Texture;
        designPlateFormePetroliere->loadFromFile("./resources/img/Cards/Development_Cards/plate_forme_petroliere.png");
        for(int i = 0; i < 5; i++)
        {
            DevelopmentCard* plateFormePetroliere = new DevelopmentCard ("Plate forme petroliere",{new ResourceToProduce{ResourceType::ENERGY,1, CardType::NONETYPE}, new ResourceToProduce{ResourceType::GOLD,1, CardType::NONETYPE}},designPlateFormePetroliere,{},CardType::STRUCTURE,5,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::EXPLORATION, false}},{ResourceType::FINANCIER},ResourceType::ENERGY);
            returnValue.push_back(plateFormePetroliere);
        }

        // Reseau de transport
        sf::Texture* designReseauDeTransport = new sf::Texture;
        designReseauDeTransport->loadFromFile("./resources/img/Cards/Development_Cards/reseau_de_transport.png");
        for(int i = 0; i < 2; i++)
        {
            DevelopmentCard* reseauDeTransport = new DevelopmentCard ("Reseau de transport",{},designReseauDeTransport,new CardVictoryPoint{1, CardType::VEHICLE},CardType::STRUCTURE,2,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}},{},ResourceType::MATERIAL);
            returnValue.push_back(reseauDeTransport);
        }

        // Usine de recyclage
        sf::Texture* designUsineDeRecyclage = new sf::Texture;
        designUsineDeRecyclage->loadFromFile("./resources/img/Cards/Development_Cards/usine_de_recyclage.png");
        for(int i = 0; i < 7; i++)
        {
            DevelopmentCard* usineDeRecyclage = new DevelopmentCard ("Usine de recyclage",{new ResourceToProduce{ResourceType::MATERIAL,2, CardType::NONETYPE}},designUsineDeRecyclage,{},CardType::STRUCTURE,7,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL}},{},ResourceType::MATERIAL);
            returnValue.push_back(usineDeRecyclage);
        }

        /****************************************** Beginning of VEHICLE cards ******************************************/

        // Brise glace -- Only one because three are created at the end.
        sf::Texture* designBriseGlace = new sf::Texture;
        designBriseGlace->loadFromFile("./resources/img/Cards/Development_Cards/brise_glace.png");
        DevelopmentCard* briseGlaceFirst = new DevelopmentCard ("Brise glace",{new ResourceToProduce{ResourceType::EXPLORATION,2, CardType::NONETYPE}},designBriseGlace,{},CardType::VEHICLE,4,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{},ResourceType::EXPLORATION);
        returnValue.push_back(briseGlaceFirst);

        // Division de chars
        sf::Texture* designDivisionDeChars = new sf::Texture;
        designDivisionDeChars->loadFromFile("./resources/img/Cards/Development_Cards/division_de_chars.png");
        for(int i = 0; i < 7; i++)
        {
            DevelopmentCard* divisionDeChars = new DevelopmentCard ("Division de chars",{new ResourceToProduce{ResourceType::EXPLORATION,1, CardType::NONETYPE}},designDivisionDeChars,{},CardType::VEHICLE,7,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}},{ResourceType::COLONEL},ResourceType::MATERIAL);
            returnValue.push_back(divisionDeChars);
        }

        // Escadrille de soucoupes
        sf::Texture* designEscadrilleDeSoucoupes = new sf::Texture;
        designEscadrilleDeSoucoupes->loadFromFile("./resources/img/Cards/Development_Cards/escadrille_de_soucoupes.png");
        for(int i = 0; i < 2; i++)
        {
            DevelopmentCard* escadrilleDeSoucoupes = new DevelopmentCard ("Escadrille de soucoupes",{new ResourceToProduce{ResourceType::EXPLORATION,3, CardType::NONETYPE}},designEscadrilleDeSoucoupes,{},CardType::VEHICLE,2,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{},ResourceType::SCIENCE);
            returnValue.push_back(escadrilleDeSoucoupes);
        }

        // Juggernaut -- Created at the end.

        // Laboratoire aeroporte
        sf::Texture* designLaboratoireAeroporte = new sf::Texture;
        designLaboratoireAeroporte->loadFromFile("./resources/img/Cards/Development_Cards/laboratoire_aeroporte.png");
        for(int i = 0; i < 3; i++)
        {
            DevelopmentCard* laboratoireAeroporte = new DevelopmentCard ("Laboratoire aeroporte",{new ResourceToProduce{ResourceType::SCIENCE,1, CardType::NONETYPE}, new ResourceToProduce{ResourceType::EXPLORATION,1, CardType::NONETYPE}},designLaboratoireAeroporte,{},CardType::VEHICLE,3,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}},{},ResourceType::SCIENCE);
            returnValue.push_back(laboratoireAeroporte);
        }

        // Mega foreuse
        sf::Texture* designMegaForeuse = new sf::Texture;
        designMegaForeuse->loadFromFile("./resources/img/Cards/Development_Cards/mega_foreuse.png");
        for(int i = 0; i < 4; i++)
        {
            DevelopmentCard* megaForeuse = new DevelopmentCard ("Mega foreuse",{new ResourceToProduce{ResourceType::MATERIAL,1, CardType::NONETYPE}, new ResourceToProduce{ResourceType::EXPLORATION,1, CardType::NONETYPE}},designMegaForeuse,{},CardType::VEHICLE,4,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}},{},ResourceType::MATERIAL);
            returnValue.push_back(megaForeuse);
        }

        // Porte avions
        sf::Texture* designPorteAvions = new sf::Texture;
        designPorteAvions->loadFromFile("./resources/img/Cards/Development_Cards/porte_avions.png");
        DevelopmentCard* porteAvions = new DevelopmentCard ("Porte Avions",{new ResourceToProduce{ResourceType::EXPLORATION, 1, CardType::VEHICLE}},designPorteAvions,new CardVictoryPoint{0, CardType::NONETYPE},CardType::VEHICLE,1,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}},{ResourceType::COLONEL,ResourceType::COLONEL},ResourceType::MATERIAL);
        returnValue.push_back(porteAvions);

        // Sous marin
        sf::Texture* designSousMarin = new sf::Texture;
        designSousMarin->loadFromFile("./resources/img/Cards/Development_Cards/sous_marin.png");
        for(int i = 0; i < 3; i++)
        {
            DevelopmentCard* sousMarin = new DevelopmentCard ("Sous marin",{new ResourceToProduce{ResourceType::EXPLORATION,2, CardType::NONETYPE}},designSousMarin,new CardVictoryPoint{0, CardType::NONETYPE},CardType::VEHICLE,3,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}},{ResourceType::COLONEL},ResourceType::MATERIAL);
            returnValue.push_back(sousMarin);
        }

        // Zeppelin -- Created at the end

        /****************************************** Beginning of RESEARCH cards ******************************************/
        // Amelioration genetique
        sf::Texture* designAmeliorationGenetique = new sf::Texture;
        designAmeliorationGenetique->loadFromFile("./resources/img/Cards/Development_Cards/amelioration_genetique.png");
        DevelopmentCard* ameliorationGenetique = new DevelopmentCard ("Amelioration genetique",{},designAmeliorationGenetique,new CardVictoryPoint{3, (int) CardType::NONETYPE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{ResourceType::FINANCIER, ResourceType::FINANCIER},ResourceType::SCIENCE);
        returnValue.push_back(ameliorationGenetique);

        // Animorphes
        sf::Texture* designAnimorphes = new sf::Texture;
        designAnimorphes->loadFromFile("./resources/img/Cards/Development_Cards/animorphes.png");
        DevelopmentCard* animorphes = new DevelopmentCard ("Animorphes",{new ResourceToProduce{ResourceType::MATERIAL, 1, CardType::NONETYPE}},designAnimorphes,new CardVictoryPoint{2, (int) CardType::NONETYPE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{ResourceType::COLONEL},ResourceType::ENERGY);
        returnValue.push_back(animorphes);

        // Aquaculture
        sf::Texture* designAquaculture = new sf::Texture;
        designAquaculture->loadFromFile("./resources/img/Cards/Development_Cards/aquaculture.png");
        DevelopmentCard* aquaculture = new DevelopmentCard ("Aquaculture",{},designAquaculture,new CardVictoryPoint{1, (int) ResourceType::FINANCIER},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},{ResourceType::FINANCIER},ResourceType::SCIENCE);
        returnValue.push_back(aquaculture);

        // Automates de controle
        sf::Texture* designAutomateControle = new sf::Texture;
        designAutomateControle->loadFromFile("./resources/img/Cards/Development_Cards/automates_de_controle.png");
        DevelopmentCard* automateControle = new DevelopmentCard ("Automates de controle",{},designAutomateControle,new CardVictoryPoint{1, (int) ResourceType::COLONEL},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::GOLD, false}},{},ResourceType::GOLD);
        returnValue.push_back(automateControle);

        // Clonage humain
        sf::Texture* designClonageHumain = new sf::Texture;
        designClonageHumain->loadFromFile("./resources/img/Cards/Development_Cards/clonage_humain.png");
        DevelopmentCard* clonageHumain = new DevelopmentCard ("Clonage Humain",{new ResourceToProduce{ResourceType::GOLD, 1, CardType::NONETYPE}},designClonageHumain,new CardVictoryPoint{1, (int) CardType::NONETYPE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::GOLD, false}},{ResourceType::FINANCIER},ResourceType::GOLD);
        returnValue.push_back(clonageHumain);

        // Controle du climat
        sf::Texture* designControlDuClimat = new sf::Texture;
        designControlDuClimat->loadFromFile("./resources/img/Cards/Development_Cards/controle_du_climat.png");
        DevelopmentCard* controlDuClimat = new DevelopmentCard ("Controle du climat",{new ResourceToProduce{ResourceType::ENERGY, 2, CardType::NONETYPE},new ResourceToProduce{ResourceType::GOLD, 1, CardType::NONETYPE}},designControlDuClimat,new CardVictoryPoint{2, (int) CardType::NONETYPE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{},ResourceType::ENERGY);
        returnValue.push_back(controlDuClimat);

        // Cryogenisation
        sf::Texture* designCryogenisation = new sf::Texture;
        designCryogenisation->loadFromFile("./resources/img/Cards/Development_Cards/cryogenisation.png");
        DevelopmentCard* cryogenisation = new DevelopmentCard ("Cryogenisation",{},designCryogenisation,new CardVictoryPoint{1, (int) ResourceType::FINANCIER},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{ResourceType::FINANCIER},ResourceType::GOLD);
        returnValue.push_back(cryogenisation);

        // Generateur quantique
        sf::Texture* designGenerateurQuantique = new sf::Texture;
        designGenerateurQuantique->loadFromFile("./resources/img/Cards/Development_Cards/generateur_quantique.png");
        DevelopmentCard* generateurQuantique = new DevelopmentCard ("Generateur quantique",{new ResourceToProduce{ResourceType::ENERGY, 3, CardType::NONETYPE}},designGenerateurQuantique,new CardVictoryPoint{1, (int) CardType::VEHICLE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{},ResourceType::ENERGY);
        returnValue.push_back(generateurQuantique);

        // Greffes bioniques
        sf::Texture* designGreffesBionique = new sf::Texture;
        designGreffesBionique->loadFromFile("./resources/img/Cards/Development_Cards/greffes_bioniques.png");
        DevelopmentCard* greffesBioniques = new DevelopmentCard ("Greffes bioniques",{new ResourceToProduce{ResourceType::MATERIAL, 2, CardType::NONETYPE}},designGreffesBionique,new CardVictoryPoint{4, (int) CardType::NONETYPE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{ResourceType::COLONEL},ResourceType::MATERIAL);
        returnValue.push_back(greffesBioniques);

        // Inverseur de gravite
        sf::Texture* designInverseurGravite = new sf::Texture;
        designInverseurGravite->loadFromFile("./resources/img/Cards/Development_Cards/inverseur_de_gravite.png");
        DevelopmentCard* inverseurGravite = new DevelopmentCard ("Inverseur de gravite",{},designInverseurGravite,new CardVictoryPoint{2, (int) CardType::PROJECT},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::KRYSTALLIUM, false}},{ResourceType::FINANCIER},ResourceType::SCIENCE);
        returnValue.push_back(inverseurGravite);

        // Mega bombe
        sf::Texture* designMegaBombe = new sf::Texture;
        designMegaBombe->loadFromFile("./resources/img/Cards/Development_Cards/mega_bombe.png");
        DevelopmentCard* megaBombe = new DevelopmentCard ("Mega bombe",{},designMegaBombe,new CardVictoryPoint{3, (int) CardType::NONETYPE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{ResourceType::COLONEL, ResourceType::COLONEL},ResourceType::ENERGY);
        returnValue.push_back(megaBombe);

        // Neuroscience
        sf::Texture* designNeuroscience = new sf::Texture;
        designNeuroscience->loadFromFile("./resources/img/Cards/Development_Cards/neuroscience.png");
        DevelopmentCard* neuroscience = new DevelopmentCard ("Neuroscience",{new ResourceToProduce{ResourceType::SCIENCE, 1, CardType::RESEARCH}},designNeuroscience,new CardVictoryPoint{1, (int) CardType::NONETYPE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{},ResourceType::SCIENCE);
        returnValue.push_back(neuroscience);

        // Realite virtuelle
        sf::Texture* designRealiteVirtuelle = new sf::Texture;
        designRealiteVirtuelle->loadFromFile("./resources/img/Cards/Development_Cards/realite_virtuelle.png");
        DevelopmentCard* realiteVirtuelle = new DevelopmentCard ("Realite virtuelle",{new ResourceToProduce{ResourceType::GOLD, 1, CardType::RESEARCH}},designRealiteVirtuelle,new CardVictoryPoint{2, (int) CardType::NONETYPE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{},ResourceType::GOLD);
        returnValue.push_back(realiteVirtuelle);

        // Robots de compagnie
        sf::Texture* designRobotsCompagnie = new sf::Texture;
        designRobotsCompagnie->loadFromFile("./resources/img/Cards/Development_Cards/robots_de_compagnie.png");
        DevelopmentCard* robotsCompagnie = new DevelopmentCard ("Robots de compagnie",{new ResourceToProduce{ResourceType::MATERIAL, 1, CardType::STRUCTURE}},designRobotsCompagnie,new CardVictoryPoint{1, (int) CardType::NONETYPE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{},ResourceType::MATERIAL);
        returnValue.push_back(robotsCompagnie);

        // Satellites
        sf::Texture* designSatellites = new sf::Texture;
        designSatellites->loadFromFile("./resources/img/Cards/Development_Cards/satellites.png");
        DevelopmentCard* satellites = new DevelopmentCard ("Satellites",{new ResourceToProduce{ResourceType::EXPLORATION, 2, CardType::NONETYPE}},designSatellites,new CardVictoryPoint{3, (int) CardType::NONETYPE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{ResourceType::COLONEL},ResourceType::EXPLORATION);
        returnValue.push_back(satellites);

        // Super calculateur
        sf::Texture* designSuperCalculateur = new sf::Texture;
        designSuperCalculateur->loadFromFile("./resources/img/Cards/Development_Cards/super_calculateur.png");
        DevelopmentCard* superCalculateur = new DevelopmentCard ("Super calculateur",{new ResourceToProduce{ResourceType::SCIENCE, 1, CardType::NONETYPE}},designSuperCalculateur,new CardVictoryPoint{1, (int) CardType::VEHICLE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{},ResourceType::SCIENCE);
        returnValue.push_back(superCalculateur);

        // Super soldats
        sf::Texture* designSuperSoldats = new sf::Texture;
        designSuperSoldats->loadFromFile("./resources/img/Cards/Development_Cards/super_soldats.png");
        DevelopmentCard* superSoldats = new DevelopmentCard ("Super soldats",{},designSuperSoldats,new CardVictoryPoint{1, (int) ResourceType::COLONEL},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{ResourceType::COLONEL},ResourceType::EXPLORATION);
        returnValue.push_back(superSoldats);

        // Super sonar
        sf::Texture* designSuperSonar = new sf::Texture;
        designSuperSonar->loadFromFile("./resources/img/Cards/Development_Cards/super_sonar.png");
        DevelopmentCard* superSonar = new DevelopmentCard ("Super sonar",{new ResourceToProduce{ResourceType::EXPLORATION, 1, CardType::VEHICLE}},designSuperSonar,new CardVictoryPoint{1, (int) CardType::NONETYPE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{},ResourceType::EXPLORATION);
        returnValue.push_back(superSonar);

        // Technologie inconnue
        sf::Texture* designTechnologieInconnue = new sf::Texture;
        designTechnologieInconnue->loadFromFile("./resources/img/Cards/Development_Cards/technologie_inconnue.png");
        DevelopmentCard* technologieInconnue = new DevelopmentCard ("Technologie inconnue",{},designTechnologieInconnue,new CardVictoryPoint{3, (int) CardType::RESEARCH},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::KRYSTALLIUM, false}},{},ResourceType::SCIENCE);
        returnValue.push_back(technologieInconnue);

        // Teleportation
        sf::Texture* designTeleportation = new sf::Texture;
        designTeleportation->loadFromFile("./resources/img/Cards/Development_Cards/teleportation.png");
        DevelopmentCard* teleportation = new DevelopmentCard ("Teleportation",{},designTeleportation,new CardVictoryPoint{8, (int) CardType::NONETYPE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{ResourceType::KRYSTALLIUM, ResourceType::KRYSTALLIUM},ResourceType::EXPLORATION);
        returnValue.push_back(teleportation);

        // Transmutation
        sf::Texture* designTransmutation = new sf::Texture;
        designTransmutation->loadFromFile("./resources/img/Cards/Development_Cards/transmutation.png");
        DevelopmentCard* transmutation = new DevelopmentCard ("Transmutation",{new ResourceToProduce{ResourceType::GOLD, 3, CardType::NONETYPE}},designTransmutation,new CardVictoryPoint{1, (int) CardType::NONETYPE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},{ResourceType::KRYSTALLIUM},ResourceType::GOLD);
        returnValue.push_back(transmutation);

        // Vaccin Universel
        sf::Texture* designVaccinUniversel = new sf::Texture;
        designVaccinUniversel->loadFromFile("./resources/img/Cards/Development_Cards/vaccin_universel.png");
        DevelopmentCard* vaccinUniversel = new DevelopmentCard ("Vaccin universel",{},designVaccinUniversel,new CardVictoryPoint{1, (int) CardType::PROJECT},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{},ResourceType::GOLD);
        returnValue.push_back(vaccinUniversel);

        // Voyage temporel
        sf::Texture* designVoyageTemporel = new sf::Texture;
        designVoyageTemporel->loadFromFile("./resources/img/Cards/Development_Cards/voyage_temporel.png");
        DevelopmentCard* voyageTemporel = new DevelopmentCard ("Voyage temporel",{},designVoyageTemporel,new CardVictoryPoint{15, (int) CardType::NONETYPE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::KRYSTALLIUM, false}, new ResourceToPay{ResourceType::KRYSTALLIUM, false}, new ResourceToPay{ResourceType::KRYSTALLIUM, false}},{},ResourceType::EXPLORATION);
        returnValue.push_back(voyageTemporel);

        /****************************************** Beginning of PROJECT cards ******************************************/
        // Agence d'espionnage
        sf::Texture* designAgenceEspionnage = new sf::Texture;
        designAgenceEspionnage->loadFromFile("./resources/img/Cards/Development_Cards/agence_d_espionnage.png");
        for (int i = 0; i < 2; i++)
        {
            DevelopmentCard* agenceEspionnage = new DevelopmentCard ("Agence d'espionnage",{new ResourceToProduce{ResourceType::EXPLORATION, 2, CardType::NONETYPE}},designAgenceEspionnage,new CardVictoryPoint{1, CardType::NONETYPE},CardType::PROJECT,2,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},{},ResourceType::EXPLORATION);
            returnValue.push_back(agenceEspionnage);
        }

        // Ascenseur Spatial
        sf::Texture* designAscenseurSpatial = new sf::Texture;
        designAscenseurSpatial->loadFromFile("./resources/img/Cards/Development_Cards/ascenseur_spatial.png");
        DevelopmentCard* ascenseurSpatial = new DevelopmentCard ("Ascenseur spatial",{},designAscenseurSpatial,new CardVictoryPoint{1, (int) ResourceType::FINANCIER},CardType::PROJECT,1,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},{ResourceType::FINANCIER},ResourceType::ENERGY);
        returnValue.push_back(ascenseurSpatial);

        // Barrage Geant
        sf::Texture* designBarrageGeant = new sf::Texture;
        designBarrageGeant->loadFromFile("./resources/img/Cards/Development_Cards/barrage_geant.png");
        DevelopmentCard* barrageGeant = new DevelopmentCard ("Barrage geant",{new ResourceToProduce{ResourceType::ENERGY, 4, CardType::NONETYPE}},designBarrageGeant,new CardVictoryPoint{1, (int) CardType::NONETYPE},CardType::PROJECT,1,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},{},ResourceType::ENERGY);
        returnValue.push_back(barrageGeant);

        // Base Lunaire
        sf::Texture* designBaseLunaire = new sf::Texture;
        designBaseLunaire->loadFromFile("./resources/img/Cards/Development_Cards/base_lunaire.png");
        DevelopmentCard* baseLunaire = new DevelopmentCard ("Base lunaire",{},designBaseLunaire,new CardVictoryPoint{10, (int) CardType::NONETYPE},CardType::PROJECT,1,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::KRYSTALLIUM, false}},{ResourceType::COLONEL, ResourceType::COLONEL},ResourceType::EXPLORATION);
        returnValue.push_back(baseLunaire);

        // Base Polaire
        sf::Texture* designBasePolaire = new sf::Texture;
        designBasePolaire->loadFromFile("./resources/img/Cards/Development_Cards/base_polaire.png");
        DevelopmentCard* basePolaire = new DevelopmentCard ("Base polaire",{new ResourceToProduce{ResourceType::EXPLORATION, 3, CardType::NONETYPE}},designBasePolaire,new CardVictoryPoint{2, (int) CardType::DISCOVERY},CardType::PROJECT,1,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},{ResourceType::COLONEL},ResourceType::EXPLORATION);
        returnValue.push_back(basePolaire);

        // Canon Solaire
        sf::Texture* designCanonSolaire = new sf::Texture;
        designCanonSolaire->loadFromFile("./resources/img/Cards/Development_Cards/canon_solaire.png");
        DevelopmentCard* canonSolaire = new DevelopmentCard ("Canon solaire",{},designCanonSolaire,new CardVictoryPoint{1, (int) ResourceType::COLONEL},CardType::PROJECT,1,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},{ResourceType::COLONEL},ResourceType::ENERGY);
        returnValue.push_back(canonSolaire);

        // Centre de propagande
        sf::Texture* designCentrePropagande = new sf::Texture;
        designCentrePropagande->loadFromFile("./resources/img/Cards/Development_Cards/centre_de_propagande.png");
        for (int i = 0; i < 2; i++)
        {
            DevelopmentCard* centrePropagande = new DevelopmentCard ("Centre de propagande",{new ResourceToProduce{ResourceType::GOLD, 1, CardType::PROJECT}},designCentrePropagande,new CardVictoryPoint{1, (int) CardType::NONETYPE},CardType::PROJECT,2,{new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},{ResourceType::COLONEL},ResourceType::GOLD);
            returnValue.push_back(centrePropagande);
        }

        // Congres Mondial
        sf::Texture* designCongresMondial = new sf::Texture;
        designCongresMondial->loadFromFile("./resources/img/Cards/Development_Cards/congres_mondial.png");
        DevelopmentCard* congresMondial = new DevelopmentCard ("Congres mondial",{},designCongresMondial,new CardVictoryPoint{3, (int) CardType::PROJECT},CardType::PROJECT,1,{new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::FINANCIER, false}, new ResourceToPay{ResourceType::FINANCIER, false}},{},ResourceType::GOLD);
        returnValue.push_back(congresMondial);

        // Exposition universelle
        sf::Texture* designExpositionUniverselle = new sf::Texture;
        designExpositionUniverselle->loadFromFile("./resources/img/Cards/Development_Cards/exposition_universelle.png");
        DevelopmentCard* expositionUniverselle = new DevelopmentCard ("Exposition Universelle",{},designExpositionUniverselle,new CardVictoryPoint{3, (int) CardType::RESEARCH},CardType::PROJECT,1,{new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::FINANCIER, false}, new ResourceToPay{ResourceType::FINANCIER, false}},{},ResourceType::GOLD);
        returnValue.push_back(expositionUniverselle);

        // Laboratoire secret
        sf::Texture* designLaboratoireSecret = new sf::Texture;
        designLaboratoireSecret->loadFromFile("./resources/img/Cards/Development_Cards/laboratoire_secret.png");
        for (int i = 0; i < 2; i++)
        {
            DevelopmentCard* laboratoireSecret = new DevelopmentCard ("Laboratoire secret",{new ResourceToProduce{ResourceType::SCIENCE, 2, CardType::NONETYPE}},designLaboratoireSecret,new CardVictoryPoint{1, (int) CardType::RESEARCH},CardType::PROJECT,2,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},{ResourceType::KRYSTALLIUM},ResourceType::SCIENCE);
            returnValue.push_back(laboratoireSecret);
        }

        // Monument national
        sf::Texture* designMonumentNational = new sf::Texture;
        designMonumentNational->loadFromFile("./resources/img/Cards/Development_Cards/monument_national.png");
        DevelopmentCard* monumentNational = new DevelopmentCard ("Monument national",{},designMonumentNational,new CardVictoryPoint{2, (int) CardType::PROJECT},CardType::PROJECT,1,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},{},ResourceType::GOLD);
        returnValue.push_back(monumentNational);

        // Musee
        sf::Texture* designMusee = new sf::Texture;
        designMusee->loadFromFile("./resources/img/Cards/Development_Cards/musee.png");
        for (int i = 0; i < 2; i++)
        {
            DevelopmentCard* musee = new DevelopmentCard ("Musee",{},designMusee,new CardVictoryPoint{2, (int) CardType::DISCOVERY},CardType::PROJECT,2,{new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},{},ResourceType::EXPLORATION);
            returnValue.push_back(musee);
        }

        // Societe secrete
            sf::Texture* designSocieteSecrete = new sf::Texture;
            designSocieteSecrete->loadFromFile("./resources/img/Cards/Development_Cards/societe_secrete.png");
        for (int i = 0; i < 2; i++)
        {
            DevelopmentCard* societeSecrete = new DevelopmentCard ("Societe secrete",{},designSocieteSecrete,new CardVictoryPoint{1, (int) ResourceType::FINANCIER},CardType::PROJECT,2,{new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::KRYSTALLIUM, false}},{},ResourceType::GOLD);
            returnValue.push_back(societeSecrete);
        }

        // Tour geante - created at the end.

        // Train magnetique
        sf::Texture* designTrainMagnetique = new sf::Texture;
        designTrainMagnetique->loadFromFile("./resources/img/Cards/Development_Cards/train_magnetique.png");
        DevelopmentCard* trainMagnetique = new DevelopmentCard ("Train magnetique",{new ResourceToProduce{ResourceType::GOLD, 1, CardType::STRUCTURE}},designTrainMagnetique,new CardVictoryPoint{2, (int) CardType::NONETYPE},CardType::PROJECT,1,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},{ResourceType::FINANCIER, ResourceType::FINANCIER},ResourceType::GOLD);
        returnValue.push_back(trainMagnetique);

        // Universite
        sf::Texture* designUniversite = new sf::Texture;
        designUniversite->loadFromFile("./resources/img/Cards/Development_Cards/universite.png");
        DevelopmentCard* universite = new DevelopmentCard ("Universite",{new ResourceToProduce{ResourceType::SCIENCE, 1, CardType::PROJECT}},designUniversite,new CardVictoryPoint{2, (int) CardType::NONETYPE},CardType::PROJECT,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},{},ResourceType::SCIENCE);
        returnValue.push_back(universite);

        // Ville-casino
        sf::Texture* designVilleCasino = new sf::Texture;
        designVilleCasino->loadFromFile("./resources/img/Cards/Development_Cards/ville_casino.png");
        for (int i = 0; i < 2; i++)
        {
            DevelopmentCard* villeCasino = new DevelopmentCard ("Ville casino",{new ResourceToProduce{ResourceType::GOLD, 2, CardType::NONETYPE}},designVilleCasino,new CardVictoryPoint{1, (int) ResourceType::FINANCIER},CardType::PROJECT,2,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},{ResourceType::FINANCIER},ResourceType::GOLD);
            returnValue.push_back(villeCasino);
        }

        // Ville sous-marine
        sf::Texture* designVilleSousMarine = new sf::Texture;
        designVilleSousMarine->loadFromFile("./resources/img/Cards/Development_Cards/ville_sous_marine.png");
        for (int i = 0; i < 2; i++)
        {
            DevelopmentCard* villeSousMarine = new DevelopmentCard ("Ville sous-marine",{new ResourceToProduce{ResourceType::SCIENCE, 1, CardType::NONETYPE}, new ResourceToProduce{ResourceType::EXPLORATION, 2, CardType::NONETYPE}},designVilleSousMarine,new CardVictoryPoint{3, (int) CardType::NONETYPE},CardType::PROJECT,2,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},{},ResourceType::EXPLORATION);
            returnValue.push_back(villeSousMarine);
        }

        // Ville souterraine
        sf::Texture* designVilleSouterraine = new sf::Texture;
        designVilleSouterraine->loadFromFile("./resources/img/Cards/Development_Cards/ville_souterraine.png");
        for (int i = 0; i < 2; i++)
        {
            DevelopmentCard* villeSouterraine = new DevelopmentCard ("Ville souterraine",{new ResourceToProduce{ResourceType::MATERIAL, 2, CardType::NONETYPE}, new ResourceToProduce{ResourceType::ENERGY, 2, CardType::NONETYPE}},designVilleSouterraine,new CardVictoryPoint{3, (int) CardType::NONETYPE},CardType::PROJECT,2,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},{ResourceType::KRYSTALLIUM},ResourceType::ENERGY);
            returnValue.push_back(villeSouterraine);
        }

        // Zone portuaire
        sf::Texture* designZonePortuaire = new sf::Texture;
        designZonePortuaire->loadFromFile("./resources/img/Cards/Development_Cards/zone_portuaire.png");
        for (int i = 0; i < 2; i++)
        {
            DevelopmentCard* zonePortuaire = new DevelopmentCard ("Zone portuaire",{new ResourceToProduce{ResourceType::MATERIAL, 2, CardType::NONETYPE}, new ResourceToProduce{ResourceType::GOLD, 2, CardType::NONETYPE}},designZonePortuaire,new CardVictoryPoint{2, (int) CardType::NONETYPE},CardType::PROJECT,2,{new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},{ResourceType::FINANCIER, ResourceType::FINANCIER},ResourceType::GOLD);
            returnValue.push_back(zonePortuaire);
        }

        /****************************************** Beginning of DISCOVERY cards ******************************************/
        // Anciens astronautes
        sf::Texture* designAnciensAstronautes = new sf::Texture;
        designAnciensAstronautes->loadFromFile("./resources/img/Cards/Development_Cards/anciens_astronautes.png");
        DevelopmentCard* anciensAstronautes = new DevelopmentCard ("Anciens Astronautes",{new ResourceToProduce{ResourceType::SCIENCE,1, CardType::DISCOVERY}},designAnciensAstronautes,new CardVictoryPoint{10, CardType::NONETYPE},CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::COLONEL, false}},{ResourceType::KRYSTALLIUM,ResourceType::KRYSTALLIUM},ResourceType::SCIENCE);
        returnValue.push_back(anciensAstronautes);

        // Arche d alliance
        sf::Texture* designArcheDAlliance = new sf::Texture;
        designArcheDAlliance->loadFromFile("./resources/img/Cards/Development_Cards/arche_d_alliance.png");
        DevelopmentCard* archeDAlliance = new DevelopmentCard ("Arche d alliance",{},designArcheDAlliance,new CardVictoryPoint{5, CardType::NONETYPE},CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}},{ResourceType::KRYSTALLIUM},ResourceType::EXPLORATION);
        returnValue.push_back(archeDAlliance);

        // Atlantide
        sf::Texture* designAtlantide = new sf::Texture;
        designAtlantide->loadFromFile("./resources/img/Cards/Development_Cards/atlantide.png");
        DevelopmentCard* atlantide = new DevelopmentCard ("Atlantide",{},designAtlantide,new CardVictoryPoint{2, ResourceType::COLONEL},CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::KRYSTALLIUM, false}},{},ResourceType::GOLD);
        returnValue.push_back(atlantide);

        // Centre de la terre -- created at the end

        // Cite d agartha
        sf::Texture* designCiteDAgartha = new sf::Texture;
        designCiteDAgartha->loadFromFile("./resources/img/Cards/Development_Cards/cite_d_agartha.png");
        DevelopmentCard* citeDAgartha = new DevelopmentCard ("Cite d agartha",{new ResourceToProduce{ResourceType::EXPLORATION,2, CardType::NONETYPE}},designCiteDAgartha,new CardVictoryPoint{1, ResourceType::COLONEL},CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::KRYSTALLIUM, false}},{},ResourceType::EXPLORATION);
        returnValue.push_back(citeDAgartha);

        // Cite d or
        sf::Texture* designCitesDOr = new sf::Texture;
        designCitesDOr->loadFromFile("./resources/img/Cards/Development_Cards/cites_d_or.png");
        DevelopmentCard* citesDOr = new DevelopmentCard ("Cites d or",{new ResourceToProduce{ResourceType::GOLD,3, CardType::NONETYPE}},designCitesDOr,new CardVictoryPoint{3, CardType::NONETYPE},CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}},{},ResourceType::GOLD);
        returnValue.push_back(citesDOr);

        // Continent perdu de mu
        sf::Texture* designContinentPerduDeMu = new sf::Texture;
        designContinentPerduDeMu->loadFromFile("./resources/img/Cards/Development_Cards/continent_perdu_de_mu.png");
        DevelopmentCard* continentPerduDeMu = new DevelopmentCard ("Continent perdu de mu",{new ResourceToProduce{ResourceType::GOLD,1, CardType::NONETYPE}},designContinentPerduDeMu,new CardVictoryPoint{2, CardType::DISCOVERY},CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}},{ResourceType::KRYSTALLIUM,ResourceType::KRYSTALLIUM},ResourceType::GOLD);
        returnValue.push_back(continentPerduDeMu);

        // Dimension parallele
        sf::Texture* designDimensionParallele = new sf::Texture;
        designDimensionParallele->loadFromFile("./resources/img/Cards/Development_Cards/dimension_parallele.png");
        DevelopmentCard* dimensionParallele = new DevelopmentCard ("Dimension parallele",{}, designDimensionParallele,new CardVictoryPoint{3, CardType::RESEARCH},CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::COLONEL, false}},{ResourceType::KRYSTALLIUM,ResourceType::KRYSTALLIUM,ResourceType::KRYSTALLIUM},ResourceType::EXPLORATION);
        returnValue.push_back(dimensionParallele);

        // Fontaine de jouvence
        sf::Texture* designFontaineDeJouvence = new sf::Texture;
        designFontaineDeJouvence->loadFromFile("./resources/img/Cards/Development_Cards/fontaine_de_jouvence.png");
        DevelopmentCard* fontaineDeJouvence = new DevelopmentCard ("Fontaine de jouvence",{}, designFontaineDeJouvence,new CardVictoryPoint{1, ResourceType::COLONEL},CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}},{ResourceType::KRYSTALLIUM,ResourceType::KRYSTALLIUM,ResourceType::KRYSTALLIUM},ResourceType::ENERGY);
        returnValue.push_back(fontaineDeJouvence);

        // Ile d avalon -- created at the end

        // Jardin des hesperides
        sf::Texture* designJardinDesHesperides = new sf::Texture;
        designJardinDesHesperides->loadFromFile("./resources/img/Cards/Development_Cards/jardin_des_hesperides.png");
        DevelopmentCard* jardinDesHesperides = new DevelopmentCard ("Jardin des hesperides",{},designJardinDesHesperides,new CardVictoryPoint{2, CardType::PROJECT},CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}},{},ResourceType::EXPLORATION);
        returnValue.push_back(jardinDesHesperides);

        // Mines du roi salomon
        sf::Texture* designMinesDuRoiSalomon = new sf::Texture;
        designMinesDuRoiSalomon->loadFromFile("./resources/img/Cards/Development_Cards/mines_du_roi_salomon.png");
        DevelopmentCard* minesDuRoiSalomon = new DevelopmentCard ("Mines du roi salomon",{new ResourceToProduce{ResourceType::GOLD,1,CardType::STRUCTURE}},designMinesDuRoiSalomon,new CardVictoryPoint{2, CardType::NONETYPE},CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}},{},ResourceType::GOLD);
        returnValue.push_back(minesDuRoiSalomon);

        // Roswell
        sf::Texture* designRoswell = new sf::Texture;
        designRoswell->loadFromFile("./resources/img/Cards/Development_Cards/roswell.png");
        DevelopmentCard* roswell = new DevelopmentCard ("Roswell",{new ResourceToProduce{ResourceType::SCIENCE,1,CardType::NONETYPE}},designRoswell,new CardVictoryPoint{1, ResourceType::COLONEL},    CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}},{ResourceType::COLONEL},ResourceType::SCIENCE);
        returnValue.push_back(roswell);

        // Tombeau d alexandre
        sf::Texture* designTombeauDAlexandre = new sf::Texture;
        designTombeauDAlexandre->loadFromFile("./resources/img/Cards/Development_Cards/tombeau_d_alexandre.png");
        DevelopmentCard* tombeauDAlexandre = new DevelopmentCard ("Tombeau d alexandre",{},designTombeauDAlexandre,new CardVictoryPoint{10, CardType::NONETYPE},CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::EXPLORATION, false},new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}},{ResourceType::COLONEL,ResourceType::COLONEL},ResourceType::GOLD);
        returnValue.push_back(tombeauDAlexandre);

        // Tresor de barbe noire -- created at the end

        // Tresor des templiers
        sf::Texture* designTresorDesTempliers = new sf::Texture;
        designTresorDesTempliers->loadFromFile("./resources/img/Cards/Development_Cards/tresor_des_templiers.png");
        DevelopmentCard* tresorDesTempliers = new DevelopmentCard ("Tresor des templiers",{new ResourceToProduce{ResourceType::GOLD,2, CardType::NONETYPE}},designTresorDesTempliers,new CardVictoryPoint{3, CardType::NONETYPE},CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}},{ResourceType::KRYSTALLIUM,ResourceType::KRYSTALLIUM},ResourceType::GOLD);
        returnValue.push_back(tresorDesTempliers);

        // Triangle des bermudes
        sf::Texture* designTriangleDesBermudes = new sf::Texture;
        designTriangleDesBermudes->loadFromFile("./resources/img/Cards/Development_Cards/triangle_des_bermudes.png");
        DevelopmentCard* triangleDesBermudes = new DevelopmentCard ("Triangle des bermudes",{new ResourceToProduce{ResourceType::SCIENCE,1, CardType::NONETYPE}},designTriangleDesBermudes,new CardVictoryPoint{4, CardType::NONETYPE},CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}},{ResourceType::KRYSTALLIUM},ResourceType::SCIENCE);
        returnValue.push_back(triangleDesBermudes);


        /****************************************** Beginning of cards for testing games ******************************************/

        // Tour geante
        sf::Texture* designTourGeante = new sf::Texture;
        designTourGeante->loadFromFile("./resources/img/Cards/Development_Cards/tour_geante.png");
        DevelopmentCard* tourGeante = new DevelopmentCard ("Tour geante",{},designTourGeante,new CardVictoryPoint{10, (int) CardType::NONETYPE},CardType::PROJECT,1,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::FINANCIER, false}},{},ResourceType::GOLD);
        returnValue.push_back(tourGeante);

        // Tresor de Barbe Noire
        sf::Texture* designTresorDeBarbeNoire = new sf::Texture;
        designTresorDeBarbeNoire->loadFromFile("./resources/img/Cards/Development_Cards/tresor_de_barbe_noire.png");
        DevelopmentCard* tresorDeBarbeNoire = new DevelopmentCard ("Tresor de barbe noire",{new ResourceToProduce{ResourceType::GOLD,1,CardType::NONETYPE},new ResourceToProduce{ResourceType::EXPLORATION,1,CardType::NONETYPE}},designTresorDeBarbeNoire,new CardVictoryPoint{2, CardType::NONETYPE},CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::EXPLORATION, false},new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}},{},ResourceType::GOLD);
        returnValue.push_back(tresorDeBarbeNoire);

        // Zeppelin
        sf::Texture* designZeppelin = new sf::Texture;
        designZeppelin->loadFromFile("./resources/img/Cards/Development_Cards/zeppelin.png");
        for(int i = 0; i < 6; i++)
        {
            DevelopmentCard* zeppelin = new DevelopmentCard ("Zeppelin",{new ResourceToProduce{ResourceType::EXPLORATION,1, CardType::NONETYPE}},designZeppelin,new CardVictoryPoint{0, CardType::NONETYPE},CardType::VEHICLE,6,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}},{},ResourceType::EXPLORATION);
            returnValue.push_back(zeppelin);
        }

        // Ile d avalon
        sf::Texture* designIleDAvalon = new sf::Texture;
        designIleDAvalon->loadFromFile("./resources/img/Cards/Development_Cards/ile_d_avalon.png");
        DevelopmentCard* ileDAvalon = new DevelopmentCard ("Ile d avalon",{new ResourceToProduce{ResourceType::SCIENCE,1,CardType::NONETYPE}},designIleDAvalon,new CardVictoryPoint{7, CardType::NONETYPE},CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}},{},ResourceType::SCIENCE);
        returnValue.push_back(ileDAvalon);

        // Centre de la terre
        sf::Texture* designCentreDeLaTerre = new sf::Texture;
        designCentreDeLaTerre->loadFromFile("./resources/img/Cards/Development_Cards/centre_de_la_terre.png");
        DevelopmentCard* centreDeLaTerre = new DevelopmentCard ("Centre De La Terre",{},designCentreDeLaTerre,new CardVictoryPoint{15, CardType::NONETYPE},CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::COLONEL, false}, new ResourceToPay{ResourceType::COLONEL, false}},{},ResourceType::EXPLORATION);
        returnValue.push_back(centreDeLaTerre);

        // Brise glace
        for(int i = 0; i < 3; i++)
        {
            DevelopmentCard* briseGlace = new DevelopmentCard ("Brise glace",{new ResourceToProduce{ResourceType::EXPLORATION,2, CardType::NONETYPE}},designBriseGlace,{},CardType::VEHICLE,4,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{},ResourceType::EXPLORATION);
            returnValue.push_back(briseGlace);
        }

        // Juggernaut
        sf::Texture* designJuggernaut = new sf::Texture;
        designJuggernaut->loadFromFile("./resources/img/Cards/Development_Cards/juggernaut.png");
        DevelopmentCard* juggernaut = new DevelopmentCard ("Juggernaut",{new ResourceToProduce{ResourceType::EXPLORATION,2, CardType::NONETYPE}},designJuggernaut,new CardVictoryPoint{1, CardType::VEHICLE},CardType::VEHICLE,1,{new ResourceToPay{ResourceType::MATERIAL, false},new ResourceToPay{ResourceType::MATERIAL, false},new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::KRYSTALLIUM, false}},{ResourceType::COLONEL,ResourceType::COLONEL},ResourceType::MATERIAL);
        returnValue.push_back(juggernaut);

        return returnValue;
    }

    /// @brief Create all empire cards for a game.
    /// @param isFaceA States if the game is played with face A or not.
    /// @return Vector of all empire cards.
    std::vector<EmpireCard*> CreateAllCards::createAllEmpireCards (bool isFaceA) const
    {
        EmpireCard* africa = this->createEmpireAFRICA(isFaceA);
        EmpireCard* noram = this->createEmpireNORAM(isFaceA);
        EmpireCard* europe = this->createEmpireEUROPE(isFaceA);
        EmpireCard* asia = this->createEmpireASIA(isFaceA);
        EmpireCard* aztec = this->createEmpireAZTEC(isFaceA);

        std::vector<EmpireCard*> empires = {asia, aztec, africa, noram, europe};
        
        return empires;
    }

    /// @brief Create the empire card AFRICA.
    /// @param isFaceA State if the empire is played with face A or B.
    /// @return Pointer to the AFRICA empire.
    EmpireCard* CreateAllCards::createEmpireAFRICA (bool isFaceA) const
    {
        std::vector<ResourceToProduce*> productionGainB = this->createFaceBOfEmpires();
        
        ResourceToProduce* firstResourceToProduceAFRICA = new ResourceToProduce{ResourceType::MATERIAL, 2, CardType::NONETYPE};
        ResourceToProduce* secondResourceToProduceAFRICA = new ResourceToProduce{ResourceType::SCIENCE, 2, CardType::NONETYPE};
        std::vector<ResourceToProduce*> productionGainAFRICA = {firstResourceToProduceAFRICA, secondResourceToProduceAFRICA};
        
        std::string africa_FaceA = "./resources/img/Cards/Empire_Face_A/Panafricaine.png";
        std::string africa_FaceB = "./resources/img/Cards/Empire_Face_B/Panafricaine.png";
        
        CardVictoryPoint* victoryPointsAFRICA  = new CardVictoryPoint{2,CardType::RESEARCH};
        
        EmpireCard* africa = new EmpireCard("AFRICA", productionGainAFRICA, africa_FaceA, victoryPointsAFRICA, productionGainB, new CardVictoryPoint{}, AFRICA, africa_FaceB, isFaceA);
        
        return africa;
    }

    /// @brief Create the empire card ASIA.
    /// @param isFaceA State if the empire is played with face A or B.
    /// @return Pointer to the ASIA empire.
    EmpireCard* CreateAllCards::createEmpireASIA (bool isFaceA) const
    {
        std::vector<ResourceToProduce*> productionGainB = this->createFaceBOfEmpires();

        ResourceToProduce* firstResourceToProduceASIA = new ResourceToProduce{ResourceType::MATERIAL, 1, CardType::NONETYPE};
        ResourceToProduce* secondResourceToProduceASIA = new ResourceToProduce{ResourceType::GOLD, 2, CardType::NONETYPE};
        std::vector<ResourceToProduce*> productionGainASIA = {firstResourceToProduceASIA, secondResourceToProduceASIA};
        
        std::string asia_FaceA = "./resources/img/Cards/Empire_Face_A/Asia.png";
        std::string asia_FaceB = "./resources/img/Cards/Empire_Face_B/Asia.png";
        
        CardVictoryPoint* victoryPointsASIA  = new CardVictoryPoint{2, CardType::PROJECT};
        
        EmpireCard* asia = new EmpireCard("ASIA", productionGainASIA, asia_FaceA, victoryPointsASIA, productionGainB, new CardVictoryPoint{}, ASIA, asia_FaceB, isFaceA);
        
        return asia;
    }
    
    /// @brief Create the empire card AZTEC.
    /// @param isFaceA State if the empire is played with face A or B.
    /// @return Pointer to the AZTEC empire.
    EmpireCard* CreateAllCards::createEmpireAZTEC (bool isFaceA) const
    {
        std::vector<ResourceToProduce*> productionGainB = this->createFaceBOfEmpires();

        ResourceToProduce* firstResourceToProduceAZTEC = new ResourceToProduce{ResourceType::ENERGY, 2, CardType::NONETYPE};
        ResourceToProduce* secondResourceToProduceAZTEC = new ResourceToProduce{ResourceType::EXPLORATION, 1, CardType::NONETYPE};
        std::vector<ResourceToProduce*> productionGainAZTEC = {firstResourceToProduceAZTEC, secondResourceToProduceAZTEC};

        std::string aztec_FaceA = "./resources/img/Cards/Empire_Face_A/Aztec.png";
        std::string aztec_FaceB = "./resources/img/Cards/Empire_Face_B/Aztec.png";

        CardVictoryPoint* victoryPointsAZTEC  = new CardVictoryPoint{3, CardType::DISCOVERY};

        EmpireCard* aztec = new EmpireCard("AZTEC", productionGainAZTEC, aztec_FaceA, victoryPointsAZTEC, productionGainB, new CardVictoryPoint{}, AZTEC, aztec_FaceB, isFaceA);

        return aztec;
    }
    
    /// @brief Create the empire card EUROPE.
    /// @param isFaceA State if the empire is played with face A or B.
    /// @return Pointer to the EUROPE empire.
    EmpireCard* CreateAllCards::createEmpireEUROPE (bool isFaceA) const
    {
        std::vector<ResourceToProduce*> productionGainB = this->createFaceBOfEmpires();

        ResourceToProduce* firstResourceToProduceEUROPE = new ResourceToProduce{ResourceType::MATERIAL, 2, CardType::NONETYPE};
        ResourceToProduce* secondResourceToProduceEUROPE = new ResourceToProduce{ResourceType::ENERGY, 1, CardType::NONETYPE};
        ResourceToProduce* thirdResourceToProduceEUROPE = new ResourceToProduce{ResourceType::SCIENCE, 1, CardType::NONETYPE};
        std::vector<ResourceToProduce*> productionGainEUROPE = {firstResourceToProduceEUROPE, secondResourceToProduceEUROPE, thirdResourceToProduceEUROPE};
        
        std::string europe_FaceA = "./resources/img/Cards/Empire_Face_A/Europe.png";
        std::string europe_FaceB = "./resources/img/Cards/Empire_Face_B/Europe.png";
        
        CardVictoryPoint* victoryPointsEUROPE  = new CardVictoryPoint{1, ResourceType::COLONEL};
        
        EmpireCard* europe = new EmpireCard("EUROPE", productionGainEUROPE, europe_FaceA, victoryPointsEUROPE, productionGainB, new CardVictoryPoint{}, EUROPE, europe_FaceB, isFaceA);
    
        return europe;
    }
    
    /// @brief Create the empire card NORAM.
    /// @param isFaceA State if the empire is played with face A or B.
    /// @return Pointer to the NORAM empire.
    EmpireCard* CreateAllCards::createEmpireNORAM (bool isFaceA) const
    {
        std::vector<ResourceToProduce*> productionGainB = this->createFaceBOfEmpires();

        ResourceToProduce* firstResourceToProduceNORAM = new ResourceToProduce{ResourceType::MATERIAL, 3, CardType::NONETYPE};
        ResourceToProduce* secondResourceToProduceNORAM = new ResourceToProduce{ResourceType::GOLD, 1, CardType::NONETYPE};
        std::vector<ResourceToProduce*> productionGainNORAM = {firstResourceToProduceNORAM, secondResourceToProduceNORAM};
        
        std::string noram_FaceA = "./resources/img/Cards/Empire_Face_A/Noram.png";
        std::string noram_FaceB = "./resources/img/Cards/Empire_Face_B/Noram.png";
        
        CardVictoryPoint* victoryPointsNORAM  = new CardVictoryPoint{1, ResourceType::FINANCIER};

        EmpireCard* noram = new EmpireCard("NORAM", productionGainNORAM, noram_FaceA, victoryPointsNORAM, productionGainB, new CardVictoryPoint{}, NORAM, noram_FaceB, isFaceA);
    
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