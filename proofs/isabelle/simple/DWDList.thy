theory DWDList imports Main
begin

datatype 'a list = 
  Nil
  | Cons 'a "'a list"

(* Isabelle generate the following induction theorem for this datatype:
   ?P DWDList.list.Nil \<Longrightarrow> (\<And>x1 x2. ?P x2 \<Longrightarrow> ?P (DWDList.list.Cons x1 x2)) \<Longrightarrow> ?P ?list
*)

fun concat where
"concat Nil Xs = Xs"
|"concat (Cons X Xs) Ys = Cons X (concat Xs Ys)"

fun length :: "'a list \<Rightarrow> nat" where
"length Nil = 0"
|"length (Cons X Xs) = 1 + length Xs"

lemma concat_length: "length (concat Xs Ys) = length Xs + length Ys"
proof(induct Xs)
  case Nil
  then show ?case by simp
next
  case (Cons X Xs)
  then show ?case by simp
qed

end