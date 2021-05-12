module Lexer where 
import Data.Char

data Token = Open Tag | Close Tag | Br | Hr | Str | Invalid deriving (Show, Eq)

data Tag = Html | Head | Body | Title | H1 | H2 | H3 | P | Ul | Li | A | Div | BadTag deriving (Show, Eq)


isTag :: [Char] -> Bool
isTag xs = if head xs == '<' && last xs == '>' then True else False



-- only call getToken on contents within <>
getToken :: [Char] -> Token
getToken ('/':xs) = Close (getTag xs)
getToken "br" = Br
getToken "hr" = Hr
getToken xs = Open (getTag xs)

getTag :: [Char] -> Tag
getTag "html" =  Html
getTag "head" =  Head
getTag "body" =  Body
getTag "title" =  Title
getTag "h1" = H1
getTag "h2" = H2
getTag "h3" = H3
getTag "p" = P
getTag "ul" = Ul
getTag "li"  = Li
getTag "a" = A
getTag "div" = Div
-- any other tag deemed invalid
getTag s = BadTag

-- takes a (s1 delim s2) string and delimiter, then returns pair of (s1, delim:s2)
-- if delimiter not found
splitLine :: (Eq a) => [a] -> a -> ([a], [a])
splitLine s delim = splitLine' ([], s) delim

splitLine' :: (Eq a) => ([a], [a]) -> a -> ([a], [a])
splitLine' (t, []) _ = (t, [])
-- may want to avoid appending to x here since seems non efficient
splitLine' (t, x:xs) delim = if x == delim then (t, x:xs) else splitLine' (t ++ [x], xs) delim

identifyLine :: [Char] -> [Token]
identifyLine ys
    | ys == []   = []
    | isSpace x  = identifyLine xs
	-- could check attribute here, it is saved as (snd tag) here, if attribute bad switch to Invalid token , yada ydada yada
    | x == '<'   = let pr = (splitLine xs '>'); tag = splitLine (fst pr) ' ' in (getToken (fst tag)) : identifyLine (tail (snd pr))
    | otherwise  = if not(b1 || b2)
					then [Str] 
					else if b1
							then Str : identifyLine(snd pr1)
							else [Invalid]
	-- if empty - its just a string 
	-- if found '<' - str : identifyLine ....
	-- if found '>' - [Invalid]
	where x  = head ys; xs = tail ys; pr1 = splitLine ys '<'; pr2 = splitLine ys '>'; b1 = not ((snd pr1) == ""); b2 = not ((snd pr2) == "")
	





-- have a stack 
-- have a stack 
-- have a stream of input (line by line)
-- for each line, lex

