# To define

## Structure

- A resourceToPay struture. This is in a vector in each card to know what needs to be paid, and what is already paid. This structure contains :
  
  - *Resource : resource. This is the resource to pay.
  
  - bool isPaid. Define if the player paid for this resource.

- A resourceToProduct structure. This is in a vector in each card to know what needs to be produce by turn. This structure contains :
  
  - *Resource : resource. This is the resource to get.
  
  - int: quantity. Quantity of this ressource.
  
  -  CardType : cardType. This is the card type needed to get this resource. The rule is one by built card of this type.

- A cardVictoryPoint structure. This contains the information concerning the victory points that may be won by this card. It contains :
  
  - int : flatPoint. This is the number of flat points that you earn whn it's build.
  
  - vector<pointByCardType> (structure that contains - numberOfPoints, CardType). This is when you have a card that says you win n point for each n type of card. Flat points are linked to the NoneType of the enum.
  
  - vector <pointByResourceType> (structure that contains - numberOfPoints, ResourceType). This is when you have a card that says you win n point for each resource that you have at the end.


