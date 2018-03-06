.model small
.386
.stack
.data
    time_info_buffer byte '00-00-00 00:00:00 00', 13, 10, '$'; 3 * 6 + 2 + 3; 19为星期
    WEEK = 19
    cell byte 9, 8, 7, 4, 2, 0, 6
.code
start:
    mov ax, @data
    mov ds, ax
    xor si, si
    xor di, di
    execute:
        mov al, cell[si];AL＝9（准备从9号单元获取年代数据）
        out 70h, al;将数字9送给70h端口
        in al,71h;从71H端口读入数据到al，（获取9号单元的内容）;未知寄存器??
        xor ah, ah
        shl ax, 4
        add time_info_buffer[di], ah
        shr al, 4
        inc di
        add time_info_buffer[di], al;搞定一个字节
        add di, 2
        inc si;更新迭代器
        cmp si, lengthof cell
        jl execute
    sub time_info_buffer[WEEK], 1; 美式星期表示法转中式
    cmp time_info_buffer[WEEK], '0'
    jg not_sunday
        add time_info_buffer[WEEK], 7
    not_sunday:
    mov ah, 09h
    mov dx, offset time_info_buffer; dx是输出字符串的地址
	int 21h
	mov ax, 4c00h; exit 0
	int 21h
end start