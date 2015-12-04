 1000  00        NOP                  ;.
 1001  01 12     AJMP  L1012          ;..
 1003  02 34 56  LJMP  L3456          ;.4V
 1006  03        RR    A              ;.
 1007  04        INC   A              ;.
 1008  05 12     INC   D12            ;..
 100A  06        INC   @R0            ;.
 100B  07        INC   @R1            ;.
 100C  08        INC   R0             ;.
 100D  09        INC   R1             ;.
 100E  0A        INC   R2             ;.
 100F  0B        INC   R3             ;.
 1010  0C        INC   R4             ;.
 1011  0D        INC   R5             ;.
L1012: 0E        INC   R6             ;.
 1013  0F        INC   R7             ;.
 1014  10 E1 05  JBC   $E0.1,L101C    ;...
 1017  11 12     ACALL L1012          ;..
 1019  12 34 56  LCALL L3456          ;.4V
L101C: 13        RRC   A              ;.
 101D  14        DEC   A              ;.
 101E  15 12     DEC   D12            ;..
 1020  16        DEC   @R0            ;.
 1021  17        DEC   @R1            ;.
 1022  18        DEC   R0             ;.
 1023  19        DEC   R1             ;.
 1024  1A        DEC   R2             ;.
 1025  1B        DEC   R3             ;.
 1026  1C        DEC   R4             ;.
 1027  1D        DEC   R5             ;.
 1028  1E        DEC   R6             ;.
 1029  1F        DEC   R7             ;.
 102A  20 E1 EF  JB    $E0.1,L101C    ; ..
 102D  21 23     AJMP  L1123          ;!#
 102F  22        RET                  ;"

 1030  23        RL    A              ;#
 1031  24 12     ADD   A,#$12         ;$.
 1033  25 12     ADD   A,D12          ;%.
 1035  26        ADD   A,@R0          ;&
 1036  27        ADD   A,@R1          ;'
 1037  28        ADD   A,R0           ;(
 1038  29        ADD   A,R1           ;)
 1039  2A        ADD   A,R2           ;*
 103A  2B        ADD   A,R3           ;+
 103B  2C        ADD   A,R4           ;,
 103C  2D        ADD   A,R5           ;-
 103D  2E        ADD   A,R6           ;.
 103E  2F        ADD   A,R7           ;/
 103F  30 E1 DA  JNB   $E0.1,L101C    ;0..
 1042  31 23     ACALL L1123          ;1#
 1044  32        RETI                 ;2

 1045  33        RLC   A              ;3
 1046  34 12     ADDC  A,#$12         ;4.
 1048  35 12     ADDC  A,D12          ;5.
 104A  36        ADDC  A,@R0          ;6
 104B  37        ADDC  A,@R1          ;7
 104C  38        ADDC  A,R0           ;8
 104D  39        ADDC  A,R1           ;9
 104E  3A        ADDC  A,R2           ;:
 104F  3B        ADDC  A,R3           ;;
 1050  3C        ADDC  A,R4           ;<
 1051  3D        ADDC  A,R5           ;=
 1052  3E        ADDC  A,R6           ;>
 1053  3F        ADDC  A,R7           ;?
 1054  40 C6     JC    L101C          ;@.
 1056  41 34     AJMP  L1234          ;A4
 1058  42 12     ORL   D12,A          ;B.
 105A  43 12 12  ORL   D12,#$12       ;C..
 105D  44 12     ORL   A,#$12         ;D.
 105F  45 12     ORL   A,D12          ;E.
 1061  46        ORL   A,@R0          ;F
 1062  47        ORL   A,@R1          ;G
 1063  48        ORL   A,R0           ;H
 1064  49        ORL   A,R1           ;I
 1065  4A        ORL   A,R2           ;J
 1066  4B        ORL   A,R3           ;K
 1067  4C        ORL   A,R4           ;L
 1068  4D        ORL   A,R5           ;M
 1069  4E        ORL   A,R6           ;N
 106A  4F        ORL   A,R7           ;O
 106B  50 53     JNC   L10C0          ;PS
 106D  51 34     ACALL L1234          ;Q4
 106F  52 12     ANL   D12,A          ;R.
 1071  53 12 12  ANL   D12,#$12       ;S..
 1074  54 12     ANL   A,#$12         ;T.
 1076  55 12     ANL   A,D12          ;U.
 1078  56        ANL   A,@R0          ;V
 1079  57        ANL   A,@R1          ;W
 107A  58        ANL   A,R0           ;X
 107B  59        ANL   A,R1           ;Y
 107C  5A        ANL   A,R2           ;Z
 107D  5B        ANL   A,R3           ;[
 107E  5C        ANL   A,R4           ;\
 107F  5D        ANL   A,R5           ;]
 1080  5E        ANL   A,R6           ;^
 1081  5F        ANL   A,R7           ;_
 1082  60 3C     JZ    L10C0          ;`<
 1084  61 45     AJMP  L1345          ;aE
 1086  62 12     XRL   D12,A          ;b.
 1088  63 12 12  XRL   D12,#$12       ;c..
 108B  64 12     XRL   A,#$12         ;d.
 108D  65 12     XRL   A,D12          ;e.
 108F  66        XRL   A,@R0          ;f
 1090  67        XRL   A,@R1          ;g
 1091  68        XRL   A,R0           ;h
 1092  69        XRL   A,R1           ;i
 1093  6A        XRL   A,R2           ;j
 1094  6B        XRL   A,R3           ;k
 1095  6C        XRL   A,R4           ;l
 1096  6D        XRL   A,R5           ;m
 1097  6E        XRL   A,R6           ;n
 1098  6F        XRL   A,R7           ;o
 1099  70 25     JNZ   L10C0          ;p%
 109B  71 45     ACALL L1345          ;qE
 109D  72 E1     ORL   C,$E0.1        ;r.
 109F  73        JMP   @A+DPTR        ;s
 10A0  74 12     MOV   A,#$12         ;t.
 10A2  75 12 12  MOV   D12,#$12       ;u..
 10A5  76 12     MOV   @R0,#$12       ;v.
 10A7  77 12     MOV   @R1,#$12       ;w.
 10A9  78 12     MOV   R0,#$12        ;x.
 10AB  79 12     MOV   R1,#$12        ;y.
 10AD  7A 12     MOV   R2,#$12        ;z.
 10AF  7B 12     MOV   R3,#$12        ;{.
 10B1  7C 12     MOV   R4,#$12        ;|.
 10B3  7D 12     MOV   R5,#$12        ;}.
 10B5  7E 12     MOV   R6,#$12        ;~.
 10B7  7F 12     MOV   R7,#$12        ;..
 10B9  80 05     SJMP  L10C0          ;..
 10BB  81 56     AJMP  L1456          ;.V
 10BD  82 E1     ANL   C,$E0.1        ;..
 10BF  83        MOVC  A,@A+PC        ;.
L10C0: 84        DIV   AB             ;.
 10C1  85 12 12  MOV   D12,D12        ;...
 10C4  86 12     MOV   D12,@R0        ;..
 10C6  87 12     MOV   D12,@R1        ;..
 10C8  88 12     MOV   D12,R0         ;..
 10CA  89 12     MOV   D12,R1         ;..
 10CC  8A 12     MOV   D12,R2         ;..
 10CE  8B 12     MOV   D12,R3         ;..
 10D0  8C 12     MOV   D12,R4         ;..
 10D2  8D 12     MOV   D12,R5         ;..
 10D4  8E 12     MOV   D12,R6         ;..
 10D6  8F 12     MOV   D12,R7         ;..
 10D8  90 34 56  MOV   DPTR,#$3456    ;.4V
 10DB  91 56     ACALL L1456          ;.V
 10DD  92 E1     MOV   $E0.1,C        ;..
 10DF  93        MOVC  A,@A+DPTR      ;.
 10E0  94 12     SUBB  A,#$12         ;..
 10E2  95 12     SUBB  A,D12          ;..
 10E4  96        SUBB  A,@R0          ;.
 10E5  97        SUBB  A,@R1          ;.
 10E6  98        SUBB  A,R0           ;.
 10E7  99        SUBB  A,R1           ;.
 10E8  9A        SUBB  A,R2           ;.
 10E9  9B        SUBB  A,R3           ;.
 10EA  9C        SUBB  A,R4           ;.
 10EB  9D        SUBB  A,R5           ;.
 10EC  9E        SUBB  A,R6           ;.
 10ED  9F        SUBB  A,R7           ;.
 10EE  A0 E1     ORL   C,/$E0.1       ;..
 10F0  A1 67     AJMP  L1567          ;.g
 10F2  A2 E1     MOV   C,$E0.1        ;..
 10F4  A3        INC   DPTR           ;.
 10F5  A4        MUL   AB             ;.
 10F6  A5        .DB   $A5            ;.
 10F7  A6 12     MOV   @R0,D12        ;..
 10F9  A7 12     MOV   @R1,D12        ;..
 10FB  A8 12     MOV   R0,D12         ;..
 10FD  A9 12     MOV   R1,D12         ;..
 10FF  AA 12     MOV   R2,D12         ;..
 1101  AB 12     MOV   R3,D12         ;..
 1103  AC 12     MOV   R4,D12         ;..
 1105  AD 12     MOV   R5,D12         ;..
 1107  AE 12     MOV   R6,D12         ;..
 1109  AF 12     MOV   R7,D12         ;..
 110B  B0 E1     ANL   C,/$E0.1       ;..
 110D  B1 67     ACALL L1567          ;.g
 110F  B2 E1     CPL   $E0.1          ;..
 1111  B3        CPL   C              ;.
 1112  B4 12 28  CJNE  A,#$12,L113D   ;..(
 1115  B5 12 25  CJNE  A,D12,L113D    ;..%
 1118  B6 12 22  CJNE  @R0,#$12,L113D ;.."
 111B  B7 12 1F  CJNE  @R1,#$12,L113D ;...
 111E  B8 12 1C  CJNE  R0,#$12,L113D  ;...
 1121  B9 12 19  CJNE  R1,#$12,L113D  ;...
 1124  BA 12 16  CJNE  R2,#$12,L113D  ;...
 1127  BB 12 13  CJNE  R3,#$12,L113D  ;...
 112A  BC 12 10  CJNE  R4,#$12,L113D  ;...
 112D  BD 12 0D  CJNE  R5,#$12,L113D  ;...
 1130  BE 12 0A  CJNE  R6,#$12,L113D  ;...
 1133  BF 12 07  CJNE  R7,#$12,L113D  ;...
 1136  C0 12     PUSH  D12            ;..
 1138  C1 78     AJMP  L1678          ;.x
 113A  C2 E1     CLR   $E0.1          ;..
 113C  C3        CLR   C              ;.
L113D: C4        SWAP  A              ;.
 113E  C5 12     XCH   A,D12          ;..
 1140  C6        XCH   A,@R0          ;.
 1141  C7        XCH   A,@R1          ;.
 1142  C8        XCH   A,R0           ;.
 1143  C9        XCH   A,R1           ;.
 1144  CA        XCH   A,R2           ;.
 1145  CB        XCH   A,R3           ;.
 1146  CC        XCH   A,R4           ;.
 1147  CD        XCH   A,R5           ;.
 1148  CE        XCH   A,R6           ;.
 1149  CF        XCH   A,R7           ;.
 114A  D0 12     POP   D12            ;..
 114C  D1 78     ACALL L1678          ;.x
 114E  D2 E1     SETB  $E0.1          ;..
 1150  D3        SETB  C              ;.
 1151  D4        DA    A              ;.
 1152  D5 12 E8  DJNZ  D12,L113D      ;...
 1155  D6        XCHD  A,@R0          ;.
 1156  D7        XCHD  A,@R1          ;.
 1157  D8 E4     DJNZ  R0,L113D       ;..
 1159  D9 E2     DJNZ  R1,L113D       ;..
 115B  DA E0     DJNZ  R2,L113D       ;..
 115D  DB DE     DJNZ  R3,L113D       ;..
 115F  DC DC     DJNZ  R4,L113D       ;..
 1161  DD DA     DJNZ  R5,L113D       ;..
 1163  DE D8     DJNZ  R6,L113D       ;..
 1165  DF D6     DJNZ  R7,L113D       ;..
 1167  E0        MOVX  A,@DPTR        ;.
 1168  E1 89     AJMP  L1789          ;..
 116A  E2        MOVX  A,@R0          ;.
 116B  E3        MOVX  A,@R1          ;.
 116C  E4        CLR   A              ;.
 116D  E5 12     MOV   A,D12          ;..
 116F  E6        MOV   A,@R0          ;.
 1170  E7        MOV   A,@R1          ;.
 1171  E8        MOV   A,R0           ;.
 1172  E9        MOV   A,R1           ;.
 1173  EA        MOV   A,R2           ;.
 1174  EB        MOV   A,R3           ;.
 1175  EC        MOV   A,R4           ;.
 1176  ED        MOV   A,R5           ;.
 1177  EE        MOV   A,R6           ;.
 1178  EF        MOV   A,R7           ;.
 1179  F0        MOVX  @DPTR,A        ;.
 117A  F1 89     ACALL L1789          ;..
 117C  F2        MOVX  @R0,A          ;.
 117D  F3        MOVX  @R1,A          ;.
 117E  F4        CPL   A              ;.
 117F  F5 12     MOV   D12,A          ;..
 1181  F6        MOV   @R0,A          ;.
 1182  F7        MOV   @R1,A          ;.
 1183  F8        MOV   R0,A           ;.
 1184  F9        MOV   R1,A           ;.
 1185  FA        MOV   R2,A           ;.
 1186  FB        MOV   R3,A           ;.
 1187  FC        MOV   R4,A           ;.
 1188  FD        MOV   R5,A           ;.
 1189  FE        MOV   R6,A           ;.
 118A  FF        MOV   R7,A           ;.


leftover symbols

D12     	12
L1123   	1123
L1234   	1234
L1345   	1345
L1456   	1456
L1567   	1567
L1678   	1678
L1789   	1789
L3456   	3456

