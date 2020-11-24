#include "../../defs.h"

/*
	IO Test:
		- Configures MPRJ pins
		- Nothing else to do: spinet is autonomous
*/

#define PROJECT 3
#define NUMNODES 6

void main()
{
	/* 
	IO Control Registers
	| DM     | VTRIP | SLOW  | AN_POL | AN_SEL | AN_EN | MOD_SEL | INP_DIS | HOLDH | OEB_N | MGMT_EN |
	| 3-bits | 1-bit | 1-bit | 1-bit  | 1-bit  | 1-bit | 1-bit   | 1-bit   | 1-bit | 1-bit | 1-bit   |

	Output: 0000_0110_0000_1110  (0x1808) = GPIO_MODE_USER_STD_OUTPUT
	| DM     | VTRIP | SLOW  | AN_POL | AN_SEL | AN_EN | MOD_SEL | INP_DIS | HOLDH | OEB_N | MGMT_EN |
	| 110    | 0     | 0     | 0      | 0      | 0     | 0       | 1       | 0     | 0     | 0       |

	Output: 0000_0110_0000_1111  (0x1809) = GPIO_MODE_MGNT_STD_OUTPUT
	| DM     | VTRIP | SLOW  | AN_POL | AN_SEL | AN_EN | MOD_SEL | INP_DIS | HOLDH | OEB_N | MGMT_EN |
	| 110    | 0     | 0     | 0      | 0      | 0     | 0       | 1       | 0     | 0     | 1       |
	
	 
	Input: 0000_0001_0000_1111 (0x0402) = GPIO_MODE_USER_STD_INPUT_NOPULL
	| DM     | VTRIP | SLOW  | AN_POL | AN_SEL | AN_EN | MOD_SEL | INP_DIS | HOLDH | OEB_N | MGMT_EN |
	| 001    | 0     | 0     | 0      | 0      | 0     | 0       | 0       | 0     | 1     | 0       |

	*/

    /*
          Inputs       | Outputs
	Node  MOSI SCK  SS   MISO TXRDY RXRDY
	0     0    1     2    3    4     7
	1     8    9    10   11   12    13
	2     14   15   16   17   18    19
	3     20   21   22   23   24    25
	4     26   27   28   29   30    31
	5     32   33   34   35   36    37

    */

	volatile uint32_t *io = &reg_mprj_io_0;
	*io++ = GPIO_MODE_USER_STD_INPUT_NOPULL;
	*io++ = GPIO_MODE_USER_STD_INPUT_NOPULL;
	*io++ = GPIO_MODE_USER_STD_INPUT_PULLUP;
	*io++ = GPIO_MODE_USER_STD_OUTPUT;
	*io++ = GPIO_MODE_USER_STD_OUTPUT;
	io += 2;
	*io++ = GPIO_MODE_USER_STD_OUTPUT;
	for (int i = 1; i < NUMNODES; i++) {
		*io++ = GPIO_MODE_USER_STD_INPUT_NOPULL;
		*io++ = GPIO_MODE_USER_STD_INPUT_NOPULL;
		*io++ = GPIO_MODE_USER_STD_INPUT_PULLUP;
		*io++ = GPIO_MODE_USER_STD_OUTPUT;
		*io++ = GPIO_MODE_USER_STD_OUTPUT;
		*io++ = GPIO_MODE_USER_STD_OUTPUT;
	}
			
    /* Apply configuration */
    reg_mprj_xfer = 1;
    while (reg_mprj_xfer == 1);

    // change to project
    reg_mprj_slave = PROJECT;

    // use logic analyser bit 0 as reset
    reg_la0_ena  = 0x00000000; // bits 31:0 outputs
    reg_la0_data = 0x00000001; // reset high is on bit 0
    reg_la0_data = 0x00000000; // low

}
