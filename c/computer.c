#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include "computer.h"
#undef mips			/* gcc already has a def for mips */

unsigned int endianSwap(unsigned int);

void PrintInfo (int changedReg, int changedMem);
unsigned int Fetch (int);
void Decode (unsigned int, DecodedInstr*, RegVals*);
int Execute (DecodedInstr*, RegVals*);
int Mem(DecodedInstr*, int, int *);
void RegWrite(DecodedInstr*, int, int *);
void UpdatePC(DecodedInstr*, int);
void PrintInstruction (DecodedInstr*);

/*Globally accessible Computer variable*/
Computer mips;
RegVals rVals;

/*
 *  Return an initialized computer with the stack pointer set to the
 *  address of the end of data memory, the remaining registers initialized
 *  to zero, and the instructions read from the given file.
 *  The other arguments govern how the program interacts with the user.
 */
void InitComputer (FILE* filein, int printingRegisters, int printingMemory,
  int debugging, int interactive) {
    int k;
    unsigned int instr;

    /* Initialize registers and memory */

    for (k=0; k<32; k++) {
        mips.registers[k] = 0;
    }
    
    /* stack pointer - Initialize to highest address of data segment */
    mips.registers[29] = 0x00400000 + (MAXNUMINSTRS+MAXNUMDATA)*4;

    for (k=0; k<MAXNUMINSTRS+MAXNUMDATA; k++) {
        mips.memory[k] = 0;
    }

    k = 0;
    while (fread(&instr, 4, 1, filein)) {
	/*swap to big endian, convert to host byte order. Ignore this.*/
        mips.memory[k] = ntohl(endianSwap(instr));
        k++;
        if (k>MAXNUMINSTRS) {
            fprintf (stderr, "Program too big.\n");
            exit (1);
        }
    }

    mips.printingRegisters = printingRegisters;
    mips.printingMemory = printingMemory;
    mips.interactive = interactive;
    mips.debugging = debugging;
}

unsigned int endianSwap(unsigned int i) {
    return (i>>24)|(i>>8&0x0000ff00)|(i<<8&0x00ff0000)|(i<<24);
}

/*
 *  Run the simulation.
 */
void Simulate () {
    char s[40];  /* used for handling interactive input */
    unsigned int instr;
    int changedReg=-1, changedMem=-1, val;
    DecodedInstr d;
    
    /* Initialize the PC to the start of the code section */
    mips.pc = 0x00400000;
    while (1) {
        if (mips.interactive) {
            printf ("> ");
            fgets (s,sizeof(s),stdin);
            if (s[0] == 'q') {
                return;
            }
        }

        /* Fetch instr at mips.pc, returning it in instr */
        instr = Fetch (mips.pc);

        printf ("Executing instruction at %8.8x: %8.8x\n", mips.pc, instr);

        /* 
	 * Decode instr, putting decoded instr in d
	 * Note that we reuse the d struct for each instruction.
	 */
        Decode (instr, &d, &rVals);

        /*Print decoded instruction*/
        PrintInstruction(&d);

        /* 
	 * Perform computation needed to execute d, returning computed value 
	 * in val 
	 */
        val = Execute(&d, &rVals);

	UpdatePC(&d,val);

        /* 
	 * Perform memory load or store. Place the
	 * address of any updated memory in *changedMem, 
	 * otherwise put -1 in *changedMem. 
	 * Return any memory value that is read, otherwise return -1.
         */
        val = Mem(&d, val, &changedMem);

        /* 
	 * Write back to register. If the instruction modified a register--
	 * (including jal, which modifies $ra) --
         * put the index of the modified register in *changedReg,
         * otherwise put -1 in *changedReg.
         */
        RegWrite(&d, val, &changedReg);

        PrintInfo (changedReg, changedMem);
    }
}

/*
 *  Print relevant information about the state of the computer.
 *  changedReg is the index of the register changed by the instruction
 *  being simulated, otherwise -1.
 *  changedMem is the address of the memory location changed by the
 *  simulated instruction, otherwise -1.
 *  Previously initialized flags indicate whether to print all the
 *  registers or just the one that changed, and whether to print
 *  all the nonzero memory or just the memory location that changed.
 */
