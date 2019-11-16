;Your Name: Zak Sakata
;hw12
;Course: CSE 240


;Q1
(define OR-GATE (lambda (a b)
  (if (or (equal? a 1) (equal? b 1))
    1
    0
  )
))
                  
(define AND-GATE (lambda (a b)
  (if (and (equal? a 1) (equal? b 1))
    1
    0
  )
))

(define XOR-GATE (lambda (a b)
  (if (equal? (OR-GATE a b) 1)
    (if (equal? (AND-GATE a b) 1)
      0
      1
    )
    0
  )
))

; Test cases
(AND-GATE 0 0)
(AND-GATE 0 1)
(AND-GATE 1 0)
(AND-GATE 1 1)
;0
;0
;0
;1
(newline)
(OR-GATE 0 0)
(OR-GATE 0 1)
(OR-GATE 1 0)
(OR-GATE 1 1)
;0
;1
;1
;1
(newline)
(XOR-GATE 0 0)
(XOR-GATE 0 1)
(XOR-GATE 1 0)
(XOR-GATE 1 1)
;0
;1
;1
;0

;Q2
(define bitAdder (lambda (x a b)
  (cons (sum-bits x a b) (carry-out x a b))
))

(define sum-bits (lambda (x a b)
  (XOR-GATE (XOR-GATE a b) x)
))

(define carry-out (lambda (x a b)
  (OR-GATE (AND-GATE a b) (AND-GATE (XOR-GATE a b) x))
))

; Test cases
(newline)
(bitAdder 0 0 0) 	
(bitAdder 0 0 1) 	
(bitAdder 0 1 0) 	
(bitAdder 0 1 1)	
(bitAdder 1 0 0) 	
(bitAdder 1 0 1)	
(bitAdder 1 1 0) 	
(bitAdder 1 1 1) 
;(0 . 0)
;(1 . 0)
;(1 . 0)
;(0 . 1)
;(1 . 0)
;(0 . 1)
;(0 . 1)
;(1 . 1)


;Q3.1
(define tail (lambda (lst)
  (list-ref lst (- (length lst) 1))
))
               
;Q3.2
(define rmtail (lambda (lst)
  (reverse (cdr (reverse lst)))
))
                 
;Q3.3
; Size-n Problem: size-n is the total number of bits to be added

; Stopping Condition: stopping condition is when the most significant bit (MSB) has been added

; Size-m Problem: assume all bits before the MSB (n-1) have been added with the carry-in to the MSB being 1 or 0 

; Solution of Size-n from Size-m: add the MSB from the two lists plus the carry-in, append to size n-1 list, detect if there is an overflow and return result

;Q3.4
                 
(define X1 '(0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0) )	
(define X2 '(1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1) )	
(define X3 '(0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1) )	
(define X4 '(1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0) )
(define X5 '(0 1 0 1 0 1 0 1 0 1 0 1 0 1 1 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 1 1) )	
(define X6 '(1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 1 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 1) )

(define n-bit-adder (lambda (L1 L2 n)
  (n-bit-adderh L1 L2 n (cons '() 0))
))
                      
(define n-bit-adderh (lambda (L1 L2 n resulti)
  (if (equal? n 0)
    (n-bit-adder-format resulti)
    (let ((sum-carry (bitAdder (cdr resulti) (tail L1) (tail L2))))
      (let ((sum (car sum-carry)) (carry (cdr sum-carry)))
        (n-bit-adderh (rmtail L1) (rmtail L2) (- n 1) (cons (append (list sum) (car resulti)) carry))
      )
    )
  )
))
                       
(define n-bit-adder-format (lambda (resulti)
  (append (list (list (cdr resulti))) (car resulti))
))

; Test cases
(newline)
(n-bit-adder  X1 X2 32)
;((1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1) . 0)
(n-bit-adder  X3 X4 32)
;((1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1) . 0)
(n-bit-adder  X5 X6 32)
;((0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0) . 1)
(n-bit-adder  X2 X3 32)
;((0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 0) . 1)
(n-bit-adder  X4 X5 32)
;((0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1) . 1)
(n-bit-adder  X1 X6 32)
;((1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 1 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 1) . 0)

; Q3.5 Sample solution:
;(define n-bit-adder1 (lambda (L1 L2 n)
;))
                       
;(define n-bit-adderhelper1 (lambda (L1 L2 n resulti)
;))
                             
;(define n-bit-adder-carry-out (lambda (L1 L2 n resulti)
;))

; Test cases
;(newline)
;(n-bit-adder1  X1 X2 32)
;(n-bit-adder1  X3 X4 32)
;(n-bit-adder1  X5 X6 32)
;(n-bit-adder1  X2 X3 32)
;(n-bit-adder1  X4 X5 32)
;(n-bit-adder1  X1 X6 32)
; Expected output
;((0) 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1)
;((0) 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1)
;((1) 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0)
;((1) 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 0)
;((1) 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1)
;((0) 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 1 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 1)




