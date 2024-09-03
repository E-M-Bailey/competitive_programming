let id x = x

let rec cycle p i acc = function
    | j when p.(j) = i -> j :: acc
    | j -> cycle p i (j :: acc) p.(j)

let rec cycles p marked acc = function
    | i when i = Array.length p -> acc
    | i when marked.(i) -> cycles p marked acc (i + 1)
    | i ->
        let cyc = cycle p i [] i in
        List.iter (fun i -> marked.(i) <- true) cyc;
        cycles p marked (cyc :: acc) (i + 1)

let rec count pred acc = function
    | [] -> acc
    | x :: tail -> count pred (acc + (if pred x then 1 else 0)) tail

let () =
    for t = 1 to Scanf.scanf " %d" id do
        let n = Scanf.scanf " %d" id in
        let p = Array.init n (fun _ -> Scanf.scanf " %d" pred) in
        let bl = Array.init n (fun _ -> Scanf.scanf " %c" ((=) '0')) in
        let ans = Array.make n 0 in
        List.iter (fun cyc ->
            let cnt = count (Array.get bl) 0 cyc in
            List.iter (fun x -> ans.(x) <- cnt) cyc)
            (cycles p (Array.make n false) [] 0);
        Array.iter (Printf.printf "%d ") ans;
        Printf.printf "\n"
    done


