# C Language Practices in GNU/Linux

## Date - 2022

This repository aims to familiarize you with the design and implementation of static and dynamic libraries in the GNU Toolchain and Linux Software development environment. Activities will be carried out that involve the handling of command line arguments, the implementation of a static library (cJSON) and a dynamic library acting as a _plugin_.

### Authors:
- **Robledo, Valentín**

### Questions

#### What are the types of type descriptors that we can find in /proc//fd?

When a file is opened, the operating system creates an entry that represents the file and allows it to store information about it. So, if we have 100 files opened, there will be 100 entries in the operating system (somewhere in the kernel). These entries are represented by integers (100, 101, 102). This entry number is the file descriptor. Therefore, the file descriptor is just an integer that uniquely represents a file opened by a process. If a process opens 10 files, its process table will have 10 entries for file descriptors. There are four types of file descriptors, standard input, standard output, standard error, and file.

#### Assuming a user is running process pid 1212, is it valid to run the following command from a new terminal? % echo “Hello, world.” >> /proc/1212/fd/1

The command execution is valid. The result of the command will write the message "Hello, world" on the file referenced by the selected file descriptor. If we open two instances of a terminal and then execute the given command in one of the terminals referencing the input file descriptor of the other terminal, we can see how we write the message "Hello, world" from the first terminal to the second.

#### 4.3. What is the difference between hard and soft limits?

In Linux, the resources that a process or session can access can be limited. There are two types of enforceable limits: hard limits and soft limits. Hard limits are established using superuser privileges and are the maximum resource limit that any process or session can have; these can never be exceeded. On the other hand, soft limits can be used by users or by the processes themselves to self-limit their use of resources, always keeping in mind that these limits must be less than or equal to the imposed hard limit. Therefore, we can say that the hard limit establishes the upper limit from which, later, users or processes can be sublimited using soft limits.
