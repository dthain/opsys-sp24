---
layout: default
title: CSE 30341 - Operating Systems Principles
---

## CSE 30341 - Operating Systems Principles

- 136 Debartolo Hall, Spring 2024
- Prof. Douglas Thain (`dthain@nd.edu`)
- Grad TA: Jin Zhou (`jzhou24@nd.edu`)
- Grad TA: Samit Muhaiman (`smuhaimi@nd.edu`)
- Ugrad TA: Chris Boumalhab (`cboumalh@nd.edu`)
- Ugrad TA: Eamon Tracey (`etracey@nd.edu`)
- Ugrad TA: Daniel "Zen" Yu (`dyu4@nd.edu`)

## Draft Office Hours (Starting Jan 22nd)

|      | Mon | Tue | Wed | Thu | Fri |
|------|-----|-----|-----|-----|-----|
|1-3PM |     | Prof. Thain (\*)|     | Prof. Thain (\*) |  |
|3-5PM |     |     |     |     |     |
|5-7PM |     |     |     |     |     |

- (\*) in 384C Fitzpatrick
- (+) in 150B Fitzpatrick (CSE student commons)

## Quick Links

- [Syllabus](syllabus)
- [General Instructions for Assignments](general)
- [Submit Reading Notes on Canvas](https://canvas.nd.edu/courses/82668/assignments)
- [Slack Channel](https://nd-cse.slack.com/archives/C06D9T46UG2)
- [Gradebook on Canvas](https://canvas.nd.edu/courses/82668/gradebook)

## Online Textbook

- Required: [Operating Systems in Three Easy Pieces](https://pages.cs.wisc.edu/~remzi/OSTEP), Remzi H. Arpaci-Dusseau and Andrea C. Arpaci-Dusseau, Arpaci-Dusseau Books, March, 2018 (Version 1.00)
- Suggested: The C Programming Language, Brian Kernighan and Dennis Ritchie, Prentice Hall, 1988.

## Tentative Schedule

|Week|Reading&nbsp;Due Mon&nbsp;11:59PM |Tuesday|Thursday|Due Friday 5PM|
|-----|-----|-----|---|---|
| 15 Jan  | Ch. 1-2     | Overview<br>[Syllabus](syllabus) | Hardware<br>[Powers](powers) | **Homework A Due**<br>**1st Notes Due**
| 12 Jan  | Ch. 3-6	| Processes	 | Processes | [Project 1 Due](project1)
| 29 Jan  | Ch. 7-11	| Scheduling	 | Scheduling	| [Project 2 Due](project2)
| 5 Feb   | Ch. 25-29	| Threads	 | Locks and Data Structures | **Homework B Due**
| 12 Feb  | Ch. 30	| Condition Vars | CV Contd / [Examples](https://github.com/dthain/opsys-sp24/tree/main/examples) | **Homework C Due**
| 19 Feb  | Ch. 31	| CV Contd       | Semaphores / [Examples](https://github.com/dthain/opsys-sp24/tree/main/examples) | **Project 3 Due**
| 26 Feb  | Ch. 32-33	| Deadlock	 | Memory Overview	| **Homework D Due**
| 4 Mar   | Ch. 13-16   | Segmentation   | [Midterm Exam](midterm)	|
| 11 Mar  | -           | Spring Break   | Spring Break |
| 18 Mar  | Ch. 17-19	| Paging Mechanisms | TLBs / Performance	| 
| 25 Mar  | Ch. 20-22	| Multi-Level Paging | Swapping	| **Project 4 Due**
| 1 Apr	  | Ch. 35-37 + 44 | I/O Devices / ([Mouse](https://github.com/dthain/basekernel/blob/master/kernel/mouse.c) / [Disk](https://github.com/dthain/basekernel/blob/master/kernel/ata.c))  | HDD [Datasheet](https://www.seagate.com/www-content/datasheets/pdfs/desktop-hdd-8tbDS1770-9-1603US-en_US.pdf) / SSD [Datasheet](https://www.micron.com/-/media/client/global/documents/products/data-sheet/ssd/m550_m2_2280_ssd.pdf) | 
| 8 Apr   | Ch. 38-39	| RAID	         | FS Abstraction | **Project 5 Due**
| 15 Apr  | Ch. 40-42	| FS Impl        | FS Structure |
| 22 Apr  | Ch. 53-55	| Security       | Security |
| 29 Apr  | -           | Review<br>**Project 6 Due** | No Class |
| 6 May	  |             |                | [Final Exam Thursday 10:30](final) |

## Some Open Source OS Kernels

<img align="right" height="192" src="http://github.com/dthain/basekernel/raw/master/screenshot-windows.png"/>

- [Basekernel](http://github.com/dthain/basekernel) (by Prof. Thain)
- [Minix](https://www.minix3.org)
- [Plan 9 from Bell Labs](https://9p.io/plan9/)
- [Linux Kernel](https://www.kernel.org)
- [NetBSD](https://www.netbsd.org)

