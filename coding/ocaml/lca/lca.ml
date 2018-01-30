(* TODO: I think there should be an alternate way to solve this
   problem that only requires one traversal of the tree. *)
(* TODO: I think there is another way to solve this problem using dynamic programming. *)

type 'a option = None | Some of 'a
type 'a tree = Leaf of 'a | Node of 'a * ('a tree) list

(* Find a path from the root of a tree to a node if it exists, *)
let rec somePath t v =
  match t with
  | Leaf w when v = w -> Some [v]
  | Leaf w -> None
  | Node (w,ts) when w = v -> Some [v]
  | Node (w,[]) -> None
  | Node (w,t::ts) ->
     match somePath t v with
     | Some ws -> Some (w::ws)
     | None -> somePath (Node (w,ts)) v

(* Calculate the least common ancestor of two nodes in an n-ary tree
   by finding a path * to both both nodes then selecting the last one
   node on those paths they share in common. *) 
let lca t v w =
  let rec pop vs ws =
    match (vs, ws) with
    | (v1::v2::vs,w1::w2::ws) when v1 = w1 && v2 = w2 -> pop (v2::vs) (w2::ws)
    | (v1::vs,w1::ws2) when v1 = w1 ->  Some w1
    | _ -> None
  in                                                       
  match (somePath t v, somePath t w) with
  | (Some vs, Some ws) -> pop vs ws
  | _ -> None


