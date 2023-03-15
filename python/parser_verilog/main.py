#Python program for verilog equivalent netlist generation using NAND and NOR logic gates
#Refer document for functioality of each block
#Developed by venkata naga ravikiran bulusu

import textwrap
import time
import sys

startTime = time.clock()
num_lines = sum(1 for item in open('block32.v')) # Input the filename

clean_lines = []
with open("block32.v", "r") as f:                # Input the filename
    lines = f.readlines()
    clean_lines = [l.strip() for l in lines if l.strip()]

with open("ingenerated.v", "w") as f:
    f.writelines('\n'.join(clean_lines))
    
##########################################################
###### Block for joining lines in the input file  ########
##########################################################
file_input = open('ingenerated.v','r') 
join_list = []
r1 = 0

for line in file_input:

    if line.find(';') < 0 and line.find('wire') < 0 and line.startswith('n')== False and line.find('endmodule') < 0:
        input_list = []
        input_list.append(line)
        r1+=1

    elif r1 > 0 and input_list[r1 - 1].find(';') < 0 and line.find(';') > 0:
        input_list.append(line)
        join_list.append(input_list[r1-1].rstrip() + ' ' + input_list[r1].strip())
        r1 = 0

    else:
        join_list.append(line)
        
with open('ingenerated.v','w') as m:
 for v in join_list:
     x = v
     m.write(x+'\n')

clean_lines = []
with open("ingenerated.v", "r") as f:                
    lines = f.readlines()
    clean_lines = [l.strip() for l in lines if l.strip()]

with open("ingenerated.v", "w") as f:
    f.writelines('\n'.join(clean_lines))
    
file_input.close
m.close
#################################################################
##############          End of the block   ######################
#################################################################

#################################################################
#####  Block for finding the start and end of wires used  #######
#################################################################
f = open('ingenerated.v','r')
wire_list = []
max_list = []
val_list = []
for s in f:
   if (s.startswith('wire') or s.startswith('n')):
       wire_list.append(s)
       wire_list = [wires.replace('n','') for wires in wire_list]
       wire_list = [wires.replace('wire','') for wires in wire_list]
       wire_list = [wires.replace(',','') for wires in wire_list]
       wire_list = [wires.replace(';','') for wires in wire_list]
       max_list = map(lambda s: s.strip(), wire_list)
       for i in max_list:
         val_list.extend(i.split())
         zmin = min(val_list)
         zmax = max(val_list)
f.close
##################################################################
###################    End of the Block      #####################
##################################################################

##################################################################
################   Block for main functionality   ################
##################################################################
##
#For opening the input file
##
f = open('ingenerated.v','r')
##
#For finding the wire value to create new wires
##
##
#Variables used
##
r = 1 
r+= int(zmax)      #counter for new wires generation 
r0 = r1 = r2 = r3 = r4 = r5 = r6 = r7 = r8 = 0
print_list = []    #list for writing the lines to file 
##
#
##
##Defining a function for NAND3XL to NAND2X1 realization  #######
def NAND3XL():
    
    r0=(line.find('U'))
    input_list.append(line[0:r0])
    r1=(line.find('.A'))
    input_list.append(line[r0:r1-1])
    r2=(line.find('.B'))
    input_list.append(line[r1+2:r2])
    r3=(line.find('.C'))
    input_list.append(line[r2+2:r3])
    r4=(line.find('.Y'))
    input_list.append(line[r3+2:r4])
    r5=(line.find(';'))
    input_list.append(line[r4+2:r5-1])
    
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'00'+' ( .A'+input_list[2].rstrip()+' .B'+input_list[3].rstrip()+' .Y('+"".join([str('n')+str(r)])+') );')
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'01'+' ( .A('+"".join([str('n')+str(r)])+')'+', .B('+"".join([str('n')+str(r)])+')'+', .Y('+"".join([str('n')+str(int(r)+1)])+')'+' );')
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'02'+' ( .A('+"".join([str('n')+str(int(r)+1)])+'), .B'+input_list[4].rstrip()+' .Y'+input_list[5].rstrip()+' );')
    r0=r1=r2=r3=r4=r5=0
    return;
##
#
##
# Defining a function for NAND2X1 to NAND2X1 realization
##
def NAND2X1():
    
    print_list.append(line)
    return;
##
#
##
# Defining a function for CLKINVX1 to NAND2X1 realization
##
def CLKINVX1():

    r0=(line.find('U'))
    input_list.append(line[0:r0])
    r1=(line.find('.A'))
    input_list.append(line[r0:r1-1])
    r2=(line.find('.Y'))
    input_list.append(line[r1+2:r2])
    r3=(line.find(';'))
    input_list.append(line[r2+2:r3-1])
    
    print_list.append('NAND2X1 '+input_list[1].rstrip()+' ( .A'+input_list[2].rstrip()+' .B'+input_list[2].rstrip()+' .Y'+input_list[3].rstrip()+' );')
    r0=r1=r2=r3=0
    return;
