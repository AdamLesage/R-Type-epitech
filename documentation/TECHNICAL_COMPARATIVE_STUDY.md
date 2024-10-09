## ECS Choice

Using an **Entity-Component-System** (ECS) architecture provides a clear separation of concerns, allowing for greater flexibility and reusability. This modular design enables components to be easily added or removed from entities without being tied to specific classes. Additionally, ECS improves performance by allowing systems to process similar components in batches, optimizing memory access and reducing cache misses. Overall, adopting ECS results in a more organized and efficient game development process.
We decided to choose this architecture for our project because it was the best architecture to use in continuing to the bootstrap.

## Design Pattern

### Mediator

The **Mediator** is a behavioral design pattern that lets you reduce chaotic dependencies between objects. The pattern restricts direct communications between the objects and forces them to collaborate only via a mediator object. In this project, the Mediator design pattern was implemented to streamline communication between engines. By centralizing interactions through a mediator, we reduced direct dependencies between components, simplifying the architecture and enhancing maintainability. This approach not only facilitates easier debugging and testing but also allows for greater scalability; new features can be added with minimal impact on existing code. Overall, the use of the Mediator pattern promotes a more organized and efficient codebase, aligning with best practices in software design.

## C++ SFML

In C++ there a many graphics library which all have advantages. Some will be better for 3Dimensions project, some will be easier to use, some will be newer, some will be older. For this project we choose to use the SFML library. The main advantage of this library is its ease of use. This library is also very optimal for 2Dimensions project like the R-Type. Finally, as Epitech student we also have used this library for many projects during our two first years.

## Networking Techniques

UDP (User Datagram Protocol) combined with binary protocols offers significant advantages for networking techniques, particularly in scenarios demanding speed and efficiency. Unlike TCP, UDP is connectionless, reducing overhead by eliminating the need for handshakes and ensuring faster data transmission, making it ideal for real-time applications such as online gaming. Binary protocols further enhance performance by using a compact data representation, minimizing the amount of data transmitted over the network. This combination leads to lower latency, reduced bandwidth usage, and improved overall performance, making UDP and binary protocols optimal choices for high-speed, resource-sensitive networking environments.

## Algorithms

### Spawn of entities

### Boss

## Storage

In a video game like the R-type there are many information and assets that you need to store (Image, sound, font, configuration file). Most of them can be stored in different formats which will not really influence our code. However, for the configuration we chose to use the libconfig library. The libconfig will allow us to store our data in a **.cfg** file and use multiple function that will help us read those files.

## Security
