# Protocol Documentation

### Introduction

This document describes the protocol used to communicate between the server and the client.

# Server-to-Client Protocol


## Player Creation
| Type  | Player ID   | Position X   | Position Y   |
|-------|-------------|--------------|--------------|
| 0x01  | 0x00000001  | 0x42f60000   | 0x42960000   |

- **Type:** 1 byte (0x01 for "player creation").
- **Player ID:** 4 bytes (e.g., 0x00000100 for a player with this ID).
- **Position X:** 4 bytes (e.g., 0x42e00000 for X position of 112.0).
- **Position Y:** 4 bytes (e.g., 0x41a00000 for Y position of 20.0).



## Projectile Creation
| Type  | Projectile ID | Position X   | Position Y   | Parent ID   |
|-------|---------------|--------------|--------------|-------------|
| 0x02  | 0x00000001    | 0x42f60000   | 0x42960000   | 0x00000001  |

- **Type:** 1 byte (0x02 for "projectile creation").
- **Projectile ID:** 4 bytes (e.g., 0x00000100 for a projectile with this ID).
- **Position X:** 4 bytes (e.g., 0x42e00000 for X position of 112.0).
- **Position Y:** 4 bytes (e.g., 0x41a00000 for Y position of 20.0).
- **Parent ID:** 4 bytes.



## Enemy Creation
| Type  | Enemy ID     | Position X   | Position Y   |
|-------|--------------|--------------|--------------|
| 0x03  | 0x00000001   | 0x42f60000   | 0x42960000   |

- **Type:** 1 byte (0x03 for "enemy creation").
- **Enemy ID:** 4 bytes (e.g., 0x00000100 for an enemy with this ID).
- **Position X:** 4 bytes (e.g., 0x42e00000 for X position of 112.0).
- **Position Y:** 4 bytes (e.g., 0x41a00000 for Y position of 20.0).
#### From 0x03 to 0x20

## Bonus Creation
| Type  | Bonus ID     | Position X   | Position Y   |
|-------|--------------|--------------|--------------|
| 0x21  | 0x00000001   | 0x42f60000   | 0x42960000   |

- **Type:** 1 byte (0x21 for "bonus creation").
- **Bonus ID:** 4 bytes (e.g., 0x00000100 for a bonus with this ID).
- **Position X:** 4 bytes (e.g., 0x42e00000 for X position of 112.0).
- **Position Y:** 4 bytes (e.g., 0x41a00000 for Y position of 20.0).
#### From 0x21 to 0x24

## Wall Creation
| Type  | Wall ID      | Position X   | Position Y   | Size X      | Size Y      |
|-------|--------------|--------------|--------------|-------------|-------------|
| 0x25  | 0x00000001   | 0x42f60000   | 0x42960000   | 0x42f60000  | 0x42960000  |

- **Type:** 1 byte (0x25 for "wall creation").
- **Wall ID:** 4 bytes (e.g., 0x00000100 for a wall with this ID).
- **Position X:** 4 bytes (e.g., 0x42e00000 for X position of 112.0).
- **Position Y:** 4 bytes (e.g., 0x41a00000 for Y position of 20.0).
- **Size X:** 4 bytes.
- **Size Y:** 4 bytes.


## Reward Creation
| Type  | Reward ID    | Position X   | Position Y   | Size X      | Size Y      |
|-------|--------------|--------------|--------------|-------------|-------------|
| 0x26  | 0x00000001   | 0x42f60000   | 0x42960000   | 0x42f60000  | 0x42960000  |

- **Type:** 1 byte (0x26 for "reward creation").
- **Reward ID:** 4 bytes.
- **Position X:** 4 bytes.
- **Position Y:** 4 bytes.
- **Size X:** 4 bytes.
- **Size Y:** 4 bytes.

#### From 0x26 to 0x28


## Entity Deletion
| Type  | Entity ID    | ExtraData (Worth of the killed entity) |
|-------|--------------|----------------------------------------|
| 0x29  | 0x00000001   |           0x0000000000001234           |

- **Type:** 4 byte (0x29 for "entity deletion").
- **Entity ID:** 4 bytes (e.g., 0x00000100 for an entity with this ID).

## Position Update
| Type  | Entity ID    | Position X   | Position Y   |
|-------|--------------|--------------|--------------|
| 0x30  | 0x00000200   | 0x43160000   | 0x428c0000   |

- **Type:** 1 byte (0x30 for "position update").
- **Entity ID:** 4 bytes.
- **Position X:** 4 bytes.
- **Position Y:** 4 bytes.


## Health Update
| Type  | Entity ID    | Health Points |
|-------|--------------|---------------|
| 0x31  | 0x00000001   | 0x00000064    |

- **Type:** 1 byte (0x31 for "health update").
- **Entity ID:** 4 bytes.
- **Health Points:** 4 bytes.


## Direction Update
| Type  | Entity ID    | Direction X  | Direction Y  |
|-------|--------------|--------------|--------------|
| 0x32  | 0x00000001   | 0x42c80000   | 0x42960000   |

- **Type:** 1 byte (0x32 for "direction update").
- **Entity ID:** 4 bytes.
- **Direction X:** 4 bytes (float).
- **Direction Y:** 4 bytes (float).


## Object Collection
| Type  | Player ID    | Object ID    |
|-------|--------------|--------------|
| 0x33  | 0x00000001   | 0x00000002   |

- **Type:** 1 byte (0x33 for "object collection").
- **Player ID:** 4 bytes.
- **Object ID:** 4 bytes.


## Projectile Firing
| Type  | Shooter ID   | Position X   | Position Y   |
|-------|--------------|--------------|--------------|
| 0x34  | 0x00000001   | 0x42f60000   | 0x42960000   |

