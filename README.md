# Timer Management in QNX Neutrino RTOS

**by**: Min Khant Soe Oke, Kaung Sithu

## Overview

This project demonstrates the implementation of timers and handling time-dependent tasks in QNX Neutrino RTOS. The focus is on setting up and using periodic timers to manage event notifications and perform actions at specific intervals. This exercise is crucial for understanding how to create responsive and efficient real-time systems where precise timing and event handling are essential.

## Dependencies

**To run this project, you need to have the following dependencies installed:**

* QNX Neutrino RTOS
* Basic knowledge of C programming
* Familiarity with system calls and handling structures in QNX

## Features

**Timers in RTOS**
- Timers trigger events after a specified duration or at regular intervals.
- Crucial for scheduling tasks in real-time systems.

**Periodic Timers**
- Trigger events repeatedly at defined intervals for regular updates or checks.

**Pulse Notification**
- QNX Neutrino uses pulses as lightweight notifications for inter-process communication.
- Pulses signal events without blocking operations.

## How to Use

1. **Start the Server**:
   - Open a terminal and run `./server`.

2. **Timer Initialization and Setup**:
   - The first timer is set up to expire every 10 milliseconds.
   - The second timer is set up to expire every 10 seconds.

3. **Message Handling**:
   - The server waits for messages (pulses) from the timers using `MsgReceive`.
   - Each time the first timer expires, it increments the `first_timer_count`.
   - Each time the second timer expires, it prints the count of the first timer’s expirations.

4. **Timers and Pulse Handling**:
   - Timers are configured using `struct sigevent` to send pulses to a specified channel.
   - The `setup_timer` function is used to configure and start the timers.
   - The server processes pulses based on their codes to differentiate between timer expirations.

## Authors

- Min Khant Soe Oke
- Kaung Sithu
