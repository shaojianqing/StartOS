
#define sti() asm ("sti"::)

#define cli() asm ("cli"::)

#define nop() asm ("nop"::)

/* 
 * Clear the interrupt IF bit, so that CPU stop to responde.
 *
 * Parameters:
 * 		no parameters.
 * Return:
 *		no return value.
 */
void clearInterrupt();

/* 
 * Setup the interrupt IF bit, so that CPU can responde.
 *
 * Parameters:
 * 		no parameters.
 * Return:
 *		no return value.
 */
void setupInterruptHlt();

/* 
 * Load the base and limit of GDT table into the GDTR register.
 *
 * Parameters:
 * 		limit: the limit of the GDT table.
 *		 addr: the base address of the GDT table.
 * Return:
 *		no return value.
 */
void loadGdtr(int limit, int addr);

/* 
 * Load the base and limit of IDT table into the IDTR register.
 *
 * Parameters:
 * 		limit: the limit of the IDT table.
 *		 addr: the base address of the IDT table.
 * Return:
 *		no return value.
 */
void loadIdtr(int limit, int addr);

/* 
 * Load the base and limit of IDT table into the IDTR register.
 *
 * Parameters:
 * 		 port: the port where to write the data.
 *		 data: the data to be sent to the port.
 * Return:
 *		no return value.
 */
void outByte(u16 port, u8 data);

/* 
 * Load the base and limit of IDT table into the IDTR register.
 *
 * Parameters:
 *		 port: the port to get the data.
 * Return:
 *		the Data from the port.
 */
u8 inByte(u16 port);

/* 
 * Copy data in the memory from src to dest with count.
 *
 * Parameters:
 *		 dest: the destination in the memory.
 *		  src: the source in the memory
 *		count: the count of the data to be copied.	
 * Return:
 *		no return value..
 */
void memcopy(byte *dest, byte *src, u32 count);

int printk(const char *fmt, ...);