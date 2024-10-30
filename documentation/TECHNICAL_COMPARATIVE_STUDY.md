# Technical and Comparative Study

This document presents a technical and comparative analysis of the architectural and design choices made in our project. We examine the Entity-Component-System (ECS) architecture, the Mediator design pattern, the SFML graphics library, networking techniques, entity spawning algorithms, storage methods, and security considerations.

## ECS Architecture

### Choice: Entity-Component-System (ECS)

- **Advantages**:
  - **Separation of Concerns**: ECS allows distinct responsibilities for entities, components, and systems, enhancing modularity and maintainability.
  - **Performance**: By processing similar components in batches, ECS optimizes memory access, reducing cache misses.
  - **Flexibility**: New components can be added or removed without altering existing class hierarchies.

- **Alternatives**:
  - **Object-Oriented Programming (OOP)**:
    - **Advantages**: Familiar to many developers; good for smaller projects.
    - **Disadvantages**: Can lead to tightly coupled classes, making code harder to maintain and extend.
  - **Data-Oriented Design (DOD)**:
    - **Advantages**: Focuses on data layout and cache efficiency, potentially leading to better performance.
    - **Disadvantages**: May increase complexity and require a steep learning curve.

### Conclusion:
ECS was selected due to its modularity and performance benefits, making it particularly suitable for larger projects.

## Design Pattern: Mediator

### Choice: Mediator Pattern

- **Advantages**:
  - **Reduced Dependencies**: Centralizes communication, minimizing direct interactions between objects.
  - **Maintainability**: Simplifies debugging and enhances scalability, allowing easy integration of new features.

- **Alternatives**:
  - **Observer Pattern**:
    - **Advantages**: Facilitates one-to-many relationships and is useful for event-driven architectures.
    - **Disadvantages**: Can lead to complex dependencies and unmanageable callback chains.
  - **Command Pattern**:
    - **Advantages**: Encapsulates requests as objects, providing flexibility in handling commands.
    - **Disadvantages**: Increases the number of classes and can complicate the architecture.

### Conclusion:
The Mediator pattern was chosen for its ability to streamline interactions and reduce coupling, which is crucial in a complex system.

## C++ SFML Graphics Library

### Choice: SFML Library

- **Advantages**:
  - **Ease of Use**: Provides a straightforward API for 2D graphics, making it beginner-friendly.
  - **Community Support**: Well-documented and widely used in educational settings, particularly in Epitech.

- **Alternatives**:
  - **SDL (Simple DirectMedia Layer)**:
    - **Advantages**: More mature library with extensive platform support and capabilities for both 2D and 3D graphics.
    - **Disadvantages**: More complex API that may require a steeper learning curve.
  - **OpenGL**:
    - **Advantages**: Offers greater control over graphics rendering and is more suited for 3D applications.
    - **Disadvantages**: More complex, requiring knowledge of shaders and lower-level graphics programming.

### Conclusion:
SFML was chosen for its simplicity and suitability for 2D games, aligning well with the project's educational context.

## Networking Techniques

### Choice: UDP with Binary Protocols

- **Advantages**:
  - **Speed and Efficiency**: UDP's connectionless nature reduces overhead, making it ideal for real-time applications.
  - **Compact Data Representation**: Binary protocols minimize data size, leading to lower latency and reduced bandwidth usage.

- **Alternatives**:
  - **TCP (Transmission Control Protocol)**:
    - **Advantages**: Guarantees delivery and order of packets, ensuring data integrity.
    - **Disadvantages**: Higher overhead due to connection establishment and error-checking mechanisms, making it less suitable for real-time applications.
  - **Text-Based Protocols (e.g., JSON over HTTP)**:
    - **Advantages**: Human-readable and easier to debug.
    - **Disadvantages**: Larger data size and increased latency due to parsing overhead.

### Conclusion:
UDP combined with binary protocols was selected for its performance advantages in real-time gaming scenarios.

## Algorithms: Entity Spawning

### Choice: Simple Spawn Algorithm

- **Advantages**:
  - **Simplicity**: Easy to implement and maintain, allowing for straightforward adjustments to enemy spawn rates.
  - **Controlled Difficulty**: Provides a predictable challenge for players, enhancing gameplay balance.

- **Alternatives**:
  - **Complex Spawn Algorithms (e.g., Wave Spawning)**:
    - **Advantages**: Creates varied gameplay experiences and can adapt to player performance.
    - **Disadvantages**: More complex to implement and may require additional tuning for balance.

### Conclusion:
The simple spawn algorithm was chosen for its clarity and ease of integration, making it suitable for the current development phase.

## Storage Methods

### Choice: libconfig for Configuration Storage

- **Advantages**:
  - **Structured Data Management**: Enables easy reading and writing of configuration data.
  - **Flexibility**: Supports various data types, allowing for diverse configuration needs.

- **Alternatives**:
  - **JSON or XML**:
    - **Advantages**: Human-readable and widely supported.
    - **Disadvantages**: Parsing overhead and potential for data manipulation risks.

### Conclusion:
Libconfig was selected for its straightforward handling of configuration data, allowing efficient management of game settings.

## Security

### Choice: Binary Protocol with Encryption

- **Advantages**:
  - **Obfuscation**: The binary format is less human-readable, complicating unauthorized data interception.
  - **Injection Protection**: Fixed-size fields reduce the risk of injection attacks common in text-based protocols.

- **Alternatives**:
  - **Text-Based Protocols with Encryption**:
    - **Advantages**: Easier to debug and test.
    - **Disadvantages**: More susceptible to injection attacks and larger data sizes.

### Conclusion:
The binary protocol, combined with encryption mechanisms like TLS/SSL, was chosen for its security benefits, particularly in protecting data integrity and confidentiality.

