#############################################################
#中断演示程序，简单走马灯测试，按下1号键用数字1循环移位测试
#中断演示程序，简单走马灯测试，按下2号键用数字2循环移位测试
#最右侧显示数据是循环计数
#这只是中断服务程序演示程序，方便大家检查中断嵌套，
#设计时需要考虑开中断，关中断，设置中断屏蔽字如何用软件指令实现，如何保护现场，中断隐指令需要多少周期
#############################################################
.text
jmp benchmark_start
###################################################################
# 中断1号               逻辑左移，每次移位4位 
# 显示区域依次显示0x00000016 0x00000106 0x00001006 0x00010006 ... 10000006  00000006 依次循环6次
###################################################################

#保存寄存器
addi $sp,$sp,-4
sw $s0,0($sp)
addi $sp,$sp,-4
sw $s3,0($sp)
addi $sp,$sp,-4
sw $s4,0($sp)
addi $sp,$sp,-4
sw $s5,0($sp)
addi $sp,$sp,-4
sw $s6,0($sp)
addi $sp,$sp,-4
sw $v0,0($sp)

MFLO $zero			# 保护现场　　EPC　中断屏蔽字
MFC0 $zero, $zero	# 开中断

# 跑马灯程序
addi $s6,$zero,1       #中断号1,2,3   不同中断号显示值不一样
addi $s4,$zero,6      #循环次数初始值  
addi $s5,$zero,1       #计数器累加值
IntLoop1:
add $s0,$zero,$s6   
IntLeftShift1:       
sll $s0, $s0, 4  
or $s3,$s0,$s4
add    $a0,$0,$s3       #display $s0
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.   
bne $s0, $zero, IntLeftShift1
sub $s4,$s4,$s5      #循环次数递减
bne $s4, $zero, IntLoop1

MFC1 $zero , $f1 		#关中断

MOVN $zero,$zero,$zero	#恢复现场

#恢复寄存器
lw $v0,0($sp)
addi $sp,$sp,4
lw $s6,0($sp)
addi $sp,$sp,4
lw $s5,0($sp)
addi $sp,$sp,4
lw $s4,0($sp)
addi $sp,$sp,4
lw $s3,0($sp)
addi $sp,$sp,4
lw $s0,0($sp)
addi $sp,$sp,4

MFC0 $zero, $zero		#开中断
ERET					#中断返回

###################################################################
# 中断2号               逻辑左移，每次移位4位 
# 显示区域依次显示0x00000016 0x00000106 0x00001006 0x00010006 ... 10000006  00000006 依次循环6次
###################################################################

#保存寄存器
addi $sp,$sp,-4
sw $s0,0($sp)
addi $sp,$sp,-4
sw $s3,0($sp)
addi $sp,$sp,-4
sw $s4,0($sp)
addi $sp,$sp,-4
sw $s5,0($sp)
addi $sp,$sp,-4
sw $s6,0($sp)
addi $sp,$sp,-4
sw $v0,0($sp)

MFLO $zero			# 保护现场　　EPC　中断屏蔽字
MFC0 $zero, $zero	# 开中断

# 跑马灯程序
addi $s6,$zero,2       #中断号1,2,3   不同中断号显示值不一样
addi $s4,$zero,6      #循环次数初始值  
addi $s5,$zero,1       #计数器累加值
IntLoop2:
add $s0,$zero,$s6   
IntLeftShift2:       
sll $s0, $s0, 4  
or $s3,$s0,$s4
add    $a0,$0,$s3       #display $s0
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.   
bne $s0, $zero, IntLeftShift2
sub $s4,$s4,$s5      #循环次数递减
bne $s4, $zero, IntLoop2



MFC1 $zero , $f1 		#关中断

MOVN $zero,$zero,$zero	#恢复现场

#恢复寄存器
lw $v0,0($sp)
addi $sp,$sp,4
lw $s6,0($sp)
addi $sp,$sp,4
lw $s5,0($sp)
addi $sp,$sp,4
lw $s4,0($sp)
addi $sp,$sp,4
lw $s3,0($sp)
addi $sp,$sp,4
lw $s0,0($sp)
addi $sp,$sp,4

MFC0 $zero, $zero		#开中断
ERET					#中断返回

###################################################################
# 中断3号               逻辑左移，每次移位4位 
# 显示区域依次显示0x00000016 0x00000106 0x00001006 0x00010006 ... 10000006  00000006 依次循环6次
###################################################################

