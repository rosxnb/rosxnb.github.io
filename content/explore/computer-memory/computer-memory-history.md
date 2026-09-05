+++
title = "Computer Memory History"
date = 2026-09-05T11:10:08+05:45
series = ["Computer Memory"]
description = "Journey and Evolution of Computer Memory"
+++


## Journey and Evolution of Computer Memory | A Reflect On History

- `1820's - 1940's` | **Mechanical Era**
    - Punch cards & delay lines
    - **Manchester Baby (1948)** ran the first stored-program, but **EDSAC (1949)**
      was the first *practical*, regularly-usable stored-program computer — it used
      Mercury delay lines for memory
    - **Devices:** Charles Babbage's Analytical Engine, Early IBM tabulators

- `1950's - 1960's` | **Magnetic Era**
    - Handwoven ferrite beads on grid of copper wire
    - Each beads could be magnetized clockwise (`1`) or anticlockwise (`0`)
    - **Devices:** Mainframes like IBM 7090

- `1970's` | **The semiconductor revolution**
    - Dynamic RAM is born (1968, Dennard/IBM) — single transistor, tiny capacitor; first
      commercial chip (Intel 1103) shipped 1970
    - **Devices:** Intel 4004 microprocessor, Apple I, Altair

- `1970's - 1980's` | **ROM and Video Games Boom**
    - Mask ROM – programmed during manufacture
    - PROM – programmable just one after manufacture
    - EPROM – memory could be erased by shining strong UV rays
    – Game cartridges were just RAM chips
    - **Devices:** Apple II, the IBM PC, Atari 2600 gaming console

- `1980's` | **Speed vs Capacity war**
    - SRAM enters the chat – its doesn't need refresh, and is faster
    – But SRAM takes 4 - 6 transistors to store a single bit
    - We settle on architecture hierarchy we use today:
      Registers (CPU) -> SRAM (L1/L2 cache) -> DRAM (memory) -> Hard Disk (Storage)
    - **Devices:** Commodore 64, Macintosh, early PC's running MS-DOS

- `1990's` | **Synchronous Era & Rise of Modules**
    - Memory & RAM used to run on their own pace
    - SDRAM (Synchronous DRAM) synced its clock speed to CPU bus
    - Memory stops being sold as loop chips, now it can be mounted into a slot on the board
    - **Devices:** Pentium processor & dawn of 3D gaming (Doom, Quake)

- `2000's` | **Bandwidth explosion**
    - DDR-RAM (Double Data Rate RAM) – instead of sending one data chunk per clock tick,
      DDR sends data on both rising and falling edges of the clock signal which effectively
      doubles speed without increasing clock frequency
    - Generations of DDR: DDR2 (lower power than original DDR, 1.8V), DDR3 (faster, 1.5V),
      DDR4 (dense, 1.2V); each generation changes the physical notch on the stick so you can't
      put wrong one in motherboard
    - **Devices:** Rise of internet, Windows XP, Multicore processors

- `2010's` | **The Flash Takeover**
    - SSD's using NAND flash memory killed mechanical HDD for Operating System
    - But NAND is bizarre as it stores electrons in a "floating gate" between silicon layers
      and to erase data you have to apply high voltage to tunnel the electrons out which degrades the
      silicon (meaning SSD's have limited lifetime)
    - 3D NAND – people stopped shrinking transistors (electrons started leaking at tiny scales) and
      started stacking them vertically
    - **Devices:** Smartphones, Ultrabooks, and the Cloud

- `2020's` | **The End of "memory" vs "storage"**
    - HBM (High Bandwidth Memory) stacks DRAM chips directly next to processor and connects them
      through microscopic holes called TSVs (Through-Silicon Vias); data travels milimeters instead
      of inches achieving speeds of over 1 Terabyte per seconds
    - DDR5 is here and doubles burst length & improves power management by having its own builtin
      voltage regulator
    - Optane (RIP) & MRAM (Magnetoresistive RAM) techmologies aim to combine the speed of DRAM with
      non-volatility of a hard drive


## The Ultimate Paradox

In the 1950's memory was slow, expensive, and tiny, but it never forgot (core memory).
Today, memory is trillions times faster, cheaper, and holds terabytes, it forgets everything the second
you the power (DRAM).

We have spent 70 years trading permanence for speed. And now, in the AI era, the bottleneck is no longer
CPU or storage but it is the bus between them. Engineers are now building "Processing-in-Memory" (PIM),
where computation happens inside the memory chip themselves, because moving data is more expensive than
calculating it.
