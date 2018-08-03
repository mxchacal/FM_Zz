import pastel
import sys
import codecs

block_size = 1

print(pastel.colorize('<fg=blue;option=bold>    <----------------->   '))
print(pastel.colorize('<fg=blue;option=bold>  <---------------------> '))
print(pastel.colorize('<fg=blue;option=bold> <----------------------->'))
print(pastel.colorize('<fg=blue;option=bold><----> '), pastel.colorize('<fg=white;option=bold>FM_Z /// DX7'),pastel.colorize('<fg=blue;option=bold> <--->'))
print(pastel.colorize('<fg=blue;option=bold> <--->'), pastel.colorize('<fg=white;option=bold> SYSEX DECODER'), pastel.colorize('<fg=blue;option=bold> <-->'))
print(pastel.colorize('<fg=blue;option=bold>  <---------------------> '))
print(pastel.colorize('<fg=blue;option=bold>    <----------------->   '))

print(' ')
filename = sys.argv[1]

print(pastel.colorize('<fg=white;options=bold>Opening : '), filename)

sysex = open(filename, "rb")

print("Done!")

print(' ')
print(pastel.colorize('<fg=red;option=bold>----------------------- Header -----------------------')) 
print(' ')

sysex.seek(0) #Go to the start of file

block = int.from_bytes(sysex.read(block_size), byteorder='big')
if block == 240 :
	print(pastel.colorize('<fg=white;option=bold>Status byte :     '), block, " --> ", pastel.colorize('<fg=green;option=bold>SYSEX start'))

block = int.from_bytes(sysex.read(block_size), byteorder='big')
if block == 67 :
	print(pastel.colorize('<fg=white;option=bold>Identifier byte : '), block, " --> ", pastel.colorize('<fg=green;option=bold>Yamaha ID is OK'))

block = int.from_bytes(sysex.read(block_size), byteorder='big')
if block == 0 :
	print(pastel.colorize('<fg=white;option=bold>Substatus & channel nb : '), block, " --> ",  pastel.colorize('<fg=green;option=bold>Bulk Data'))

block = int.from_bytes(sysex.read(block_size), byteorder='big')
if block == 0 :
	print(pastel.colorize('<fg=white;option=bold>Format number : '), block, " --> ",  pastel.colorize('<fg=green;option=bold>For 1 voice'))
elif block == 9 :
	print(pastel.colorize('<fg=white;option=bold>Format number : '), block, " --> ",  pastel.colorize('<fg=green;option=bold>For 32 voices'))

block = int.from_bytes(sysex.read(block_size), byteorder='big')
if block == 20 :
	print(pastel.colorize('<fg=white;option=bold>MSB byte count : '), block)

block = int.from_bytes(sysex.read(block_size), byteorder='big')
if block == 0 :
	print(pastel.colorize('<fg=white;option=bold>LSB byte count : '), block)

print(' ')
print(pastel.colorize('<fg=red;option=bold>--------------------- Data Bytes ---------------------')) 
print(' ')

count = 6

for count in range(6, 0, -1) :
	
	print(pastel.colorize('<fg=white;option=bold>OP'), count, pastel.colorize('<fg=blue;option=bold>Attack rate : '), int.from_bytes(sysex.read(block_size), byteorder='big'))
	print(pastel.colorize('<fg=white;option=bold>OP'), count, pastel.colorize('<fg=blue;option=bold>Decay rate : '), int.from_bytes(sysex.read(block_size), byteorder='big'))
	print(pastel.colorize('<fg=white;option=bold>OP'), count, pastel.colorize('<fg=blue;option=bold>Sustain rate : '), int.from_bytes(sysex.read(block_size), byteorder='big'))
	print(pastel.colorize('<fg=white;option=bold>OP'), count, pastel.colorize('<fg=blue;option=bold>Release rate : '), int.from_bytes(sysex.read(block_size), byteorder='big'))

	print(pastel.colorize('<fg=white;option=bold>OP'), count, pastel.colorize('<fg=blue;option=bold>Attack level : '), int.from_bytes(sysex.read(block_size), byteorder='big'))
	print(pastel.colorize('<fg=white;option=bold>OP'), count, pastel.colorize('<fg=blue;option=bold>Decay level : '), int.from_bytes(sysex.read(block_size), byteorder='big'))
	print(pastel.colorize('<fg=white;option=bold>OP'), count, pastel.colorize('<fg=blue;option=bold>Sustain level : '), int.from_bytes(sysex.read(block_size), byteorder='big'))
	print(pastel.colorize('<fg=white;option=bold>OP'), count, pastel.colorize('<fg=blue;option=bold>Release level : '), int.from_bytes(sysex.read(block_size), byteorder='big'))


