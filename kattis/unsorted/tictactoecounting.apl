⎕IO←0
t←⍳3
T←3×t
D←(9⍴3)⍴⊃0 0
W←((t∘.+T)⍪(T∘.+t)⍪2 3⍴0 4 8 2 4 6)
g←{s←2|+/0≠⍵⋄}
{D[⊂⍵]←g⍵}¨⌽,⍳⍴D
g←{s←2|≢⍺,⍵⋄I←((⍳9)∊⍵,⍺)+(⍳9)∊⍺{s:⍺⋄⍵}⍵⋄⊃D[⊂I]←⊂⍵{0<≡D[⊂I]:⊃D[⊂I]⋄∨/∧/W∊⍺:s(~s)⋄5=≢⍺:0 0⋄⊃+⌿⌽(⍺g⍵∘,)¨(⍳9)~(⍺,⍵)}⍺}
⍬g⍬
⎕←¨{{0<≡⍵:⍕⍵⋄'-1 -1'}⊃D[⊂(1 2)+.×⍵∘=¨'XO']}¨⊢/⊃⎕CSV'/dev/fd/0'⍬⍬1