void PrintInfo ( int changedReg, int changedMem) {
    int k, addr;
    printf ("New pc = %8.8x\n", mips.pc);
    if (!mips.printingRegisters && changedReg == -1) {
        printf ("No register was updated.\n");
    } else if (!mips.printingRegisters) {
        printf ("Updated r%2.2d to %8.8x\n",
        changedReg, mips.registers[changedReg]);
    } else {
        for (k=0; k<32; k++) {
            printf ("r%2.2d: %8.8x  ", k, mips.registers[k]);
            if ((k+1)%4 == 0) {
                printf ("\n");
            }
        }
    }
    if (!mips.printingMemory && changedMem == -1) {
        printf ("No memory location was updated.\n");
    } else if (!mips.printingMemory) {
        printf ("Updated memory at address %8.8x to %8.8x\n",
        changedMem, Fetch (changedMem));
    } else {
        printf ("Nonzero memory\n");
        printf ("ADDR	  CONTENTS\n");
        for (addr = 0x00400000+4*MAXNUMINSTRS;
             addr < 0x00400000+4*(MAXNUMINSTRS+MAXNUMDATA);
             addr = addr+4) {
            if (Fetch (addr) != 0) {
                printf ("%8.8x  %8.8x\n", addr, Fetch (addr));
            }
        }
    }
}

/*
 *  Return the contents of memory at the given address. Simulates
 *  instruction fetch. 
 */
unsigned int Fetch ( int addr) {
    return mips.memory[(addr-0x00400000)/4];
}

/* Decode instr, returning decoded instruction. */
void Decode ( unsigned int instr, DecodedInstr* d, RegVals* rVals) {
    /* Your code goes here */
    
    /// R-format
    // opcode   rs      rt      rd      shamt   func
    // 31-26    25-21   20-16   15-11   10-6    6-0
    
    /// I-format
    // opcode   rs      rt      imm
    // 31-26    25-21   20-16   15-0
    
    /// J-format
    // opcode   address
    // 31-26    26-0
    
    // Grab the first 6 bits of the instruction, which contains the opcode.
    d->op = instr >> 26;
    
    // Depending on the opcode, the decoding varies...
    switch(d->op) {
        // All R-format instructions have an opcode of 0 (the first 6 bits).
        case 0x0: {
            d->type = R;
            // Mask for 5 bits after the first 6, then shift by 21 which leaves you the 5 bit rs.
            d->regs.r.rs = (instr & 0x3e00000) >> 21;
            // Do essentially the same operation using a different mask and shift amount for rs & rd.
            d->regs.r.rt = (instr & 0x1f0000) >> 16;
            d->regs.r.rd = (instr & 0xf800) >> 11;
            d->regs.r.shamt = (instr & 0x7c0) >> 6;
            d->regs.r.funct = instr & 0x3f; // No need for a shift since funct is simply the remaining 6 bits.
            
            // Since we cannot write to the $0 register, so we exit.
            // The exception is with funct code 0x8 which is for `jr`, which doesn't use rd.
            if((instr & 0x3f) != 0x8 && d->regs.r.rd == 0)   //Cannot write $0, exclude jr
                exit(0);

            rVals->R_rs = mips.registers[d->regs.r.rs];
            rVals->R_rt = mips.registers[d->regs.r.rt];
            rVals->R_rd = mips.registers[d->regs.r.rd];
            break;
        }
        // For all J-format instructions...
        case 0x2: // simply move onto 0x3 which is the same
        case 0x3:
            d->type = J;
            int target = (instr & 0x3FFFFFF) << 2;
            d->regs.j.target = target + (mips.pc & 0xF0000000);
            break;
            // & 0x3FFFFFF is a mask that gets bits 26-0.
            // & 0xF0000000 is a mask for the 4 most significant bits
        // For any other opcode, it is going to be an I-format instruction.
        default:
            d->type = I;
            
            d->regs.r.rs = (instr & 0x3e00000) >> 21;
            d->regs.r.rt = (instr & 0x1f0000) >> 16;

            // With the exception of `beq`, `bne`, and `sw`, we cannot write to $0 register.
            // Aforementioned registers simply don't make use of rt.
            if(d->op != 0x2b && d->op != 0x4 && d->op != 0x5  && d->regs.r.rt == 0)
                exit(0);
            
            rVals->R_rs = mips.registers[d->regs.r.rs];
            rVals->R_rt = mips.registers[d->regs.r.rt];
            
            // This remaining switch statement deals with how to handle the immediate,
            // which depends on the opcode...
            
            // For ease of use, let's declare a temporary holder for the immediate.
            int immediate = instr & 0xFFFF; // This only looks at the last 16 bits.
            
            switch (d->op) {
                // For `beq` and `bne`, it is the same...
                case 0x4:
                case 0x5:
                    immediate = immediate << 2;
                    
                    // Look at the 16th bit (done by ANDing with 0b1000000000000000)
                    if (immediate & 0b1000000000000000) {
                        immediate += immediate & 0xFFFC0000; // The 16th bit is 1, so, we must sign-extend.
                        // Note that 0xFFFC0000 is 1111 1111 1111 1100 0000 0000 0000 0000
                    }
                    
                    immediate += mips.pc + 4; // Convert to 32 bits
                    break;
                // For `addiu`, `lw`, and `sw`, we do...
                case 0x9:
                case 0x23:
                case 0x2b:
                    if (immediate & 0b1000000000000000) {
                        immediate += 0xffff0000;
                        // We pad it all with 1's.
                    }
                    break;
                // For `lui`...
                case 0xf:
                    // We pad the immediate with 16 zeroes on the right
                    immediate = immediate << 16;
                    break;
                default:
                    break;
            }
            
            d->regs.i.addr_or_immed = immediate;
            
            break;
        }
    }


