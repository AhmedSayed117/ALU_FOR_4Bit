// To Run This Code
// iverilog -o ALU ALU.vl
// vvp ALU

//Names:
/*          
    1-  Ahmed Sayed Hassan --> 20190034
    2-  Khaled Ashraf Hanafy  --> 20190186
    3-  Ebrahim Mohamed Ebrahim Hegy --> 20190009
    4-  Omar Mohamed Mahmoud --> 20190730
    5-  Sondos Emara Gomaa --> 20190249      
*/

//My Main Functions

//fullAdder
module fullAdder(output S, output Cout,input A,input B,input Cin);
wire   w0,w1,w2,w3;

xor(w0, A, B);
xor(S, Cin, w0);
and(w1, A, B);
and(w2, A, Cin);
and(w3, B, Cin);
or(Cout, w1, w2, w3);
endmodule

//Multiplexer 2 To 1
module Multi_2x1(output out,input n1,input n2,input n3);
wire FirstAnd, SecondAnd, C;

not (C,n3);
and (FirstAnd, n1, C);
and (SecondAnd, n2, n3);
or (out, FirstAnd, SecondAnd);
endmodule

//Multiplexer 4 To 1 Using Thre Multiplexer 2 To 1
module Multi_4x1(output out,input i0,input i1,input i2,input i3,input s1,input s0);
wire outputFirstMul,outputSecondmux2;

Multi_2x1 Multi_1(outputFirstMul,i0,i1,s1);
Multi_2x1 Multi_2(outputSecondmux2,i2,i3,s1);
Multi_2x1 Multi_3(out,outputFirstMul,outputSecondmux2,s0);
endmodule

//Adding two 4-bit numbers  *****< we Use ALU circuit instead of this function >*****
module Four_bit_adder(output [3:0] s, output out, input [3:0] a, input [3:0] b , in);
wire in;
assign in=0;
wire [3:1]c;

fullAdder f0(a[0],b[0],in,c[1],s[0]);
fullAdder f1(a[1],b[1],c[1],c[2],s[1]);
fullAdder f2(a[2],b[2],c[2],c[3],s[2]);
fullAdder f3(a[3],b[3],c[3],out,s[3]);
endmodule

//Subtracting two 4-bit numbers.  *****< we Use ALU circuit instead of this function >*****
module Sub_two_4bits_Num(S, C, cout, A,B);

output [3:0] S;   // The 4-bit output
output 	C;       // The 1-bit carry/borrow status. /must = 1 to perform subtraction
output 	cout;    // The 1-bit for the overflow condition .
input [3:0] 	A;   // The 4-bit input.
input [3:0] 	B;   // The 4-bit input , we will get its complement by xor it with 1.

wire    cin;      // if it = 0 then we add if it = 1 we substract .
assign cin =1;
wire 	C0;     // The carry out .
wire 	C1;     // The carry out .
wire 	C2;     // The carry out .
wire 	C3;     // The carry out . we use it to know if threre is a carry

wire 	B0;     // the result of the xor (the B complement in subtraction case)
wire 	B1;     //  the result of the xor (the B complement in subtraction case)
wire 	B2;     //  the result of the xor (the B complement in subtraction case)
wire 	B3;     //  the result of the xor (the B complement in subtraction case)

xor(B0, B[0], cin);
xor(B1, B[1], cin);
xor(B2, B[2], cin);
xor(B3, B[3], cin);
xor(C, C3, cin); //Carry does not equals C3 for subtraction.
xor(cout, C3, C2);

fullAdder f0(S[0], C0, A[0], B0, Op);
fullAdder f1(S[1], C1, A[1], B1, C0);
fullAdder f2(S[2], C2, A[2], B2, C1);
fullAdder f3(S[3], C3, A[3], B3, C2);

endmodule

//Adding 1 to a 4-bit number.   *****< we Use ALU circuit instead of this function >*****
module add_4bitNum_ByOne(output [3:0] S, output Out, input [3:0] A);
wire cin;
assign cin =1;
wire y;
assign y =0;
wire C0,C1,C2,C3;

fullAdder f0(S[0], C0, A[0], y, cin);
fullAdder f1(S[1], C1, A[1], y, cin);
fullAdder f2(S[2], C2, A[2], y, cin);
fullAdder f3(S[3], C3, A[3], y, cin);

endmodule

// Subtracting 1 from a 4-bit number.   *****< we Use ALU circuit instead of this function >*****
module Sub_4bitNum_ByOne(S,Out,A);

