#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include "hello1.h"

MODULE_AUTHOR("Artem Protsenko");
MODULE_DESCRIPTION("Module 2.");
MODULE_LICENSE("Dual BSD/GPL");


static uint repeat_count = 1;
module_param(repeat_count, uint, S_IRUGO);
MODULE_PARM_DESC(repeat_count, "Number of times 'Hello, world!' is printed.");

static int __init hello2_init(void) {
    int i;

    if (repeat_count == 0 || (repeat_count >= 5 && repeat_count <= 10)) {
        pr_warn("Warning repeat_count is 0 or between 5 and 10\n");
    } else if (repeat_count > 10) {
        pr_err("Error repeat_count is greater than 10\n");
        return -EINVAL;
    }

    for (i = 0; i < repeat_count; i++) {
        print_hello();
    }
    return 0;
}

static void __exit hello2_exit(void) {
    pr_info("Goodbye, World 2!\n");
}

module_init(hello2_init);
module_exit(hello2_exit);