/*
 *  Print the disassembled version of the given instruction
 *  followed by a newline.
 */
void PrintInstruction ( DecodedInstr* d) {
    /* Your code goes here */

    switch(d->op){ //checks format based on op
        case 0x0: //R format
            switch(d->regs.r.funct){ //checks instruction based on funct
                //addu Rdest, Rsrc1, Rsrc2
                case 0x21:
                    printf("addu\t $%d, $%d, $%d\n", d->regs.r.rd, d->regs.r.rs, d->regs.r.rt);
                    break;
                //subu Rdest, Rsrc1, Rsrc2
                case 0x23:
                    printf("subu\t $%d, $%d, $%d\n", d->regs.r.rd, d->regs.r.rs, d->regs.r.rt);
                    break;
                //sll Rdest, Rsrc, shamt
                case 0x00:
                    printf("sll\t $%d, $%d, $%d\n", d->regs.r.rd, d->regs.r.rt, d->regs.r.shamt);
                    break;
                //srl Rdest, Rsrc, shamt
                case 0x02:
                    printf("srl\t $%d, $%d, $%d\n", d->regs.r.rd, d->regs.r.rt, d->regs.r.shamt);
                    break;
                //and Rdest, Rsrc1, Rsrc2
                case 0x24:
                    printf("and\t $%d, $%d, $%d\n", d->regs.r.rd, d->regs.r.rs, d->regs.r.rt);
                    break;
                //or Rdest, Rsrc1, Rsrc2
                case 0x25:
                    printf("or\t $%d, $%d, $%d\n", d->regs.r.rd, d->regs.r.rs, d->regs.r.rt);
                    break;
                //slt Rdest, Rsrc1, Rsrc2
                case 0x2a:
                    printf("slt\t $%d, $%d, $%d\n", d->regs.r.rd, d->regs.r.rs, d->regs.r.rt);
                    break;
                //jr Rsrc
                case 0x8:
                    printf("jr\t $31\n");
                    break;
                default:
                    break;
            }
            break;

        case 0x2: //J format (j instruction)
            //j address
             printf("j\t 0x%.8x\n", d->regs.j.target);
                break;

        case 0x3: //J format (jal instruction)
            //jal address
            printf("jal\t 0x%.8x\n", d->regs.j.target);
            break;
        
        default: //I format
            switch(d->op){ //checks for instruction based on op
                //addiu Rdest, Rsrc1, imm
                case 0x9:
                    printf("addiu\t $%d, $%d, %d\n", d->regs.i.rt, d->regs.i.rs, d->regs.i.addr_or_immed);
                    break;
                //andi Rdest, Rsrc, imm
                case 0xc:
                    printf("andi\t $%d, $%d, 0x%x\n", d->regs.i.rt, d->regs.i.rs, d->regs.i.addr_or_immed);
                    break;
                //ori Rdest, Rsrc, imm
                case 0xd:
                    printf("ori\t $%d, $%d, 0x%x\n", d->regs.i.rt, d->regs.i.rs, d->regs.i.addr_or_immed);
                    break;
                //lui Rdest, imm
                case 0xf:
                    printf("lui\t $%d, 0x%x\n", d->regs.i.rt, d->regs.i.addr_or_immed >> 16);
                    break;
                //beq Rsrc1, Rsrc2, raddr
                case 0x4:
                    printf("beq\t $%d, $%d, 0x%.8x\n", d->regs.i.rs, d->regs.i.rt, d->regs.i.addr_or_immed);
                    break;
                //bne Rsrc1, Rsrc2, raddr
                case 0x5:
                    printf("bne\t $%d, $%d, 0x%.8x\n", d->regs.i.rs, d->regs.i.rt, d->regs.i.addr_or_immed);
                    break;
                //lw Rdest, offset (Radd)
                case 0x23:
                    printf("lw\t $%d, %d($%d)\n", d->regs.i.rt, d->regs.i.addr_or_immed, d->regs.i.rs);
                    break;
                //sw Rsrc, offset (Radd)
                case 0x2b:
                    printf("sw\t $%d, %d($%d)\n", d->regs.i.rt, d->regs.i.addr_or_immed, d->regs.i.rs);
                    break;
                default:
                    break;
            }
            break;
    }
}

