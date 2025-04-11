//
// WRITTEN BY: Jeniffer Martinez and Kamden Hayes
//Final Project
// CDA 3103

#include "spimcore.h"

/* ALU */
/* 10 Points */
//check value of ALUControl
//Assign Zero to 1 if the result is zero; otherwise assign 0
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
//Partition instruction into : op, r1, r2, r3, funct, offset, jsec
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
        switch (op) {
        //R-TYPE
        case 0x00000000: 
        controls->RegDst = 1;
        controls->RegWrite = 1;
        controls->Jump = 0;
        controls->Branch = 0;
        controls->MemRead = 0;
        controls->MemtoReg = 0;
        controls->MemWrite = 0;
        controls->ALUOp = 7;
        controls->ALUSrc = 0;
        break;
        
        //ADDI
        case 0x20000000: 
        controls->RegDst = 0;
        controls->RegWrite = 1;
        controls->Jump = 0;
        controls->Branch = 0;
        controls->MemRead = 0;
        controls->MemtoReg = 0;
        controls->MemWrite = 0;
        controls->ALUOp = 0;
        controls->ALUSrc = 1;
        break;
        
        //LW
        case 0x8C000000: 
        controls->RegDst = 0;
        controls->RegWrite = 1;
        controls->Jump = 0;
        controls->Branch = 0;
        controls->MemRead = 1;
        controls->MemtoReg = 1;
        controls->MemWrite = 0;
        controls->ALUOp = 0;
        controls->ALUSrc = 1;
        break;
        
        //SW
        case 0xAC000000:
        controls->RegDst = 0;
        controls->RegWrite = 0;
        controls->Jump = 0;
        controls->Branch = 0;
        controls->MemRead = 0;
        controls->MemtoReg = 0;
        controls->MemWrite = 1;
        controls->ALUOp = 0;
        controls->ALUSrc = 1;
        break;
        
        //LUI
        case 0x3C000000:
        controls->RegDst = 0;
        controls->RegWrite = 1;
        controls->Jump = 0;
        controls->Branch = 0;
        controls->MemRead = 0;
        controls->MemtoReg = 0;
        controls->MemWrite = 0;
        controls->ALUOp = 6;
        controls->ALUSrc = 1;
        break;
        
        //SLTI
        case 0x28000000: 
        controls->RegDst = 0;
        controls->RegWrite = 1;
        controls->Jump = 0;
        controls->Branch = 0;
        controls->MemRead = 0;
        controls->MemtoReg = 0;
        controls->MemWrite = 0;
        controls->ALUOp = 2;
        controls->ALUSrc = 1;
        break;
        
        //SLTIU
        case 0x2C000000: 
        controls->RegDst = 0;
        controls->RegWrite = 1;
        controls->Jump = 0;
        controls->Branch = 0;
        controls->MemRead = 0;
        controls->MemtoReg = 0;
        controls->MemWrite = 0;
        controls->ALUOp = 3;
        controls->ALUSrc = 1;
        break;
        
        //BEQ
        case 0x10000000:
        controls->RegDst = 2; 
        controls->RegWrite = 0;
        controls->Jump = 0;
        controls->Branch = 1;
        controls->MemRead = 0;
        controls->MemtoReg = 2; 
        controls->MemWrite = 0;
        controls->ALUOp = 1; 
        controls->ALUSrc = 0;
        break;
    
        //Jump
        case 0x08000000:
        controls->RegDst = 2;
        controls->RegWrite = 0;
        controls->Jump = 1;
        controls->Branch = 0;
        controls->MemRead = 0;
        controls->MemtoReg = 2;
        controls->MemWrite = 0;
        controls->ALUOp = 2;
        controls->ALUSrc = 2;
        break;
        
        //Halt if no case is met in switch statement
        default: return 1;
    }
    
    //Return 0 if switch statement is broken out of
    return 0;
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
//Assign the sign-extended value of offset to extended_value
void sign_extend(unsigned offset,unsigned *extended_value)
{
        //Masks for checking sign and adding one to the first 16 bits (if needed)
        unsigned signCheckMask = 0x00008000;
        unsigned incrementMask = 0xffff0000;
        unsigned result = offset & signCheckMask;

        //Negative Case
        if(result > 1){
            //Set first 16 bits to one to show a negative
            *extended_value = offset | incrementMask;
        }
        //Positive Case
        if(result == 0){
            //Put 0 in first 16 bits to show a positive
            *extended_value = offset;
        }
}

int rType_Decode(unsigned data1, unsigned data2, unsigned funct, unsigned *ALUresult, char *Zero) {
    switch(funct){
            //ADD
            case 32:
            ALU(data1, data2, 0, ALUresult, Zero);
            break;

            //SUBTRACT
            case 34: 
            ALU(data1, data2, 1, ALUresult, Zero);
            break;

            //OR
            case 37:
            ALU(data1, data2, 5, ALUresult, Zero);
            break;
            
            //AND
            case 36:
            ALU(data1, data2, 4, ALUresult, Zero);
            break;

            //SLT
            case 42:
            ALU(data1, data2, 2, ALUresult, Zero);
            break;

            //SLTU
            case 43:
            ALU(data1, data2, 3, ALUresult, Zero);
            break;

            //Return 1 to halt if none of the cases are met
            default:return 1;
    }
    //Don't halt if the switch is broken out of
    return 0;
}