output 	Out;        // The 1-bit carry/borrow status. /must = 1 to perform subtraction
output [3:0] S;      // The 4-bit output
input [3:0] 	A;      // The 4-bit input.
wire cin;
assign cin =0;
wire y;
assign y =1;
wire C0,C1,C2,C3;

fullAdder f0(S[0], C0, A[0], y, cin);
fullAdder f1(S[1], C1, A[1], y, cin);
fullAdder f2(S[2], C2, A[2], y, cin);
fullAdder f3(S[3], C3, A[3], y, cin);

endmodule

//Bitwise ANDing two 1-bit numbers.
module bitwise_AND (output out ,input wire n1,input wire n2);

wire  out  =   n1&n2;

endmodule

// Bitwise ORing two 1-bit numbers.
module bitwise_OR (output out, input wire n1,input wire n2);

wire out   =    n1|n2;

endmodule

// Bitwise XORing two 1-bit numbers.
module bitwise_XOR (output out , input wire n1,input wire n2);

wire out  =    n1^n2;

endmodule

//Arithmetic shifting right of a 4-bit number that will discard the least significant bit.
module shiftRight(output wire [3:0] out,input wire[3:0] in);

assign out[0] = in[1];
assign out[1] = in[2];
assign out[2] = in[3];
assign out[3] = in[3];

endmodule

//Arithmetic shifting Left of a 4-bit number that will discard the least significant bit.
module shiftLeft(output wire [3:0] out,input wire[3:0] in);

assign out[0] = 0;
assign out[1] = in[0];
assign out[2] = in[1];
assign out[3] = in[2];

endmodule

//Arthmetic_Circuit for 1 bits
module Arthmetic_Circuit(output wire carry,output wire Sum,input wire cin,input wire s1,input wire s0,input wire A,input wire B);
output wire FirstMulti;
wire NOTB;
not(NOTB,B);

// out,i0,i1,i2,i3,s1,s0
Multi_4x1 m1(FirstMulti , B , NOTB , 0 , 1 , s1 , s0);
//S, Cout, A, B, Cin
fullAdder f1(Sum , carry , A , FirstMulti , cin);

endmodule

//LogicGates for 1 Bits
module LogicGates(output wire E,input wire s1,input wire s0,input A,input B);
output wire OutOfAnd,OutOfOr,OutOfXor,OutOfNot;
bitwise_AND AND(OutOfAnd,A,B);
bitwise_OR OR(OutOfOr,A,B);
bitwise_XOR XOR(OutOfXor,A,B);
not(OutOfNot,A);

Multi_4x1 m1(E,OutOfAnd,OutOfOr,OutOfXor,OutOfNot,s0,s1);//  -->  s1 s0

endmodule

//main Component
module ALU(output wire [3:0] F,input wire s3,input wire s2,input wire s1,input wire s0,input wire cin,input wire [3:0] A,input wire [3:0] B);
wire [3:0] Shift_Right ;
shiftRight SHR(Shift_Right,A);

wire [3:0] Shift_Left ;
wire [4:0] result;
shiftLeft SHL(Shift_Left,A);

wire [4:0]carries;
assign carries[0] = cin;

generate
        genvar i;

for(i=0;i<=3;i=i+1)

begin
        wire Sum,E,carry;
Arthmetic_Circuit A1 (carry,Sum,carries[i],s0,s1,A[i],B[i]); //s0 -> s1
assign carries[i+1] = carry;

LogicGates L1(E,s1,s0,A[i],B[i]);
Multi_4x1 m1(F[i],Sum,E,Shift_Left[i],Shift_Right[i],s2,s3);// --> s3 s2
assign result[i] = F[i];

end
        endgenerate

assign result[4] = carries[4];

initial
        begin
$monitor("F = %b",result);
end

        endmodule

module main();

wire [3:0] A = 4'b0111;
wire [3:0] B = 4'b1011;
wire [3:0] F;

ALU alu1( F, 0, 0 , 1 , 1 , 1 , A , B);

endmodule
//Comments!!

