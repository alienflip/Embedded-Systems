// http://docs.arduino.cc/learn/programming/vidor

// new module declaration
module COUNTER #(
pWIDTH=8
) (
// define input port 
input                   iCLK,
// define reset port
input                   iRESET,
// define output register (memory) as pWIDTH bytes long 
output reg [pWIDTH-1:0] oCOUNTER
);
// program implimenting the above module
always @(posedge iCLK)
begin
// if we see high RESET signal, reset the counter
if (iRESET) begin
oCOUNTER<=0;
// otherwise, incriment the oCOUNTER
end else begin
oCOUNTER <= oCOUNTER+1;
end
end
endmodule

// Notice here, that the 'input' variable represent simple BUS, and 'reg' maintains state.
// This works, as a product, because HSI (hardware software interface) is well defined:
/*
LIGHTWEIGHT BUS
--------------
Signal        Direction    Direction  Width Description
              Controller   Peripheral		
ADDRESS       O            I          var.  Register address, width determines
READ          O            I          1     Read strobe
READ_DATA     I            O          32    Data being read
WRITE         O            I          1     Write strobe
WRITE_DATA    O            I          32    Data to write at a given address
BYTE_ENABLE   O            I          4     Optional signal to flag which bytes of the 32 bit word are actually going to be written
WAIT_REQUEST  I            O          1     Optional signal to flag the peripheral is busy. Read and write strobes will be considered valid only if this signal is not asserted.

PIPELINED BUS
------------
Signal          Direction   Direction   Width Description
                Controller  Peripheral	
BURST_COUNT     O           I           var.  Number of sequential operations to perform
READ_DATAVALID  I           O           1     Peripheral uses this signal to flag when data is being provided to controller. Can be asserted with any delay and there is no guarantee on contiunity. A read operation with a burst size of 4 will assert 4 times READ_DATAVALID per each READ strobe
*/

