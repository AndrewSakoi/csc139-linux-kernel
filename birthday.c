//Andrew Sakoi
//CSC139 Section 3
//Programming Assignment 1
//birthday.c

#include <linux/module.h>   /* Needed by all modules  */
#include <linux/kernel.h>   /* Needed for KERN_INFO   */
#include <linux/init.h>     /* Needed for the macros  */
#include <linux/list.h>     /* Needed for linked list */
#include <linux/types.h>    /* Needed for list macros */
#include <linux/slab.h>     /* Needed for Kernel */
#include <linux/sort.h>

#define DRIVER_AUTHOR       "Andrew Sakoi" /* My name */
#define DRIVER_DESC         "Assignment1" /* Description of this Kernel */
#define DRIVER_LICE         "GPL" /* License Info */
#define NUM_OF_BIRTHDAYS    6

/* Birthday struct  */
typedef struct _birthday {

	int day;
	int month;
	int year;
	char* name;
	struct list_head list;

}birthday;
/* Declare and init the head of the linked list. */
LIST_HEAD(birthday_list);

/*
This function is called when the module is loaded.
It initializes the birthday struct vallues,
allocates memory for a struct element and creates
and inserts 5 birthdays into the list.
Then prints each birthday to to the kernel log
*/
//return negative value if A before B
//compares years/day/months and returns -1,0,1
 int  compare_birthdays(void *priv,struct list_head *a,struct list_head *b){


	int returnValue = 0;
	if(a!=NULL && b!=NULL){


	 birthday *ptrA= container_of(a, birthday,list);

	 birthday *ptrB= container_of(b, birthday,list);

	int yearA = ptrA->year;
	int yearB = ptrB->year;
	int monthA =ptrA->month;
	int monthB =ptrB->month;
	int dayA = ptrA->day;
	int dayB = ptrB->day;




	if(yearA >yearB)
		returnValue= 1;
	else if(yearA<yearB)
		returnValue= -1;
	else {
		if(monthA>monthB)
			returnValue= 1;
		else if(monthA<monthB)
			returnValue= -1;
		else{
			if(dayA>dayB)
				returnValue= 1;
			else if(dayA<dayB)
				returnValue= -1;
			else returnValue= 0;
		}

	}

	}
	return returnValue;
}




int birthdayList_init(void) {

	printk(KERN_INFO "Loading Module\n");

	char name1[15] = "Mallory";
	char name2[15] = "Bob";
	char name3[15] = "Kate";
	char name4[15] = "Alice";
	char name5[15] = "Nancy";
	/* Allocate 5 birthdays from kernel */
	char * month[12] = {"Jan","Feb","March","April","May","June","July","August","Sept","Oct","Nov","Dec"};


	birthday *person;
	int i = 0;

		/* Request malloc to the kernel. */
		person = kmalloc(sizeof(*person), GFP_KERNEL);
		/* Assign value to the struct. */
		person->name = name5;
		person->day = 9;
		person->month = 6;
		person->year = 2003;
		/* Init the list within the struct. */
		INIT_LIST_HEAD(&person->list);
		/* Add this struct to the tail of the list. */
		list_add_tail(&person->list, &birthday_list);
		person = kmalloc(sizeof(*person), GFP_KERNEL);
		/* Assign value to the struct. */
		person->name = name1;
		person->day = 12;
		person->month = 9;
		person->year = 1958;
		/* Init the list within the struct. */
		INIT_LIST_HEAD(&person->list);
		/* Add this struct to the tail of the list. */
		list_add_tail(&person->list, &birthday_list);

		person = kmalloc(sizeof(*person), GFP_KERNEL);
		/* Assign value to the struct. */
		person->name = name3;
		person->day = 8;
		person->month = 3;
		person->year = 1978;
		/* Init the list within the struct. */
		INIT_LIST_HEAD(&person->list);
		/* Add this struct to the tail of the list. */
		list_add_tail(&person->list, &birthday_list);

		person = kmalloc(sizeof(*person), GFP_KERNEL);
		/* Assign value to the struct. */
		person->name = name4;
		person->day = 1;
		person->month = 9;
		person->year = 1999;
		/* Init the list within the struct. */
		INIT_LIST_HEAD(&person->list);
		/* Add this struct to the tail of the list. */
		list_add_tail(&person->list, &birthday_list);

		person = kmalloc(sizeof(*person), GFP_KERNEL);
		/* Assign value to the struct. */
		person->name = name2;
		person->day = 8;
		person->month = 3;
		person->year = 1978;
		/* Init the list within the struct. */
		INIT_LIST_HEAD(&person->list);
		/* Add this struct to the tail of the list. */
		list_add_tail(&person->list, &birthday_list);

		printk(KERN_INFO "Pre Sort\n");
		/* Go thru the list and print. */
		birthday *ptr ;
		list_for_each_entry(ptr, &birthday_list, list) {

			printk(KERN_INFO "%s born on %s %d, Year %d;\n",
			ptr->name,
			month[ptr->month],
			ptr->day,
			ptr->year);
		}

		printk(KERN_INFO "Post Sort\n");
		list_sort(NULL,&birthday_list,compare_birthdays);
		list_for_each_entry(ptr, &birthday_list, list) {

			printk(KERN_INFO "%s born on %s %d, Year %d;\n",
			ptr->name,
			month[ptr->month],
			ptr->day,
			ptr->year);
		}

	return 0;
}




/*
This function is called when the module is removed.
It prints the list of birthdays being removed, and
then deletes the list from kernel memory
*/
void birthdayList_exit(void) {

	printk(KERN_INFO "Removing Module\n");

	/* Go thru the list and free the memory. */
	birthday *ptr, *next;
	list_for_each_entry_safe(ptr, next, &birthday_list, list) {

		printk(KERN_INFO "Removing Birthday: Month %d Day %d Year %d\n",
			ptr->month,
			ptr->day,
			ptr->year);
		/*Delete list using included functions*/
		list_del(&ptr->list);
		/*free list memory*/
		kfree(ptr);

	}

	printk(KERN_INFO "Memory free done\n");

}

/* Macros for registering module entry and exit points. */
module_init(birthdayList_init);
module_exit(birthdayList_exit);

MODULE_LICENSE(DRIVER_LICE);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR(DRIVER_AUTHOR);









