module Tree where

data Tree a = EmptyTree | Node a [Tree a] deriving (Show)

{-instance Show (Tree a) where 
	show EmptyTree = "-"
	show (Node a ys) = show a + "[" ++ show ys ++ "]"-}

-- path should start from root node
treeInsert :: (Eq a) => a -> [a] -> Tree a -> Tree a 
treeInsert toInsert [] EmptyTree = Node toInsert []
treeInsert toInsert [] (Node a ys) = Node a (treeInsert' toInsert [] ys)
treeInsert toInsert (x:xs) EmptyTree = EmptyTree
treeInsert toInsert (x:xs) (Node a ys) = if x == a 
											then Node a (treeInsert' toInsert xs ys)
											else Node a [EmptyTree] --invalid path 

treeInsert' :: (Eq a) => a -> [a] -> [Tree a] -> [Tree a]
treeInsert' toInsert [] ys = (Node toInsert []) : ys
treeInsert' toInsert (x:xs) [] = (Node toInsert []):[]
treeInsert' toInsert (x:xs) ((Node a ts):ys) = let y = Node a ts in if x == a
									then (treeInsert toInsert (x:xs) y): ys 
									else y: (treeInsert' toInsert (x:xs) ys)
									