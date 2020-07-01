#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// GD32VF103 is RV32IMAC compliant, so we need to encode the IMAC extensions
#define OPCODE 0x0000007F
#define RD     0x00000F80
#define FUNCT3 0x00007000
#define RS1    0x000F8000
#define RS2    0x01F00000
#define FUNCT7 0xFE000000

// compressed format C
#define C_OPCODE 0x0003
#define C_RS2    0x007C
#define C_RS1    0x0F80
#define C_FUNCT4 0xF000
#define C_FUNCT3 0xE000
#define CI_IMM1  0x1000
#define CSS_IMM  (CI_IMM1 | C_RS1)
#define CIW_IMM  0x1FE0
#define C_RD_    0x001D // needs to be fixed

/*

printbin(-1 & OPCODE);  printf("\n");
printbin(-1 & RD);      printf("\n");
printbin(-1 & FUNCT3);  printf("\n");
printbin(-1 & RS1);     printf("\n");
printbin(-1 & RS2);     printf("\n");
printbin(-1 & FUNCT7);  printf("\n");

outputs:

00000000000000000000000001111111
00000000000000000000111110000000
00000000000000000111000000000000
00000000000011111000000000000000
00000001111100000000000000000000
11111110000000000000000000000000

*/


int base_opcodes[] = {
    
};

// ## RVC Instruction set (64 bit commands removed)

// table of the compressed opcodes ( '-' indicates that the digit is not important to the opcode)
// the hex mask is to be used to filter out the opcode from the other bits,
// i.e "instruction & mask"

/*  Opcode              Hex Mask    Hex Code    Name
    0000000000000000    FFFF        0000        Illegal instruction
    000-----------00    E003        0000        C.ADDI4SPN
    001-----------00    E003        2000        C.FLD
    010-----------00    E003        4000        C.LW
    011-----------00    E003        6000        C.FLW
    100-----------00    E003        8000        Reserved
    101-----------00    E003        A000        C.FSD
    110-----------00    E003        C000        C.SW
    111-----------00    E003        E000        C.FSW
    0000000000000001    FFFF        0001        C.NOP
    000-----------01    E003        0001        C.ADDI
    001-----------01    E003        2001        C.JAL
    010-----------01    E003        4001        C.LI
    011-00010-----01    EF83        6101        C.ADDI16SP
    011-----------01    E003                    C.LUI
    100-00--------01    EC03                    C.SRLI
    100000---0000001    FC7F                    C.SRLI64    (I don't think this command is used on this chip)
    100-10--------01    EC03                    C.ANDI
    100011---00---01    FC63                    C.SUB
    100011---01---01    FC63                    C.XOR
    100011---10---01    FC63                    C.OR
    100011---11---01    FC63                    C.AND
    100111---00---01    FC63                    C.SUBW
    100111---01---01    FC63                    C.ADDW
    100111---10---01    FC63                    Reserved
    100111---11---01    FC63                    Reserved
    101-----------01    E003                    C.J
    110-----------01    E003                    C.BEQZ
    111-----------01    E003                    C.BNEZ
    000-[!=0]-----10    E003                    C.SLLI
    0000[!=0]0000010    F0FF                    C.SLLI64    (I don't think this is used either)
    001-----------10    E003                    C.FLDSP
    010-----------10    E003                    C.LWSP
    011-----------10    E003                    C.FLWSP
    1000-----0000010    F07F                    C.JR
    1000----------10    F003                    C.MV
    1001000000000010    FFFF                    C.EBREAK
    1001-----0000010    F07F                    C.JALR
    1001----------10    F001                    C.ADD
    101-----------10    E003                    C.FSDSP
    110-----------10    E003                    C.SWSP
    111-----------10    E003                    C.FSWSP

*/


/*  Binary              Hex Mask    Name
    
*/


char * compressed_opcodes_ascii[] = {

};

// bits 2 though 6 of the word indicates the base opcode.
// The names of those base opcodes are indexed into base_codes_ascii
// based on those bits. This is mostly for testing and includes
// extensions that our IMAC chip doesn't have.
char * base_opcodes_ascii[] = {
    "LOAD",
    "LOAD-FP",
    "custom-0",
    "MISC-MEM",
    "OP-IMM",
    "AUIPC",
    "OP-IMM-32",
    "48b",
    "STORE",
    "STORE-FP",
    "custom-1",
    "AMO",
    "OP",
    "LUI",
    "OP-32",
    "64b",
    "MADD",
    "MSUB",
    "NMSUB",
    "NMADD",
    "OP-FP",
    "reserved",
    "custom-2/rv128",
    "48b",
    "BRANCH",
    "JLAR",
    "reserved",
    "JAL",
    "SYSTEM",
    "reserved",
    "custom-3/rv128",
    ">=80b"
};

