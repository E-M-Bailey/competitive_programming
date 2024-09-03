let id x = x
let id2 x y = (x, y)
let id3 x y z = (x, y, z)
let id4 x y z w = (x, y, z, w)

type range = {lo : int; hi : int}
let (@=>) lo hi = {lo; hi}

module Range = struct

    let make n start = start @=> start + n
    let empty = make 0
    let singleton = make 1

    let length {lo; hi} = max 0 (hi - lo)
    let mem a {lo; hi} = lo <= a && a < hi
    let is_empty {lo; hi} = lo >= hi
    let equal ra rb = ra = rb || (is_empty ra && is_empty rb)

    let midpoint = function
        | rng when is_empty rng -> assert false
        | {lo; hi} when mem 0 {lo; hi} ->
            let sum = lo + hi in
            (if sum >= 0 then sum else sum - 1) / 2
        | {lo; hi} -> lo - (lo - hi) / 2

    let split mid {lo; hi} = lo @=> mid, mid @=> hi
    let split2 gap {lo; hi} = lo @=> gap.lo, gap.hi @=> hi

    let left {lo; hi} = lo
    let right {lo; hi} = hi - 1
    let pop_left {lo; hi} = lo + 1 @=> hi
    let pop_right {lo; hi} = lo @=> hi - 1

    let refine pred rng =
        let mid = midpoint rng in
        let left, right = split2 (singleton mid) rng in
        if pred mid then right else left
    let rec first_false pred rng = if is_empty rng
        then rng.lo
        else first_false pred (refine pred rng)

    let rec fold_left op acc rng = if is_empty rng
        then acc
        else fold_left op (op acc (left rng)) (pop_left rng)
    let rec fold_right op acc rng = if is_empty rng
        then acc
        else fold_right op (op (right rng) acc) (pop_right rng)

    let rec iter f rng = if not (is_empty rng)
        then f (left rng); iter f (pop_left rng)
    let rec iteri_rec f rng i = if not (is_empty rng)
        then f i (left rng); iteri_rec f (pop_left rng) (i + 1)
    let iteri f rng = iteri_rec f rng 0
end

let freq_array op zero arr bound =
    let freq = Array.make bound zero in
    Array.iteri (fun i x -> freq.(x) <- op i freq.(x) x) arr;
    freq

let pref_sum_shift_inplace arr = Array.iteri (fun i x -> if i > 0 then arr.(i) <- arr.(i - 1) + x) arr

let count_below_mod pref n m guess =
    let k = (n + 1) / m in
    Range.fold_left (fun acc i ->
        let l = i * m and r = min (n + 1) ((i + 1) * m) in
        let x = min r (guess + l) in
        acc + pref.(x) - pref.(l)) 0 (0 @=> k + 1)

let () =
    for t = 1 to Scanf.scanf " %d" id do
        let n, q = Scanf.scanf " %d %d" id2 in
        let a = Array.init n (fun _ -> Scanf.scanf " %d" succ) in
        let x = Array.init q (fun _ -> Scanf.scanf " %d" id) in

        let pref = freq_array (fun _ acc _ -> acc + 1) 0 a (n + 2) in
        pref_sum_shift_inplace pref;

        let xi = freq_array (fun i acc _ -> i :: acc) [] x (n + 2) in
        let ans = Array.make q 0 in
        
        Array.iteri (fun m qi -> if m <> 0 then
            let median = Range.first_false (fun guess -> count_below_mod pref n m guess <= n / 2) (0 @=> m) - 1 in
            List.iter (fun i -> ans.(i) <- median) qi) xi;

        Array.iter (fun a -> Printf.printf "%d " a) ans;
        Printf.printf "\n"
    done

