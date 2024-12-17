#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include <linux/list.h>
#include "hello1.h"

MODULE_AUTHOR("Artem Protsenko");
MODULE_DESCRIPTION("Module 1.");
MODULE_LICENSE("Dual BSD/GPL");

struct time_entry {
    struct list_head list;
    ktime_t start_time;
    ktime_t end_time;
};

static LIST_HEAD(time_list);

void print_hello(void)
{
    struct time_entry *entry;
    entry = kmalloc(sizeof(*entry), GFP_KERNEL);

    entry->start_time = ktime_get();
    pr_info("Hello, World!\n");
    entry->end_time = ktime_get();

    list_add_tail(&entry->list, &time_list);
}

EXPORT_SYMBOL(print_hello);

static void __exit hello1_exit(void) {
    struct time_entry *entry, *tmp;

    list_for_each_entry_safe(entry, tmp, &time_list, list) {
        pr_info("Time spent on print %lld ns\n", ktime_to_ns(ktime_sub(entry->end_time, entry->start_time)));
        list_del(&entry->list);
        kfree(entry);
    }
    pr_info("Goodbye, World 1!\n");
}

module_exit(hello1_exit);