- **Type:** 1 byte (0x34 for "projectile firing").
- **Shooter ID:** 4 bytes.
- **Position X:** 4 bytes.
- **Position Y:** 4 bytes.


## Projectile Collision
| Type  | Projectile ID| Entity ID    |
|-------|--------------|--------------|
| 0x35  | 0x00000002   | 0x00000001   |

- **Type:** 1 byte (0x35 for "projectile collision").
- **Projectile ID:** 4 bytes.
- **Entity ID:** 4 bytes.


## Score Update
| Type  | Player ID    | New Score    |
|-------|--------------|--------------|
| 0x36  | 0x00000001   | 0x000003E8   |

- **Type:** 1 byte (0x36 for "score update").
- **Player ID:** 4 bytes.
- **New Score:** 4 bytes.


## State Change
| Type  | Entity ID    | New State    |
|-------|--------------|--------------|
| 0x37  | 0x00000001   | 0x00000002   |

- **Type:** 1 byte (0x37 for "state change").
- **Entity ID:** 4 bytes.
- **New State:** 4 bytes.


## Player Death
| Type  | Entity ID    |
|-------|--------------|
| 0x38  | 0x00000001   |

- **Type:** 1 byte (0x38 for "player Death").
- **Entity ID:** 4 bytes.


## Number connected player
| Type  | Number Player |
|-------|---------------|
| 0x39  | 0x00000001    |

- **Type:** 1 byte (0x39 for "Number player").
- **number player:** 4 bytes.

## Level update
| Type  | New Level     |
|-------|---------------|
| 0x3a  | 0x00000001    |

- **Type:** 1 byte (0x3a for "New Level").
- **New Level:** 4 bytes.

## Calculate network latency
| Type |      Ping      |
| 0x99 | 0x000003E8     |
- **Type:** 1 byte (0x99 for "Ping").
- **ping:** 4 bytes.

# Client-to-Server Protocol: Player Input and Start Game

This protocol defines how the client communicates player input and game start requests to the server.

## 1. Player Input
This message is used by the client to send the player's inputs, such as movement or actions (e.g., firing a weapon).

| Byte Offset | Field Name  | Size (in bytes) | Description                                                  |
|-------------|--------------|-----------------|--------------------------------------------------------------|
| 0           | Message Type | 1               | **0x40** (Player Input)                                       |
| 1           | Player ID    | 4               | Unique ID of the player sending the input (e.g., 0x00000100). |
| 5           | Input Flags  | 1               | Flags representing the input: movement, actions, etc.         |

### Example:
| **0x40** | **0x00000100** | **0x01** | **0x00000FA0** | **0x42C80000** | **0x42960000** |
- **0x40:** Type (Player Input).
- **0x00000100:** Player ID (e.g., player with ID 1).
- **0x01:** Input flags (ascii number).

## 2. Start Game
This message is sent from the client to the server when the player is ready to start a new game.

| Byte Offset | Field Name   | Size (in bytes) | Description                                                   |
|-------------|--------------|-----------------|---------------------------------------------------------------|
| 0           | Message Type | 1               | **0x41** (Start Game)                                          |
| 1           | Player ID    | 4               | Unique ID of the player requesting to start the game.          |

### Example:
| **0x41** | **0x00000100** | **0x01** | **0x00000FA0** |
- **0x41:** Type (Start Game).
- **0x00000100:** Player ID.

## Enemy Creation 
| Type  | Entity Type  | Position X   | Position Y   |
|-------|--------------|--------------|--------------|
| 0x42  |     0x03     | 0x42f60000   | 0x42960000   |

- **Type:** 1 byte (0x43 for "enemy creation").
- **Entity Type:** 1 byte (0x03 for "basic ennemy").
- **Position X:** 4 bytes (e.g., 0x42e00000 for X position of 112.0).
- **Position Y:** 4 bytes (e.g., 0x41a00000 for Y position of 20.0).
#### From 0x03 to 0x20

## Entity Deletion
| Type  | Entity ID    |
|-------|--------------|
| 0x43  | 0x00000001   |

- **Type:** 1 byte (0x43 for "entity deletion").
- **Entity ID:** 4 bytes (e.g., 0x00000100 for an entity with this ID).

## Entity Wave Creation
| Type  |
|-------|
| 0x44  |

- **Type:** 1 byte (0x44 for "Entity Wave Creation").

## Godmode enable/disable 
| Type  | enable/disable |
|-------|----------------|
| 0x45  |   0x01 0x02    |

- **Type:** 1 byte (0x45 for "Godmode enable/disable ").
- **enable/disable:** 1 byte (0x01 for "enable" 0x02 for "disable").

## set shoot speed 
| Type  | speed |
|-------|-------|
| 0x46  | > 0.1 |

- **Type:** 1 byte (0x46 for "set shoot speed ").
- **speed:** 4 bytes (0x41a00000 for a speed of 20.0).

## Player Teleportation 
| Type  | Position X   | Position Y   |
|-------|--------------|--------------|
| 0x47  | 0x42f60000   | 0x42960000   |

- **Type:** 1 byte (0x47 for "Player Telportation").
- **Position X:** 4 bytes (e.g., 0x42e00000 for X position of 112.0).
- **Position Y:** 4 bytes (e.g., 0x41a00000 for Y position of 20.0).

## set lives 
| Type  | lives |
|-------|-------|
| 0x48  |  >10  |

- **Type:** 1 byte (0x48 for "set lives").
- **speed:** 4 bytes (0x41a00000 for 20hp / 2 lives).