##
#
##
# Defining a function for OAI22XL to NAND2X1 realization
##
def OAI22XL():

    r0=(line.find('U'))
    input_list.append(line[0:r0])
    r1=(line.find('.A0'))
    input_list.append(line[r0:r1-1])
    r2=(line.find('.A1'))
    input_list.append(line[r1+3:r2])
    r3=(line.find('.B0'))
    input_list.append(line[r2+3:r3])
    r4=(line.find('.B1'))
    input_list.append(line[r3+3:r4])
    r5=(line.find('.Y'))
    input_list.append(line[r4+3:r5])
    r6=(line.find(';'))
    input_list.append(line[r5+2:r6-1])
    
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'00'+' ( .A'+input_list[2].rstrip()+' .B'+input_list[3].rstrip()+' .Y('+"".join([str('n')+str(r)])+') );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'01'+' ( .A'+input_list[4].rstrip()+' .B'+input_list[5].rstrip()+' .Y('+"".join([str('n')+str(int(r)+1)])+') );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'02'+' ( .A('+"".join([str('n')+str(r)])+'), .B('+"".join([str('n')+str(r)])+'),'+' .Y('+"".join([str('n')+str(int(r)+2)])+') );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'03'+' ( .A('+"".join([str('n')+str(int(r)+1)])+'), .B('+"".join([str('n')+str(int(r)+1)])+'),'+' .Y('+"".join([str('n')+str(int(r)+3)])+') );')
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'04'+' ( .A('+"".join([str('n')+str(int(r)+2)])+'), .B('+"".join([str('n')+str(int(r)+3)])+'),'+' .Y'+input_list[6].rstrip()+' );')
    r0=r1=r2=r3=r4=r5=r6=0
    return;
##
#
##
# Defining a function for OAI221X1 to NAND2X1 realization
##
def OAI221X1():

    r0=(line.find('U'))
    input_list.append(line[0:r0])
    r1=(line.find('.A0'))
    input_list.append(line[r0:r1-1])
    r2=(line.find('.A1'))
    input_list.append(line[r1+3:r2])
    r3=(line.find('.B0'))
    input_list.append(line[r2+3:r3])
    r4=(line.find('.B1'))
    input_list.append(line[r3+3:r4])
    r5=(line.find('.C0'))
    input_list.append(line[r4+3:r5])
    r6=(line.find('.Y'))
    input_list.append(line[r5+3:r6])
    r7=(line.find(';'))
    input_list.append(line[r6+2:r7-1])
    
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'00'+' ( .A'+input_list[2].rstrip()+' .B'+input_list[3].rstrip()+' .Y('+"".join([str('n')+str(r)])+') );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'01'+' ( .A'+input_list[4].rstrip()+' .B'+input_list[5].rstrip()+' .Y('+"".join([str('n')+str(int(r)+1)])+') );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'02'+' ( .A('+"".join([str('n')+str(r)])+'), .B('+"".join([str('n')+str(r)])+'),'+' .Y('+"".join([str('n')+str(int(r)+2)])+') );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'03'+' ( .A('+"".join([str('n')+str(int(r)+1)])+'), .B('+"".join([str('n')+str(int(r)+1)])+'),'+' .Y('+"".join([str('n')+str(int(r)+3)])+') );')
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'04'+' ( .A('+"".join([str('n')+str(int(r)+2)])+'), .B('+"".join([str('n')+str(int(r)+3)])+'),'+' .Y('+"".join([str('n')+str(int(r)+4)])+') );')
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'05'+' ( .A('+"".join([str('n')+str(int(r)+4)])+'), .B('+"".join([str('n')+str(int(r)+4)])+'),'+' .Y('+"".join([str('n')+str(int(r)+5)])+') );')
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'06'+' ( .A('+"".join([str('n')+str(int(r)+5)])+'), .B'+input_list[6].rstrip()+' .Y'+input_list[7].rstrip()+' );')
    r0=r1=r2=r3=r4=r5=r6=r7=0
    return;
##
#
##
# Defining a function for OAI21XL to NAND2X1 realization
##
def OAI21XL():

    r0=(line.find('U'))
    input_list.append(line[0:r0])
    r1=(line.find('.A0'))
    input_list.append(line[r0:r1-1])
    r2=(line.find('.A1'))
    input_list.append(line[r1+3:r2])
    r3=(line.find('.B0'))
    input_list.append(line[r2+3:r3])
    r4=(line.find('.Y'))
    input_list.append(line[r3+4:r4])
    r5=(line.find(';'))
    input_list.append(line[r4+2:r5-1])
    
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'00'+' ( .A'+input_list[2].rstrip()+' .B'+input_list[3].rstrip()+' .Y('+"".join([str('n')+str(r)])+') );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'01'+' ( .A('+"".join([str('n')+str(r)])+'), .B('+"".join([str('n')+str(r)])+'),'+' .Y('+"".join([str('n')+str(int(r)+1)])+') );')
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'02'+' ( .A('+"".join([str('n')+str(int(r)+1)])+'), .B('+input_list[4].rstrip()+' .Y'+input_list[5].rstrip()+' );')
    r0=r1=r2=r3=r4=r5=0
    return;
