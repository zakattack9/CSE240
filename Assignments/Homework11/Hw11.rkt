; Q1 (5 points)
; Enter your code here
(- (+ (* 9 2) 5) 3)
(- (* 5 (+ 6 (/ 12 5))) (* 21 4))
(* 21 4 (+ (- 5 (* 7 3)) (/ 9 4)))
(* (+ 2 3) (+ 4 (/ (+ (/ 5 6) (* 7 8)) (- 9 10))))
(+ (/ (- (/ (/ (* (- 4 6) (+ 4 (* 6 5))) 2) 2) 5) 2) (+ (/ (+ (* 4 5) (* 4 (/ 5 2))) 2) (* 4 5)))


; Q2 (5 points)
(define Product
  (lambda (x y)
    (* x y)
  )
)

(Product 10 40)

; Q3 (5 points)
(define Power
  (lambda (x y)
    (if (= y 0)
      1
      (* x (Power x (- y 1)))
    )
  )
)

(Power 2 5)

; Q4: Please enter test values 2 and 5. It should return 32. (5 points)
(display "Enter 2 5 as test case. It returns 32")
(newline)
(define (ReadForPower)
  (Power (read) (read))
)

(ReadForPower)

; Q5 (5 points)
(define ProductPowers
  (lambda (w x y z)
    (* (Power w x) (Power y z))
  )
)

(ProductPowers 2 5 3 4)

;Q6 (5 points)
(define (ProductLet x y)
  (let ((num1 x) (num2 y))
    (* num1 num2)
  )
)

(ProductLet 60 40)

; Q7 (10 points)
(define (Letexpression)
  (let ((two 2) (four 4) (five 5) (six 6))
    (+ (/ (- (/ (/ (* (- four six) (+ four (* six five))) two) two) five) two) (+ (/ (+ (* four five) (* four (/ five two))) two) (* four five)))
  )
)

(Letexpression)

; Q8: Enter values 1 2 3 4 5 6 7 8, and it should return 20. (10 points)
(display "Enter 1 2 3 4 5 6 7 8 and e, and it returns 20.")
(newline)
(define accumulator
  (lambda (evensum next)
    (if (integer? next)
      (if (even? next)
        (accumulator (+ next evensum) (read))
        (accumulator evensum (read))
      )
      evensum
    )
    
  )
)  
  
(accumulator 0 0) 