#保存寄存器
addi $sp,$sp,-4
sw $s0,0($sp)
addi $sp,$sp,-4
sw $s3,0($sp)
addi $sp,$sp,-4
sw $s4,0($sp)
addi $sp,$sp,-4
sw $s5,0($sp)
addi $sp,$sp,-4
sw $s6,0($sp)
addi $sp,$sp,-4
sw $v0,0($sp)

MFLO $zero			# 保护现场　　EPC　中断屏蔽字
MFC0 $zero, $zero	# 开中断

# 跑马灯程序
addi $s6,$zero,3       #中断号1,2,3   不同中断号显示值不一样
addi $s4,$zero,6      #循环次数初始值  
addi $s5,$zero,1       #计数器累加值
IntLoop3:
add $s0,$zero,$s6   
IntLeftShift3:       
sll $s0, $s0, 4  
or $s3,$s0,$s4
add    $a0,$0,$s3       #display $s0
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.   
bne $s0, $zero, IntLeftShift3
sub $s4,$s4,$s5      #循环次数递减
bne $s4, $zero, IntLoop3


MFC1 $zero , $f1 		#关中断

MOVN $zero,$zero,$zero	#恢复现场

#恢复寄存器
lw $v0,0($sp)
addi $sp,$sp,4
lw $s6,0($sp)
addi $sp,$sp,4
lw $s5,0($sp)
addi $sp,$sp,4
lw $s4,0($sp)
addi $sp,$sp,4
lw $s3,0($sp)
addi $sp,$sp,4
lw $s0,0($sp)
addi $sp,$sp,4

MFC0 $zero, $zero		#开中断
ERET					#中断返回


.text
benchmark_start:
 addi $s1,$zero, 1   #≤‚ ‘j,jal,jr÷∏¡Ó£¨»Á–Ë“™ø…∑÷ø™≤‚ ‘£¨÷¥––’˝≥£”¶∏√ «15∏ˆ÷‹∆⁄
 j jmp_next1
 addi $s1,$zero, 1
 addi $s2,$zero, 2
 addi $s3,$zero, 3
jmp_next1:
 j jmp_next2
 addi $s1,$zero, 1
 addi $s2,$zero, 2
 addi $s3,$zero, 3
jmp_next2:
 j jmp_next3
 addi $s1,$zero, 1
 addi $s2,$zero, 2
 addi $s3,$zero, 3
jmp_next3:
 j jmp_next4
 addi $s1,$zero, 1
 addi $s2,$zero, 2
 addi $s3,$zero, 3
jmp_next4:jal jmp_count

######################################


#“∆Œª≤‚ ‘  –Ë“™÷ß≥÷≥¨addi,sll,add,syscall,srl,sll,sra,beq,j,syscall    revise date:2015/12/16 tiger

.text
addi $s0,$zero,1     #ºÚµ•“∆Œª£¨—≠ª∑≤‚ ‘£¨0∫≈«¯”Úœ‘ æµƒ «≥ı º÷µ1◊Û“∆1Œª÷ÿ∏¥15¥Œµƒ÷µ£¨1∫≈«¯”Ú «¿€º”÷µ
addi $s1,$zero,1  
sll $s1, $s1, 31   #¬ﬂº≠◊Û“∆31Œª $s1=0x80000000
 

###################################################################
#                ¬ﬂº≠”““∆≤‚ ‘ 
# œ‘ æ«¯”Ú“¿¥Œœ‘ æ0x80000000 0x20000000 0x08000000 0x02000000 0x00800000 0x00200000 0x00080000 0x00020000 0x00008000 0x00002000 0x00000800 0x00000200 0x00000080 0x00000020 0x00000008 0x00000002 0x00000000  
###################################################################
LogicalRightShift:            #¬ﬂº≠”““∆≤‚ ‘£¨Ω´◊Ó∏ﬂŒª1÷ŒªœÚ”“”““∆÷±÷¡Ω·π˚Œ™¡„

add    $a0,$0,$s1       #display $s1    #¬ﬂº≠”““∆≤‚ ‘£¨Ω´◊Ó∏ﬂŒª1÷ŒªœÚ”“”““∆÷±÷¡Ω·π˚Œ™¡„
addi   $v0,$0,34        # display hex
syscall                 # we are out of here.  
     