##
#
##
# Defining a function for OAI2BB1X1 to NAND2X1 realization
##
def OAI2BB1X1():

    r0=(line.find('U'))
    input_list.append(line[0:r0])
    r1=(line.find('.A0N'))
    input_list.append(line[r0:r1-1])
    r2=(line.find('.A1N'))
    input_list.append(line[r1+4:r2])
    r3=(line.find('.B0'))
    input_list.append(line[r2+4:r3])
    r4=(line.find('.Y'))
    input_list.append(line[r3+4:r4])
    r5=(line.find(';'))
    input_list.append(line[r4+2:r5-1])
    
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'00'+' ( .A'+input_list[2].rstrip()+' .B'+input_list[2].rstrip()+' .Y('+"".join([str('n')+str(r)])+') );')
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'01'+' ( .A'+input_list[3].rstrip()+' .B'+input_list[3].rstrip()+' .Y('+"".join([str('n')+str(int(r)+1)])+') );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'02'+' ( .A('+"".join([str('n')+str(r)])+'), .B('+"".join([str('n')+str(int(r)+1)])+'),'+' .Y('+"".join([str('n')+str(int(r)+2)])+') );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'03'+' ( .A('+"".join([str('n')+str(int(r)+2)])+'), .B('+"".join([str('n')+str(int(r)+2)])+'),'+' .Y('+"".join([str('n')+str(int(r)+3)])+') );')
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'04'+' ( .A('+"".join([str('n')+str(int(r)+3)])+'), .B('+input_list[4].rstrip()+' .Y'+input_list[5].rstrip()+' );')
    r0=r1=r2=r3=r4=r5=0
    return;
##
#
##
# Defining a function for OAI211XL to NAND2X1 realization
##
def OAI211XL():

    r0=(line.find('U'))
    input_list.append(line[0:r0])
    r1=(line.find('.A0'))
    input_list.append(line[r0:r1-1])
    r2=(line.find('.A1'))
    input_list.append(line[r1+3:r2])
    r3=(line.find('.B0'))
    input_list.append(line[r2+3:r3])
    r4=(line.find('.C0'))
    input_list.append(line[r3+3:r4])
    r5=(line.find('.Y'))
    input_list.append(line[r4+3:r5])
    r6=(line.find(';'))
    input_list.append(line[r5+2:r6-1])
    
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'00'+' ( .A'+input_list[2].rstrip()+' .B'+input_list[3].rstrip()+' .Y('+"".join([str('n')+str(r)])+') );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'01'+' ( .A('+"".join([str('n')+str(r)])+'), .B('+"".join([str('n')+str(r)])+'),'+' .Y('+"".join([str('n')+str(int(r)+1)])+') );')
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'02'+' ( .A('+"".join([str('n')+str(int(r)+1)])+'), .B'+input_list[4].rstrip()+' .Y('+"".join([str('n')+str(int(r)+2)])+') );')
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'03'+' ( .A('+"".join([str('n')+str(int(r)+2)])+'), .B('+"".join([str('n')+str(int(r)+2)])+'),'+' .Y('+"".join([str('n')+str(int(r)+3)])+') );')
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'04'+' ( .A('+"".join([str('n')+str(int(r)+3)])+'), .B'+input_list[5].rstrip()+' .Y'+input_list[6].rstrip()+' );')
    r0=r1=r2=r3=r4=r5=r6=0
    return;
##
#
##
# Defining a function for NOR2XL to NOR2X1 realization
##
def NOR2XL():
    
    print_list.append(line)
    return;
##
#
##
# Defining a function for OAI33X1 to NAND2X1 realization
##
def OAI33X1():

    r0=(line.find('U'))
    input_list.append(line[0:r0])
    r1=(line.find('.A0'))
    input_list.append(line[r0:r1-1])
    r2=(line.find('.A1'))
    input_list.append(line[r1+3:r2])
    r3=(line.find('.A2'))
    input_list.append(line[r2+3:r3])
    r4=(line.find('.B0'))
    input_list.append(line[r3+3:r4])
    r5=(line.find('.B1'))
    input_list.append(line[r4+3:r5])
    r6=(line.find('.B2'))
    input_list.append(line[r5+3:r6])
    r7=(line.find('.Y'))
    input_list.append(line[r6+3:r7])
    r8=(line.find(';'))
    input_list.append(line[r7+2:r8-1])
    
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'00'+' ( .A'+input_list[2].rstrip()+' .B'+input_list[3].rstrip()+' .Y('+"".join([str('n')+str(r)])+') );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'01'+' ( .A'+input_list[5].rstrip()+' .B'+input_list[6].rstrip()+' .Y('+"".join([str('n')+str(int(r)+1)])+') );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'02'+' ( .A('+"".join([str('n')+str(r)])+'), .B('+"".join([str('n')+str(r)])+'),'+' .Y('+"".join([str('n')+str(int(r)+2)])+') );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'03'+' ( .A('+"".join([str('n')+str(int(r)+1)])+'), .B('+"".join([str('n')+str(int(r)+1)])+'),'+' .Y('+"".join([str('n')+str(int(r)+3)])+') );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'04'+' ( .A('+"".join([str('n')+str(int(r)+2)])+'), .B'+input_list[4].rstrip()+' .Y('+"".join([str('n')+str(int(r)+4)])+') );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'05'+' ( .A('+"".join([str('n')+str(int(r)+3)])+'), .B'+input_list[7].rstrip()+' .Y('+"".join([str('n')+str(int(r)+5)])+') );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'06'+' ( .A('+"".join([str('n')+str(int(r)+4)])+'), .B('+"".join([str('n')+str(int(r)+4)])+'),'+' .Y('+"".join([str('n')+str(int(r)+6)])+') );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'07'+' ( .A('+"".join([str('n')+str(int(r)+5)])+'), .B('+"".join([str('n')+str(int(r)+5)])+'),'+' .Y('+"".join([str('n')+str(int(r)+7)])+') );')
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'08'+' ( .A('+"".join([str('n')+str(int(r)+6)])+'), .B('+"".join([str('n')+str(int(r)+7)])+'),'+' .Y'+input_list[8].rstrip()+' );')
    r0=r1=r2=r3=r4=r5=r6=r7=r8=0
    return;
