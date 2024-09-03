let id x = x
let const x y = x

let scan f = Scanf.scanf f id
let print = Printf.printf

let () =
    for tc = 1 to scan " %d" do
        let l = scan " %d" in
        let r = scan " %d" in
        let d = float_of_int (r - l) in
        let n = int_of_float (sqrt (2. *. d +. 0.25) +. 0.5) in
        print "%d\n" n
    done
    
