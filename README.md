# Philosophers

<div align="right">

[![GitHub stars](https://img.shields.io/github/stars/oliverkingz/philosophers?color=brightgreen)]()
[![Visits Badge](https://badges.pufler.dev/visits/oliverkingz/philosophers)]()
[![Created Badge](https://badges.pufler.dev/created/oliverkingz/philosophers)]()
[![Updated Badge](https://badges.pufler.dev/updated/oliverkingz/philosophers)]()

</div>

[**42-Cursus**] This project is a simulation of the classic "Dining Philosophers" problem, where philosophers sit around a table and alternate between eating, thinking, and sleeping. The goal is to prevent deadlocks and ensure that no philosopher starves. The project is implemented using threads and mutexes in C, with an optional bonus using processes and semaphores.

Keywords

- **Threads**
- **Mutexes**
- **Deadlock Prevention**
- **Processes**
- **Semaphores**
- **C Programming**
- **Synchronization**
- **Simulation**

<div align="right">
  
Made by: [![Contributors Display](https://badges.pufler.dev/contributors/oliverkingz/philosophers?size=30&padding=5&perRow=10&bots=true)](https://github.com/OliverKingz)

</div>

---

## Index

- [Overview](#overview)
- [Features](#features)
- [Bonus Features](#bonus-features-not-done)
- [Requirements](#requirements)
- [How to Run](#how-to-run)
  - [Example Usage](#example-usage)
  - [Bonus Usage](#bonus-usage)
  - [Error Handling](#error-handling-and-testing)
- [What I Learned](#what-i-learned)
- [Author](#author)
- [Acknowledgments](#acknowledgments)

---

## Overview

The Philosophers project is a simulation of the classic Dining Philosophers problem, a well-known concurrency problem in computer science. The goal is to manage multiple threads (philosophers) that share resources (forks) without causing deadlocks or starvation. The project is implemented in C using threads and mutexes for the mandatory part, and processes and semaphores for the bonus part. The simulation stops when a philosopher dies of starvation or when all philosophers have eaten a specified number of times.

---

## Features

- **Thread Management**: Each philosopher is represented by a separate thread.
- **Mutex Synchronization**: Forks are protected by mutexes to prevent race conditions.
- **State Logging**: The program logs the state of each philosopher (eating, sleeping, thinking) with timestamps.
- **Deadlock Prevention**: The program ensures that no deadlock occurs by carefully managing the order in which philosophers pick up forks.
- **Starvation Prevention**: The program ensures that no philosopher starves by enforcing a maximum time between meals.

---

## Bonus Features (Not done)

- **Process Management**: The bonus part uses processes instead of threads.
- **Semaphore Synchronization**: Forks are managed using semaphores.
- **Centralized Fork Management**: Forks are placed in the center of the table, and their availability is managed by a semaphore.

---

## Requirements

- The project must be written in C.
- No memory leaks are allowed.
- The program must handle errors gracefully and avoid undefined behavior.
- The program must follow the 42 Norm, which includes specific formatting and coding standards.

---

## How to Run

1. Clone this repository:
   ```bash
   git clone [repository-url]
   cd philosophers
   ```
2. Compile the project:
   ```bash
   make
   ```
3. Run the project:
   ```bash
   ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
   ```

### Example Usage

| **Input Command**         | **Description**                                                               | **Expected Output**                                            |
| ------------------------- | ----------------------------------------------------------------------------- | -------------------------------------------------------------- |
| `./philo 5 800 200 200`   | 5 philosophers, die after 800ms, eat for 200ms, sleep for 200ms.              | Philosophers alternate between eating, sleeping, and thinking. |
| `./philo 3 400 100 100 5` | 3 philosophers, die after 400ms, eat for 100ms, sleep for 100ms, eat 5 times. | Simulation stops after each philosopher has eaten 5 times.     |
| `./philo 1 800 200 200`   | 1 philosopher, die after 800ms, eat for 200ms, sleep for 200ms.               | Philosopher dies after 800ms since there's only one fork.      |

### Bonus Usage

For bonus features, use the bonus rule in the Makefile:

```bash
make bonus
```

| **Input Command**               | **Description**                                                               | **Expected Output**                                            |
| ------------------------------- | ----------------------------------------------------------------------------- | -------------------------------------------------------------- |
| `./philo_bonus 5 800 200 200`   | 5 philosophers, die after 800ms, eat for 200ms, sleep for 200ms.              | Philosophers alternate between eating, sleeping, and thinking. |
| `./philo_bonus 3 400 100 100 5` | 3 philosophers, die after 400ms, eat for 100ms, sleep for 100ms, eat 5 times. | Simulation stops after each philosopher has eaten 5 times.     |

### Error Handling and Testing

| **Input Command**          | **Description**                  | **Expected Output**                                     |
| -------------------------- | -------------------------------- | ------------------------------------------------------- |
| `./philo 5 800 200`        | Missing arguments.               | Error message: `Error: Invalid number of arguments`.    |
| `./philo 5 800 200 200 -5` | Negative number of times to eat. | Error message: `Error: Invalid argument`.               |
| `./philo 0 800 200 200`    | Zero philosophers.               | Error message: `Error: Invalid number of philosophers`. |

---

## What I Learned

- **Thread Synchronization**: I learned how to manage multiple threads and avoid race conditions using mutexes.
- **Deadlock Prevention**: I gained a deeper understanding of how to prevent deadlocks in concurrent programs.
- **Process Management**: I explored the differences between threads and processes, and how to manage them using semaphores.
- **Error Handling**: I improved my skills in handling errors and edge cases in C programs.

---

## Author

<div align="center">

| **Name**               | **GitHub Profile**                            | **42 Login** |
| ---------------------- | --------------------------------------------- | ------------ |
| **Oliver King Zamora** | [OliverKingz](https://github.com/oliverkingz) | **ozamora-** |

</div>

---

## Acknowledgments

This project is part of the **42 Cursus**, a rigorous programming curriculum that emphasizes hands-on learning and problem-solving. Special thanks to the 42 team for providing this challenging and rewarding project!  
Also thanks to peers and mentors for their feedback and support during the development process.

- **42 Network**: For providing the resources and environment to work on this project.
- **Peers and Mentors**: For their valuable feedback and support during the development process.

---

## TBD
- Test checking parser
	- Not enough arguments
	- Negative numbers
	- 0 philosophers
	- Overflow
- Test case for 1 philosopher. (Edge case)
- Test case when a philosopher dies. 
- Test case when no philosopher dies.
- Test with a large number of philosophers. (Stress test)
- Test memory leaks with valgrind --tools=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes
- Test data races with valgrind --tools=helgrind --track-origins=yes

Tips
- Use color in the output to make it more readable.
- Use your own my_usleep as it is more precise than the standard one.
- You can use write instead of printf to avoid buffering issues.