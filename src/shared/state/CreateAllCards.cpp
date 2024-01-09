#include "CreateAllCards.h"

namespace state
{
    /// @brief Create all development cards for a game.
    /// @return Vector of all development cards.
    std::vector<DevelopmentCard*> CreateAllCards::createAllDevelopmentCards () const
    {
        std::vector<DevelopmentCard*> returnValue = {};

        std::string basePath = "./resources/img/Cards/Development_Cards/";

        /****************************************** Beginning of STRUCTURE cards ******************************************/

        // Base militaire
        std::string relativePathTextureBaseMilitaire = basePath + "base_militaire.png";
        for(int i = 0; i < 6; i++)
        {
            DevelopmentCard* baseMilitaire = new DevelopmentCard ("Base militaire",{new ResourceToProduce{ResourceType::MATERIAL,1, CardType::NONETYPE}, new ResourceToProduce{ResourceType::SCIENCE,1, CardType::NONETYPE}},relativePathTextureBaseMilitaire,new CardVictoryPoint{},CardType::STRUCTURE,6,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::ENERGY, false}},{ResourceType::COLONEL},ResourceType::MATERIAL);
            returnValue.push_back(baseMilitaire);
        }

        // Centrale nucleaire
        std::string relativePathTextureCentraleNucleaire = basePath + "centrale_nucleaire.png";
        for(int i=0;i<5;i++)
        {
            DevelopmentCard* centraleNucleaire = new DevelopmentCard ("Centrale nucleaire",{new ResourceToProduce{ResourceType::ENERGY,3, CardType::NONETYPE}},relativePathTextureCentraleNucleaire,new CardVictoryPoint{},CardType::STRUCTURE,5,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{},ResourceType::ENERGY);
            returnValue.push_back(centraleNucleaire);
        }

        // Centre de recherche
        for(int i = 0; i < 7; i++)
        {
            std::string relativePathTextureCentreDeRecherche = basePath + "centre_de_recherche.png";
            DevelopmentCard* centreDeRecherche = new DevelopmentCard ("Centre de recherche",{new ResourceToProduce{ResourceType::SCIENCE,2, CardType::NONETYPE}},relativePathTextureCentreDeRecherche,new CardVictoryPoint{},CardType::STRUCTURE,7,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::ENERGY, false}},{},ResourceType::SCIENCE);
            returnValue.push_back(centreDeRecherche);
        }

        // Complexe industriel
        std::string relativePathTextureComplexeIndustriel = basePath + "complexe_industriel.png";
        for(int i = 0; i < 6; i++)
        {
            DevelopmentCard* complexeIndustriel = new DevelopmentCard ("Complexe industriel",{new ResourceToProduce{ResourceType::MATERIAL,1, CardType::NONETYPE}, new ResourceToProduce{ResourceType::GOLD,1, CardType::NONETYPE}},relativePathTextureComplexeIndustriel,new CardVictoryPoint{},CardType::STRUCTURE,6,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::ENERGY, false}},{ResourceType::FINANCIER},ResourceType::GOLD);
            returnValue.push_back(complexeIndustriel);
        }

        // Eoliennes
        std::string relativePathTextureEoliennes = basePath + "eoliennes.png";
        for(int i = 0; i < 7; i++)
        {
            DevelopmentCard* eoliennes = new DevelopmentCard ("Eoliennes",{new ResourceToProduce{ResourceType::ENERGY,1, CardType::NONETYPE}},relativePathTextureEoliennes,new CardVictoryPoint{},CardType::STRUCTURE,7,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}},{},ResourceType::ENERGY);
            returnValue.push_back(eoliennes);
        }

        // Place financiere
        std::string relativePathTexturePlaceFinanciere = basePath + "place_financiere.png";
        for(int i = 0; i < 5; i++)
        {
            DevelopmentCard* placeFinanciere = new DevelopmentCard ("Place financiere",{new ResourceToProduce{ResourceType::GOLD,2, CardType::NONETYPE}},relativePathTexturePlaceFinanciere,new CardVictoryPoint{},CardType::STRUCTURE,5,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::ENERGY, false}},{ResourceType::FINANCIER},ResourceType::GOLD);
            returnValue.push_back(placeFinanciere);
        }

        // Plate-forme petroliere

        std::string relativePathTexturePlateFormePetroliere = basePath + "plate_forme_petroliere.png";
        for(int i = 0; i < 5; i++)
        {
            DevelopmentCard* plateFormePetroliere = new DevelopmentCard ("Plate forme petroliere",{new ResourceToProduce{ResourceType::ENERGY,1, CardType::NONETYPE}, new ResourceToProduce{ResourceType::GOLD,1, CardType::NONETYPE}},relativePathTexturePlateFormePetroliere,new CardVictoryPoint{},CardType::STRUCTURE,5,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::EXPLORATION, false}},{ResourceType::FINANCIER},ResourceType::ENERGY);
            returnValue.push_back(plateFormePetroliere);
        }

        // Reseau de transport
        std::string relativePathTextureReseauDeTransport = basePath + "reseau_de_transport.png";
        for(int i = 0; i < 2; i++)
        {
            DevelopmentCard* reseauDeTransport = new DevelopmentCard ("Reseau de transport",{},relativePathTextureReseauDeTransport,new CardVictoryPoint{1, CardType::VEHICLE},CardType::STRUCTURE,2,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}},{},ResourceType::MATERIAL);
            returnValue.push_back(reseauDeTransport);
        }

        // Usine de recyclage
        std::string relativePathTextureUsineDeRecyclage = basePath + "usine_de_recyclage.png";
        for(int i = 0; i < 7; i++)
        {
            DevelopmentCard* usineDeRecyclage = new DevelopmentCard ("Usine de recyclage",{new ResourceToProduce{ResourceType::MATERIAL,2, CardType::NONETYPE}},relativePathTextureUsineDeRecyclage,new CardVictoryPoint{},CardType::STRUCTURE,7,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL}},{},ResourceType::MATERIAL);
            returnValue.push_back(usineDeRecyclage);
        }

        /****************************************** Beginning of VEHICLE cards ******************************************/

        // Brise glace -- Only one because three are created at the end.
        std::string relativePathTextureBriseGlace = basePath + "brise_glace.png";
        DevelopmentCard* briseGlaceFirst = new DevelopmentCard ("Brise glace",{new ResourceToProduce{ResourceType::EXPLORATION,2, CardType::NONETYPE}},relativePathTextureBriseGlace,new CardVictoryPoint{},CardType::VEHICLE,4,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{},ResourceType::EXPLORATION);
        returnValue.push_back(briseGlaceFirst);

        // Division de chars
        std::string relativePathTextureDivisionDeChars = basePath + "division_de_chars.png";
        for(int i = 0; i < 7; i++)
        {
            DevelopmentCard* divisionDeChars = new DevelopmentCard ("Division de chars",{new ResourceToProduce{ResourceType::EXPLORATION,1, CardType::NONETYPE}},relativePathTextureDivisionDeChars,new CardVictoryPoint{},CardType::VEHICLE,7,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}},{ResourceType::COLONEL},ResourceType::MATERIAL);
            returnValue.push_back(divisionDeChars);
        }

        // Escadrille de soucoupes
        std::string relativePathTextureEscadrilleDeSoucoupes = basePath + "escadrille_de_soucoupes.png";
        for(int i = 0; i < 2; i++)
        {
            DevelopmentCard* escadrilleDeSoucoupes = new DevelopmentCard ("Escadrille de soucoupes",{new ResourceToProduce{ResourceType::EXPLORATION,3, CardType::NONETYPE}},relativePathTextureEscadrilleDeSoucoupes,new CardVictoryPoint{},CardType::VEHICLE,2,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{},ResourceType::SCIENCE);
            returnValue.push_back(escadrilleDeSoucoupes);
        }

        // Juggernaut -- Created at the end.

        // Laboratoire aeroporte
        std::string relativePathTextureLaboratoireAeroporte = basePath + "laboratoire_aeroporte.png";
        for(int i = 0; i < 3; i++)
        {
            DevelopmentCard* laboratoireAeroporte = new DevelopmentCard ("Laboratoire aeroporte",{new ResourceToProduce{ResourceType::SCIENCE,1, CardType::NONETYPE}, new ResourceToProduce{ResourceType::EXPLORATION,1, CardType::NONETYPE}},relativePathTextureLaboratoireAeroporte,new CardVictoryPoint{},CardType::VEHICLE,3,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}},{},ResourceType::SCIENCE);
            returnValue.push_back(laboratoireAeroporte);
        }

        // Mega foreuse
        std::string relativePathTextureMegaForeuse = basePath + "mega_foreuse.png";
        for(int i = 0; i < 4; i++)
        {
            DevelopmentCard* megaForeuse = new DevelopmentCard ("Mega foreuse",{new ResourceToProduce{ResourceType::MATERIAL,1, CardType::NONETYPE}, new ResourceToProduce{ResourceType::EXPLORATION,1, CardType::NONETYPE}},relativePathTextureMegaForeuse,new CardVictoryPoint{},CardType::VEHICLE,4,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}},{},ResourceType::MATERIAL);
            returnValue.push_back(megaForeuse);
        }

        // Porte avions
        std::string relativePathTexturePorteAvions = basePath + "porte_avions.png";
        DevelopmentCard* porteAvions = new DevelopmentCard ("Porte Avions",{new ResourceToProduce{ResourceType::EXPLORATION, 1, CardType::VEHICLE}},relativePathTexturePorteAvions,new CardVictoryPoint{0, CardType::NONETYPE},CardType::VEHICLE,1,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}},{ResourceType::COLONEL,ResourceType::COLONEL},ResourceType::MATERIAL);
        returnValue.push_back(porteAvions);

        // Sous marin
        std::string relativePathTextureSousMarin = basePath + "sous_marin.png";
        for(int i = 0; i < 3; i++)
        {
            DevelopmentCard* sousMarin = new DevelopmentCard ("Sous marin",{new ResourceToProduce{ResourceType::EXPLORATION,2, CardType::NONETYPE}},relativePathTextureSousMarin,new CardVictoryPoint{0, CardType::NONETYPE},CardType::VEHICLE,3,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}},{ResourceType::COLONEL},ResourceType::MATERIAL);
            returnValue.push_back(sousMarin);
        }

        // Zeppelin -- Created at the end

        /****************************************** Beginning of RESEARCH cards ******************************************/
        // Amelioration genetique
        std::string relativePathTextureAmeliorationGenetique = basePath + "amelioration_genetique.png";
        DevelopmentCard* ameliorationGenetique = new DevelopmentCard ("Amelioration genetique",{},relativePathTextureAmeliorationGenetique,new CardVictoryPoint{3, (int) CardType::NONETYPE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{ResourceType::FINANCIER, ResourceType::FINANCIER},ResourceType::SCIENCE);
        returnValue.push_back(ameliorationGenetique);

        // Animorphes
        std::string relativePathTextureAnimorphes = basePath + "animorphes.png";
        DevelopmentCard* animorphes = new DevelopmentCard ("Animorphes",{new ResourceToProduce{ResourceType::MATERIAL, 1, CardType::NONETYPE}},relativePathTextureAnimorphes,new CardVictoryPoint{2, (int) CardType::NONETYPE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{ResourceType::COLONEL},ResourceType::ENERGY);
        returnValue.push_back(animorphes);

        // Aquaculture
        std::string relativePathTextureAquaculture = basePath + "aquaculture.png";
        DevelopmentCard* aquaculture = new DevelopmentCard ("Aquaculture",{},relativePathTextureAquaculture,new CardVictoryPoint{1, (int) ResourceType::FINANCIER},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},{ResourceType::FINANCIER},ResourceType::SCIENCE);
        returnValue.push_back(aquaculture);

        // Automates de controle
        std::string relativePathTextureAutomateControle = basePath + "automates_de_controle.png";
        DevelopmentCard* automateControle = new DevelopmentCard ("Automates de controle",{},relativePathTextureAutomateControle,new CardVictoryPoint{1, (int) ResourceType::COLONEL},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::GOLD, false}},{},ResourceType::GOLD);
        returnValue.push_back(automateControle);

        // Clonage humain
        std::string relativePathTextureClonageHumain = basePath + "clonage_humain.png";
        DevelopmentCard* clonageHumain = new DevelopmentCard ("Clonage Humain",{new ResourceToProduce{ResourceType::GOLD, 1, CardType::NONETYPE}},relativePathTextureClonageHumain,new CardVictoryPoint{1, (int) CardType::NONETYPE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::GOLD, false}},{ResourceType::FINANCIER},ResourceType::GOLD);
        returnValue.push_back(clonageHumain);

        // Controle du climat
        std::string relativePathTextureControlDuClimat = basePath + "controle_du_climat.png";
        DevelopmentCard* controlDuClimat = new DevelopmentCard ("Controle du climat",{new ResourceToProduce{ResourceType::ENERGY, 2, CardType::NONETYPE},new ResourceToProduce{ResourceType::GOLD, 1, CardType::NONETYPE}},relativePathTextureControlDuClimat,new CardVictoryPoint{2, (int) CardType::NONETYPE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{},ResourceType::ENERGY);
        returnValue.push_back(controlDuClimat);

        // Cryogenisation
        std::string relativePathTextureCryogenisation = basePath + "cryogenisation.png";
        DevelopmentCard* cryogenisation = new DevelopmentCard ("Cryogenisation",{},relativePathTextureCryogenisation,new CardVictoryPoint{1, (int) ResourceType::FINANCIER},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{ResourceType::FINANCIER},ResourceType::GOLD);
        returnValue.push_back(cryogenisation);

        // Generateur quantique
        std::string relativePathTextureGenerateurQuantique = basePath + "generateur_quantique.png";
        DevelopmentCard* generateurQuantique = new DevelopmentCard ("Generateur quantique",{new ResourceToProduce{ResourceType::ENERGY, 3, CardType::NONETYPE}},relativePathTextureGenerateurQuantique,new CardVictoryPoint{1, (int) CardType::VEHICLE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{},ResourceType::ENERGY);
        returnValue.push_back(generateurQuantique);

        // Greffes bioniques
        std::string relativePathTextureGreffesBionique = basePath + "greffes_bioniques.png";
        DevelopmentCard* greffesBioniques = new DevelopmentCard ("Greffes bioniques",{new ResourceToProduce{ResourceType::MATERIAL, 2, CardType::NONETYPE}},relativePathTextureGreffesBionique,new CardVictoryPoint{4, (int) CardType::NONETYPE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{ResourceType::COLONEL},ResourceType::MATERIAL);
        returnValue.push_back(greffesBioniques);

        // Inverseur de gravite
        std::string relativePathTextureInverseurGravite = basePath + "inverseur_de_gravite.png";
        DevelopmentCard* inverseurGravite = new DevelopmentCard ("Inverseur de gravite",{},relativePathTextureInverseurGravite,new CardVictoryPoint{2, (int) CardType::PROJECT},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::KRYSTALLIUM, false}},{ResourceType::FINANCIER},ResourceType::SCIENCE);
        returnValue.push_back(inverseurGravite);

        // Mega bombe
        std::string relativePathTextureMegaBombe = basePath + "mega_bombe.png";
        DevelopmentCard* megaBombe = new DevelopmentCard ("Mega bombe",{},relativePathTextureMegaBombe,new CardVictoryPoint{3, (int) CardType::NONETYPE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{ResourceType::COLONEL, ResourceType::COLONEL},ResourceType::ENERGY);
        returnValue.push_back(megaBombe);

        // Neuroscience
        std::string relativePathTextureNeuroscience = basePath + "neuroscience.png";
        DevelopmentCard* neuroscience = new DevelopmentCard ("Neuroscience",{new ResourceToProduce{ResourceType::SCIENCE, 1, CardType::RESEARCH}},relativePathTextureNeuroscience,new CardVictoryPoint{1, (int) CardType::NONETYPE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{},ResourceType::SCIENCE);
        returnValue.push_back(neuroscience);

        // Realite virtuelle
        std::string relativePathTextureRealiteVirtuelle = basePath + "realite_virtuelle.png";
        DevelopmentCard* realiteVirtuelle = new DevelopmentCard ("Realite virtuelle",{new ResourceToProduce{ResourceType::GOLD, 1, CardType::RESEARCH}},relativePathTextureRealiteVirtuelle,new CardVictoryPoint{2, (int) CardType::NONETYPE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{},ResourceType::GOLD);
        returnValue.push_back(realiteVirtuelle);

        // Robots de compagnie
        std::string relativePathTextureRobotsCompagnie = basePath + "robots_de_compagnie.png";
        DevelopmentCard* robotsCompagnie = new DevelopmentCard ("Robots de compagnie",{new ResourceToProduce{ResourceType::MATERIAL, 1, CardType::STRUCTURE}},relativePathTextureRobotsCompagnie,new CardVictoryPoint{1, (int) CardType::NONETYPE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{},ResourceType::MATERIAL);
        returnValue.push_back(robotsCompagnie);

        // Satellites
        std::string relativePathTextureSatellites = basePath + "satellites.png";
        DevelopmentCard* satellites = new DevelopmentCard ("Satellites",{new ResourceToProduce{ResourceType::EXPLORATION, 2, CardType::NONETYPE}},relativePathTextureSatellites,new CardVictoryPoint{3, (int) CardType::NONETYPE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{ResourceType::COLONEL},ResourceType::EXPLORATION);
        returnValue.push_back(satellites);

        // Super calculateur
        std::string relativePathTextureSuperCalculateur = basePath + "super_calculateur.png";
        DevelopmentCard* superCalculateur = new DevelopmentCard ("Super calculateur",{new ResourceToProduce{ResourceType::SCIENCE, 1, CardType::NONETYPE}},relativePathTextureSuperCalculateur,new CardVictoryPoint{1, (int) CardType::VEHICLE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{},ResourceType::SCIENCE);
        returnValue.push_back(superCalculateur);

        // Super soldats
        std::string relativePathTextureSuperSoldats = basePath + "super_soldats.png";
        DevelopmentCard* superSoldats = new DevelopmentCard ("Super soldats",{},relativePathTextureSuperSoldats,new CardVictoryPoint{1, (int) ResourceType::COLONEL},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{ResourceType::COLONEL},ResourceType::EXPLORATION);
        returnValue.push_back(superSoldats);

        // Super sonar
        std::string relativePathTextureSuperSonar = basePath + "super_sonar.png";
        DevelopmentCard* superSonar = new DevelopmentCard ("Super sonar",{new ResourceToProduce{ResourceType::EXPLORATION, 1, CardType::VEHICLE}},relativePathTextureSuperSonar,new CardVictoryPoint{1, (int) CardType::NONETYPE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{},ResourceType::EXPLORATION);
        returnValue.push_back(superSonar);

        // Technologie inconnue
        std::string relativePathTextureTechnologieInconnue = basePath + "technologie_inconnue.png";
        DevelopmentCard* technologieInconnue = new DevelopmentCard ("Technologie inconnue",{},relativePathTextureTechnologieInconnue,new CardVictoryPoint{3, (int) CardType::RESEARCH},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::KRYSTALLIUM, false}},{},ResourceType::SCIENCE);
        returnValue.push_back(technologieInconnue);

        // Teleportation
        std::string relativePathTextureTeleportation = basePath + "teleportation.png";
        DevelopmentCard* teleportation = new DevelopmentCard ("Teleportation",{},relativePathTextureTeleportation,new CardVictoryPoint{8, (int) CardType::NONETYPE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{ResourceType::KRYSTALLIUM, ResourceType::KRYSTALLIUM},ResourceType::EXPLORATION);
        returnValue.push_back(teleportation);

        // Transmutation
        std::string relativePathTextureTransmutation = basePath + "transmutation.png";
        DevelopmentCard* transmutation = new DevelopmentCard ("Transmutation",{new ResourceToProduce{ResourceType::GOLD, 3, CardType::NONETYPE}},relativePathTextureTransmutation,new CardVictoryPoint{1, (int) CardType::NONETYPE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},{ResourceType::KRYSTALLIUM},ResourceType::GOLD);
        returnValue.push_back(transmutation);

        // Vaccin Universel
        std::string relativePathTextureVaccinUniversel = basePath + "vaccin_universel.png";
        DevelopmentCard* vaccinUniversel = new DevelopmentCard ("Vaccin universel",{},relativePathTextureVaccinUniversel,new CardVictoryPoint{1, (int) CardType::PROJECT},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{},ResourceType::GOLD);
        returnValue.push_back(vaccinUniversel);

        // Voyage temporel
        std::string relativePathTextureVoyageTemporel = basePath + "voyage_temporel.png";
        DevelopmentCard* voyageTemporel = new DevelopmentCard ("Voyage temporel",{},relativePathTextureVoyageTemporel,new CardVictoryPoint{15, (int) CardType::NONETYPE},CardType::RESEARCH,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::KRYSTALLIUM, false}, new ResourceToPay{ResourceType::KRYSTALLIUM, false}, new ResourceToPay{ResourceType::KRYSTALLIUM, false}},{},ResourceType::EXPLORATION);
        returnValue.push_back(voyageTemporel);

        /****************************************** Beginning of PROJECT cards ******************************************/
        // Agence d'espionnage
        std::string relativePathTextureAgenceEspionnage = basePath + "agence_d_espionnage.png";
        for (int i = 0; i < 2; i++)
        {
            DevelopmentCard* agenceEspionnage = new DevelopmentCard ("Agence d'espionnage",{new ResourceToProduce{ResourceType::EXPLORATION, 2, CardType::NONETYPE}},relativePathTextureAgenceEspionnage,new CardVictoryPoint{1, CardType::NONETYPE},CardType::PROJECT,2,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},{},ResourceType::EXPLORATION);
            returnValue.push_back(agenceEspionnage);
        }

        // Ascenseur Spatial
        std::string relativePathTextureAscenseurSpatial = basePath + "ascenseur_spatial.png";
        DevelopmentCard* ascenseurSpatial = new DevelopmentCard ("Ascenseur spatial",{},relativePathTextureAscenseurSpatial,new CardVictoryPoint{1, (int) ResourceType::FINANCIER},CardType::PROJECT,1,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},{ResourceType::FINANCIER},ResourceType::ENERGY);
        returnValue.push_back(ascenseurSpatial);

        // Barrage Geant
        std::string relativePathTextureBarrageGeant = basePath + "barrage_geant.png";
        DevelopmentCard* barrageGeant = new DevelopmentCard ("Barrage geant",{new ResourceToProduce{ResourceType::ENERGY, 4, CardType::NONETYPE}},relativePathTextureBarrageGeant,new CardVictoryPoint{1, (int) CardType::NONETYPE},CardType::PROJECT,1,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},{},ResourceType::ENERGY);
        returnValue.push_back(barrageGeant);

        // Base Lunaire
        std::string relativePathTextureBaseLunaire = basePath + "base_lunaire.png";
        DevelopmentCard* baseLunaire = new DevelopmentCard ("Base lunaire",{},relativePathTextureBaseLunaire,new CardVictoryPoint{10, (int) CardType::NONETYPE},CardType::PROJECT,1,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::KRYSTALLIUM, false}},{ResourceType::COLONEL, ResourceType::COLONEL},ResourceType::EXPLORATION);
        returnValue.push_back(baseLunaire);

        // Base Polaire
        std::string relativePathTextureBasePolaire = basePath + "base_polaire.png";
        DevelopmentCard* basePolaire = new DevelopmentCard ("Base polaire",{new ResourceToProduce{ResourceType::EXPLORATION, 3, CardType::NONETYPE}},relativePathTextureBasePolaire,new CardVictoryPoint{2, (int) CardType::DISCOVERY},CardType::PROJECT,1,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},{ResourceType::COLONEL},ResourceType::EXPLORATION);
        returnValue.push_back(basePolaire);

        // Canon Solaire
        std::string relativePathTextureCanonSolaire = basePath + "canon_solaire.png";
        DevelopmentCard* canonSolaire = new DevelopmentCard ("Canon solaire",{},relativePathTextureCanonSolaire,new CardVictoryPoint{1, (int) ResourceType::COLONEL},CardType::PROJECT,1,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},{ResourceType::COLONEL},ResourceType::ENERGY);
        returnValue.push_back(canonSolaire);

        // Centre de propagande
        std::string relativePathTextureCentrePropagande = basePath + "centre_de_propagande.png";
        for (int i = 0; i < 2; i++)
        {
            DevelopmentCard* centrePropagande = new DevelopmentCard ("Centre de propagande",{new ResourceToProduce{ResourceType::GOLD, 1, CardType::PROJECT}},relativePathTextureCentrePropagande,new CardVictoryPoint{1, (int) CardType::NONETYPE},CardType::PROJECT,2,{new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},{ResourceType::COLONEL},ResourceType::GOLD);
            returnValue.push_back(centrePropagande);
        }

        // Congres Mondial
        std::string relativePathTextureCongresMondial = basePath + "congres_mondial.png";
        DevelopmentCard* congresMondial = new DevelopmentCard ("Congres mondial",{},relativePathTextureCongresMondial,new CardVictoryPoint{3, (int) CardType::PROJECT},CardType::PROJECT,1,{new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::FINANCIER, false}, new ResourceToPay{ResourceType::FINANCIER, false}},{},ResourceType::GOLD);
        returnValue.push_back(congresMondial);

        // Exposition universelle
        std::string relativePathTextureExpositionUniverselle = basePath + "exposition_universelle.png";
        DevelopmentCard* expositionUniverselle = new DevelopmentCard ("Exposition Universelle",{},relativePathTextureExpositionUniverselle,new CardVictoryPoint{3, (int) CardType::RESEARCH},CardType::PROJECT,1,{new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::FINANCIER, false}, new ResourceToPay{ResourceType::FINANCIER, false}},{},ResourceType::GOLD);
        returnValue.push_back(expositionUniverselle);

        // Laboratoire secret
        std::string relativePathTextureLaboratoireSecret = basePath + "laboratoire_secret.png";
        for (int i = 0; i < 2; i++)
        {
            DevelopmentCard* laboratoireSecret = new DevelopmentCard ("Laboratoire secret",{new ResourceToProduce{ResourceType::SCIENCE, 2, CardType::NONETYPE}},relativePathTextureLaboratoireSecret,new CardVictoryPoint{1, (int) CardType::RESEARCH},CardType::PROJECT,2,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},{ResourceType::KRYSTALLIUM},ResourceType::SCIENCE);
            returnValue.push_back(laboratoireSecret);
        }

        // Monument national
        std::string relativePathTextureMonumentNational = basePath + "monument_national.png";
        DevelopmentCard* monumentNational = new DevelopmentCard ("Monument national",{},relativePathTextureMonumentNational,new CardVictoryPoint{2, (int) CardType::PROJECT},CardType::PROJECT,1,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},{},ResourceType::GOLD);
        returnValue.push_back(monumentNational);

        // Musee
        std::string relativePathTextureMusee = basePath + "musee.png";
        for (int i = 0; i < 2; i++)
        {
            DevelopmentCard* musee = new DevelopmentCard ("Musee",{},relativePathTextureMusee,new CardVictoryPoint{2, (int) CardType::DISCOVERY},CardType::PROJECT,2,{new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},{},ResourceType::EXPLORATION);
            returnValue.push_back(musee);
        }

        // Societe secrete
            std::string relativePathTextureSocieteSecrete = basePath + "societe_secrete.png";
        for (int i = 0; i < 2; i++)
        {
            DevelopmentCard* societeSecrete = new DevelopmentCard ("Societe secrete",{},relativePathTextureSocieteSecrete,new CardVictoryPoint{1, (int) ResourceType::FINANCIER},CardType::PROJECT,2,{new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::KRYSTALLIUM, false}},{},ResourceType::GOLD);
            returnValue.push_back(societeSecrete);
        }

        // Tour geante - created at the end.

        // Train magnetique
        std::string relativePathTextureTrainMagnetique = basePath + "train_magnetique.png";
        DevelopmentCard* trainMagnetique = new DevelopmentCard ("Train magnetique",{new ResourceToProduce{ResourceType::GOLD, 1, CardType::STRUCTURE}},relativePathTextureTrainMagnetique,new CardVictoryPoint{2, (int) CardType::NONETYPE},CardType::PROJECT,1,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},{ResourceType::FINANCIER, ResourceType::FINANCIER},ResourceType::GOLD);
        returnValue.push_back(trainMagnetique);

        // Universite
        std::string relativePathTextureUniversite = basePath + "universite.png";
        DevelopmentCard* universite = new DevelopmentCard ("Universite",{new ResourceToProduce{ResourceType::SCIENCE, 1, CardType::PROJECT}},relativePathTextureUniversite,new CardVictoryPoint{2, (int) CardType::NONETYPE},CardType::PROJECT,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},{},ResourceType::SCIENCE);
        returnValue.push_back(universite);

        // Ville-casino
        std::string relativePathTextureVilleCasino = basePath + "ville_casino.png";
        for (int i = 0; i < 2; i++)
        {
            DevelopmentCard* villeCasino = new DevelopmentCard ("Ville casino",{new ResourceToProduce{ResourceType::GOLD, 2, CardType::NONETYPE}},relativePathTextureVilleCasino,new CardVictoryPoint{1, (int) ResourceType::FINANCIER},CardType::PROJECT,2,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},{ResourceType::FINANCIER},ResourceType::GOLD);
            returnValue.push_back(villeCasino);
        }

        // Ville sous-marine
        std::string relativePathTextureVilleSousMarine = basePath + "ville_sous_marine.png";
        for (int i = 0; i < 2; i++)
        {
            DevelopmentCard* villeSousMarine = new DevelopmentCard ("Ville sous-marine",{new ResourceToProduce{ResourceType::SCIENCE, 1, CardType::NONETYPE}, new ResourceToProduce{ResourceType::EXPLORATION, 2, CardType::NONETYPE}},relativePathTextureVilleSousMarine,new CardVictoryPoint{3, (int) CardType::NONETYPE},CardType::PROJECT,2,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},{},ResourceType::EXPLORATION);
            returnValue.push_back(villeSousMarine);
        }

        // Ville souterraine
        std::string relativePathTextureVilleSouterraine = basePath + "ville_souterraine.png";
        for (int i = 0; i < 2; i++)
        {
            DevelopmentCard* villeSouterraine = new DevelopmentCard ("Ville souterraine",{new ResourceToProduce{ResourceType::MATERIAL, 2, CardType::NONETYPE}, new ResourceToProduce{ResourceType::ENERGY, 2, CardType::NONETYPE}},relativePathTextureVilleSouterraine,new CardVictoryPoint{3, (int) CardType::NONETYPE},CardType::PROJECT,2,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},{ResourceType::KRYSTALLIUM},ResourceType::ENERGY);
            returnValue.push_back(villeSouterraine);
        }

        // Zone portuaire
        std::string relativePathTextureZonePortuaire = basePath + "zone_portuaire.png";
        for (int i = 0; i < 2; i++)
        {
            DevelopmentCard* zonePortuaire = new DevelopmentCard ("Zone portuaire",{new ResourceToProduce{ResourceType::MATERIAL, 2, CardType::NONETYPE}, new ResourceToProduce{ResourceType::GOLD, 2, CardType::NONETYPE}},relativePathTextureZonePortuaire,new CardVictoryPoint{2, (int) CardType::NONETYPE},CardType::PROJECT,2,{new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}},{ResourceType::FINANCIER, ResourceType::FINANCIER},ResourceType::GOLD);
            returnValue.push_back(zonePortuaire);
        }

        /****************************************** Beginning of DISCOVERY cards ******************************************/
        // Anciens astronautes
        std::string relativePathTextureAnciensAstronautes = basePath + "anciens_astronautes.png";
        DevelopmentCard* anciensAstronautes = new DevelopmentCard ("Anciens Astronautes",{new ResourceToProduce{ResourceType::SCIENCE,1, CardType::DISCOVERY}},relativePathTextureAnciensAstronautes,new CardVictoryPoint{10, CardType::NONETYPE},CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::COLONEL, false}},{ResourceType::KRYSTALLIUM,ResourceType::KRYSTALLIUM},ResourceType::SCIENCE);
        returnValue.push_back(anciensAstronautes);

        // Arche d alliance
        std::string relativePathTextureArcheDAlliance = basePath + "arche_d_alliance.png";
        DevelopmentCard* archeDAlliance = new DevelopmentCard ("Arche d alliance",{},relativePathTextureArcheDAlliance,new CardVictoryPoint{5, CardType::NONETYPE},CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}},{ResourceType::KRYSTALLIUM},ResourceType::EXPLORATION);
        returnValue.push_back(archeDAlliance);

        // Atlantide
        std::string relativePathTextureAtlantide = basePath + "atlantide.png";
        DevelopmentCard* atlantide = new DevelopmentCard ("Atlantide",{},relativePathTextureAtlantide,new CardVictoryPoint{2, ResourceType::COLONEL},CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::KRYSTALLIUM, false}},{},ResourceType::GOLD);
        returnValue.push_back(atlantide);

        // Centre de la terre -- created at the end

        // Cite d agartha
        std::string relativePathTextureCiteDAgartha = basePath + "cite_d_agartha.png";
        DevelopmentCard* citeDAgartha = new DevelopmentCard ("Cite d agartha",{new ResourceToProduce{ResourceType::EXPLORATION,2, CardType::NONETYPE}},relativePathTextureCiteDAgartha,new CardVictoryPoint{1, ResourceType::COLONEL},CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::KRYSTALLIUM, false}},{},ResourceType::EXPLORATION);
        returnValue.push_back(citeDAgartha);

        // Cite d or
        std::string relativePathTextureCitesDOr = basePath + "cites_d_or.png";
        DevelopmentCard* citesDOr = new DevelopmentCard ("Cites d or",{new ResourceToProduce{ResourceType::GOLD,3, CardType::NONETYPE}},relativePathTextureCitesDOr,new CardVictoryPoint{3, CardType::NONETYPE},CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}},{},ResourceType::GOLD);
        returnValue.push_back(citesDOr);

        // Continent perdu de mu
        std::string relativePathTextureContinentPerduDeMu = basePath + "continent_perdu_de_mu.png";
        DevelopmentCard* continentPerduDeMu = new DevelopmentCard ("Continent perdu de mu",{new ResourceToProduce{ResourceType::GOLD,1, CardType::NONETYPE}},relativePathTextureContinentPerduDeMu,new CardVictoryPoint{2, CardType::DISCOVERY},CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}},{ResourceType::KRYSTALLIUM,ResourceType::KRYSTALLIUM},ResourceType::GOLD);
        returnValue.push_back(continentPerduDeMu);

        // Dimension parallele
        std::string relativePathTextureDimensionParallele = basePath + "dimension_parallele.png";
        DevelopmentCard* dimensionParallele = new DevelopmentCard ("Dimension parallele",{}, relativePathTextureDimensionParallele,new CardVictoryPoint{3, CardType::RESEARCH},CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::SCIENCE, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::COLONEL, false}},{ResourceType::KRYSTALLIUM,ResourceType::KRYSTALLIUM,ResourceType::KRYSTALLIUM},ResourceType::EXPLORATION);
        returnValue.push_back(dimensionParallele);

        // Fontaine de jouvence
        std::string relativePathTextureFontaineDeJouvence = basePath + "fontaine_de_jouvence.png";
        DevelopmentCard* fontaineDeJouvence = new DevelopmentCard ("Fontaine de jouvence",{}, relativePathTextureFontaineDeJouvence,new CardVictoryPoint{1, ResourceType::COLONEL},CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}},{ResourceType::KRYSTALLIUM,ResourceType::KRYSTALLIUM,ResourceType::KRYSTALLIUM},ResourceType::ENERGY);
        returnValue.push_back(fontaineDeJouvence);

        // Ile d avalon -- created at the end

        // Jardin des hesperides
        std::string relativePathTextureJardinDesHesperides = basePath + "jardin_des_hesperides.png";
        DevelopmentCard* jardinDesHesperides = new DevelopmentCard ("Jardin des hesperides",{},relativePathTextureJardinDesHesperides,new CardVictoryPoint{2, CardType::PROJECT},CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}},{},ResourceType::EXPLORATION);
        returnValue.push_back(jardinDesHesperides);

        // Mines du roi salomon
        std::string relativePathTextureMinesDuRoiSalomon = basePath + "mines_du_roi_salomon.png";
        DevelopmentCard* minesDuRoiSalomon = new DevelopmentCard ("Mines du roi salomon",{new ResourceToProduce{ResourceType::GOLD,1,CardType::STRUCTURE}},relativePathTextureMinesDuRoiSalomon,new CardVictoryPoint{2, CardType::NONETYPE},CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}},{},ResourceType::GOLD);
        returnValue.push_back(minesDuRoiSalomon);

        // Roswell
        std::string relativePathTextureRoswell = basePath + "roswell.png";
        DevelopmentCard* roswell = new DevelopmentCard ("Roswell",{new ResourceToProduce{ResourceType::SCIENCE,1,CardType::NONETYPE}},relativePathTextureRoswell,new CardVictoryPoint{1, ResourceType::COLONEL},    CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}},{ResourceType::COLONEL},ResourceType::SCIENCE);
        returnValue.push_back(roswell);

        // Tombeau d alexandre
        std::string relativePathTextureTombeauDAlexandre = basePath + "tombeau_d_alexandre.png";
        DevelopmentCard* tombeauDAlexandre = new DevelopmentCard ("Tombeau d alexandre",{},relativePathTextureTombeauDAlexandre,new CardVictoryPoint{10, CardType::NONETYPE},CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::EXPLORATION, false},new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}},{ResourceType::COLONEL,ResourceType::COLONEL},ResourceType::GOLD);
        returnValue.push_back(tombeauDAlexandre);

        // Tresor de barbe noire -- created at the end

        // Tresor des templiers
        std::string relativePathTextureTresorDesTempliers = basePath + "tresor_des_templiers.png";
        DevelopmentCard* tresorDesTempliers = new DevelopmentCard ("Tresor des templiers",{new ResourceToProduce{ResourceType::GOLD,2, CardType::NONETYPE}},relativePathTextureTresorDesTempliers,new CardVictoryPoint{3, CardType::NONETYPE},CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}},{ResourceType::KRYSTALLIUM,ResourceType::KRYSTALLIUM},ResourceType::GOLD);
        returnValue.push_back(tresorDesTempliers);

        // Triangle des bermudes
        std::string relativePathTextureTriangleDesBermudes = basePath + "triangle_des_bermudes.png";
        DevelopmentCard* triangleDesBermudes = new DevelopmentCard ("Triangle des bermudes",{new ResourceToProduce{ResourceType::SCIENCE,1, CardType::NONETYPE}},relativePathTextureTriangleDesBermudes,new CardVictoryPoint{4, CardType::NONETYPE},CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}},{ResourceType::KRYSTALLIUM},ResourceType::SCIENCE);
        returnValue.push_back(triangleDesBermudes);


        /****************************************** Beginning of cards for testing games ******************************************/

        // Tour geante
        std::string relativePathTextureTourGeante = basePath + "tour_geante.png";
        DevelopmentCard* tourGeante = new DevelopmentCard ("Tour geante",{},relativePathTextureTourGeante,new CardVictoryPoint{10, (int) CardType::NONETYPE},CardType::PROJECT,1,{new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::GOLD, false}, new ResourceToPay{ResourceType::FINANCIER, false}},{},ResourceType::GOLD);
        returnValue.push_back(tourGeante);

        // Tresor de Barbe Noire
        std::string relativePathTextureTresorDeBarbeNoire = basePath + "tresor_de_barbe_noire.png";
        DevelopmentCard* tresorDeBarbeNoire = new DevelopmentCard ("Tresor de barbe noire",{new ResourceToProduce{ResourceType::GOLD,1,CardType::NONETYPE},new ResourceToProduce{ResourceType::EXPLORATION,1,CardType::NONETYPE}},relativePathTextureTresorDeBarbeNoire,new CardVictoryPoint{2, CardType::NONETYPE},CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::EXPLORATION, false},new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}},{},ResourceType::GOLD);
        returnValue.push_back(tresorDeBarbeNoire);

        // Zeppelin
        std::string relativePathTextureZeppelin = basePath + "zeppelin.png";
        for(int i = 0; i < 6; i++)
        {
            DevelopmentCard* zeppelin = new DevelopmentCard ("Zeppelin",{new ResourceToProduce{ResourceType::EXPLORATION,1, CardType::NONETYPE}},relativePathTextureZeppelin,new CardVictoryPoint{0, CardType::NONETYPE},CardType::VEHICLE,6,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}},{},ResourceType::EXPLORATION);
            returnValue.push_back(zeppelin);
        }

        // Ile d avalon
        std::string relativePathTextureIleDAvalon = basePath + "ile_d_avalon.png";
        DevelopmentCard* ileDAvalon = new DevelopmentCard ("Ile d avalon",{new ResourceToProduce{ResourceType::SCIENCE,1,CardType::NONETYPE}},relativePathTextureIleDAvalon,new CardVictoryPoint{7, CardType::NONETYPE},CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}},{},ResourceType::SCIENCE);
        returnValue.push_back(ileDAvalon);

        // Centre de la terre
        std::string relativePathTextureCentreDeLaTerre = basePath + "centre_de_la_terre.png";
        DevelopmentCard* centreDeLaTerre = new DevelopmentCard ("Centre De La Terre",{},relativePathTextureCentreDeLaTerre,new CardVictoryPoint{15, CardType::NONETYPE},CardType::DISCOVERY,1,{new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::EXPLORATION, false}, new ResourceToPay{ResourceType::COLONEL, false}, new ResourceToPay{ResourceType::COLONEL, false}},{},ResourceType::EXPLORATION);
        returnValue.push_back(centreDeLaTerre);

        // Brise glace
        for(int i = 0; i < 3; i++)
        {
            DevelopmentCard* briseGlace = new DevelopmentCard ("Brise glace",{new ResourceToProduce{ResourceType::EXPLORATION,2, CardType::NONETYPE}},relativePathTextureBriseGlace,new CardVictoryPoint{},CardType::VEHICLE,4,{new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::SCIENCE, false}},{},ResourceType::EXPLORATION);
            returnValue.push_back(briseGlace);
        }

        // Juggernaut
        std::string relativePathTextureJuggernaut = basePath + "juggernaut.png";
        DevelopmentCard* juggernaut = new DevelopmentCard ("Juggernaut",{new ResourceToProduce{ResourceType::EXPLORATION,2, CardType::NONETYPE}},relativePathTextureJuggernaut,new CardVictoryPoint{1, CardType::VEHICLE},CardType::VEHICLE,1,{new ResourceToPay{ResourceType::MATERIAL, false},new ResourceToPay{ResourceType::MATERIAL, false},new ResourceToPay{ResourceType::MATERIAL, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::ENERGY, false}, new ResourceToPay{ResourceType::KRYSTALLIUM, false}},{ResourceType::COLONEL,ResourceType::COLONEL},ResourceType::MATERIAL);
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

        std::string aztec_FaceA = "./resources/img/Cards/Empire_Face_A/Azteca.png";
        std::string aztec_FaceB = "./resources/img/Cards/Empire_Face_B/Azteca.png";

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
        
        std::string europe_FaceA = "./resources/img/Cards/Empire_Face_A/Europa.png";
        std::string europe_FaceB = "./resources/img/Cards/Empire_Face_B/Europa.png";
        
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