##
#
##
# Defining a function for XNOR2XL to NOR2X1 realization
##
def XNOR2XL():
    
    r0=(line.find('U'))
    input_list.append(line[0:r0])
    r1=(line.find('.A'))
    input_list.append(line[r0:r1-1])
    r2=(line.find('.B'))
    input_list.append(line[r1+2:r2])
    r3=(line.find('.Y'))
    input_list.append(line[r2+2:r3])
    r4=(line.find(';'))
    input_list.append(line[r3+2:r4-1])
    
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'00'+' ( .A'+input_list[2].rstrip()+' .B'+input_list[3].rstrip()+' .Y('+"".join([str('n')+str(r)])+') );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'01'+' ( .A'+input_list[2].rstrip()+' .B('+"".join([str('n')+str(r)])+'),'+' .Y('+"".join([str('n')+str(int(r)+1)])+') );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'02'+' ( .A('+"".join([str('n')+str(r)])+')'+', .B'+input_list[3].rstrip()+' .Y('+"".join([str('n')+str(int(r)+2)])+') );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'03'+' ( .A('+"".join([str('n')+str(int(r)+1)])+'), .B('+"".join([str('n')+str(int(r)+2)])+'),'+' .Y'+input_list[4].rstrip()+' );')
    r0=r1=r2=r3=r4=0
    return;
##
#
##
# Defining a function for AOI32X1 to NAND2X1 realization
##
def AOI32X1():

    r0=(line.find('U'))
    input_list.append(line[0:r0])
    r1=(line.find('.A0'))
    input_list.append(line[r0:r1-1])
    r2=(line.find('.A1'))
    input_list.append(line[r1+3:r2])
    r3=(line.find('.A2'))
    input_list.append(line[r2+3:r3])
    r4=(line.find('.B0'))
    input_list.append(line[r3+3:r4])
    r5=(line.find('.B1'))
    input_list.append(line[r4+3:r5])
    r6=(line.find('.Y'))
    input_list.append(line[r5+3:r6])
    r7=(line.find(';'))
    input_list.append(line[r6+2:r7-1])
    
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'00'+' ( .A'+input_list[2].rstrip()+' .B'+input_list[3].rstrip()+' .Y('+"".join([str('n')+str(r)])+') );')
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'01'+' ( .A'+input_list[5].rstrip()+' .B'+input_list[6].rstrip()+' .Y('+"".join([str('n')+str(int(r)+1)])+') );')
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'02'+' ( .A('+"".join([str('n')+str(r)])+'), .B('+"".join([str('n')+str(r)])+'),'+' .Y('+"".join([str('n')+str(int(r)+2)])+') );')
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'03'+' ( .A('+"".join([str('n')+str(int(r)+1)])+'), .B('+"".join([str('n')+str(int(r)+1)])+'),'+' .Y('+"".join([str('n')+str(int(r)+3)])+') );')
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'04'+' ( .A('+"".join([str('n')+str(int(r)+2)])+'), .B'+input_list[4].rstrip()+' .Y('+"".join([str('n')+str(int(r)+4)])+') );')
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'05'+' ( .A('+"".join([str('n')+str(int(r)+4)])+'), .B('+"".join([str('n')+str(int(r)+4)])+'),'+' .Y('+"".join([str('n')+str(int(r)+5)])+') );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'06'+' ( .A('+"".join([str('n')+str(int(r)+5)])+'), .B('+"".join([str('n')+str(int(r)+3)])+'),'+' .Y'+input_list[7].rstrip()+' );')
    r0=r1=r2=r3=r4=r5=r6=r7=0
    return;