//Arthmetic_Circuit for 4 Bits
/*
module Arthmetic_Circuit(output wire cout,input wire cin,input wire s1,input wire s0,input [3:0] A,input [3:0] B);

    output wire FirstMulti,SecondMulti,therdMulti,LastMulti,Result,
    SumfirstFulladder,SumSecondFulladder,SumtherdFulladder,SumLastFulladder;
    wire NOTB0,NOTB1,NOTB2,NOTB3,
    CarryFirstFullAdder,CarrySecondFullAdder,CarryThersdFullAdder;
    not(NOTB0,B[0]);not(NOTB1,B[1]);not(NOTB2,B[2]);not(NOTB3,B[3]);
   
    // out,i0,i1,i2,i3,s1,s0
    Multi_4x1 m1(FirstMulti , B[0] , NOTB0 , 0 , 1 , s1 , s0);
    //S, Cout, A, B, Cin
    fullAdder f1(SumfirstFulladder , CarryFirstFullAdder , A[0] , FirstMulti , cin);

    Multi_4x1 m2(SecondMulti , B[1] , NOTB1 , 0 , 1 , s1 , s0);
    //S, Cout, A, B, Cin
    fullAdder f2(SumSecondFulladder , CarrySecondFullAdder , A[1] , SecondMulti , CarryFirstFullAdder);

    Multi_4x1 m3(therdMulti , B[2] , NOTB2 , 0 , 1 , s1 , s0);
    //S, Cout, A, B, Cin
    fullAdder f3(SumtherdFulladder , CarryThersdFullAdder , A[2] , therdMulti , CarrySecondFullAdder);

    Multi_4x1 m4(LastMulti , B[3] , NOTB3 , 0 , 1 , s1 , s0);
    //S, Cout, A, B, Cin
    fullAdder f4(SumLastFulladder , cout , A[3] , LastMulti , CarryThersdFullAdder);

    initial
    begin
        $monitor("SumfirstFulladder=%b,SumSecondFulladder=%b,SumtherdFulladder=%b, SumLastFulladder = %b",SumfirstFulladder,SumSecondFulladder,SumtherdFulladder,SumLastFulladder);
    end

endmodule
*/


//LogicGates for 4 Bits
/*
module LogicGates(output wire E,input wire s1,input wire s0,input [3:0] A,input [3:0] B);
    output wire OutOfAnd,OutOfOr,OutOfXor,OutOfNot;
    bitwise_AND AND(OutOfAnd,A,B);
    bitwise_OR OR(OutOfOr,A,B);
    bitwise_XOR XOR(OutOfXor,A,B);
    not(OutOfNot,A);

    Multi_4x1 m1(E,OutOfAnd,OutOfOr,OutOfXor,OutOfNot,s1,s0);

    initial
    begin
        $monitor("E = %d",E);
    end

endmodule
*/


//real TestCases For ALU
/*
module TestCases();
        //  F, 0, 0 , 0 , 0 , 0 , A , B  --> result = 10010
        //  F, 0, 0 , 0 , 0 , 1 , A , B  --> result = 10011
        //  F, 0, 0 , 0 , 1 , 0 , A , B  --> result = 01011
        //  F, 0, 0 , 0 , 1 , 1 , A , B  --> result = 01100
        //  F, 0, 0 , 1 , 0 , 0 , A , B  --> result = 00111
        //  F, 0, 0 , 1 , 0 , 1 , A , B  --> result = 01000
        //  F, 0, 0 , 1 , 1 , 0 , A , B  --> result = 10110
        //  F, 0, 0 , 1 , 1 , 1 , A , B  --> result = 10111

        //  F, 0, 1 , 0 , 0 , 1 , A , B  --> result = 10011
        //  F, 0, 1 , 0 , 1 , 1 , A , B  --> result = 01111
        //  F, 0, 1 , 1 , 0 , 1 , A , B  --> result = 01100
        //  F, 0, 1 , 1 , 1 , 1 , A , B  --> result = 11000

        //  F, 1, 0 , 1 , 1 , 1 , A , B  --> result = 11110
        //  F, 1, 1 , 0 , 1 , 1 , A , B  --> result = 00011

        //s3 s2  --> Arth Logic shift
            //s1 s0 --> Arth
                //cin 0
                    // 0 0 A+B          
                    // 0 1 A + not b 
                    // 1 0 A            
                    // 1 1 A-1          
                //cin 1
                    // 0 0 A + B + 1    
                    // 0 1 A + NOT B +1 
                    // 1 0 A + 1        
                    // 1 1 A
            //s1 s0 --> logic
                // 0 0 and      
                // 0 1 or       
                // 1 0 xor      
                // 1 1 not a    
            
            //s3 s2 -->Shift
                //1 0 shiftleft A    
                //1 1 shiftright A   
    endmodule
*/