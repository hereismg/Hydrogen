```angular2html
statements  : (EL* expr?)* EF|RBRACE

expr        : identifier eq expr
            : comp-expr ("and"|"or" comp-expr)*

comp-expr   : "not" comp-expr
            : arith-expr (ee|gt|lt|gte|lte arith-expr)*

arith-expr  : term (plus|minus term)* 

term        : factor (mul|div|mod factor)*

factor      : (plus|minus) factor
            : power

power       : call (pow factor)*

call        : atom (LPAREN (expr (COMMA expr)*)? RPAREN)?

atom        : identifier|int|float|string
            : lparen expr rparen
            : if-expr
            : for-expr
            : while-expr
            : func-expr

if-expr     : expr "if" expr (else core)?
            : "if" expr core
              ("elif" expr core)*
              ("else" core)?

for-expr    : "for" identifier 
              (from int)? 
              to int 
              (step int)? 
              core

while-expr  : "while" expr core

func-expr   : "function" identifier 
              lparen 
                  (identifier (eq expr)? 
                      (comma identifier (eq expr)?)*
                  )?
              rparen
              core

core       : (colon expr) | (lbrace statements rbrace)
```