##
#
##
# Defining a function for OAI32X1 to NAND2X1 realization
##
def OAI32X1():

    r0=(line.find('U'))
    input_list.append(line[0:r0])
    r1=(line.find('.A0'))
    input_list.append(line[r0:r1-1])
    r2=(line.find('.A1'))
    input_list.append(line[r1+3:r2])
    r3=(line.find('.A2'))
    input_list.append(line[r2+3:r3])
    r4=(line.find('.B0'))
    input_list.append(line[r3+3:r4])
    r5=(line.find('.B1'))
    input_list.append(line[r4+3:r5])
    r6=(line.find('.Y'))
    input_list.append(line[r5+3:r6])
    r7=(line.find(';'))
    input_list.append(line[r6+2:r7-1])
    
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'00'+' ( .A'+input_list[2].rstrip()+' .B'+input_list[3].rstrip()+' .Y('+"".join([str('n')+str(r)])+') );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'01'+' ( .A'+input_list[5].rstrip()+' .B'+input_list[6].rstrip()+' .Y('+"".join([str('n')+str(int(r)+1)])+') );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'02'+' ( .A('+"".join([str('n')+str(r)])+'), .B('+"".join([str('n')+str(r)])+'),'+' .Y('+"".join([str('n')+str(int(r)+2)])+') );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'03'+' ( .A('+"".join([str('n')+str(int(r)+1)])+'), .B('+"".join([str('n')+str(int(r)+1)])+'),'+' .Y('+"".join([str('n')+str(int(r)+3)])+') );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'04'+' ( .A('+"".join([str('n')+str(int(r)+2)])+'), .B'+input_list[4].rstrip()+' .Y('+"".join([str('n')+str(int(r)+4)])+') );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'05'+' ( .A('+"".join([str('n')+str(int(r)+4)])+'), .B('+"".join([str('n')+str(int(r)+4)])+'),'+' .Y('+"".join([str('n')+str(int(r)+5)])+') );')
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'06'+' ( .A('+"".join([str('n')+str(int(r)+5)])+'), .B('+"".join([str('n')+str(int(r)+3)])+'),'+' .Y'+input_list[7].rstrip()+' );')
    r0=r1=r2=r3=r4=r5=r6=r7=0
    return;
##
#
##
# Defining a function for CLKINVX1 to NAND2X1 realization
##
def INVX2():

    r0=(line.find('U'))
    input_list.append(line[0:r0])
    r1=(line.find('.A'))
    input_list.append(line[r0:r1-1])
    r2=(line.find('.Y'))
    input_list.append(line[r1+2:r2])
    r3=(line.find(';'))
    input_list.append(line[r2+2:r3-1])
    
    print_list.append('NAND2X1 '+input_list[1].rstrip()+' ( .A'+input_list[2].rstrip()+' .B'+input_list[2].rstrip()+' .Y'+input_list[3].rstrip()+' );')
    r0=r1=r2=r3=0
    return;
##
#
##
# Defining a function for OAI31X1 to NAND2X1 realization
##
def OAI31X1():

    r0=(line.find('U'))
    input_list.append(line[0:r0])
    r1=(line.find('.A0'))
    input_list.append(line[r0:r1-1])
    r2=(line.find('.A1'))
    input_list.append(line[r1+3:r2])
    r3=(line.find('.A2'))
    input_list.append(line[r2+3:r3])
    r4=(line.find('.B0'))
    input_list.append(line[r3+3:r4])
    r5=(line.find('.Y'))
    input_list.append(line[r4+3:r5])
    r6=(line.find(';'))
    input_list.append(line[r5+2:r6-1])
    
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'00'+' ( .A'+input_list[2].rstrip()+' .B'+input_list[3].rstrip()+' .Y('+"".join([str('n')+str(r)])+') );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'01'+' ( .A('+"".join([str('n')+str(r)])+'), .B('+"".join([str('n')+str(r)])+'),'+' .Y('+"".join([str('n')+str(int(r)+1)])+') );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'02'+' ( .A('+"".join([str('n')+str(int(r)+1)])+'),'+' .B'+input_list[4].rstrip()+' .Y('+"".join([str('n')+str(int(r)+2)])+') );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'03'+' ( .A('+"".join([str('n')+str(int(r)+2)])+'), .B('+"".join([str('n')+str(int(r)+2)])+'),'+' .Y('+"".join([str('n')+str(int(r)+3)])+') );')
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'04'+' ( .A('+"".join([str('n')+str(int(r)+3)])+'), .B'+input_list[5].rstrip()+' .Y'+input_list[6].rstrip()+' );')
    r0=r1=r2=r3=r4=r5=r6=0
    return;
