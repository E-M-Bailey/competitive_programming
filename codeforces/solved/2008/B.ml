let ident x = x
let const x y = x
let subst x y z = x z (y z)

let scan_int () = Scanf.scanf " %d" ident
let scan_string () = Scanf.scanf " %s" ident
let panic s = raise ( Failure s )

let refine pred (lo, hi) =
    let mid = lo + (hi - lo) / 2 in
    if pred mid then (mid + 1, hi) else (lo, mid)

(* First value in [lo, hi) where pred is false, or hi if none are, assuming true -> false monotonicity *)
let rec binsearch pred = function
    | lo, hi when lo = hi -> lo
    | rng -> binsearch pred (refine pred rng)

let sqrt_lim = 32768

let ifsqrt n = binsearch (fun x -> x * x <= n) (0, min (n + 1) sqrt_lim) - 1
let icsqrt n = binsearch (fun x -> x * x < n) (0, min (n + 1) sqrt_lim)

let square op x = op x x
let odd x = x mod 2 != 0

let rec binary_pow op id x = function
    | 0 -> id
    | n when odd n -> op (binary_pow op id x (n - 1)) x
    | n -> square op (binary_pow op id x (n / 2))

let string_rep = binary_pow (^) ""

let beautiful_square m =
    let outer = string_rep "1" m in
    let inner = "1" ^ (string_rep "0" (m - 2)) ^ "1" in
    outer ^ (string_rep inner (m - 2)) ^ outer

let () =
    for case = 1 to scan_int () do
        let n = scan_int () in
        let s = scan_string () in
        let m = icsqrt n in
        let good = m * m = n && s = beautiful_square m in
        Printf.printf "%s\n" (if good then "YES" else "NO")
    done

