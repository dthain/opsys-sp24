# CSE 30341 - Metric Powers Reference

## Metric Computations

In this course, we will perform a lot of back-of-the-envelope computations about the sizes of memory spaces, storage devices, and related them to sizes of integers needed to address them. You should be able to perform these conversions quickly and express the result as a compact metric value (e.g. 16MB)
If you haven't done so already, memorize the powers of two up to at least ten, and farther if you like. Repeat them every day until they roll off your tongue easily.

```
2^0 = 1
2^1 = 2
2^2 = 4
2^3 = 8
2^4 = 16
2^5 = 32
2^6 = 64
2^7 = 128
2^8 = 256
2^9 = 512
2^10 = 1024 (Kilo)
2^11 = 2048
2^12 = 4096
2^13 = 8192
...
```

You already know that in the metric (SI) system, the prefix Kilo (K) usually means 1000, not 1024. However, when dealing with binary addressable objects, powers of 10 do not naturally occur, and so we use the following approximations widely:

```
2^10 = Kilo
2^20 = Mega
2^30 = Giga
2^40 = Tera
2^50 = Peta
2^60 = Exa
```

Note: Multiplying or dividing by 2^10 (Kilo) moves up or down by one metric prefix. So, Kilo*Kilo=Mega and Tera/Kilo=Giga.
A computer memory is conceptually organized as an array of words, such that each word can be individually written. (Most commonly, each word is one byte, although other sizes are possible.) To select any one word from that array, we must have a integer with enough bits so that it can count as high as the number of words in the array. An integer used to locate a word in memory is known as an address or a pointer.

## Examples

**Example 1:** Suppose that we have a computer with a 16-bit address size. That means each address is represented as an integer between zero and 2^16-1, and the largest possible memory it could address is 2^16 bytes. How much memory can this computer address?
 
```
2^16 B = 2^6 * 2^10 B = 2^6 KB = 64KB
```

**Answer:** It can address up to 64KB.

**Example 2:** Suppose that you are designing an architecture for a computer that requires 256MB of memory. How many address bits are needed to address the whole memory?

```
256MB = 256 * 2^20 B = 2^8 * 2^20 B = 2^28 B
```

**Answer:** At least 28 address bits are needed.

**Example 3:** How many 32-bit items can I store in a 1MB memory? Just divide one value by the other to get the number of items:

```
1MB / 32 bits = 1MB / 4B = 2^20B / 2^2B = 2^18
```

Now put the number of items back into metric form:

```
2^18 items = 2^8 * 2^10 items = 256 * 2^10 items = 256K items
```

**Answer:** 256K items