##
#
def OAI2BB2X1():
    
    r0=(line.find('U'))
    input_list.append(line[0:r0])
    r1=(line.find('.B0'))
    input_list.append(line[r0:r1-1])
    r2=(line.find('.B1'))
    input_list.append(line[r1+3:r2-1])
    r3=(line.find('.A0N'))
    input_list.append(line[r2+3:r3-1])
    r4=(line.find('.A1N'))
    input_list.append(line[r3+4:r4-1])
    r5=(line.find('.Y'))
    input_list.append(line[r4+4:r5-1])
    r6=(line.find(';'))
    input_list.append(line[r5+2:r6-1])
    
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'00'+' ( .A'+input_list[2].rstrip()+', .B'+input_list[2].rstrip()+', .Y('+"".join([str('n')+str(r)])+') );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'01'+' ( .A'+input_list[3].rstrip()+', .B'+input_list[3].rstrip()+', .Y('+"".join([str('n')+str(int(r)+1)])+') );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'02'+' ( .A('+"".join([str('n')+str(r)])+')'+', .B('+"".join([str('n')+str(int(r)+1)])+')'+', .Y('+"".join([str('n')+str(int(r)+2)])+')'+' );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'03'+' ( .A'+input_list[4].rstrip()+', .B'+input_list[5].rstrip()+', .Y('+"".join([str('n')+str(int(r)+3)])+') );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'04'+' ( .A('+"".join([str('n')+str(int(r)+2)])+')'+', .B('+"".join([str('n')+str(int(r)+2)])+')'+', .Y('+"".join([str('n')+str(int(r)+4)])+')'+' );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'05'+' ( .A('+"".join([str('n')+str(int(r)+3)])+')'+', .B('+"".join([str('n')+str(int(r)+3)])+')'+', .Y('+"".join([str('n')+str(int(r)+5)])+')'+' );')
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'06'+' ( .A('+"".join([str('n')+str(int(r)+4)])+')'+', .B('+"".join([str('n')+str(int(r)+5)])+')'+', .Y'+input_list[6].rstrip()+' );')

    r0=r1=r2=r3=r4=r5=r6=0
    return;
##
#
def AOI21X1():
    
    r0=(line.find('U'))
    input_list.append(line[0:r0])
    r1=(line.find('.A0'))
    input_list.append(line[r0:r1-1])
    r2=(line.find('.A1'))
    input_list.append(line[r1+3:r2-1])
    r3=(line.find('.B0'))
    input_list.append(line[r2+3:r3-1])
    r4=(line.find('.Y'))
    input_list.append(line[r3+3:r4-1])
    r5=(line.find(';'))
    input_list.append(line[r4+2:r5-1])
    
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'00'+' ( .A'+input_list[2].rstrip()+', .B'+input_list[3].rstrip()+', .Y('+"".join([str('n')+str(r)])+') );')
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'01'+' ( .A('+"".join([str('n')+str(r)])+')'+', .B('+"".join([str('n')+str(r)])+')'+', .Y('+"".join([str('n')+str(int(r)+1)])+')'+' );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'02'+' ( .A('+"".join([str('n')+str(int(r)+1)])+'), .B'+input_list[4].rstrip()+', .Y'+input_list[5].rstrip()+' );')
    r0=r1=r2=r3=r4=r5=0
    return;
##
#
def AOI31X1():
    
    r0=(line.find('U'))
    input_list.append(line[0:r0])
    r1=(line.find('.A0'))
    input_list.append(line[r0:r1-1])
    r2=(line.find('.A1'))
    input_list.append(line[r1+3:r2])
    r3=(line.find('.A2'))
    input_list.append(line[r2+3:r3])
    r4=(line.find('.B0'))
    input_list.append(line[r3+3:r4])
    r5=(line.find('Y'))
    input_list.append(line[r4+3:r5-1])
    r6=(line.find(';'))
    input_list.append(line[r5+1:r6-1])
    
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'00'+' ( .A'+input_list[2].rstrip()+' .B'+input_list[3].rstrip()+' .Y('+"".join([str('n')+str(r)])+') );')
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'01'+' ( .A('+"".join([str('n')+str(r)])+')'+', .B('+"".join([str('n')+str(r)])+')'+', .Y('+"".join([str('n')+str(int(r)+1)])+')'+' );')
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'02'+' ( .A('+"".join([str('n')+str(int(r)+1)])+'), .B'+input_list[4].rstrip()+' .Y('+"".join([str('n')+str(int(r)+2)])+') );')
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'03'+' ( .A('+"".join([str('n')+str(int(r)+2)])+')'+', .B('+"".join([str('n')+str(int(r)+2)])+')'+', .Y('+"".join([str('n')+str(int(r)+3)])+')'+' );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'04'+' ( .A('+"".join([str('n')+str(int(r)+3)])+'), .B'+input_list[5].rstrip()+' .Y'+input_list[6].rstrip()+' );')
    r0=r1=r2=r3=r4=r5=r6=0
    return;
##
#
def NOR3XL():
    
    r0=(line.find('U'))
    input_list.append(line[0:r0])
    r1=(line.find('.A'))
    input_list.append(line[r0:r1-1])
    r2=(line.find('.B'))
    input_list.append(line[r1+2:r2])
    r3=(line.find('.C'))
    input_list.append(line[r2+2:r3])
    r4=(line.find('.Y'))
    input_list.append(line[r3+2:r4])
    r5=(line.find(';'))
    input_list.append(line[r4+2:r5-1])
    
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'00'+' ( .A'+input_list[2].rstrip()+' .B'+input_list[3].rstrip()+' .Y('+"".join([str('n')+str(r)])+') );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'01'+' ( .A('+"".join([str('n')+str(r)])+')'+', .B('+"".join([str('n')+str(r)])+')'+', .Y('+"".join([str('n')+str(int(r)+1)])+')'+' );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'02'+' ( .A('+"".join([str('n')+str(int(r)+1)])+'), .B'+input_list[4].rstrip()+' .Y'+input_list[5].rstrip()+' );')
    r0=r1=r2=r3=r4=r5=0
    return;
