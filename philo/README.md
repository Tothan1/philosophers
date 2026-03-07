*This project has been created as part of the 42 curriculum by tle-rhun*

## Description

This project is an implementation of the classic Dining Philosophers problem, a synchronization problem in computer science. The goal is to simulate philosophers sitting at a round table, alternating between eating, thinking, and sleeping, while sharing forks. The challenge is to prevent deadlocks and ensure no philosopher starves.

 Rules

- Philosophers must alternate between eating, thinking, and sleeping.
- To eat, a philosopher needs two forks (one on each side).
- Forks are shared resources, and only one philosopher can use a fork at a time.
- Philosophers cannot communicate with each other.
- The simulation stops when a philosopher dies from starvation or when all philosophers have eaten a specified number of times (if provided).

## Instructions

 Compilation

To compile the program, use the provided Makefile:

```bash
make
```

This will generate the `philo` executable.

### Execution

Run the program with the following arguments:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers`: The number of philosophers and forks (1-200).
- `time_to_die`: Time in milliseconds after which a philosopher dies if they haven't started eating.
- `time_to_eat`: Time in milliseconds it takes for a philosopher to eat.
- `time_to_sleep`: Time in milliseconds it takes for a philosopher to sleep.
- `number_of_times_each_philosopher_must_eat` (optional): If specified, the simulation stops when all philosophers have eaten this many times.

 Examples

- `./philo 5 800 200 200 7`: Simulates 5 philosophers, each must eat 7 times.

## Ressources

 Constraints

- The program must use threads and mutexes for synchronization.
- No global variables are allowed.
- The program must handle edge cases, such as 1 philosopher.
- Output must be formatted correctly and not interleaved due to concurrent access.
- The program must be leak-free and handle errors gracefully.

 Output

The program prints the state of each philosopher in the format:

```
timestamp_in_ms philosopher_id state
```

States include:
- `has taken a fork`
- `is eating`
- `is sleeping`
- `is thinking`
- `died`