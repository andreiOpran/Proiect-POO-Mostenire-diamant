# Car Dealership Management Project

## Main Classes

### Vehicle
Base class for vehicles, implementing `IOInterfaceVehicul` and `InterfataVehicul`. Contains attributes such as brand, model, manufacture year, availability, and price.

### FuelVehicle
Extends `Vehicle` and adds attributes specific to fuel vehicles, such as fuel type and consumption.

### ElectricVehicle
Extends `Vehicle` and adds attributes for electric vehicles, such as electric range and charging time.

### HybridVehicle
Extends `FuelVehicle` and `ElectricVehicle` and adds attributes for hybrid vehicles, such as hybrid type.

### Showroom
Class for managing showrooms, with methods to set and get the showroom name, address, and list of available vehicles.

### Client
Class for managing clients, with methods to set and get the name, remaining payment, credit limit, and purchased vehicles.

### Transaction
Class for managing transactions, with methods to set and get the client, purchased vehicle, and paid amount.

## Main Features

- **Interactive Menu:** Allows users to interact with the application in an easy and intuitive way.
- **Inheritance:** Implements inheritance between classes to ensure code reuse and logical organization.
  - **Diamond Inheritance:** The project uses diamond inheritance to demonstrate multiple inheritance and resolve ambiguity.
  - **Parent-Child-Grandchild Hierarchy:** The project uses a three-level inheritance hierarchy with parent, child, and grandchild classes.
- **Use of STL:** Utilizes standard collections (vector) for data management.
- **Upcasting and Downcasting:** Uses `dynamic_cast` for safe upcasting and downcasting between class types.

***

![image](https://github.com/AndreiFishe/Proiect-2-POO-Dealer-auto/assets/116067445/4d2eb124-f3a1-4d20-aaac-37f28b22eee4)

