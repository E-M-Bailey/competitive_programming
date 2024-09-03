let id x = x

type bezout = {x : int; y : int; gcd : int}

let rec euclid_rec a b = if b.gcd = 0
    then a
    else
        let q = a.gcd / b.gcd in
        euclid_rec b {x = a.x - b.x * q; y = a.y - b.y * q; gcd = a.gcd - b.gcd * q}
let euclid a b = euclid_rec {x = 1; y = 0; gcd = a} {x = 0; y = 1; gcd = b} 

let madd m x y =
    let sum = x + y in
    if sum >= m || sum < 0 then sum - m else sum
let mmul m x y = Int64.to_int (Int64.rem (Int64.mul (Int64.of_int x) (Int64.of_int y)) (Int64.of_int m))
let minv m x =
    let y = (euclid x m).x in
    if y < 0 then y + m else y

let sum_pairs plus times zero arr = 
    let _, ans = Array.fold_left (fun (s1, s2) x -> (plus s1 x, plus s2 (times s1 x))) (zero, zero) arr in
    ans

let modulus = 1000000007
let add = madd modulus and mul = mmul modulus and inv = minv modulus

let () =
    for t = 1 to Scanf.scanf " %d" id do
        let n = Scanf.scanf " %d" id in
        let num_arr = Array.init n (fun _ -> Scanf.scanf " %d" id) in
        let den_arr = Array.make n 1 in
        let sump = sum_pairs add mul 0 in
        let num = sump num_arr and den = sump den_arr in
        Printf.printf "%d\n" (mul num (inv den))
    done

