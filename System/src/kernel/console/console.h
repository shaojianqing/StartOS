
typedef struct Console Console;

struct Console {

	byte *buffer;

	u32 width;

	u32 height;

	u32 currentX;

	u32 currentY;

	void (*clear)(Console *this);

	void (*scrollScreen)(Console *this);

	void (*printInfo)(const char* format, ...);

	void (*putChar)(Console *this, char c, char color);

	void (*putBinary)(Console *this, byte data, char color);

	void (*printByte)(Console *this, byte value, char color);

	void (*printInteger)(Console *this, u32 data, char color);

	void (*printString)(Console *this, char *message, char color);
};

void initConsoleSetting();
