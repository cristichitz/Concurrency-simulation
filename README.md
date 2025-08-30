# 🍝 Dining Philosophers

A multithreaded simulation of the classic **Dining Philosophers Problem** - a fundamental synchronization challenge in computer science that demonstrates deadlock, race conditions, and resource sharing between concurrent processes.

## 📖 The Problem

Five philosophers sit around a circular table with five forks. Each philosopher alternates between **thinking**, **eating**, and **sleeping**. To eat, a philosopher needs **both** the fork to their left and right. The challenge is to design a solution where:

- Philosophers don't starve (deadlock prevention)
- No data races occur (thread safety)
- Resources are shared efficiently (no unnecessary blocking)

## 🚀 Features

- **Thread-safe implementation** using mutexes and atomic operations
- **Deadlock prevention** through smart fork acquisition ordering
- **Precise timing** with microsecond accuracy
- **Real-time monitoring** of philosopher states
- **Configurable parameters** for different scenarios
- **Memory leak detection** compatible with Valgrind

## 🛠️ Technical Implementation

### Core Concepts
- **One thread per philosopher** for true parallelism
- **Mutex-protected forks** to prevent race conditions
- **Atomic variables** for simulation control
- **Timestamp logging** for state transitions
- **Smart fork ordering** to break circular wait conditions

### Deadlock Prevention Strategy
```c
// Even philosophers: pick left fork first, then right
// Odd philosophers: pick right fork first, then left
// This breaks the circular wait condition
```

## 📋 Usage

### Compilation
```bash
make
```

### Execution
```bash
./philo_exec [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```

### Parameters
- **number_of_philosophers**: Number of philosophers (and forks)
- **time_to_die**: Time in milliseconds - if a philosopher doesn't eat within this time, they die
- **time_to_eat**: Time in milliseconds a philosopher spends eating
- **time_to_sleep**: Time in milliseconds a philosopher spends sleeping  
- **number_of_times_each_philosopher_must_eat**: (Optional) Simulation stops when all philosophers have eaten this many times

### Examples

```bash
# Basic simulation - 5 philosophers, generous timing
./philo_exec 5 800 200 200

# Stress test - tight timing that challenges the algorithm
./philo_exec 4 310 200 100

# Impossible scenario - demonstrates starvation detection
./philo_exec 3 300 100 100

# Limited meals - simulation ends after each philosopher eats 5 times
./philo_exec 5 800 200 200 5
```

## 📊 Output Format

```
[timestamp_ms] [philosopher_id] [action]
```

**Actions:**
- `is thinking` - Philosopher is in thinking state
- `has taken a fork` - Philosopher picked up a fork
- `is eating` - Philosopher is eating (has both forks)
- `is sleeping` - Philosopher is sleeping
- `died` - Philosopher died from starvation

**Example Output:**
```
0 1 is thinking
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
200 3 is thinking
201 3 has taken a fork
400 1 is thinking
```

## 🔧 Development

### Debug Build
```bash
make CFLAGS="-Wall -Werror -Wextra -g -fsanitize=thread"
```

### Memory Leak Detection
```bash
valgrind --leak-check=full ./philo_exec 5 800 200 200
```

### Thread Error Detection
```bash
valgrind --tool=helgrind ./philo_exec 5 800 200 200
```

## 🏗️ Project Structure

```
├── includes/
│   └── philos.h          # Headers and structure definitions
├── src/
│   ├── parse.c           # Argument parsing and input validation
│   ├── philo_routine.c   # Main philosopher thread routine
│   ├── philos.c          # Program entry point and orchestration
│   └── sim_start.c       # Simulation initialization and control
├── utils/
│   └── utils.c           # Utility functions (timing, printing, etc.)
├── Makefile              # Build configuration
└── README.md             # This file
```

## 🧠 Algorithm Insights

### Why This Problem Matters
The Dining Philosophers problem illustrates fundamental challenges in concurrent programming:

1. **Deadlock**: All philosophers pick up their left fork simultaneously
2. **Starvation**: One philosopher never gets both forks
3. **Race Conditions**: Unsynchronized access to shared resources

### Solution Highlights
- **Asymmetric fork acquisition**: Even/odd philosophers use different ordering
- **Atomic simulation control**: Thread-safe start/stop mechanisms
- **Precise death detection**: Continuous monitoring of last meal times
- **Resource cleanup**: Proper mutex destruction and memory management

## ⚡ Performance Considerations

- **Minimal locking overhead**: Forks are only locked when needed
- **Efficient timing**: Uses high-resolution timestamps
- **Scalable design**: Works with any number of philosophers
- **Memory efficient**: Linear memory usage O(n)

## 🐛 Common Issues & Solutions

| Issue | Cause | Solution |
|-------|-------|----------|
| Immediate death | `time_to_die` too small | Increase death timer or reduce eat/sleep times |
| Deadlock | All philosophers pick same fork first | Implement asymmetric fork ordering |
| Race conditions | Unprotected shared data | Use atomic operations for shared variables |
| Memory leaks | Missing cleanup | Ensure all mallocs have corresponding frees |

## 📚 Learning Outcomes

This project demonstrates mastery of:
- **Pthread programming** (mutex, thread creation/joining)
- **Synchronization primitives** (mutexes, atomic operations)
- **Deadlock prevention** strategies
- **Race condition** elimination
- **Resource management** in concurrent environments
- **Real-time systems** concepts

## 🤝 Contributing

Feel free to fork this project and experiment with different deadlock prevention strategies or optimization techniques!

## 📄 License

This project is part of the 42 School curriculum.

---

*"The philosophers will either find a way to share the forks peacefully, or they will starve while contemplating the nature of concurrency."*
