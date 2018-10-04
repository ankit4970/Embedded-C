/* ************************************************************************************************
 * funcPointer.c
 *      Basic demostration of how to use callbacks (using function pointer) in C
 *************************************************************************************************/

#include <stdio.h>
#include <stdint.h>

struct file_operations 
{
    void (*read)();         // Callbacks
    void (*write)();
    void (*open)();
    void (*close)();
};

struct miscdevice 
{
    int minor;
    const char *name;
    const struct file_operations *fops;
    const char *nodename;
};

void my_open() 
{
    printf("Open function calle\n");
}

void my_read() 
{
    printf("Read function called\n");
}

void my_write() 
{
    printf("Write function called\n");
}

void my_close() 
{
    printf("close function called\n");
}

static const struct file_operations my_fops = 
{
    .open = &my_open,
    .read = &my_read,
    .write = &my_write,
    .close = &my_close,
};

static struct miscdevice my_device = 
{
    .name = "mydriver",
    .fops = &my_fops,
};

int main() 
{
    printf("Function pointer entry\n");

    printf("Name of driver : %s\n", my_device.name);
    my_device.fops->open();
    my_device.fops->read();
    my_device.fops->write();
    my_device.fops->close();

    return 0;
}