srl $s1, $s1, 2   
beq $s1, $zero, shift_next1
j LogicalRightShift

shift_next1:

add    $a0,$0,$s1       #display $s1
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.  


###################################################################
#                ¬ﬂº≠◊Û“∆≤‚ ‘ 
# œ‘ æ«¯”Ú“¿¥Œœ‘ æ0x00000004 0x00000010 0x00000040 0x00000100 0x00000400 0x00001000 0x00004000 0x00010000 0x00040000 0x00100000 0x00400000 0x01000000 0x04000000 0x10000000 0x40000000 0x00000000 
###################################################################

addi $s1,$zero, 1        #                ¬ﬂº≠◊Û“∆≤‚ ‘ 
LogicalLeftShift:         #¬ﬂº≠◊Û“∆≤‚ ‘£¨Ω´◊ÓµÕŒª1÷ŒªœÚ◊Û“∆÷±÷¡Ω·π˚Œ™¡„
sll $s1, $s1, 2  

add    $a0,$0,$s1       #display $s1
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.  
      
beq $s1, $zero, ArithRightShift
j LogicalLeftShift


###################################################################
#                À„ ı”““∆≤‚ ‘ 
# œ‘ æ«¯”Ú“¿¥Œœ‘ æ0x80000000 0xf0000000 0xff000000 0xfff00000 0xffff0000 0xfffff000 0xffffff00 0xfffffff0 0xffffffff 
###################################################################
ArithRightShift:          #À„ ı”““∆≤‚ ‘£¨#À„ ı“∆Œª≤‚ ‘£¨80000000À„ ı”““∆£¨“¿¥Œœ‘ æŒ™F0000000,FF000000,FFF00000,FFFF0000÷±÷¡FFFFFFFF

addi $s1,$zero,1     #                À„ ı”““∆≤‚ ‘ 
sll $s1, $s1, 31   #¬ﬂº≠◊Û“∆31Œª $s1=0x80000000

add    $a0,$0,$s1       #display $s1
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.  

sra $s1, $s1, 3    #$s1=0X80000000-->0XF0000000

add    $a0,$0,$s1       #display $s1
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.  


sra $s1, $s1, 4    #0XF0000000-->0XFF000000

add    $a0,$0,$s1       #display $s1
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.  


sra $s1, $s1, 4    #0XFF000000-->0XFFF00000

add    $a0,$0,$s1       #display $s1
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.  

sra $s1, $s1, 4    

add    $a0,$0,$s1       #display $s1
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.  

sra $s1, $s1, 4    

add    $a0,$0,$s1       #display $s1
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.  


sra $s1, $s1, 4    

add    $a0,$0,$s1       #display $s1
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.  


sra $s1, $s1, 4    

add    $a0,$0,$s1       #display $s1
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.  


sra $s1, $s1, 4    


add    $a0,$0,$s1       #display $s1
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.  

#############################################################
#◊ﬂ¬Ìµ∆≤‚ ‘,≤‚ ‘addi,andi,sll,srl,sra,or,ori,nor,syscall  LED∞¥◊ﬂ¬Ìµ∆∑Ω Ω¿¥ªÿœ‘ æ ˝æ›
#############################################################

.text
addi $s0,$zero,1 
sll $s3, $s0, 31      # $s3=0x80000000
sra $s3, $s3, 31      # $s3=0xFFFFFFFF   
addu $s0,$zero,$zero   # $s0=0         
addi $s2,$zero,12 

addiu $s6,$0,3  #◊ﬂ¬Ìµ∆º∆ ˝
zmd_loop:

addiu $s0, $s0, 1    #º∆À„œ¬“ª∏ˆ◊ﬂ¬Ìµ∆µƒ ˝æ›
andi $s0, $s0, 15  

#######################################
addi $t0,$0,8    
addi $t1,$0,1
left:

sll $s3, $s3, 4   #◊ﬂ¬Ìµ∆◊Û“∆
or $s3, $s3, $s0

add    $a0,$0,$s3       # display $s3
addi   $v0,$0,34         # system call for LED display 
syscall                 # display 

sub $t0,$t0,$t1
bne $t0,$0,left
#######################################

addi $s0, $s0, 1   #º∆À„œ¬“ª∏ˆ◊ﬂ¬Ìµ∆µƒ ˝æ›
addi $t8,$0,15
and $s0, $s0, $t8
sll $s0, $s0, 28     

