//
// Jeniffer Martinez
// CDA 3103
#include "spimcore.h"


/* ALU */
/* 10 Points */
//check value of ALUControl
void ALU(unsigned A, unsigned B, char ALUControl, unsigned *ALUresult, char *Zero)
{
      //addition - 000
    if (ALUControl == 0) {
        // Addition
        *ALUresult = A + B;
    }

    //subtraction - 001
    else if (ALUControl == 1) {
        // Subtraction
        *ALUresult = A - B;
    }

    // if A < B, Z = 1; otherwise, Z = 0  - 010
    else if (ALUControl == 2) {
        if ((int)A < (int)B) {
            *ALUresult = 1;
        } else {
            *ALUresult = 0;
        }
    }

    //if A < B, Z = 1; otherwise, Z = 0 (A and B are unsigned integers) - 011
    else if (ALUControl == 3) {
        if (A < B) {
            *ALUresult = 1;
        } else {
            *ALUresult = 0;
        }
    }

    //AND - 100
    else if (ALUControl == 4) {
        // AND
        *ALUresult = A & B;
    }

    //OR - 101
    else if (ALUControl == 5) {
        // OR (bitwise)
        *ALUresult = A | B;
    }

    //Z = Shift B left by 16 bits - 110
    else if (ALUControl == 6)
    {
        *ALUresult = B << 16;
    }

    //NOT A - 111
    else if (ALUControl == 7)
    {
        *ALUresult = ~A;
    }

    //base case
    else {
        *ALUresult = 0;
    }


    if (*ALUresult == 0) {
        *Zero = 1;
    } else {
        *Zero = 0;
    }
}


/* instruction fetch */
/* 10 Points */
//get instruction from PC and write to instruction
//Return 1 if halt condition occurs; otherwise, return 0.
// note: PC unsigned
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
    if (PC & 3 || PC > 65532)
        return 1;
    else{
        *instruction = Mem[(PC>>2)];
        return 0;
    }
}


/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
    *op = (instruction & 0xFC000000) >> 26;
    *r1 = (instruction >> 21) & 0x1F; // instruction [25-21]
    *r2 = (instruction >> 16) & 0x1F; // instruction [20-16]
    *r3 = (instruction >> 11) & 0x1F; // instruction [15-11]
    *funct = (instruction & 0x3F);
    *offset = (instruction & 0xFFFF);
    *jsec = (instruction & 0x3FFFFFF);
}



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{

}

/* Read Register */
/* 5 Points */
// read registers and store into data1 and data2
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{
    *data1 = Reg[r1];
    *data2 = Reg[r2];
}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{

}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{

}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{

}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{

}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{

}

