# CSE 30341 - Metric Math Refresher

In this course, we will perform a lot of back-of-the-envelope computations about the sizes of memory spaces, storage devices, and related them to sizes of integers needed to address them. You should be able to perform these conversions quickly and express the result as a compact metric value (e.g. 16MB).  These computations aren't *hard* but they require a little effort to memorize, and regular practice in order to exercise them quickly.

## Powers of Two

If you haven't done so already, memorize the powers of two up to at least `2^10`, and farther if you like. Repeat them every day until they roll off your tongue easily.  

| Power | Value |
|-------|-------|
| 2^0  | 1 |
| 2^1  | 2 |
| 2^2  | 4 |
| 2^3  | 8 |
| 2^4  | 16 |
| 2^5  | 32 |
| 2^6  | 64 |
| 2^7  | 128 |
| 2^8  | 256 |
| 2^9  | 512 |
| 2^10 | 1024 (Kilo)

## Metric Prefixes for Memory Size

You should already know the SI system in which prefixes are uses to represent powers of ten.  However, in computer systems,
binary powers of two occur more naturally than powers of ten.  And so we often use the following binary approximations,
especially when dealing with memory systems.  Memorize these:

| Prefix | SI Value | Binary Approx |
|--------|----------|---------------|
| K - Kilo   | 10^3     | 2^10          |
| M - Mega   | 10^6     | 2^20          |
| G - Giga   | 10^9     | 2^30          |
| T - Tera   | 10^12    | 2^40          |
| P - Peta   | 10^15    | 2^50          |
| E - Exa    | 10^18    | 2^60          |

**Handy Note:** Multiplying or dividing by 2^10 (Kilo) moves up or down by one metric prefix. So, Kilo*Kilo=Mega and Tera/Kilo=Giga.
A computer memory is conceptually organized as an array of words, such that each word can be individually written. (Most commonly, each word is one byte, although other sizes are possible.) To select any one word from that array, we must have a integer with enough bits so that it can count as high as the number of words in the array. An integer used to locate a word in memory is known as an address or a pointer.

## Metric Prefixes for Time

The following prefixes are used in the normal SI way to indicate values smaller than one.
Computer systems operate at very small time scales and so we often measure events in micro- or nano-seconds.

| Prefix    | SI Value |
|-----------|----------|
| m - Milli | 10^-3    |
| μ - Micro | 10^-6    |
| n - Nano  | 10^-9    |
| p - Pico  | 10^-12   |
| f - Femto | 10^-15   |

## Simplifying Examples

In this class, you will often need to simplify expressions using binary
powers and metric values.  The goal is to yield a single value represented
as a small (0-1023) number modified by metric units.

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

**Example 3:** How many 32-bit items can I store in a 1MB memory?

Keep in mind that there are eight **bits** in a **byte**.
Just divide one value by the other to get the number of items:

```
1MB / 32 bits = 1MB / 4B = 2^20B / 2^2B = 2^18
```

Now put the number of items back into metric form:

```
2^18 items = 2^8 * 2^10 items = 256 * 2^10 items = 256K items
```

**Answer:** 256K items

**Example 4:** Suppose I have a network card that can transmit a 2KB packet every microsecond.  Approximately how fast is this in bytes per second?

If this is a quick back of the envelope approximation, then we can let `K` be the convenient value of `10^3` instead of the usual
value of `2^10` and do this:

```
2KB / us = 2 * 10^3 B / 10^-6 s = 2 * 10^3 * 10^6 = 2 * 10^9 B / s = 2GB/s
```

**Answer:** 2GB per second