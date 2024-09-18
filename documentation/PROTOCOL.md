# Protocol communication

## Introduction

This document describes the protocol used to communicate between the server and the client.

## Protocol

Protocol must be binary, it means that all messages are sent in binary format.

### Message structure

Each message is composed by an ID and a content.

The ID is a 4 bytes unsigned integer that represents the message type.

```cpp
unsigned int id;
```

The content is a array of bytes that represents the message data such as `std::string`

```cpp
std::string content;
```

Message structure:

```cpp
class BinaryMessage {
    public:
        unsigned int id;
        std::string content;
};
```