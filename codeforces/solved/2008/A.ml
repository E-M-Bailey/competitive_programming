let id x = x

let () = 
    let cases = Scanf.scanf "%d\n" id in
    for case = 1 to cases do
        let a = Scanf.scanf "%d " id in
        let b = Scanf.scanf "%d\n" id in

        let good = (if a > 0 then a else b) mod 2 = 0 in
        Printf.printf "%s\n" (if good then "YES" else "NO")
    done