##
#
def AOI2BB1X1():
    
    r0=(line.find('U'))
    input_list.append(line[0:r0])
    r1=(line.find('.A0'))
    input_list.append(line[r0:r1-1])
    r2=(line.find('.A1'))
    input_list.append(line[r1+4:r2-1])
    r3=(line.find('.B0'))
    input_list.append(line[r2+4:r3-1])
    r4=(line.find('.Y'))
    input_list.append(line[r3+3:r4-1])
    r5=(line.find(';'))
    input_list.append(line[r4+2:r5-1])
    
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'00'+' ( .A'+input_list[2].rstrip()+', .B'+input_list[2].rstrip()+', .Y('+"".join([str('n')+str(r)])+') );')
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'01'+' ( .A'+input_list[3].rstrip()+', .B'+input_list[3].rstrip()+', .Y('+"".join([str('n')+str(int(r)+1)])+') );')
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'02'+' ( .A('+"".join([str('n')+str(r)])+')'+', .B('+"".join([str('n')+str(int(r)+1)])+')'+', .Y('+"".join([str('n')+str(int(r)+2)])+')'+' );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'03'+' ( .A('+"".join([str('n')+str(int(r)+3)])+'), .B'+input_list[4].rstrip()+', .Y'+input_list[5].rstrip()+' );')
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'04'+' ( .A('+"".join([str('n')+str(int(r)+2)])+')'+', .B('+"".join([str('n')+str(int(r)+2)])+')'+', .Y('+"".join([str('n')+str(int(r)+3)])+')'+' );')
    r0=r1=r2=r3=r4=r5=0
    return;
##
#
def OR2X2():
    
    r0=(line.find('U'))
    input_list.append(line[0:r0])
    r1=(line.find('.A'))
    input_list.append(line[r0:r1-1])
    r2=(line.find('.B'))
    input_list.append(line[r1+2:r2])
    r3=(line.find('.Y'))
    input_list.append(line[r2+2:r3])
    r4=(line.find(';'))
    input_list.append(line[r3+2:r4-1])
    
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'00'+' ( .A'+input_list[2].rstrip()+' .B'+input_list[3].rstrip()+' .Y('+"".join([str('n')+str(r)])+') );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'01'+' ( .A('+"".join([str('n')+str(r)])+')'+', .B('+"".join([str('n')+str(r)])+')'+', .Y'+input_list[4].rstrip()+' );') 
             
    r0=r1=r2=r3=r4=r5=0
    return;
##
#
def MXI2XL():
    
    r0=(line.find('U'))
    input_list.append(line[0:r0])
    r1=(line.find('.A'))
    input_list.append(line[r0:r1-1])
    r2=(line.find('.B'))
    input_list.append(line[r1+2:r2])
    r3=(line.find('.S0'))
    input_list.append(line[r2+2:r3])
    r4=(line.find('.Y'))
    input_list.append(line[r3+3:r4])
    r5=(line.find(';'))
    input_list.append(line[r4+2:r5-1])
    
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'00'+' ( .A'+input_list[4].rstrip()+' .B'+input_list[3].rstrip()+' .Y('+"".join([str('n')+str(r)])+') );')
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'01'+' ( .A('+"".join([str('n')+str(r)])+')'+', .B('+"".join([str('n')+str(r)])+')'+', .Y('+"".join([str('n')+str(int(r)+4)])+')'+' );')
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'02'+' ( .A'+input_list[4].rstrip()+' .B'+input_list[4].rstrip()+' .Y('+"".join([str('n')+str(int(r)+1)])+') );')
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'03'+' ( .A('+"".join([str('n')+str(int(r)+1)])+'), .B'+input_list[2].rstrip()+' .Y('+"".join([str('n')+str(int(r)+2)])+') );')
    print_list.append('NAND2X1 '+input_list[1].rstrip()+'04'+' ( .A('+"".join([str('n')+str(int(r)+2)])+')'+', .B('+"".join([str('n')+str(int(r)+2)])+')'+', .Y('+"".join([str('n')+str(int(r)+3)])+')'+' );')
    print_list.append('NOR2X1 '+input_list[1].rstrip()+'05'+' ( .A('+"".join([str('n')+str(int(r)+3)])+')'+', .B('+"".join([str('n')+str(int(r)+4)])+')'+', .Y'+input_list[5].rstrip()+' );')    
    r0=r1=r2=r3=r4=r5=0
    return;
