# Philosophers Project

## Overview

The **Philosophers** project from 42 School simulates a classic problem where multiple philosophers sit around a dining table, trying to eat while sharing a limited number of forks. The goal of the project is to implement a simulation of philosophers who either **think**, **eat**, or **sleep**, while ensuring proper synchronization and avoiding issues like **deadlock** and **starvation**.

## Problem Description

You are tasked with implementing a program that simulates the dining philosophers problem using **threads** and **mutexes**. Each philosopher alternates between thinking, eating, and sleeping. To eat, a philosopher must first take two forks, one on their left and one on their right. However, no two philosophers can eat simultaneously if they share a fork. Your program must ensure that:

- Philosophers do not starve (i.e., all philosophers get a chance to eat).
- Philosophers avoid deadlock (i.e., a state where all philosophers are waiting for forks indefinitely).
- The program should be optimized for performance and be capable of simulating many philosophers at once.

## Requirements

- **Philosopher struct**: You need to implement a `philosopher` structure containing attributes such as their current state (thinking, eating, sleeping), the time they last ate, their fork locks, etc.
- **Mutexes**: Each philosopher has a mutex for each fork, which they lock and unlock when they pick up and put down forks.
- **Thread synchronization**: Use `pthread` to create and manage threads, ensuring that philosophers take turns eating and avoid race conditions.
- **Fork pickup logic**: Philosophers can only eat if they have both forks, and each fork is shared between two philosophers.

## Features

- **Simulation of philosophers’ behaviors**: Philosophers alternate between thinking, eating, and sleeping.
- **Thread synchronization**: Properly implemented using **pthread_mutex** to avoid race conditions and ensure mutual exclusion.
- **Deadlock avoidance**: The program prevents the philosophers from entering a deadlock state where no philosopher can proceed.
- **Starvation avoidance**: Ensures all philosophers get a chance to eat.
- **Time management**: The program manages the time for each action (eating, sleeping) using `usleep` and `gettimeofday`.

## Functionality

The program accepts the following parameters:

1. **Number of philosophers**: The number of philosophers participating in the simulation.
2. **Time to die**: The time in milliseconds after which a philosopher will die if they haven’t eaten.
3. **Time to eat**: The time in milliseconds a philosopher spends eating.
4. **Time to sleep**: The time in milliseconds a philosopher spends sleeping.
5. **Maximum meals** (optional): The maximum number of meals a philosopher should eat before stopping.

## Requirements for Compilation

- A **C compiler** that supports C99 or later (e.g., `gcc`).
- **pthread** library for managing threads and synchronization.

## How to Compile and Run

To compile and run the program, follow these steps:

1. Clone the repository or create the project files.
2. Compile the program using the following command:

   ```bash
   gcc -pthread philosophers.c -o philosophers
   ```

3. Run the program by passing the required arguments. For example:

   ```bash
   ./philosophers 5 800 200 200
   ```

   In this example, there are 5 philosophers, each philosopher dies after 800 milliseconds if they haven't eaten, and they will eat for 200 milliseconds and sleep for 200 milliseconds.

## Example Output

```bash
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
0 1 is sleeping
0 1 is thinking
...
```

## Key Concepts

- **Multithreading**: Using `pthread_create` and `pthread_join` to manage multiple philosophers.
- **Mutexes**: Each fork is represented by a mutex, and the philosopher locks the mutexes for the left and right forks when eating.
- **Deadlock Prevention**: We prevent philosophers from getting stuck in a situation where they can't eat because of missing forks.
- **Starvation Avoidance**: The system ensures that no philosopher is deprived of food for an extended period.
