cmake_minimum_required(VERSION 3.23)
project(DT8025 C)

set(CMAKE_C_STANDARD 11)

include_directories(Assignment2/Assignment2_Part1/lib)
include_directories(Assignment2/Assignment2_Part2/Assigment2part2/lib)

add_executable(DT8025
        Assignment2/Assignment2_Part1/lib/piface.c
        Assignment2/Assignment2_Part1/lib/piface.h
        Assignment2/Assignment2_Part1/lib/rpi-armtimer.c
        Assignment2/Assignment2_Part1/lib/rpi-armtimer.h
        Assignment2/Assignment2_Part1/lib/rpi-base.h
        Assignment2/Assignment2_Part1/lib/rpi-gpio.c
        Assignment2/Assignment2_Part1/lib/rpi-gpio.h
        Assignment2/Assignment2_Part1/lib/rpi-interrupts.c
        Assignment2/Assignment2_Part1/lib/rpi-interrupts.h
        Assignment2/Assignment2_Part1/lib/rpi-systimer.c
        Assignment2/Assignment2_Part1/lib/rpi-systimer.h
        Assignment2/Assignment2_Part1/lib/rpi3.h
        Assignment2/Assignment2_Part1/lib/startup.c
        Assignment2/Assignment2_Part1/lib/syscalls.c
        Assignment2/Assignment2_Part1/a2p1.c
        Assignment2/Assignment2_Part2/Assigment2part2/lib/expstruct.c
        Assignment2/Assignment2_Part2/Assigment2part2/lib/expstruct.h
        Assignment2/Assignment2_Part2/Assigment2part2/lib/piface.c
        Assignment2/Assignment2_Part2/Assigment2part2/lib/piface.h
        Assignment2/Assignment2_Part2/Assigment2part2/lib/rpi-armtimer.c
        Assignment2/Assignment2_Part2/Assigment2part2/lib/rpi-armtimer.h
        Assignment2/Assignment2_Part2/Assigment2part2/lib/rpi-base.h
        Assignment2/Assignment2_Part2/Assigment2part2/lib/rpi-gpio.c
        Assignment2/Assignment2_Part2/Assigment2part2/lib/rpi-gpio.h
        Assignment2/Assignment2_Part2/Assigment2part2/lib/rpi-interrupts.c
        Assignment2/Assignment2_Part2/Assigment2part2/lib/rpi-interrupts.h
        Assignment2/Assignment2_Part2/Assigment2part2/lib/rpi-systimer.c
        Assignment2/Assignment2_Part2/Assigment2part2/lib/rpi-systimer.h
        Assignment2/Assignment2_Part2/Assigment2part2/lib/rpi3.h
        Assignment2/Assignment2_Part2/Assigment2part2/lib/startup.c
        Assignment2/Assignment2_Part2/Assigment2part2/lib/syscalls.c
        Assignment2/Assignment2_Part2/Assigment2part2/a2p2.c)
