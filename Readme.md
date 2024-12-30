# WiFi Communication Simulator

This project simulates WiFi communication models for **WiFi 4 (CSMA/CA)**, **WiFi 5 (MU-MIMO)**, and **WiFi 6 (OFDMA)**. The simulation calculates **throughput**, **average latency**, and **maximum latency** based on various parameters like the number of users, channel bandwidth, and backoff time. It uses object-oriented programming principles such as **inheritance**, **polymorphism**, **data hiding**, and **templates**.

## Table of Contents

- [Installation and Setup](#installation-and-setup)
  - [Running `setup.sh`](#running-setupsh)
  - [Makefile](#makefile)
- [Usage](#usage)
  - [Running the Program](#running-the-program)
  - [Examples](#examples)
- [Simulation Output](#simulation-output)
  - [Throughput, Average and Max Latency](#throughput-average-and-max-latency)
- [Object-Oriented Concepts](#object-oriented-concepts)
  - [Classes, Templates, and Polymorphism](#classes-templates-and-polymorphism)
  - [Smart Pointers and STL Containers](#smart-pointers-and-stl-containers)
- [UML Diagram](#uml-diagram)

## Installation and Setup

### Running `setup.sh`

To set up the project structure, run the provided `setup.sh` script. This will organize all the required directories and move the source files into the appropriate folders.

1. **Make the script executable**:

   ```bash
   chmod +x setup.sh
   ```

2. **Run the setup script**:
   ```bash
   ./setup.sh
   ```

This will create the following directories:

- [build](http://_vscodecontentref_/1) - for compiled object files and executables
- [src](http://_vscodecontentref_/2) - for the source `.cpp` files
- [include](http://_vscodecontentref_/3) - for header `.h` files

### Makefile

The provided [Makefile](http://_vscodecontentref_/4) is configured to build the project for both Linux and Windows environments.

- **To build the project**:

  ```bash
  make
  ```

- **To build with debugging symbols**:

  ```bash
  make debug
  ```

- **To build with optimizations**:

  ```bash
  make optimized
  ```

- **To clean build files**:
  ```bash
  make clean
  ```

The [Makefile](http://_vscodecontentref_/5) will handle the compilation of all source files and link them into an executable. It uses the `g++` compiler for compilation.

## Usage

### Running the Program

Once the setup is complete, you can run the program as follows:

1. **Build the project** using the [Makefile](http://_vscodecontentref_/6):

   ```bash
   make
   ```

2. **Run the executable**:

   ```bash
   ./build/WifiSimulator
   ```

3. The program will display a menu where you can select one of the three WiFi communication types (WiFi 4, WiFi 5, or WiFi 6), input the number of users, and simulate the communication.

### Examples

Let's say you run the program and choose **WiFi 4**, then input **1 user** and **10 users** for the simulation.

1. **For 1 user**:

   - **WiFi 4** will simulate the communication for a single user, checking if the channel is free (using CSMA/CA). The throughput will be calculated by dividing the data transmitted by the total time taken.
   - **WiFi 5** will simulate multiple user communication with MU-MIMO, and the throughput will reflect the shared use of the channel after channel state information (CSI) is exchanged.
   - **WiFi 6** uses OFDMA to subdivide the channel, allowing more efficient transmission, and throughput will depend on how the sub-channels are assigned.

2. **For 10 users**:
   - The **WiFi 4** throughput will likely decrease compared to 1 user due to channel contention and backoff times.
   - In **WiFi 5**, multiple users will communicate in parallel after the CSI exchange, affecting throughput and latency.
   - **WiFi 6** with OFDMA will allow for more parallel transmissions and better resource management, resulting in a better throughput compared to the other two.

### Simulation Output

#### Throughput, Average, and Max Latency

##### Throughput Formula:

Throughput is calculated using the formula:
\[ \text{Throughput} = \frac{\text{Total Data Transmitted (bits)}}{\text{Total Time (seconds)}} \]

- **Total Data** = Number of Packets \(\times\) Packet Size (in bits)
- **Total Time** = Time of last transmission - Time of first transmission

##### Average Latency:

Average latency is the mean of the latencies of all transmitted packets, calculated as:
\[ \text{Average Latency} = \frac{\text{Total Latency}}{\text{Number of Packets Transmitted}} \]

- **Total Latency** is the sum of the latency for each packet transmission.

##### Maximum Latency:

Maximum latency is simply the maximum value among the latencies recorded for all transmissions.

### Bandwidth and Other Information

- **Bandwidth**: 20 MHz
- **Modulation**: 256-QAM
- **Coding Rate**: 5/6
- **Packet Size**: 1 KB
- **WiFi 4**: Uses CSMA/CA for channel access.
- **WiFi 5**: Uses MU-MIMO for parallel transmission after CSI exchange.
- **WiFi 6**: Uses OFDMA to subdivide the channel into units of 2 MHz, 4 MHz, or 10 MHz for parallel transmission.

## Object-Oriented Concepts

### Classes, Templates, and Polymorphism

- **Classes**: The project uses multiple classes like `AccessPoint`, `Channel`, `User`, `Packet`, and `Simulator` to model the various components of the WiFi communication system.
- **Templates**: Templates are used to handle different data types and allow flexibility in the implementation of functions like `calculateThroughput()`.
- **Polymorphism**: The `Simulator` class is used as a base class, and the derived classes `WiFi4Simulator`, `WiFi5Simulator`, and `WiFi6Simulator` implement their specific simulation behavior using **method overriding**.

### Smart Pointers and STL Containers

- **Smart Pointers**: The program uses `std::shared_ptr<User>` for memory management, ensuring that user objects are properly deleted when no longer needed.
- **STL Containers**: `std::vector` and `std::map` are used to store users and manage backoff times in the simulations.

### Why These Concepts and Libraries?

- **Data Hiding**: The implementation of classes encapsulates the logic related to communication (e.g., channel access, user management) and exposes only necessary methods (e.g., `manageDataFlow()`, `isChannelAvailable()`), maintaining data hiding and modularity.
- **Polymorphism**: Allows the simulation logic to be extended easily with new types of communication models (like WiFi 7) by adding new derived classes from `Simulator`.
- **Templates**: Enhance code reusability and flexibility, especially in calculating metrics like throughput, without worrying about the underlying types.
- **STL and Smart Pointers**: Using `std::shared_ptr` avoids manual memory management and ensures proper cleanup. `std::vector` and `std::map` help with dynamic data storage, providing efficient access and storage for simulation data.

## UML Diagram

Below is a UML diagram that shows the inheritance hierarchy of the `WiFiSimulator` classes:

```plaintext
+------------------+
|    Simulator     |
+------------------+
         ^
         |
+------------------+
| WiFi4Simulator   |
+------------------+
         ^
         |
+------------------+
| WiFi5Simulator   |
+------------------+
         ^
         |
+------------------+
| WiFi6Simulator   |
+------------------+
```
