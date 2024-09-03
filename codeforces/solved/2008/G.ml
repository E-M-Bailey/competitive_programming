let id x = x

let rec list_init_rec n f = function
    | i when i = n -> []
    | i -> (f i) :: list_init_rec n f (i + 1)
module List = struct
    include List
    
    let init n f = list_init_rec n f 0
end

type bezout = {x : int; y : int; gcd : int}

let rec euclid_rec a b = if b.gcd = 0
    then a
    else
        let q = a.gcd / b.gcd in
        euclid_rec b {x = a.x - b.x * q; y = a.y - b.y * q; gcd = a.gcd - b.gcd * q}
let euclid a b = euclid_rec {x = 1; y = 0; gcd = a} {x = 0; y = 1; gcd = b}
let gcd a b = (euclid a b).gcd

let rec mex_rec k a = match k, a with
    | _, [] -> assert false
    | k, x :: [] -> x + k
    | k, x :: y :: tail when y > x + k || y < 0 -> x + k
    | k, x :: y :: tail when x = y -> mex_rec k (y :: tail)
    | k, x :: y :: tail -> mex_rec (k + 1 + x - y) (y :: tail)
let mex k a = mex_rec k (-1 :: a)

let () =
    for t = 1 to Scanf.scanf " %d" id do
        let n, k = Scanf.scanf " %d %d" (fun n k -> n, k) in
        let a = List.init n (fun _ -> Scanf.scanf " %d" id) in
        let g = List.fold_left gcd 0 a in
        Printf.printf "%d\n" (mex k (if n = 1 then a else List.init n (( * ) g)))
    done
    

