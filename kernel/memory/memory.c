#include <stddef.h>
#include <stdint.h>

#include "arch/arm1176/arm1176-mmu.h"

#include "boot/hardware_detect.h"

#include "memory/memory.h"

#include "lib/printk.h"
#include "lib/memset.h"

#define MAX_MEMORY	(1024*1024*1024)		// 1GB
#define CHUNK_SIZE	4096

static int memory_debug = 0;

static unsigned int memory_total;

static unsigned int memory_map[MAX_MEMORY/CHUNK_SIZE/32];

static unsigned int max_chunk = 0;

// Addded for the last part
static int last = -1;

/* Mark a chunk as used (1) */
static int memory_mark_used(int chunk) {
    int element, bit;
    element = chunk / 32;
    bit = chunk % 32;
    memory_map[element] |= 1 << bit;
    return 0;
}

/* Mark a chunk as free (0) */
static int memory_mark_free(int chunk) {
    int element, bit;
    element = chunk / 32;
    bit = chunk % 32;
    memory_map[element] &= ~(1 << bit);
    return 0;
}

/* See if a chunk is used */
static int memory_test_used(int chunk) {
    int element, bit;
    element = chunk / 32;
    bit = chunk % 32;
    return memory_map[element] & (1 << bit);
}

/* Initialize memory */
static int memory_init(unsigned long memory_total, unsigned long memory_kernel) {
    int i;
    if (memory_total > MAX_MEMORY) {
        printk("Error! Too much memory!\n");
        return -1;
    }
    printk("Initializing %dMB of memory. "
           "%dkB used by kernel, %dkB used by memory map\n",
           memory_total / 1024 / 1024,
           memory_kernel / 1024,
           (MAX_MEMORY / CHUNK_SIZE / 32) / 1024);

    max_chunk = (memory_total / CHUNK_SIZE);

    /* Clear it out, probably not necessary */
    for (i = 0; i < max_chunk / 32; i++) {
        memory_map[i] = 0;
    }

    /* Mark OS area as used */
    for (i = 0; i < (memory_kernel / CHUNK_SIZE) + 1; i++) {
        memory_mark_used(i);
    }

    return 0;
}

static int find_free(int num_chunks) {
    int i, j;
    int start_chunk = (last + 1) % max_chunk; // added this so that it takes the last chunck and increments by 1 and to start the search
    int check = 0; // added this for myself to check if all the chuncks have been checked for free space

    for (i = start_chunk; i < start_chunk + max_chunk; i++) { // starting the loop
        int chunk = i % max_chunk; // making sure that, chunk is "i" divided by max chunck
        if (!memory_test_used(chunk)) {
            for (j = 0; j < num_chunks; j++) {
                if (memory_test_used((chunk + j) % max_chunk)) {
                    check = 0;
                    break;
                }
                check = 1; // I have added the check condition but I am a bit confused if it was a correct thing to do or not
            }
            if (j == num_chunks) {
                last = chunk;
                return chunk;
            }
        }
    }

    if (check) {

        return -1; // return when no free space
    }

    return -1;
}

/* Report the amount of free memory */
int32_t memory_total_free(void) {
    int32_t total_free = 0, i;
    for (i = 0; i < max_chunk; i++) {
        if (!memory_test_used(i)) total_free++;
    }
    return total_free * CHUNK_SIZE;
}

/* allocate an area of memory */
/* rounds up to nearest chunk size */
void *memory_allocate(uint32_t size) {
    int first_chunk;
    int num_chunks;
    int i;

    if (memory_debug) {
        printk("Allocating memory of size %d bytes\n", size);
    }

    if (size == 0) size = 1;

    num_chunks = ((size - 1) / CHUNK_SIZE) + 1;

    if (memory_debug) {
        printk("\tRounding up to %d %d chunks\n", num_chunks, CHUNK_SIZE);
    }

    //added this to allocate some meory & show the error
    first_chunk = find_free(num_chunks);

    if (first_chunk < 0) {
        printk("Error Error Error!! %d bytes of memory!\n", size);
        return NULL;
    }

    for (i = 0; i < num_chunks; i++) {
        memory_mark_used(first_chunk + i);
    }

    if (memory_debug) {
        printk("MEM: Allocated %d bytes at %x\n",
               size, first_chunk * CHUNK_SIZE);
    }

    return (void *)(first_chunk * CHUNK_SIZE);
}


int32_t memory_free(void *location, uint32_t size) {
    int i;
    int num_chunks;
    int first_chunk;

    if (memory_debug) {
        int32_t total;
        total = memory_total_free();
        printk("Free before: %d\n", total);
    }

    num_chunks = ((size - 1) / CHUNK_SIZE) + 1;

    if (memory_debug) {
        printk("Freeing %d bytes (%d CHUNKS) at %x\n",
               size, num_chunks, location);
    }

    first_chunk = (int)location / CHUNK_SIZE;

    /* Poison old memory */
    memset(location, 'V', size);

    for (i = 0; i < num_chunks; i++) {
        memory_mark_free(first_chunk + i);
    }

    if (memory_debug) {
        int32_t total;
        total = memory_total_free();
        printk("Free after: %d\n", total);
    }

    return 0;
}

uint32_t memory_get_total(void) {
    return memory_total;
}

void memory_hierarchy_init(unsigned long memory_kernel) {
    uint32_t start, length;



    hardware_get_memory(&start, &length);

    memory_total = length;

    /* Init memory subsystem */
    memory_init(memory_total, memory_kernel);

    if ((hardware_get_type() == RPI_MODEL_2B) ||
        (hardware_get_type() == RPI_MODEL_3B)) {

        printk("Enabling MMU with 1:1 Virt/Phys page mapping\n");
        enable_mmu(0, memory_total, memory_kernel);
    } else {

        /* Setup Memory Hierarchy */

        // memset_benchmark(memory_total);
        /* Enable L1 i-cache */
        printk("Enabling L1 icache\n");
        enable_l1_icache();

        /* Enable branch predictor */
        printk("Enabling branch predictor\n");
        enable_branch_predictor();

        /* Enable L1 d-cache */
        printk("Enabling MMU with 1:1 Virt/Phys page mapping\n");
        enable_mmu(0, memory_total, memory_kernel);
        printk("Enabling L1 dcache\n");
        enable_l1_dcache();
    }
}