// prints binary of a decimal
void printbin(int input) {
    for(int i = 0; i < 32; i++) {
        if(input & 0x80000000) printf("1");
        else printf("0");

        input = input << 1;
    }
}

// converts a string representation of a hex value into an integer
int hexstr_to_int(char* str) {
    
    int len = strlen(str); len--; // length of the string, indexed at 0
    int output = 0;

    int i = 0;
    while(len >= 0) {
        int digit_value;
        switch(str[i]) {
            case '0': digit_value = 0 ; break;
            case '1': digit_value = 1 ; break;
            case '2': digit_value = 2 ; break;
            case '3': digit_value = 3 ; break;
            case '4': digit_value = 4 ; break;
            case '5': digit_value = 5 ; break;
            case '6': digit_value = 6 ; break;
            case '7': digit_value = 7 ; break;
            case '8': digit_value = 8 ; break;
            case '9': digit_value = 9 ; break;
            case 'A': digit_value = 10; break;
            case 'B': digit_value = 11; break;
            case 'C': digit_value = 12; break;
            case 'D': digit_value = 13; break;
            case 'E': digit_value = 14; break;
            case 'F': digit_value = 15; break;
            default:
                digit_value = 0; 
                printf("Invalid hex format %s\n", str);
        }

        // output += digit*(16^n)
        output += (digit_value * (int) pow((double) 16, (double) len) );

        len--; i++;
    }

    return output;
}

// returns 1 if the first 16 bits encodes a compressed command, 0 if otherwise
int is16(int instruction) {

    // the instruction is 16 bits if the first 2 bits are set
    
    if( (instruction & 3) == 3) return 1;
    
    return 0;
}

int main( int argc, char * argv[] ) {
    
    FILE *fp;

    // printf("Size of int: %d\n\n", sizeof(int));

    // file name is hard-coded because windows doesn't like reading arguments from the command
    // line for some reason. Not sure how to make an executable which executes from the
    // command line with arguments. This will have to do for now
    fp = fopen( "blink.hex", "r" );

    char c; // this will hold one char from the file at a time. Used to find ':' or EOF
    char byte_count_ascii[2 + 1]; // This says how much data in bytes to read
    char address_ascii[4 + 1]; // this gives the address of the following data
    char record_type_ascii[2 + 1]; // this gives the record type
    char data[255 * 2 + 1]; // here's the actual data. it will never be bigger than 255 bytes
    // " + 1 " above is just to have room to terminate the string with a 0

    // these are the integer versions of the ascii after doing ascii->int conversion
    int byte_count;
    int address;
    int record_type;

    while(1) {
        c = fgetc(fp);
        if( feof(fp) ) { // loop breaks at end of file
            break;
        }

        if( c == ':' ) { // begin reading record once ":" is found.

            // I'm not sure if all these values need to be initialized to 0 but might as well be safe
            byte_count = 0;
            address    = 0;
            record_type= 0;

            for(int i = 0; i < 3; i++) byte_count_ascii[i] = 0;
            for(int i = 0; i < 5; i++) address_ascii[i]    = 0;
            for(int i = 0; i < 3; i++) record_type_ascii[i]= 0;
            for(int i = 0; i < 255 * 2; i++) data[i]       = 0;

            // reading the record
            fread(byte_count_ascii, 1, 2, fp);
            fread(address_ascii, 1, 4, fp);
            fread(record_type_ascii, 1, 2, fp);

            byte_count = hexstr_to_int(byte_count_ascii);
            address = hexstr_to_int(address_ascii);
            record_type = hexstr_to_int(record_type_ascii);

            fread(data, 1, byte_count*2, fp);

            // prints the hex info on this line
            /*
            printf("byte count: %d\taddress: 0x%s, %d\trecord type: %d\tdata: %s\n", 
                byte_count, address_ascii, address, record_type, data);
            */

            if(record_type == 0) {
                
                int num_instructions = byte_count / 4;
                char instruction_ascii[8 + 1];
                unsigned int instruction;

                for(int i = 0; i < num_instructions; i++) {
                    
                    memcpy(instruction_ascii, i*8 + data, 8);
                    instruction = hexstr_to_int(instruction_ascii) & OPCODE;
                    
                    if( is16(instruction) ) {
                        instruction = instruction >> 2; // eat the first two bits
                        if(instruction < 32) printf("%s\n", base_opcodes_ascii[instruction]);
                        else printf("%s\n", instruction_ascii);
                    } else { // if the first two bits are not set, we are dealing with a compressed command...
                        printf("%s\n", instruction_ascii);
                    }

                    // printbin(instruction & OPCODE);
                    // printf("\n");

                }
            }
        }
    }

    fclose(fp);
    return(0);

}