/* ALU operations */
/* 10 Points */
// use ALU on inputs based on ALUop and funct
//Return 1 if a halt condition occurs; otherwise, return 0.
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{
      switch (ALUOp) {
        //In all cases with "if(ALUSrc==1)", if the ALUSrc variable is one then extended_value is used instead of data2

        //ADD
        case 0: 
        if (ALUSrc == 1){
            ALU(data1, extended_value, ALUOp, ALUresult, Zero);
        }
        else{ 
            ALU(data1, data2, ALUOp, ALUresult, Zero);
        }
        break;

        //SUB
        case 1: 
        if (ALUSrc == 1){
            ALU(data1, extended_value, ALUOp, ALUresult, Zero);
        }
        else{
            ALU(data1, data2, ALUOp, ALUresult, Zero);
        }
        break;

        //SLT
        case 2: 
        if (ALUSrc == 1){
            ALU(data1, extended_value, ALUOp, ALUresult, Zero);
        }
        else{
            ALU(data1, data2, ALUOp, ALUresult, Zero);
        }
        break;

        //SLTU
        case 3:
        if (ALUSrc == 1){
            ALU(data1, extended_value, ALUOp, ALUresult, Zero);
        }
        else{
            ALU(data1, data2, ALUOp, ALUresult, Zero);
        }        
        break;
        
        //AND
        case 4:
        if (ALUSrc == 1){
            ALU(data1, extended_value, ALUOp, ALUresult, Zero);
        }
        else{
            ALU(data1, data2, ALUOp, ALUresult, Zero);
        }
        break;

        //OR
        case 5: 
        if (ALUSrc == 1){
            ALU(data1, extended_value, ALUOp, ALUresult, Zero);
        }
        else{
            ALU(data1, data2, ALUOp, ALUresult, Zero);
        }    
        break;
        //SLL
        case 6:
        if (ALUSrc == 1){
            ALU(data1, extended_value, ALUOp, ALUresult, Zero);
        }
        else{
            ALU(data1, data2, ALUOp, ALUresult, Zero);
        }
        break;
        
        //R-TYPE
        case 7:
        return rType_Decode(data1, data2, funct, ALUresult, Zero);
        break;

        //Return 1 if none of the switch cases were met (Halt)
        default: return 1;
        }
    
    //If the swtich is broken out of then return 0 to signal no halt
    return 0;
}

/* Read / Write Memory */
/* 10 Points */
/* 10 Points */
//determine if a memory write operation or memory read operation or neither
//reading from memory --> ALUresult to memdata
//writing to memory --> write value of data2 to memory location ALUresult
//Return 1 if a halt condition occurs; otherwise, return 0.
int rw_memory(unsigned ALUresult, unsigned data2, char MemWrite, char MemRead, unsigned *memdata, unsigned *Mem)
{
    for (int i = 0; i < 2; i++) {
        if (i == 0 && MemRead) {
            if ((ALUresult % 4 == 0) && ALUresult < 65536)
                *memdata = Mem[ALUresult >> 2];
            else
                return 1;
        }

        if (i == 1 && MemWrite) {
            if ((ALUresult % 4 == 0) && ALUresult < 65536)
                Mem[ALUresult >> 2] = data2;
            else
                return 1;
        }
    }

    return 0;
}



/* Write Register */
/* 10 Points */
//Write data ALUresult or memdata to r2 or r3
void write_register(unsigned r2, unsigned r3, unsigned memdata, unsigned ALUresult, char RegWrite, char RegDst, char MemtoReg, unsigned *Reg)
{
      
    if (RegWrite == 1) // write to register
    {
        if (RegDst == 1)
        {
            if (MemtoReg == 1) // memdata written to register
            {
                Reg[r3] = memdata; //memdata to register 3
            }
            else
            {
                Reg[r3] = ALUresult; // ALUresult to register 3
            }
        }


        else // RegDst == 0;
        {
            if (MemtoReg == 1)
            {
                Reg[r2] = memdata; // memdata to register 2
            }
            else
            {
                Reg[r2] = ALUresult; // ALUresult to register 2
            }
        }
    }
}

/* PC update */
/* 10 Points */
//Update the program counter (PC).
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{
          // Go to next instruction if not a branch or jump
    if(Jump == 0x0 && Branch == 0x0){
        *PC += 4;
    }

    //Jump operation
    if(Branch == 0x0 && Jump == 0x1){
        unsigned PC4Bits = (*PC + 4) & 0xF0000000;
        unsigned shift = jsec<<2;
        *PC = PC4Bits | shift;
    }

    //Branch Operation
    if(Branch == 0x1 && Jump == 0x0 && Zero == 0x1){
        *PC = (extended_value << 2) + (*PC + 4);
    }
}