addi $t0,$0,8
addi $t1,$0,1

zmd_right:

srl $s3, $s3, 4  #◊ﬂ¬Ìµ∆”““∆
or $s3, $s3, $s0

addu    $a0,$0,$s3       # display $s3
addi   $v0,$0,34         # system call for LED display 
syscall                 # display 

sub $t0,$t0,$t1
bne $t0,$0,zmd_right
srl $s0, $s0, 28  
#######################################

sub $s6,$s6,$t1
beq $s6,$0, exit
j zmd_loop

exit:

add $t0,$0,$0
nor $t0,$t0,$t0      #test nor  ori
sll $t0,$t0,16
ori $t0,$t0,0xffff

addu   $a0,$0,$t0       # display $t0
addi   $v0,$0,34         # system call for LED display 
syscall                 # display 
#################################################################################
#±æ≥Ã–Ú µœ÷0-15∫≈◊÷µ•‘™µƒΩµ–Ú≈≈–Ú,¥À≥Ã–Úø…‘⁄mars mips∑¬’Ê∆˜÷–‘À––
#‘À–– ±«ÎΩ´Mars Setting÷–µƒMemory Configuration…Ë÷√Œ™Compact£¨data at address 0
#
#################################################################################
 .text
sort_init:
 addi $s0,$0,-1
 addi $s1,$0,0
 
 sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
  sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
  sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
  sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
  sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
  sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
  sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
    sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
   
 addi $s0,$s0,1
 
 add $s0,$zero,$zero   
 addi $s1,$zero,60   #≈≈–Ú«¯º‰
sort_loop:
 lw $s3,0($s0)     
 lw $s4,0($s1)
 slt $t0,$s3,$s4
 beq $t0,$0,sort_next   #Ωµ–Ú≈≈–Ú
 sw $s3, 0($s1)
 sw $s4, 0($s0)   
sort_next:
 addi $s1, $s1, -4   
 bne $s0, $s1, sort_loop  
 
 add    $a0,$0,$s0       #display $s0
 addi   $v0,$0,34         # display hex
 syscall                 # we are out of here.  DISP: disp $r0, 0
 
 addi $s0,$s0,4
 addi $s1,$zero,60
 bne $s0, $s1, sort_loop

 addi   $v0,$zero,50         # system call for pause
 syscall                  # we are out of here.   
 
 
#############################################
# insert your ccmb benchmark program here!!!
#############################################

j benchmark_start       #delete this instruction for ccmb bencmark
#C1 instruction benchmark



#C2 instruction benchmark



#Mem instruction benchmark




#Branch instruction benchmark


                 
 addi   $v0,$zero,10         # system call for exit
 syscall                  # we are out of here.   
 
 #MIPS¥¶¿Ì∆˜ µœ÷÷–«Î”√Õ£ª˙÷∏¡Ó µœ÷syscall

jmp_count: addi $s0,$zero, 0
       addi $s0,$s0, 1
       add    $a0,$0,$s0      
       addi   $v0,$0,34         # display hex
       syscall                 # we are out of here.  
       
       addi $s0,$s0, 2
       add    $a0,$0,$s0      
       addi   $v0,$0,34         # display hex
       syscall                 # we are out of here.  
       
       addi $s0,$s0, 3
       add    $a0,$0,$s0      
       addi   $v0,$0,34         # display hex
       syscall                 # we are out of here.  
       
       addi $s0,$s0, 4       
       add    $a0,$0,$s0      
       addi   $v0,$0,34         # display hex
       syscall                 # we are out of here.  
       
       addi $s0,$s0, 5              
       add    $a0,$0,$s0      
       addi   $v0,$0,34         # display hex
       syscall                 # we are out of here.  
       
       addi $s0,$s0, 6              
       add    $a0,$0,$s0      
       addi   $v0,$0,34         # display hex
       syscall                 # we are out of here.  

       addi $s0,$s0, 7              
       add    $a0,$0,$s0      
       addi   $v0,$0,34         # display hex
       syscall                 # we are out of here.  

       addi $s0,$s0, 8              
       add    $a0,$0,$s0      
       addi   $v0,$0,34         # display hex
       addi   $v0,$0,34         # display hex       
       syscall                 # we are out of here.  

       
       jr $31
