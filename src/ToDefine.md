# To define

## Structure

- A resourceToPay struture. This is in a vector in each card to know what needs to be paid, and what is already paid. This structure contains :
  
  - ResourceType : resource. This is the resource to pay.
  
  - bool isPaid. Define if the player paid for this resource.

- A resourceToProduct structure. This is in a vector in each card to know what needs to be produce by turn. This structure contains :
  
  - ResourceType : resource. This is the resource to get.
  
  - int: quantity. Quantity of this ressource.
  
  - CardType : cardType. This is the card type needed to get this resource. The rule is one by built card of this type.

- A cardVictoryPoint structure. This contains the information concerning the victory points that may be won by this card. It contains :
  
  - int : numberOfPoints. This is the number of flat points that you earn whn it's build.
  
  - int : cardOrResourceType. We will make a static cast from resources / card type (or 0 if no condition).
