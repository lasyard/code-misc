/* To compile it, first write a Makefile contains this
 * obj-m += kernel_setkeycode.o
 * then execute make
 * make -C /lib/modules/$(uname -r)/build M=$(pwd) modules
 */

#include <linux/input.h>
#include <linux/module.h>

static unsigned char test_keycode[] = {
    [0x01] = KEY_1,
    [0x02] = KEY_2,
    [0x03] = KEY_3,
    [0x04] = KEY_4,
};

static struct input_dev *test_dev;

static int test_dev_setkeycode(struct input_dev *dev, int scancode, int keycode)
{
    pr_err("scancode = %d, keycode = %d.\n", scancode, keycode);
    return 0;
}

static int __init test_dev_init(void)
{
    int i;
    int err;
    pr_err("test_dev_init()\n");
    /* init input_dev */
    test_dev = input_allocate_device();
    test_dev->name = "test-dev";
    test_dev->phys = "test";
    test_dev->id.bustype = BUS_PARPORT;
    test_dev->id.vendor = 0x0011;
    test_dev->id.product = 0x0011;
    test_dev->id.version = 0x0110;
    test_dev->evbit[0] = BIT(EV_KEY) | BIT(EV_REP);
    test_dev->keycode = test_keycode;
    test_dev->keycodesize = sizeof(test_keycode[0]);
    test_dev->keycodemax = ARRAY_SIZE(test_keycode);
    for (i = 0; i < ARRAY_SIZE(test_keycode); i++) {
        set_bit(test_keycode[i], test_dev->keybit);
    }
    test_dev->setkeycode = test_dev_setkeycode;
    err = input_register_device(test_dev);
    if (err) {
        pr_err("input_register_device ERR = %d!\n", err);
        input_free_device(test_dev);
        return err;
    }
    return 0;
}

static void __exit test_dev_exit(void)
{
    input_unregister_device(test_dev);
    pr_err("test_dev_exit()\n");
}

MODULE_LICENSE("GPL");

module_init(test_dev_init);
module_exit(test_dev_exit);
