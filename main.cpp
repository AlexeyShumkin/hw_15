#include "ht_chat.h"

int main()
{
	Chat c;
	c.reg((char*)"l1", (char*)"p1", sizeof("p1"));
	c.reg((char*)"l2", (char*)"p2", sizeof("p2"));
	c.reg((char*)"l3", (char*)"p3", sizeof("p3"));
	c.reg((char*)"l4", (char*)"p4", sizeof("p4"));
	c.reg((char*)"l5", (char*)"p5", sizeof("p5"));
	c.reg((char*)"l6", (char*)"p6", sizeof("p6"));
	c.reg((char*)"l7", (char*)"p7", sizeof("p7"));
	c.reg((char*)"l8", (char*)"p8", sizeof("p8"));
	c.reg((char*)"l9", (char*)"p9", sizeof("p9"));
	c.reg((char*)"l10", (char*)"p10", sizeof("p10"));
	c.reg((char*)"l11", (char*)"p11", sizeof("p11"));
	c.login((char*)"l10", (char*)"p10", sizeof("p10"));
	c.login((char*)"l12", (char*)"p12", sizeof("p12"));
	c.login((char*)"l10", (char*)"p100", sizeof("p10"));
}