##
#
##
# Creating a for loop for accessing each line in the file
for line in f:

    if line.find("NAND3XL")> -1:
       line = line.replace(" ","")
       input_list=[]
       NAND3XL()
       r+=2

    elif line.find("NAND2X1")> -1:
       NAND2X1()

    elif line.find("CLKINVX1")> -1:
       line = line.replace(" ","")
       input_list = []
       CLKINVX1()

    elif line.find("OAI22XL")> -1:
       line = line.replace(" ","")
       input_list = []
       OAI22XL()
       r+=4
       
    elif line.find("OAI221X1")> -1:
       line = line.replace(" ","")
       input_list = []
       OAI221X1()
       r+=6
       
    elif line.find("OAI21XL")> -1:
       line = line.replace(" ","")
       input_list = []
       OAI21XL()
       r+=2
       
    elif line.find("OAI2BB1X1")> -1:
       line = line.replace(" ","")
       input_list = []
       OAI2BB1X1()
       r+=4
       
    elif line.find("OAI211XL")> -1:
       line = line.replace(" ","")
       input_list = []
       OAI211XL()
       r+=4

    elif line.find("OAI33X1")> -1:
       line = line.replace(" ","")
       input_list = []
       OAI33X1()
       r+=8
       
    elif line.find("XNOR2XL")> -1:
       line = line.replace(" ","")
       input_list = []
       XNOR2XL()
       r+=3

    elif line.find("NOR2XL")> -1:
       line = line.replace("NOR2XL","NOR2X1")
       NOR2XL()

    elif line.find("AOI32X1")> -1:
       line = line.replace(" ","")
       input_list = []
       AOI32X1()
       r+=6
       
    elif line.find("OAI32X1")> -1:
       line = line.replace(" ","")
       input_list = []
       OAI32X1()
       r+=6
       
    elif line.find("INVX2")> -1:
       line = line.replace(" ","")
       input_list = []
       INVX2()
       
    elif line.find("OAI31X1")> -1:
       line = line.replace(" ","")
       input_list = []
       OAI31X1()
       r+=4
       
    elif line.find("OAI2BB2X1")>-1:
        line = line.replace(" ","")
        input_list = []
        OAI2BB2X1()
        r+=6
        
    elif line.find("AOI21X1")>-1:
        line = line.replace(" ","")
        input_list = []
        AOI21X1()
        r+=2
        
    elif line.find("AOI31X1")>-1:
        line = line.replace(" ","")
        input_list = []
        AOI31X1()
        r+=4
        
    elif line.find("NOR3XL")>-1:
        line = line.replace(" ","")
        input_list = []
        NOR3XL()
        r+=2

    elif line.find("AOI2BB1X1")>-1:
        line = line.replace(" ","")
        input_list = []
        AOI2BB1X1()
        r+=4
        
    elif line.find("OR2X2")>-1:
        line = line.replace(" ","")
        input_list = []
        OR2X2()
        r+=1

    elif line.find("MXI2XL")>-1:
        line = line.replace(" ","")
        input_list = []
        MXI2XL()
        r+=5

    else:
        print_list.append(line)

##
# for generating output file
with open('block32_equivalent.v','w') as g:
 for v in print_list:
     x = v
     g.write(x+'\n')
##
# For cleaning the spaces in the file
clean_lines = []
with open("block32_equivalent.v", "r") as file_output:
    lines = file_output.readlines()
    clean_lines = [l.strip() for l in lines if l.strip()]

with open("block32_equivalent.v", "w") as file_output:
    file_output.writelines('\n'.join(clean_lines))
##
#
##
# Closing the files
g.close
file_output.close
  
##################################################
#########  End of Main functionaility  ###########
##################################################

##################################################
##### Block for adding new wires generated #######
##################################################

f = open('block32_equivalent.v','r')
wire_count = r
w1_list = []
w3_list = []
w4_list = []
w5_list = []

for e in range((int(zmin)),(int(r))):
    w1_list.append("".join([str(' n')+str(e)+str(',')]))
    w2_list = []
    w2_list.append("wire ".rstrip())
    w2_list.append(''.join(w1_list + ['']).rstrip(' '))
    w2_list.append(";")
    w3_list =(''.join(w2_list + ['']).rstrip(' '))
    w3_list = w3_list.replace(",;",";")
    
for r in f:

    if r.find('wire') >-1:
        w5_list.append(w3_list)

    elif r.startswith('n') == True:
         w4_list.append(r)
    else:
         w5_list.append(r)

##
# for generating output file
with open('block32_equivalent.v','w') as g:
 for v in w5_list:
     x = v
     x = textwrap.fill(x,130)   # Wrapped the text for writing the wires block to a fixed with of 130
     g.write(x+'\n')
##
# For cleaning the spaces in the file
clean_lines = []
with open("block32_equivalent.v", "r") as file_output:
    lines = file_output.readlines()
    clean_lines = [l.strip() for l in lines if l.strip()]

with open("block32_equivalent.v", "w") as file_output:
    file_output.writelines('\n'.join(clean_lines))
##
#
##
# Closing the files
g.close
file_output.close

Endtime = time.clock()
Totaltime =  Endtime - startTime

#########################################
###########    Dashboard   ##############
#########################################

print ("Python program for verilog equivalent netlist generation using NAND and NOR logic gates")
print ("- using Python version", sys.version)
print ("Total conversion time:", Totaltime)
print ("Total source lines:", num_lines)
print ("Total number of new wires added:", int(wire_count) - int(zmax))
print ("Average lines/sec:", ( "%.1f" % (float(num_lines)/(Totaltime+.05 ) ) ))

#####################################################################
############-------------    The End       ----------################
#####################################################################


