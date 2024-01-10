# CSE 30341-01 Operating Systems Principles

Spring 2022, Prof. Douglas Thain (dthain@nd.edu), University of Notre Dame

## Overview

An operating system (OS) is a critical layer of software that manages hardware resources and that provides user programs with a simple and consistent interface to the machine. In this course, we will examine the services and abstractions commonly provided by operating systems, and we will study the underlying mechanisms used to implement them. Topics include processes and threads, synchronization, cpu scheduling, deadlocks, memory management, segmentation and paging systems, storage and file systems, distributed systems, and virtualization.

A good understanding of OS internals offers several benefits, whether you intend to work in computer hardware or computer software. First, by understanding how an OS works, you will be able to write better software applications by making efficient use of OS abstractions such as filesystems and memory allocators. Second, the traditional problems that occur in operating systems (like scheduling, synchronization, and resource management) also occur in all sorts of other systems, ranging from small embedded computers to large scale cloud computing systems. The techniques that you learn here will have applications in every kind of computer system.

The concepts presented in class will be explored through a series of six intensive programming assignments. The assignments will make use of the C programming language, which the universal language for implementing and accessing operating systems at the lowest level. The projects will give students ample practice in manipulating pointers, managing memory, invoking system services, and dealing with error conditions. Although we will offer some technical guidance on these matters, students should expect to spend significant time debugging, consulting reference materials, and revising the projects until they work properly.

The goals for each student in this course are:

- To understand the abstractions and services provided by an operating system.
- To understand the mechanisms and algorithms used to implement these services
- To get practical experience using and implementing operating system services.

The course materials will test each student's achievement of these goals at several levels. For each topic in the course, students must be able to:

- Describe traditional operating system structures and algorithms.
- Demonstrate in detail how they apply to various programs and data.
- Evaluate the strengths and weaknesses of related structures and algorithms.
- Propose and evaluate a variety of improvements upon traditional methods.
- Implement basic methods in a working computing system.

## Course Communications

The course web page contains the schedule, assignments, and other critical information:

[http://dthain.github.io/opsys-sp22](http://dthain.github.io/opsys-sp22)

Canvas will be used for distributing grades and class recordings:

[https://canvas.nd.edu/courses/33829](https://canvas.nd.edu/courses/33829)

## Textbooks

- Required: Remzi H. Arpaci-Dusseau and Andrea C. Arpaci-Dusseau, **Operating Systems in Three Easy Pieces**, Arpaci-Dusseau Books, 2019. [http://ostep.org](http://ostep.org)

- Suggested Reference: Kernighan and Ritchie, The C Programming Language, Prentice-Hall, 1988.

## Reading Assignments

The textbook provides the foundation of the course, and it will be important for you to absorb it thoroughly.  To encourage regular
reading and preparation for class, you will turn in summary notes on the assigned readings each Monday by 11:59PM.  (A form will be provided on the course web page.)  The easiest way to do this is just take notes on paper, and then snap a few photos for upload.  If you prefer to type them out, then attach a PDF instead.

Your notes can be organized in whatever way is appropriate to that chapter and is useful for you. Good things to include may be an outline of the chapter, definition of key terms, a sketch of the systems or data structures being discussed, that sort of thing.  Along with your notes, you should submit **one thoughtful question** you would like to discuss that week. I will try to answer a few highlighted questions each week, and steer the lecture to address them.

Grading on notes will be very simple: either one, one-half, or zero points. There will be fourteen opportunities to earn a total of twelve points, so you may miss up to two without penalty.  The first round of notes are due on **Thursday, January 13th**, and then every **Monday at 11:59PM** thereafter.

## Attendance and Classroom Recording

To succeed in this class, you should attend and actively participate in all the scheduled lectures, however, attendance is not taken.
You will get the most out of class if you have done the required readings in advance and actively take notes during class.
I typically work by diagramming key structures of the OS on the chalkboard, and then work through examples and take questions.

Please refrain from using your laptops for non-class activities, since this [tends to distract others](https://www.insidehighered.com/news/2018/07/27/class-cellphone-and-laptop-use-lowers-exam-scores-new-study-shows) as well as yourself.  Let's use this time to work together instead.

Each class meeting will be recorded using Panopto and made available on Canvas.  Recordings are intended as a **back-up option** so that you
can catch up if you are out sick, travelling for an interview, or just need a review.  However, watching the videos is not a good substitute for regular attendance.  Recordings typically only capture the front of the classroom and the instructor's voice,
but may also incidentally record students during class, or shortly before and after class.
If you have any concerns about what has been recorded, please see the instructor.

**Note: Sharing any part of class recordings outside of the university is absolutely prohibited and may result in disciplinary action.**  

## Grading

The course grade will be based on six programming projects, one homework, a midterm, and a final exam. For each assignment, a numeric grade will be assigned. Grades will be made available in Canvas. Projects and homeworks are 60% of the course grade, chapter notes are 10%, and the midterm and final exam are each 15%. At the end of the semester, number grades will be converted to letter grades: 90/80/70 are the usual cutoffs for A/B/C grades, respectively. The instructor will exercise discretion on borderline grades, or to account for a trend of increasing/decreasing grades throughout the semester.

If you believe an error has been made in grading an item, please bring it to the attention of the TA who graded it within seven days of receiving it. (The TA who graded it knows the details best, and so can give you the best explanation.) Factual and clerical errors will of course be cheerfully corrected. If you are unsatisfied with the TA's explanation, you may appeal to the instructor. After seven days, graded items are final and will not be revisited.

Late assignments are not generally accepted.  However, each student may use **one late pass** for one assignment during the semester.  To exercise this option,
please email the instructor prior to the deadline.  The late pass will give you an extension of one week on the assignment.  (Cannot be used for the final assignment.)

## Campus Health and Safety

At the time of writing, classes are to be conducted in person normally, with masking precautions.
Of course, we may need to adjust if the campus situation changes.

If you have a mild illness (or are required to quarantine as a precaution) then you should make
use of the classroom recordings and continue to complete assignments in the ordinary way.
Office hours will be available by Zoom if needed.  If you have a more serious illness, then
please contact the instructor when you are able, and we will make alternate arrangements.

## Academic Code of Honor

As a student at Notre Dame, you are bound by the Academic Code of Honor (http://honorcode.nd.edu), which states:

> As a member of the Notre Dame community, I acknowledge that it is my responsibility to learn and abide by principles of intellectual honesty and academic integrity, and therefore I will not participate in or tolerate academic dishonesty.

The purpose of the homeworks and assignments in this course is for each student to gain the discipline and skills in design, programming, and analysis, so that they will be able to work independently in a professional setting. To that end, all exams, homeworks, and programming assignments are to be completed individually. Each student must write their own code from scratch with their own hands based on their own understanding of the course material.

You may consult with other students and outside resources in order to better understand concepts and techniques, or to debug localized problems. You may not copy code from another student or resource, excepting any starter code provided by the instructor.

## Some Campus Resources

If you require an accommodation for a disability, please first contact the Sara Bea Center (sarabeadisabilityservices.nd.edu) for a consultation, and we will be happy to work together on a solution. If you encounter a difficult life situation and don't know what to do, the University Counseling Center (ucc.nd.edu) or the Care and Wellness Consultants (care.nd.edu) can help and also connect you with other campus resources.
