import System.IO
import Lexer
import Parser

main = do
	handle <- openFile "file.html" ReadMode
	contents <- hGetContents handle
	let toks = identifyLine contents; ast = getAST toks in print(verifyHtml ast)
	hClose handle