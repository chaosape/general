#use "lca.ml";;
let t = Node (1,[Leaf 2; Leaf 3]);;
Some 1 = lca t 2 3 ;;
let t = Node (1,[Leaf 2; Leaf 3]);;
Some 1 = lca t 1 3 ;;
let t = Node (4,[Node (1,[Leaf 2; Leaf 3])]);;
Some 1 = lca t 2 3 ;;
let t = Node (4,[Node (1,[Leaf 2; Leaf 3])]);;
Some 4 = lca t 4 3 ;;
let t = Node (4,[Node (1,[Leaf 2; Leaf 3])]);;
Some 4 = lca t 4 2 ;;

