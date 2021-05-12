module Parser where
import Lexer 
import Tree
import Data.List

data Result = MissingHtmlTag | MissingHeadTag | MissingBodyTag | NestedPDivTag | ValidHtml deriving (Show)


isOpen :: Token -> Bool
isOpen (Open t) = True
isOpen _ = False

matchingTags :: Token -> Token -> Bool 
matchingTags (Close t1) (Open t2) = if t1 == t2 then True else False
matchingTags _ _ = False

getAST :: [Token] -> Tree Token
getAST ls = getAST' ls [] EmptyTree

getAST' :: [Token] -> [Token] -> Tree Token -> Tree Token
getAST' [] [] ts = ts
getAST' [] (y:ys) _ = Node Invalid []
getAST' (x:xs) ys ts
	| x == (Open BadTag) = Node Invalid [EmptyTree]
	| isOpen x = let  yys = x:ys in getAST' xs yys (treeInsert x (reverse ys) ts)
	| x == Invalid = Node Invalid [EmptyTree, EmptyTree]
	| x `elem` [Br, Hr, Str] = if ys == [] 
								then Node Invalid [EmptyTree, EmptyTree, EmptyTree, EmptyTree]
								else getAST' xs ys (treeInsert Str (reverse ys) ts)
	| length ys > 0 && matchingTags x y = getAST' xs (tail ys) ts 
	| otherwise = Node Invalid [EmptyTree, EmptyTree, EmptyTree]
	where y = head ys

-- go through the Tree returned by getAST, and ensure that 
verifyHtml :: Tree Token -> Result
verifyHtml (Node a ts)
	|	a == (Open Html) = verifyHeadBody ts
	|	otherwise = MissingHtmlTag

verifyHeadBody :: [Tree Token] -> Result 
verifyHeadBody ts = let headPresent = foldr (||) False (map verifyHead ts); bodyPresent = foldr (||) False (map verifyBody ts) in 
					if headPresent && bodyPresent 
						then verifyPDivTag ts
						else if headPresent 
								then MissingBodyTag
								else MissingHeadTag
	
	
verifyHead :: Tree Token  -> Bool 
verifyHead (Node a _) = if a == (Open Head) then True else False
verifyHead _ = False

verifyBody :: Tree Token  -> Bool 
verifyBody (Node a _) = if a == (Open Body) then True else False
verifyBody _ = False

verifyPDivTag :: [Tree Token] -> Result
verifyPDivTag [] = ValidHtml
verifyPDivTag xs = foldr mergePDivResult ValidHtml (map verifyPDivTag' xs) 

verifyPDivTag' :: Tree Token -> Result
verifyPDivTag' (Node (Open P) xs) = let pDivExists = foldr (||) False (map pDivInTree xs) in if pDivExists then NestedPDivTag else ValidHtml
verifyPDivTag' (Node _ xs) = verifyPDivTag xs
verifyPDivTag' EmptyTree = ValidHtml

pDivInTree :: Tree Token -> Bool
pDivInTree (Node tag _)
	|	tag `elem` [(Open P), (Open Div)] = True
	|	otherwise = False
pDivInTree _ = False


mergePDivResult :: Result -> Result -> Result
mergePDivResult ValidHtml ValidHtml = ValidHtml
mergePDivResult _ _ = NestedPDivTag
