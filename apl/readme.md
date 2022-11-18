# APL 


## Getting started

Install [RIDE+DyalogAPL mentioned.](https://mrprajesh.co.in/blog/hello-world-apl.html)

```
use ` to start the command. RIDE will give suggestions.
use `` to start with their name. hit TAB to autocomple complete 
```
`]boxing on`


### IOTA

```
        ⍳10               ⍝ This is iota 1 to n
1 2 3 4 5 6 7 8 9 10
        ⍳ 3 6             ⍝ mat 3x6
┌───┬───┬───┬───┬───┬───┐
│1 1│1 2│1 3│1 4│1 5│1 6│
├───┼───┼───┼───┼───┼───┤
│2 1│2 2│2 3│2 4│2 5│2 6│
├───┼───┼───┼───┼───┼───┤
│3 1│3 2│3 3│3 4│3 5│3 6│
└───┴───┴───┴───┴───┴───┘
```

### Reductions

```
      +/⍳10             ⍝ / is reduction; + is the operation
55

      a ← 1 2 3 4 5    ⍝ reduction using a var and multiply/TIMES  op
      
      ×/a
120

      1 +/a           ⍝ no change
1 2 3 4 5
      2 +/a           ⍝ adds consecutive two elements
3 5 7 9
      3 +/a           ⍝ adds consecutive three elements
6 9 12
      5 +/a           ⍝ adds consecutive five or len(a) elements. i.e. reduction
15
```

### Scan

```
      +\⍳10             ⍝ \ is scan; + is the operation; default is inclusive .
1 3 6 10 15 21 28 36 45 55

```


## zip

```
a,¨b
┌────┬────┬────┬────┬────┬────┬────┬────┐
│1 10│2 20│3 30│4 40│5 50│6 60│7 70│8 80│
└────┴────┴────┴────┴────┴────┴────┴────┘
```
```

⍝ This is a modulo (a % b) is written as b | a 
      3 | 15
0  
      3 | 17
2      

```

## MATRIX
```
      1 2 3 ∘.× 1 2 3
1 2 3
2 4 6
3 6 9

```

```

a← 1 2 3 4
      a
1 2 3 4
        ≢ a           ⍝ tally or len(a)
4
      ⌽ a          ⍝ reverse
4 3 2 1

```


 ⍳9
1 2 3 4 5 6 7 8 9
      3 | ⍳9
1 2 0 1 2 0 1 2 0
      0 = 3 | ⍳9
0 0 1 0 0 1 0 0 1
