---
layout: default
title: CSE 30341 - Operating Systems Principles
---

## CSE 30341 - Operating Systems Principles

<img align="right" height="192" src="http://github.com/dthain/basekernel/raw/master/screenshot-windows.png"/>

- 155 Debartolo Hall, Spring 2024
- Prof. Douglas Thain (`dthain@nd.edu`)
- Grad TA: Jin Zhou (`jzhou24@nd.edu`)
- Grad TA: Samit Muhaiman (`smuhaimi@nd.edu`)
- Ugrad TA: Chris Boumalhab (`cboumalh@nd.edu`)
- Ugrad TA: Eamon Tracey (`etracey@nd.edu`)
- Ugrad TA: Daniel "Zen" Yu (`dyu4@nd.edu`)

##  Office Hours - Starting Jan 22nd

|      | Mon | Tue | Wed | Thu | Fri |
|------|-----|-----|-----|-----|-----|
|1-3PM | Jin | Prof. Thain | Jin | Prof. Thain | |
|3-5PM | Eamon (4-6) | Chris | Eamon | Chris | Samit
|5-6:30PM | Zen | | Zen | | |

- Prof. Thain in 384C Fitzpatrick
- Others in 150B Fitzpatrick (CSE student commons)

## Quick Links

- [Syllabus](syllabus)
- [General Instructions for Assignments](general)
- [Gradebook on Canvas](https://canvas.nd.edu/courses/82668/gradebook)
- [Assignments on Canvas](https://canvas.nd.edu/courses/82668/assignments)
- [Slack Channel](https://nd-cse.slack.com/archives/C06D9T46UG2)

## Online Textbook

[<img align="right" height="128" src="https://pages.cs.wisc.edu/~remzi/OSTEP/book-cover-two.jpg"/>](http://ostep.org)

- Required: [Operating Systems in Three Easy Pieces](https://pages.cs.wisc.edu/~remzi/OSTEP), Remzi H. Arpaci-Dusseau and Andrea C. Arpaci-Dusseau, Arpaci-Dusseau Books, March, 2018 (Version 1.00)
- Suggested: The C Programming Language, Brian Kernighan and Dennis Ritchie, Prentice Hall, 1988.

## Tentative Schedule

|Week|Reading&nbsp;Due Mon&nbsp;11:59PM |Tuesday|Thursday|Due Friday 11:59PM|
|-----|-----|-----|---|---|
| 15 Jan  |             | Overview<br>[Syllabus](syllabus)<br>[Metric Math](metric) | Hardware<br>[Hardware Overview](hardware)| **[Homework A](homework-metric)**<br>**Ch 1-2 Notes Due**
| 12 Jan  | Ch. 3-6	| Processes | Processes | [Project 1](project1)
| 29 Jan  | Ch. 7-11	| Scheduling <br> [Basekernel Procs](basekernel-process)| Scheduling	| [Homework B](homework-b)
| 5 Feb   | Ch. 25-29	| Threads	 | Locks and Data Structures |  [Project 2](project2)
| 12 Feb  | Ch. 30	| Condition Vars | CV Contd / [Examples](https://github.com/dthain/opsys-sp24/tree/main/examples) | [Homework C](homework-c)
| 19 Feb  | Ch. 31	| CV Contd / [Pathfinder](https://www.cs.cornell.edu/courses/cs614/1999sp/papers/pathfinder.html)    | Semaphores / [Examples](https://github.com/dthain/opsys-sp24/tree/main/examples) | [Project 3](project3)
| 26 Feb  | Ch. 32-33	| Deadlock	 | Memory Overview	| [Homework D](homework-d)
| 4 Mar   | Ch. 13-16   | Segmentation   | [Midterm Exam](midterm)	|
| 11 Mar  | -           | Spring Break   | Spring Break |
| 18 Mar  | Ch. 17-19	| Paging Mechanisms | TLBs / Performance	| **[Project 4](project4)**
| 25 Mar  | Ch. 20-22	| Multi-Level Paging | Swapping	| <br>(Easter Break)
| 1 Apr	  | Ch. 35-37 + 44 | Swapping Cont. | I/O Devices / ([Mouse](https://github.com/dthain/basekernel/blob/master/kernel/mouse.c) / [Disk](https://github.com/dthain/basekernel/blob/master/kernel/ata.c))  | [Homework E](homework-e)
| 8 Apr   | Ch. 38-39	| HDD [Datasheet](datasheets/seagate-st8000-hdd.pdf) / SSD [Datasheet](micron-2280-ssd.pdf) | Buffer Cache / Files-Dirs | [Project 5](project5)
| 15 Apr  | Ch. 40-42	| FS Impl        | FS Impl | **Homework F**
| 22 Apr  | Ch. 53-55	| Security       | Security | **Project 6**
| 29 Apr  | -           | Review | No Class |
| 6 May	  |             |                | [Final Exam Thursday 10:30](final) |

## Project 3 Extra Credit Submissions

![](project3-mosaic.png)

## Very Incomplete List of Notable Operating Systems

Mainframe Era:

- [ATLAS](https://en.wikipedia.org/wiki/Atlas_Supervisor) (perhaps first "real" OS?)
- [IBM 1401](https://en.wikipedia.org/wiki/IBM_1401)
- [IBM 7090 / CTSS](https://en.wikipedia.org/wiki/IBM_7090)
- [IBM System/360](https://en.wikipedia.org/wiki/IBM_System/360)
- [MULTICS](https://multicians.org)

Minicomputer Era:
- [VAX/VMS](https://en.wikipedia.org/wiki/VAX) / [OpenVMS](https://en.wikipedia.org/wiki/OpenVMS)
- [TOPS-20](https://en.wikipedia.org/wiki/TOPS-20)
- [Unix](https://en.wikipedia.org/wiki/Unix)

Microcomputer Era:
- [CP/M](https://en.wikipedia.org/wiki/CP/M)
- [DOS](https://en.wikipedia.org/wiki/DOS)
- [Windows](https://en.wikipedia.org/wiki/Microsoft_Windows)
- [AmigaOS](https://en.wikipedia.org/wiki/AmigaOS)
- [BeOS](https://en.wikipedia.org/wiki/BeOS)
- [NetBSD](https://netbsd.org) / [OpenBSD](https://openbsd.org) / [FreeBSD](https://freebsd.org)
- [Linux](https://kernel.org)

Microkernels:
- [Mach](https://en.wikipedia.org/wiki/Mach_(kernel))
- [L4](https://en.wikipedia.org/wiki/L4_microkernel_family)

Teaching and Experimental:
- [Singularity](https://en.wikipedia.org/wiki/Singularity_(operating_system))
- [Minix](https://www.minix3.org)
- [Plan 9 from Bell Labs](https://9p.io/plan9/)
- [Basekernel](http://github.com/dthain/basekernel) (by Prof. Thain)

Real-Time and Embedded Operating Systems
- [QNX](https://en.wikipedia.org/wiki/QNX)
- [FreeRTOS](https://en.wikipedia.org/wiki/FreeRTOS)
- [ROS](https://en.wikipedia.org/wiki/Robot_Operating_System)
