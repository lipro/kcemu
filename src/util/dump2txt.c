#include <ctype.h>
#include <stdio.h>

/*
 *        AnaDisk 2.07 26-Aug-92
 *
 *
 *                           DUMP DISKETTE TO A DOS FILE
 *
 *        Dump provides a facility to read selected areas of a diskette and
 *        write them to a DOS file.  The range of cylinders to be "dumped"
 *        to diskette, as well as the side of the diskette may be speci-
 *        fied.  This function is not limited to DOS diskettes.
 *
 *        Each sector written to the file is optionally preceded by an 8-
 *        byte header record of the following form:
 *
 *             +------+------+------+------+------+------+---------+
 *             | ACYL | ASID | LCYL | LSID | LSEC | LLEN |  COUNT  |
 *             +------+------+------+------+------+------+---------+
 *
 *                 ACYL    Actual cylinder, 1 byte
 *                 ASID    Actual side, 1 byte
 *                 LCYL    Logical cylinder; cylinder as read, 1 byte
 *                 LSID    Logical side; or side as read, 1 byte
 *                 LSEC    Sector number as read, 1 byte
 *                 LLEN    Length code as read, 1 byte
 *                 COUNT   Byte count of data to follow, 2 bytes.  If zero,
 *                         no data is contained in this sector.
 */

int
dump_header(void)
{
	int acyl, asid, lcyl, lsid, lsec, llen, c, count;

	acyl = getchar(); if (acyl == EOF) return -1;
	asid = getchar(); if (asid == EOF) return -1;
	lcyl = getchar(); if (lcyl == EOF) return -1;
	lsid = getchar(); if (lsid == EOF) return -1;
	lsec = getchar(); if (lsec == EOF) return -1;
	llen = getchar(); if (llen == EOF) return -1;
	c    = getchar(); if (c    == EOF) return -1;
	count = c;
	c    = getchar(); if (c    == EOF) return -1;
	count |= (c << 8);

	printf("H/C/S: %d/%d/%d\n", lsid, lcyl, lsec);
	printf("+------+------+------+------+------+------+-----------+\n");
	printf("| acyl | asid | lcyl | lsid | lsec | llen |     count |\n");
	printf("|  %3d |  %3d |  %3d |  %3d |  %3d |  %3d | %9d |\n",
		acyl, asid, lcyl, lsid, lsec, llen, count);
	printf("+------+------+------+------+------+------+-----------+\n");

	return count;
}

int
dump_sector(void)
{
	unsigned char buf[16];
	int a, b, c, len, blen, ret;

	len = dump_header();
	if (len < 0)
		return -1;

	a = 0;
	ret = 0;
	while (a < len) {
		for (b = 0;b < 16;b++) {
			if ((a + b) >= len)
				break;
			c = getchar();
			if (c == EOF) {
				ret = -1;
				break;
			}
			buf[b] = c;
			blen = b + 1;
		}
		printf("%04x: ", a);
		for (b = 0;b < 16;b++) {
			if (b < blen) {
				printf("%02x ", buf[b]);
			} else {
				printf("   ");
			}
			if (b == 7)
				printf("- ");
		}
		printf(" |  ");
		for (b = 0;b < blen;b++) {
			printf("%c", (isprint(buf[b])) ? buf[b] : '.');
			if (b == 7)
				printf(" - ");
		}
		printf("\n");
		if (blen != 16)
			break;
		a += 16;
	}
	printf("\n");
	
	return ret;
}

int
main(void)
{
	while (242) {
		if (dump_sector() < 0)
			break;
	}
	return 0;
}
