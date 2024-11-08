.model small
.stack 100h
.data
    infix db '3+5*2-9', '$'  ; Chuỗi biểu thức trung tố, ký tự '$' là ký tự kết thúc
    postfix db 20 dup('$')    ; Chuỗi hậu tố sau khi chuyển đổi
    result dw ?               ; Lưu kết quả cuối cùng

.code
main proc
    ; Thiết lập đoạn mã
    mov ax, @data
    mov ds, ax

    ; Chuyển đổi trung tố sang hậu tố
    call infix_to_postfix

    ; Tính giá trị biểu thức hậu tố
    call evaluate_postfix

    ; Thoát chương trình
    mov ax, 4C00h
    int 21h
main endp

;----------------------------------------------------------------------
; infix_to_postfix: Chuyển đổi từ trung tố sang hậu tố
;----------------------------------------------------------------------
infix_to_postfix proc
    ; Đặt con trỏ tới chuỗi infix và postfix
    mov si, offset infix
    mov di, offset postfix

    ; Khởi tạo ngăn xếp toán tử
    mov bx, 0          ; Con trỏ ngăn xếp tạm thời cho toán tử

next_char:
    ; Đọc từng ký tự trong biểu thức
    mov al, [si]
    inc si
    cmp al, '$'
    je end_conversion   ; Kết thúc nếu gặp ký tự '$'

    ; Xử lý nếu là số (toán hạng)
    cmp al, '0'
    jl check_operator
    cmp al, '9'
    jg check_operator
    ; Nếu là số, thêm vào chuỗi hậu tố
    mov [di], al
    inc di
    jmp next_char

check_operator:
    ; Xử lý nếu là toán tử (+, -, *, /)
    cmp al, '+'
    je handle_plus
    cmp al, '-'
    je handle_minus
    cmp al, '*'
    je handle_multiply
    cmp al, '/'
    je handle_divide
    jmp next_char

handle_plus:
    ; Xử lý toán tử '+'
    ; (chèn mã xử lý toán tử tại đây, push vào stack nếu cần)
    jmp next_char

handle_minus:
    ; Xử lý toán tử '-'
    ; (chèn mã xử lý toán tử tại đây, push vào stack nếu cần)
    jmp next_char

handle_multiply:
    ; Xử lý toán tử '*'
    ; (chèn mã xử lý toán tử tại đây, push vào stack nếu cần)
    jmp next_char

handle_divide:
    ; Xử lý toán tử '/'
    ; (chèn mã xử lý toán tử tại đây, push vào stack nếu cần)
    jmp next_char

end_conversion:
    ; Thêm ký tự kết thúc vào chuỗi hậu tố
    mov [di], '$'
    ret
infix_to_postfix endp

;----------------------------------------------------------------------
; evaluate_postfix: Tính giá trị của biểu thức hậu tố
;----------------------------------------------------------------------
evaluate_postfix proc
    ; Thiết lập con trỏ tới chuỗi hậu tố
    mov si, offset postfix

    ; Khởi tạo ngăn xếp để lưu toán hạng
    mov cx, 0          ; Sử dụng cx làm con trỏ ngăn xếp tạm thời cho toán hạng

evaluate_next:
    ; Đọc từng ký tự trong chuỗi hậu tố
    mov al, [si]
    inc si
    cmp al, '$'
    je end_evaluation   ; Kết thúc nếu gặp ký tự '$'

    ; Xử lý nếu là số
    cmp al, '0'
    jl evaluate_operator
    cmp al, '9'
    jg evaluate_operator
    ; Nếu là số, chuyển sang giá trị số và push vào ngăn xếp
    sub al, '0'
    push ax
    jmp evaluate_next

evaluate_operator:
    ; Xử lý các toán tử (+, -, *, /)
    cmp al, '+'
    je eval_plus
    cmp al, '-'
    je eval_minus
    cmp al, '*'
    je eval_multiply
    cmp al, '/'
    je eval_divide
    jmp evaluate_next

eval_plus:
    ; Lấy hai số từ ngăn xếp, tính tổng và push kết quả lại vào ngăn xếp
    pop bx
    pop ax
    add ax, bx
    push ax
    jmp evaluate_next

eval_minus:
    ; Tương tự, thực hiện phép trừ
    pop bx
    pop ax
    sub ax, bx
    push ax
    jmp evaluate_next

eval_multiply:
    ; Thực hiện phép nhân
    pop bx
    pop ax
    imul bx
    push ax
    jmp evaluate_next

eval_divide:
    ; Thực hiện phép chia
    pop bx
    pop ax
    cwd         ; mở rộng dấu cho ax thành dx:ax để chia
    idiv bx
    push ax
    jmp evaluate_next

end_evaluation:
    ; Kết quả cuối cùng
    pop ax
    mov result, ax
    ret
evaluate_postfix endp

end main
