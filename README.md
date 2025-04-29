# dds

**dds (Data Distribution Service)** is a lightweight implementation designed for efficient and reliable communication in distributed systems. This project is written in C and focuses on simplicity and performance.

---

## Table of Contents

1. [Features](#features)
2. [Getting Started](#getting-started)
3. [Usage](#usage)
4. [Contributing](#contributing)
5. [License](#license)

---

## Features

- Lightweight and efficient implementation of DDS.
- TCP-based transport layer for reliable communication.
- Discovery service for registering and looking up endpoints.
- Designed for simplicity and extensibility.

---

## Getting Started

### Prerequisites

Make sure you have the following installed:

- A C compiler (e.g., GCC or Clang)
- `make` build system

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/luzizheng/dds.git
   cd dds
   ```

2. Build the project:
   ```bash
   make
   ```

### Running the Example

- After building, you can run the generated executable:
  ```bash
  ./dds
  ```

---

## Usage

This project includes the following core components:

### Transport Layer
The transport layer provides TCP-based messaging functionality. You can use it to send and receive messages across your distributed system.

### Discovery Service
The discovery service is responsible for registering and looking up endpoints. It uses Minix IPC for communication between components.

---

## Contributing

We welcome contributions from the community! Here’s how you can help:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Make your changes and commit them (`git commit -m "Add some feature"`).
4. Push your changes to the branch (`git push origin feature-branch`).
5. Open a pull request.

---

## License

This project is currently not licensed. If you'd like to contribute a license, feel free to open an issue or pull request.

---

## Acknowledgments

Special thanks to all contributors and the open-source community for their efforts in enhancing distributed communication systems.