/* Perform computation needed to execute d, returning computed value */
int Execute ( DecodedInstr* d, RegVals* rVals) {
    /* Your code goes here */
    int value = 0; //value to compute based on the MIPS operation

    switch(d->op) { //checks format based on op
        case 0x0: //R format
            switch(d->regs.r.funct){ //checks instruction based on funct
                //addu Rdest, Rsrc1, Rsrc2
                //R[rd] = R[rs] + R[rt]
                case 0x21:
                    value = (unsigned int)rVals->R_rs + (unsigned int)rVals->R_rt;
                    break;
                //subu Rdest, Rsrc1, Rsrc2
                //R[rd] = R[rs] - R[rt]
                case 0x23:
                    value = (unsigned int)rVals->R_rs - (unsigned int)rVals->R_rt;
                    break;
                //sll Rdest, Rsrc, shamt
                //R[rd] = R[rt] << shamt
                case 0x00:
                    value = rVals->R_rs << d->regs.r.shamt;
                    break;
                //srl Rdest, Rsrc, shamt
                //R[rd] = R[rt] >> shamt
                case 0x02:
                    value = rVals->R_rs >> d->regs.r.shamt;
                    break;
                //and Rdest, Rsrc1, Rsrc2
                //R[rd] = R[rs] & R[rt]
                case 0x24:
                    value = rVals->R_rs & rVals->R_rt;
                    break;
                //or Rdest, Rsrc1, Rsrc2
                //R[rd] = R[rs] | R[rt]
                case 0x25:
                    value = rVals->R_rs | rVals->R_rt;
                    break;
                //slt Rdest, Rsrc1, Rsrc2
                //R[rd] = (R[rs] < R[rt]) ? 1 : 0
                case 0x2a:
                    if (rVals->R_rs < rVals->R_rt){
                        value = 1;
                    }
                    break;
                //jr Rsrc
                //PC=R[rs]
                case 0x8:
                    value = mips.registers[d->regs.r.rs];
                    break;
                default:
                    break;
            }
            break;

        case 0x2: //J format (j instruction)
            //j address
            //PC=JumpAddr
            value = d->regs.j.target; //address
            rVals->R_rt = mips.pc + 4; //Update PC counter
            break;

        case 0x3: //J format (jal instruction)
            //jal address
            //R[31]=PC+8;PC=JumpAddr
            value = d->regs.j.target; //address
            rVals->R_rt = mips.pc + 4; //Update PC counter
            break;
        
        default: //I format
            switch(d->op){ //checks for instruction based on op
                //addiu Rdest, Rsrc1, imm
                //R[rt] = R[rs] + SignExtImm
                case 0x9:
                    value = rVals->R_rs + d->regs.i.addr_or_immed;
                    break;
                //andi Rdest, Rsrc, imm
                //R[rt] = R[rs] & ZeroExtImm
                case 0xc:
                    value = rVals->R_rs & d->regs.i.addr_or_immed;
                    break;
                //ori Rdest, Rsrc, imm
                //R[rt] = R[rs] | ZeroExtImm
                case 0xd:
                    value = rVals->R_rs | d->regs.i.addr_or_immed;
                    break;
                //lui Rdest, imm
                //R[rt] = {imm, 16’b0}
                case 0xf:
                    value = d->regs.i.addr_or_immed;
                    break;
                //beq Rsrc1, Rsrc2, raddr
                //if(R[rs]==R[rt])
                //PC=PC+4+BranchAddr
                case 0x4:
                    if(rVals->R_rs == rVals->R_rt) {
                        value = d->regs.i.addr_or_immed;
                    }
                    break;
                //bne Rsrc1, Rsrc2, raddr
                //if(R[rs]!=R[rt])
                //PC=PC+4+BranchAddr
                case 0x5:
                    if(rVals->R_rs != rVals->R_rt) {
                        value = d->regs.i.addr_or_immed;
                    }
                    break;
                //lw Rdest, offset (Radd)
                //R[rt] = M[R[rs]+SignExtImm]
                case 0x23:
                    value = rVals->R_rs + d->regs.i.addr_or_immed;
                    break;
                //sw Rsrc, offset (Radd)
                //M[R[rs]+SignExtImm] = R[rt]
                case 0x2b:
                    value = rVals->R_rs + d->regs.i.addr_or_immed;
                    break;
                default:
                    break;
            }
            break;
    }

    return value; //return computed value
}

