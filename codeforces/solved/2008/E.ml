let id x = x
let id2 x y = (x, y)

let upd_freq ch =
    let code = Char.code ch - Char.code 'a' in
    (fun i -> (+) (if i = code then 1 else 0))

let upd_freq_list acc ch = match acc with
    | [] -> assert false
    | (even, odd) :: tail -> (Array.mapi (upd_freq ch) odd, even) :: (even, odd) :: tail

let zeros = Array.make 26 0

let rec string_fold_left_rec op acc s = function
    | i when i = String.length s -> acc
    | i -> string_fold_left_rec op (op acc s.[i]) s (i + 1)
let string_fold_left op acc s = string_fold_left_rec op acc s 0

let pref_freq_list = string_fold_left upd_freq_list [(zeros, zeros)]

let rev_string s =
    let n = String.length s in
    String.init n (fun i -> s.[n - 1 - i])

let array_map2 op arr1 arr2 = Array.init (Array.length arr1) (fun i -> op arr1.(i) arr2.(i))

let rec eval_one left right =
    let sum = array_map2 (+) left right in
    Array.fold_left max 0 sum

let rec eval pref suff acc = match pref, suff with
    | [], _ -> acc
    | _, [] -> acc
    | (peven, podd) :: ptail, (seven, sodd) :: stail ->
        let cur = (eval_one peven sodd) + (eval_one podd seven) in
        eval ptail stail (max acc cur)

let () =
    for t = 1 to Scanf.scanf " %d" id do
        let n, s = Scanf.scanf " %d %s" id2 in
        let pref = pref_freq_list s in
        let suff = List.rev (pref_freq_list (rev_string s)) in
        let ans = n - eval (if n mod 2 = 0 then pref else List.tl pref) suff 0 in
        Printf.printf "%d\n" ans
    done

