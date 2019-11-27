; define map function to apply encrypt/decrypt on list
(define map-str (lambda (proc proc2 lst key) ; proc2 determines whether to encrypt or decrypt character
  (if (null? lst)
    '()
    (cons (proc proc2 (car lst) key) (map-str proc proc2 (cdr lst) key))
  )
))

; define function to determine if character should be encrypted/decrypted
(define select-char (lambda (proc ch key)
  (if (or (char-alphabetic? ch) (char-numeric? ch))
    (proc ch key)
    ch ; don't encrypt non-alphanumeric characters 
  )
))

; define function to read in valid key
(define (get-key)
  (let ((key (read)))
    (if (<= key 4)
      key
      (begin
        (display "Enter a number between 1 & 4")
        (newline)
        (get-key)
      )
    )
  )
)

; define a main encryption function to encrypt each character in string
(define encrypt (lambda (str)
  (list->string (map-str select-char encrypt-char (string->list str) (get-key)))
))

; define helper function to encrypt string character with key
(define encrypt-char (lambda (ch key)
  (integer->char (+ (char->integer ch) key))
))

; define a main decrypt function to decrypt each character in a string
(define decrypt (lambda (str)
  (list->string (map-str select-char decrypt-char (string->list str) (get-key)))
))

; define helper function to decrypt string character with key
(define decrypt-char (lambda (ch key)
  (integer->char (- (char->integer ch) key))
))

(encrypt "Hello CSE240!")
(decrypt "Khoor FVH573!")