/* 
 * Update the program counter based on the current instruction. For
 * instructions other than branches and jumps, for example, the PC
 * increments by 4 (which we have provided).
 */
void UpdatePC ( DecodedInstr* d, int val) {
    mips.pc+=4;
    /* Your code goes here */
    
    /*
     The input that UpdatePC gets comes from Execute().
     Instructions that update the PC include...
              I       J       R
            -beq    -j      -jr
            -bne    -jal
     
     For BEQ and BNE, the value given indicates whether or not
     to take the branch. For J & R instructions, the value given
     is an address to jump to.
     */
    
    // When it's beq or bne...
    if (d->type == I && (d->op == 0x4 || d->op == 0x5)) {
        // Take the branch when val is nonzero.
        if (val) {
                mips.pc = val;
        }
    } else if (d->type == J && (d->op == 0x2 || d->op == 0x3)) { // When it's a `j` or `jal`...
        mips.pc = val; // Correct the PC
    } else if (d->type == R && d->regs.r.funct == 0x08) { // When it's `jr`...
        mips.pc = val;
    }
}

/*
 * Perform memory load or store. Place the address of any updated memory 
 * in *changedMem, otherwise put -1 in *changedMem. Return any memory value 
 * that is read, otherwise return -1. 
 *
 * Remember that we're mapping MIPS addresses to indices in the mips.memory 
 * array. mips.memory[0] corresponds with address 0x00400000, mips.memory[1] 
 * with address 0x00400004, and so forth.
 *
 */
int Mem( DecodedInstr* d, int val, int *changedMem) {
    /* Your code goes here */
    switch(d->op) {
        // For `lw`...
        case 0x23:
            // Lowest 16 bits of address divided by 4...
            val = mips.memory[(val - 0x00400000) / 4];
            return val; // Return the memory that is read...
        // For `sw`...
        case 0x2b:
            mips.memory[(val - 0x00400000) / 4] = mips.registers[d->regs.i.rt];
            *changedMem = val; // Put the address of the updated memory...
            return *changedMem; // Return memory that is read.
        default:
            *changedMem = -1; // nothing changed
    }
    
    return val;
}

/* 
 * Write back to register. If the instruction modified a register--
 * (including jal, which modifies $ra) --
 * put the index of the modified register in *changedReg,
 * otherwise put -1 in *changedReg.
 */
void RegWrite( DecodedInstr* d, int val, int *changedReg) {
    /* Your code goes here */
    // All R-format write to the register $rd, except 0x8, which is `jr`.
    if(d->op == 0x0 && d->regs.r.funct != 0x8) {
        *changedReg = d->regs.r.rd;
        mips.registers[d->regs.r.rd] = rVals.R_rd;
    } else {
        switch(d->op) {
            // This is for `jal`, where we ned to set $ra
            case 0x3:
                // 31 = $ra...
                *changedReg = 31;
                mips.registers[31] = rVals.R_rt;
                break;
            // Case is the same for `addiu`, `andi`, & `ori`...
            case 0x9:
            case 0xc:
            case 0xd:
                *changedReg = d->regs.i.rt;
                mips.registers[d->regs.i.rt] = val;
                break;
            // For `lw`...
            case 0x23:
                *changedReg = d->regs.i.rt;
                mips.registers[d->regs.i.rt] = val;
                break;
            // For `lui`...
            case 0xf:
                *changedReg = d->regs.i.rt;
                mips.registers[d->regs.i.rt] = d->regs.i.addr_or_immed;
                break;
            // By default, an instruction will not change a register.
            default:
                *changedReg = -1;
                break;
        }
    }
}
