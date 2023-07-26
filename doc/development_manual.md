# 海琛开发者手册

---

## 基础数据类型

- int
- float

- String
  - 不区分字符串类型和字符类型，统一是字符串类型

## 上下文无关文法

```CFG
expr        : term (plus|minus term)*

term        : factor (mul|div factor)*

factor      : power (pow factor)*

power       : int|float
            : (plus|minus) power
            : lparen expr rparen
```
